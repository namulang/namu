/*


	프로젝트명:	게임엔진 노드
	개발 언어:	C++
	개발 툴:	VC++ 2008 SP1 한글판, DirectX SDK 2010 JUNE
	개발 환경:	Window 7 x64
	
	메모:	
	내역:	2010-07-05	개발 시작			
			2010-07-08	build 2
			2010-07-13	build 3 
			2010-07-16	build 4
			2010-07-27	build 5		이제 더이상 못만들겠다고 했는데... 다행히 5도 나왔음 ^_^
*/

#include <Windows.h>
#include "CHUB.hpp"
#include "CWindow.hpp"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	try
	{	
		//	초기화:
		CHUB	hub(hInstance, lpCmdLine, nCmdShow);
		//	게임 기동:
		hub.handleMessage();
	}
	//	 심각한 오류는 여기서 메세지박스를 띄우고 프로그램을 종료한다
	catch(CError e)
	{
		e.showMessage();
		e.log();
	}
}


