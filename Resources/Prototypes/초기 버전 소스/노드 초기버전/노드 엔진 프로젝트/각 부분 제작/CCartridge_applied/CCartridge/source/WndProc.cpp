#include <Windows.h>
#include <tchar.h>
#include "CINI.hpp"

//	윈도우프로시져:
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_ACTIVATEAPP:
		{
			if( wParam == TRUE )
			{
				// App is now active, so re-enable XInput
				//g_ini._window_activate = true;
			}
			else
			{
				// App is now inactive, so disable XInput to prevent
				// user input from effecting application and to 
				// disable rumble. 
				//g_ini._window_activate = false;
			}
			break;
		}
		case WM_SIZE:
		{
			GetClientRect(hWnd, &g_ini._client_rect); // CWindow가 ini에서 지정된 크기로 윈도우의 크기를 재변경하고, 자동으로 이곳이 콜백됨
			break;
		}	
		case WM_SIZING:
		{
			if( wParam == TRUE )
			{
				// App is now active, so re-enable XInput
				g_ini._window_activate = true;
			}
			else
			{
				// App is now inactive, so disable XInput to prevent
				// user input from effecting application and to 
				// disable rumble. 
				g_ini._window_activate = false;
			}
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0); // WM_QUIT를 보냄
			return(0);
		}
	}

	return(DefWindowProc(hWnd, msg, wParam, lParam));
}
