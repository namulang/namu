
#include "_StdAfx.h"


CMain*	g_pApp	= NULL;


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CMain appMain;

	g_pApp	= &appMain;

	if(FAILED(appMain.Create(hInst)))
		return -1;

	INT	msg = appMain.Run();
	return msg;

}