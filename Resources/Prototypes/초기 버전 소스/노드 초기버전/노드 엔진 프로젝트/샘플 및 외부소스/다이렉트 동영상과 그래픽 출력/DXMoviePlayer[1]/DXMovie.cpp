#include "CometInclude.h"
#include	<windows.h>
#include	<ddraw.h>
#include	<mmstream.h>
#include	<amstream.h>
#include	<ddstream.h>


#include	"DXMovie.h"

#pragma comment(lib,"amstrmid.lib")

LPDIRECTDRAW  ddraw = NULL;
LPDIRECTDRAWSURFACE primary = NULL;
LPDIRECTDRAWSURFACE renderBuffer = NULL;
DDSURFACEDESC ddsd;

bool Init_Movie(void)
{
    HRESULT hr;

    if (DirectDrawCreate( NULL  , &ddraw, NULL ) != DD_OK)
		return	false;

	if (hr = ddraw->SetCooperativeLevel(g_hWnd, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN) != DD_OK) 
	//if (hr = ddraw->SetCooperativeLevel(g_hWnd, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT) != DD_OK) 
	{
		ddraw->Release();
		return	false;
	}

    // 우선순위 16 bit -> 24 Bit -> 32 Bit
	if (hr = ddraw->SetDisplayMode(640, 480, 24) != DD_OK) 
    {
	    if (hr = ddraw->SetDisplayMode(640, 480, 16) != DD_OK) 
        {
	        if (hr = ddraw->SetDisplayMode(640, 480, 32) != DD_OK) 
            {
               ddraw->Release();
               return false;
            }
        }
	}

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	if (ddraw->CreateSurface(&ddsd, &primary, NULL ) != DD_OK) 
	{
		ddraw->Release();
		return	false;
	}

    return true;
}


bool UnInit_Movie(void)
{
    renderBuffer->Release();
    primary->Release();
	ddraw->SetCooperativeLevel(g_hWnd, DDSCL_NORMAL);
	ddraw->RestoreDisplayMode();
	ddraw->Release();
    ddraw = NULL;
	CoUninitialize();

    //Sleep(500);
    return true;
}

bool ShowMovie(char *filename)
{
    if(Init_Movie() == false) return false;
    
    IMediaStream			*vstream;
    IDirectDrawMediaStream	*ddstream;
    IDirectDrawStreamSample *ddsample;
    IAMMultiMediaStream		*mmstream;

    WCHAR	wFileName[128];
	RECT	rect;

	//OpenMMStream
	CoInitialize(NULL);

    CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER, IID_IAMMultiMediaStream, (void **)&mmstream);

    mmstream->Initialize(STREAMTYPE_READ, 0, NULL);

    mmstream->AddMediaStream(ddraw, &MSPID_PrimaryVideo, 0, NULL);
    mmstream->AddMediaStream(NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL );

    MultiByteToWideChar(CP_ACP, 0, filename, -1, wFileName, sizeof(wFileName)/sizeof(*wFileName) );
    mmstream->OpenFile(wFileName, 0);

    //mmstream->AddRef();
	//mmstream->Release();

	//RenderStreamToSurface

    mmstream->GetMediaStream(MSPID_PrimaryVideo, &vstream);
    vstream->QueryInterface(IID_IDirectDrawMediaStream, (void**)&ddstream);

    HRESULT hr = ddstream->CreateSample(NULL, NULL, 0, &ddsample);
    ddsample->GetSurface(&renderBuffer, NULL);
    mmstream->SetState(STREAMSTATE_RUN);
	GetWindowRect(g_hWnd, &rect);
	char* pKeyboard;

	while(ddsample->Update( 0, NULL, NULL, 0) == S_OK)
	{
		if (renderBuffer->IsLost() != DD_OK)
			renderBuffer->Restore();

		if (primary->IsLost() != DD_OK)
		
		primary->Restore();
		primary->Blt(&rect, renderBuffer, NULL, DDBLT_WAIT, NULL);


		pKeyboard = g_DInput.GetKeyState();
		if( pKeyboard[DIK_ESCAPE]  & 0X80 )
			break;
	}


	mmstream->SetState(STREAMSTATE_STOP);
	mmstream->Release();
    vstream->Release();
    ddstream->Release();
    ddsample->Release();

    UnInit_Movie();
	return	true;
}
