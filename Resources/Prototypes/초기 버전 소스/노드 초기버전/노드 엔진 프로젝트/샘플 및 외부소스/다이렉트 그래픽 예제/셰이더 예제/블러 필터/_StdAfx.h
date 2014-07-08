//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __STDAFX_H_
#define __STDAFX_H_

#pragma once


#pragma warning(disable: 4996)


#define STRICT
#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT			0x0400
#define _WIN32_WINDOWS			0x0400

#define DIRECTINPUT_VERSION		0x0800


#pragma once
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "comctl32.lib")


#pragma warning( disable : 4018)
#pragma warning( disable : 4100)
#pragma warning( disable : 4245)
#pragma warning( disable : 4503)
#pragma warning( disable : 4663)
#pragma warning( disable : 4786)

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

#include <windows.h>
#include <windowsx.h>
#include <basetsd.h>
#include <commctrl.h>
#include <commdlg.h>

#include <math.h>
#include <mmsystem.h>
#include <stdio.h>
#include <tchar.h>


#include <D3D9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "_d3d/DXUtil.h"
#include "_d3d/D3DUtil.h"
#include "_d3d/D3DEnum.h"
#include "_d3d/D3DSettings.h"
#include "_d3d/D3DApp.h"

#include "resource.h"


#define SAFE_NEWINIT(p, CLASSTYPE)									\
{																	\
	if(NULL == (p))													\
	{																\
		p = new CLASSTYPE;											\
		if(!(p))													\
			return -1;												\
																	\
		if(FAILED((p)->Init()))										\
		{															\
			delete p;												\
			p = NULL;												\
			return -1;												\
		}															\
	}																\
}

#define SAFE_NEWCREATE1(p, CLASSTYPE, v0)							\
{																	\
	if(NULL == (p))													\
	{																\
		p = new CLASSTYPE;											\
		if(!(p))													\
			return -1;												\
																	\
		if(FAILED((p)->Create(v0)))									\
		{															\
			delete p;												\
			p = NULL;												\
			return -1;												\
		}															\
	}																\
}

#define SAFE_RESTORE(p)												\
{																	\
	if(p && FAILED((p)->Restore() ))								\
	{																\
		return -1;													\
	}																\
}

#define SAFE_FRMOV(p)												\
{																	\
	if(p && FAILED((p)->FrameMove() ))								\
	{																\
		return -1;													\
	}																\
}

#define SAFE_INVALID(p)			{	if(p)	(p)->Invalidate();		}
#define SAFE_RENDER(p)			{	if(p)	(p)->Render();			}


#include "_McUtil/McGrid.h"
#include "_McUtil/McInput.h"
#include "_McUtil/McCam.h"


#include "ShaderEx.h"



#include "Main.h"

#endif