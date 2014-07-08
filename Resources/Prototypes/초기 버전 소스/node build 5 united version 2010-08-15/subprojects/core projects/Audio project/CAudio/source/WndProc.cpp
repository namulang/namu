#include <Windows.h>
#include <tchar.h>


//	윈도우프로시져:
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0); // WM_QUIT를 보냄
		return(0);
	}

	return(DefWindowProc(hWnd, msg, wParam, lParam));
}
