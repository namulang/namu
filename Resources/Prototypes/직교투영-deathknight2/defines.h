#pragma once
#pragma warning( disable : 4819 )
#pragma warning( disable : 4996 )

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia 07 - 10 - 6 Header
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <math.h>
#include <iostream>
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia 07 - 10 - 6 enum
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
enum VERTEX {VER_CUBE, VER_LAND, VER_END};
enum TEXTURE {TEX_SOPI, TEX_END};
enum PLANET { PLANET_END};
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia 07 - 10 - 6 struct
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//struct tagPlanet
//{
//	D3DXMATRIXA16	matWorld;	//연산완료된 행렬
//	D3DXVECTOR3		vPos;		//위치
//	D3DXVECTOR3		vRot;		//회전축 벡터
//	float			fMag;		//축소 확대
//	float			fRot;		//회전 각도
//	float			fRotSpeed;	//회전 스피드
//	TEXTURE	Texture;	//어떤 텍스쳐를 쓰는지
//	bool			bGo;
//};
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia 07 - 10 - 9 struct
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// 텍스쳐가 필요할때
struct CUSTOMVERTEX
{
	FLOAT	x, y, z;	//정점
	DWORD	color;		//색깔
	float	tu, tv;		//텍스쳐 좌표 
};
// 텍스쳐가 필요없을때
struct NONETEXTUREVERTEX
{
	FLOAT	x, y, z;	//정점
	DWORD	color;		//색깔
};
// 인덱스
struct tagIndex
{
	WORD _0;
	WORD _1;
	WORD _2;
};
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia 07 - 10 - 6 define
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//#define FULLMODE
#define WINSIZEX	800.0f
#define WINSIZEY	600.0f
#define D3DFVF_CUSTOMAXIS D3DFVF_XYZ 
#define D3DFVF_COLOR D3DFVF_DIFFUSE
#define MouseFLOAT 0.05f
#define MovingSpeed 0.06f
#define COOLTIME_MAX_DIVIDE 3000
#define SAFE_DELETE(p)   if(p) { delete (p); p = NULL; }
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia 07 - 10 - 6 extern
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
extern HWND						g_hWnd;		
extern HINSTANCE				g_hInst;	


