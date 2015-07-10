#pragma once

#include "../Modules/Core/Core.hpp"
#include "../Modules/ListGliph/ListGliph.hpp"
#include "../Modules/TextGliph/TextGliph.hpp"
#include "../Modules/SwitchGliph/SwitchGliph.hpp"
#include "../Modules/MessageWindow/MessageWindow.hpp"
#include "../Modules/QueryWindow/QueryWindow.hpp"
#include "../Modules/InputWindow/InputWindow.hpp"
#include "../Modules/ListWindow/ListWindow.hpp"
#include "../Commons/Defines/ClassMacros/ClassMacros.hpp"
#include "../Modules/FloatingGliph/FloatingGliph.hpp"
#include "../Modules/GearGliph/GearGliph.hpp"
#include "../Modules/TextListWindow/TextListWindow.hpp"


//	NEModule이 kernal에 있어야 하는 이유
//	템플릿클래스이기 때문이다. 템플릿클래스는 특성상 인스턴스가 선언하면서 생성된다. NE_DLL은 이미 존재하는 DLL의 인스턴스를 가져오는 매크로.
//	때문에 템플릿 클래스를 DLL에서 사용하고 싶다면 2가지를 택해야한다.
//		1. DLL 내부에 인스턴스를 미리 생성하고 _declspec(dllimport)로 외부에서 가져와 쓴다
//		2. 외부에서 템플릿 클래스 인스턴스를 생성한다. 이때 템플릿클래스에 NE_DLL을 쓰면 외부에서 include할때 _declspec(dllimport)로 변환되므로
//		NE_DLL 없이 헤더를 작성해야 하고, 그렇게되면 내부에서 생성한 클래스템플릿을 export해야하는 방법을 생각해야 할것이다.
//	여기서는 템플릿클래스가 선언된 DLL에 같이 NEModule을 선언함으로써 번거로운 2번 대신, 1번을 택했다.

#ifndef LAZYGENIUSFRAMEWORK_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "LazyGeniusFramework.dev.dbg.lib")
#			else
#				pragma comment(lib, "LazyGeniusFramework.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "LazyGeniusFramework.dev.lib")
#			else
#				pragma comment(lib, "LazyGeniusFramework.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "LazyGeniusFramework.lib")
#		else
#			pragma comment(lib, "LazyGeniusFramework.mbcs.lib")
#		endif
#	endif
#endif
