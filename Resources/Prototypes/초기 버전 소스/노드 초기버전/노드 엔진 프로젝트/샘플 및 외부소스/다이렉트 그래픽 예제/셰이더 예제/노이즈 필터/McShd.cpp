


#include "_StdAfx.h"


CMain*		g_pApp  = NULL;


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    CMain d3dApp;

    g_pApp  = &d3dApp;

    InitCommonControls();
	
    if( FAILED( d3dApp.Create( hInst ) ) )
        return 0;

    return d3dApp.Run();
}