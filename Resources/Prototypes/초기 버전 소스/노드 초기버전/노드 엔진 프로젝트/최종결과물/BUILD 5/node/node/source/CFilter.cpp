#include "CFilter.hpp"
//	기본생성자
CFilter::CFilter(LPDIRECT3DDEVICE9 device, UINT render_target_width, UINT render_target_height)
: _technique(NULL), _err(NULL), _effect(NULL), _enable(false),
_render_target_width(render_target_width), _render_target_height(render_target_height)
{
	_ratio = (float) _render_target_width / _render_target_height;
}
//	소멸자
CFilter::~CFilter()
{
	release();
}	
//	필터 해제 (콜백)
void	CFilter::release()
{
	_technique = NULL;
	if (_effect)
	{
		_effect->Release();
		_effect = NULL;
	}	
	if (_err)
	{
		_err->Release();
		_err = NULL;
	}
}	
//	버텍스를 렌더링함 (CEngine에도 같은 코드가 있음)
void	CFilter::drawVertex(LPDIRECT3DDEVICE9 device)	
{
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//	셰이더 파일(오브젝트파일)을 읽어들인다.
void	CFilter::loadShaderFile(LPCTSTR filename, LPDIRECT3DDEVICE9 device)
{
	if (_effect)
	{
		CError e
		(	
			_T("경고10:\t셰이더를 생성하려 했으나, 이미 존재합니다. 이전 셰이더를 해제하고 덮어씁니다."),
			_T("해결방법:"),
			_T(__FUNCTION__)
		);
		_effect->Release();
		_effect = NULL;
	}
	//	shader파일 로드
	FILE*	file_pointer;		
	_tfopen_s(&file_pointer, filename, _T("rb"));

	if (file_pointer == NULL)
		return ;

	fseek(file_pointer, 0L, SEEK_END);
	long	size = ftell(file_pointer);

	fseek(file_pointer, 0L, SEEK_SET);
	TCHAR*	source_code = new TCHAR[size];
	fread(source_code, size, sizeof(TCHAR), file_pointer);
	fclose(file_pointer);

	//	shader 생성		
	if ( FAILED(D3DXCreateEffect(device, source_code, size, NULL, NULL, D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, NULL, &_effect, &_err)) )
	{
		//	경고. 포스트이펙트를 사용하지 않음
		CString compile_message = _T("");
		if (_err)
			compile_message = (LPCTSTR) _err->GetBufferPointer();

		CError e
		(	
			_T("경고08:\t셰이더를, 초기화 하지 못했습니다.") + compile_message, 
			_T("해결방법:"),
			_T(__FUNCTION__)
		);
		e.log();			
		_enable = false; // 특정 셰이더만 파일 로드를 못한경우, 그 셰이더만 사용하지 못하도록 해야한다
	}			
	else
		_enable = true;
}
//	버텍스를 할당한다.
void	CFilter::setVertex(LPDIRECT3DVERTEXBUFFER9 vertex_buffer, CArea vertex_area , DWORD color, CArea texture_area)
{	
	MYVERTEX*	vertex;
	//	버퍼 잠구기:
	vertex_buffer->Lock(	0, 4 * sizeof(MYVERTEX), (void**) &vertex, NULL);	
	//	버텍스 설정:		
	//		좌하:
	vertex[0].x = vertex_area._x1;		vertex[0].y = vertex_area._y2;
	vertex[0].tu = texture_area._x1;	vertex[0].tv = texture_area._y1;
	vertex[0].z = 1.0f;					vertex[0].color = color;
	//		좌상:
	vertex[1].x = vertex_area._x1;		vertex[1].y = vertex_area._y1;
	vertex[1].tu = texture_area._x1;	vertex[1].tv = texture_area._y2;
	vertex[1].z = 1.0f;					vertex[1].color = color;
	//		우하:
	vertex[2].x =vertex_area._x2;		vertex[2].y = vertex_area._y2;
	vertex[2].tu = texture_area._x2;	vertex[2].tv = texture_area._y1;
	vertex[2].z = 1.0f;					vertex[2].color = color;
	//		우상:
	vertex[3].x = vertex_area._x2;		vertex[3].y = vertex_area._y1;
	vertex[3].tu = texture_area._x2;	vertex[3].tv = texture_area._y2;
	vertex[3].z = 1.0f;					vertex[3].color = color;
	//	버퍼 풀기:
	vertex_buffer->Unlock();
}
//	렌더스테이트를 변경한다.
void	CFilter::setRenderState(LPDIRECT3DDEVICE9 device, char mode)
{
	if (mode == DEFAULT_CENGINE_RENDERSTATE_LINEAR)
	{
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	else if (mode == DEFAULT_CENGINE_RENDERSTATE_ALPHABLENDING)
	{
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	else if (mode == DEFAULT_CENGINE_RENDERSTATE_DARKEN)
	{
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	}
	else if (mode == DEFAULT_CENGINE_RENDERSTATE_NEGATIVE)
	{
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
	}			 
}