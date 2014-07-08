/*
	파일명:	CTexutre.hpp
	이름:	텍스쳐 클래스
	기능:	텍스쳐를 등록 / 소멸 / 크기등등 관리하는 
*/
#pragma once
//	선언:
//		기본 인클루드:
#include <atlstr.h>
#include <Windows.h>
#include <d3dx9.h>
//		커스텀 인클루드:
#include "CError.hpp"
#include "define.hpp"
//	정의:
//		클래스:
class CTexture
{
//	멤버함수:
public:
	//	생성자:
	CTexture();
	//	소멸자:
	~CTexture();
	//	텍스쳐:
	void	loadTexture(LPDIRECT3DDEVICE9 device, bool is32bit_texture);
	void	UnloadTexture();
	void	setTexture(LPDIRECT3DDEVICE9 device);
	//	파일경로:
	void	setFileName(CString filename);
	void	releaseFileName();	



//	멤버변수:	
public:
	//	크기:
	float	_width,
			_height,
			_halfwidth,
			_halfheight;	
	//	텍스쳐 접근자:
	LPDIRECT3DTEXTURE9	_texture;

//	개인변수:
private:	
	//	파일명:
	CString				_filename;
};