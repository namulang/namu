// main.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include <d3dx9.h>
#include "resource.h"

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND						g_hWnd					= NULL;
LPDIRECT3D9					g_pD3D					= NULL;
LPDIRECT3DDEVICE9			g_pD3DDevice			= NULL;
ID3DXSprite *				g_pD3DXSprite			= NULL;
LPDIRECT3DTEXTURE9			g_pTexture				= NULL;
const int					SCREEN_WIDTH			= 800;
const int					SCREEN_HEIGHT			= 600;

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT	InitializeD3D		( );
void RenderFrame			( );

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpCmdLine,
                    int       nCmdShow )
{
	WNDCLASSEX	winClass;
	MSG			uMsg;
	HRESULT		hr;

    memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hIcon	       = LoadIcon(hInstance, (LPCTSTR)IDC_DXSPRITE);
    winClass.hIconSm	   = LoadIcon(hInstance, (LPCTSTR)IDC_DXSPRITE);
	winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if( !RegisterClassEx(&winClass) )
		return E_FAIL;

	g_hWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", 
                             "Direct3D 9 - ID3DXSprite Example",
						     WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					         0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL );

	if( g_hWnd == NULL )
		return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );
    UpdateWindow( g_hWnd );

	//----------------------------------------------------------------
	// Create the DirectX device
	//----------------------------------------------------------------
	if (FAILED( InitializeD3D()))
		return 0;


	//----------------------------------------------------------------
	// CREATE THE ID3DXSprite
	//----------------------------------------------------------------

	// Create the ID3DXSprite interface object
	hr = D3DXCreateSprite(g_pD3DDevice, &g_pD3DXSprite );
	if( FAILED(hr) )
		return hr;


	//----------------------------------------------------------------
	// LOAD THE TEXTURE FOR THE SPRITE
	//----------------------------------------------------------------
	hr = D3DXCreateTextureFromFile( 
								 g_pD3DDevice,
								 "my_mug.dds",
                                 &g_pTexture );
	if ( FAILED(hr) )
		return hr;





	// ---------
	// Main Loop
	// ---------
	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{ 
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
        else
		{
			// Render the current frame
		    RenderFrame();
		}
	}

	// -------------------------
	// Release directx resources
	// -------------------------
	if (g_pD3DXSprite)
	{
		g_pD3DXSprite->Release();
		g_pD3DXSprite = NULL;
	}
	
	if (g_pTexture)
	{
		g_pTexture->Release();
		g_pTexture = NULL;
	}

	if (g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}




    UnregisterClass( "MY_WINDOWS_CLASS", winClass.hInstance );

	return (int)uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
							 UINT   msg, 
							 WPARAM wParam, 
							 LPARAM lParam )
{

	switch( msg )
	{
        case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;

			}
		}
        break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
		
        case WM_DESTROY:
		{
            PostQuitMessage(0);
		}
        break;

		default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Name: InitializeD3D()
// Desc: Create DirectX interface objects
//		 Initialize the view matrix.
//		 Setup render states that will not need changing throughout
//		 the life of the application.
//-----------------------------------------------------------------------------
HRESULT InitializeD3D( )
{
	HRESULT hr;

	// Create a direct 3D interface object
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( g_pD3D == NULL )
	{
		// TO DO: Respond to failure of Direct3DCreate9
		return E_FAIL;
	}

    D3DDISPLAYMODE d3ddm;

    if( FAILED( hr = g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		// TO DO: Respond to failure of GetAdapterDisplayMode
		return hr;
	}
	

	// 
	if( FAILED( hr = g_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
												d3ddm.Format, D3DUSAGE_DEPTHSTENCIL,
												D3DRTYPE_SURFACE, D3DFMT_D16 ) ) )
	{
		if( hr == D3DERR_NOTAVAILABLE )
			// POTENTIAL PROBLEM: We need at least a 16-bit z-buffer!
			return hr;
	}

	//
	// Do we support hardware vertex processing? If so, use it. 
	// If not, downgrade to software.
	//

	D3DCAPS9 d3dCaps;

	if( FAILED( hr = g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, 
		                               D3DDEVTYPE_HAL, &d3dCaps ) ) )
	{
		// TO DO: Respond to failure of GetDeviceCaps
		return hr;
	}

	DWORD dwBehaviorFlags = 0;

	if( d3dCaps.VertexProcessingCaps != 0 )
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//
	// Everything checks out - create a simple, windowed device.
	//

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

    d3dpp.BackBufferFormat       = d3ddm.Format;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed               = TRUE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Attempt to create a HAL device, end app on failure just to keep things
	// simple.  In other words we are not trying to create a REF device if the
	// HAL fails.
    if( FAILED( hr = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
                                      dwBehaviorFlags, &d3dpp, &g_pD3DDevice ) ) )
	{
		// Should respond to failure of creating the hardware device.
		return hr;
	}

	
	// If we get here everything worked!
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: RenderFrame()
// Desc: Draw the image to the framebuffer.
//-----------------------------------------------------------------------------
void RenderFrame( )
{
	if (!g_pD3DDevice && !g_pD3DXSprite && !g_pTexture)
		return;


    // Clear the frame & depth buffer ready for drawing (Black color)
    g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,  0x00000000, 1.0f, 0 );

	g_pD3DDevice->BeginScene();
	{
		//-------------------------
		// Render the sprite
		//

		D3DXVECTOR3 vecPos = D3DXVECTOR3(0,0,0);

		if (g_pD3DXSprite && g_pTexture)
		{
			g_pD3DXSprite->Begin( D3DXSPRITE_ALPHABLEND );
			g_pD3DXSprite->Draw(g_pTexture, NULL, NULL, &vecPos, 0xffffffff);
			g_pD3DXSprite->End();
		}
			
				
	}
	g_pD3DDevice->EndScene();
	
	
	// Frame buffer to Front buffer
	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );

}

