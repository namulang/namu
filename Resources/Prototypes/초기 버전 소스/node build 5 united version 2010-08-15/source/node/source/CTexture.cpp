#include "CTexture.hpp"

//	생성자
CTexture::CTexture() : _texture(NULL), _filename(_T("")),
_width(0), _height(0), _halfwidth(0), _halfheight(0)
{}	
//	소멸자
CTexture::~CTexture()
{
	if( _texture )
		_texture->Release();	
}	
//	미리 입력된 경로로, 텍스쳐를 읽어들임
void	CTexture::loadTexture(LPDIRECT3DDEVICE9 device, bool is32bit_texture)
{
	//	예외상황 처리:
	//		filename이 없는 경우:
	if (_filename == _T(""))
	{
		//	약한 에러. 에러 정보만 기록한다
		CError e
		(	
			_T("경고06:\t텍스쳐를 읽어올 파일정보가 없습니다."), 
			_T("해결방법: ."),
			_T(__FUNCTION__)
		);
		e.log();
		return ;
		//	로그를 기록하고 텍스쳐를 덮어서 로딩한다
	}
	//		텍스쳐가 이미 있는 경우:
	if ( _texture )
	{
		//	약한 에러. 에러 정보만 기록한다
		CError e
		(	
			_T("경고01:\t1. 텍스쳐가 초기화 되지 않았습니다. 텍스쳐의 갯수를 저장하는 변수(_texture_size)가 외부에서 변경되지 않았나 의심합니다."), 
			_T("텍스쳐를 강제로 릴리즈 했습니다"),
			_T(__FUNCTION__)
		);
		e.log();
		UnloadTexture();			
	}


	//	메인코드:
	//		텍스쳐 로드:
	D3DXIMAGE_INFO	info;
	D3DFORMAT		format;
	if (is32bit_texture)
		format = D3DFMT_A8B8G8R8; // 디스플레이의 32비트와, 텍스쳐의 32비트는 다른것이다. 16비트-32비트 도 되고, 32비트-16비트도 된다.
	else
		format = D3DFMT_A1R5G5B5;

	D3DXCreateTextureFromFileEx(device, _filename,D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, DEFAULT_CTEXTURE_MIPMAPLEVEL, 0, 
		D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, DEFAULT_CENGINE_COLORKEY,
		&info, NULL, &_texture);
	//(info.Width);
	//	예외상황처리:
	//		텍스쳐 로드 실패:
	if (!_texture)
	{
		//	약한 에러. 에러 정보만 기록한다
		CString	message;
		message = _T("경고03:\t텍스쳐를 읽는데 실패했습니다. 파일이 존재하지 않은 것 같습니다. 파일명:" + _filename);
		CError e
		(	
			message, 
			_T("해결방법"),
			_T(__FUNCTION__)
		);
		e.log();	
	}
	else
	{
		//	텍스쳐의 정보를 갱신한다
		_width = static_cast<float> (info.Width);
		_halfwidth = _width / 2.0f;
		_height = static_cast<float> (info.Height);
		_halfheight = _height / 2.0f;
	}
}
//	텍스쳐를 릴리즈 한다. 경로는 남아있기때문에, 경로를 인풋하지 않고도 바로 로드가 가능하다.
void	CTexture::UnloadTexture() 
{
	if (_texture)
	{
		_texture->Release();
		_texture = NULL;
		_height = 0;
		_width = 0;
		_halfheight = 0;
		_halfwidth = 0;
	}
}
//	텍스쳐를 디바이스에 세팅한다.
void	CTexture::setTexture(LPDIRECT3DDEVICE9 device)
{
	if (_texture)
		device->SetTexture(0, _texture);
}
//	텍스쳐 경로를 인풋한다.
void	CTexture::setFileName(CString filename)
{
	_filename = filename;
}
void	CTexture::releaseFileName()
{
	_filename = _T("");
}