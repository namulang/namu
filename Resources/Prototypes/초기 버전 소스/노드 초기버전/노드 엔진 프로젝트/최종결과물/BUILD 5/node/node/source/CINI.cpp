#include "CINI.hpp"

//	생성자
CINI::CINI() 
: _graphic_window_mode(DEFAULT_CINI_GRAPHIC_MODE), _graphic_height(DEFAULT_CINI_GRAPHIC_HEIGHT),
_graphic_width(DEFAULT_CINI_GRAPHIC_WIDTH), _graphic_ratio(DEFAULT_CINI_GRAPHIC_RATIO), 
_graphic_vertical_synchronize(DEFAULT_CINI_GRAPHIC_VERTICAL_SYNCHRONIZE),
_graphic_32colorbit(DEFAULT_CINI_GRAPHIC_32COLORBIT), _grpahic_32bit_texture(DEFAULT_CINI_GRAPHIC_32BITTEXTURE),
_graphic_isShaderOn(DEFAULT_CINI_GRAPHIC_IS_SHADER_ON), 
_graphic_shader_quality(DEFAULT_CINI_GRAPHIC_SHADER_QUALITY),
_info_hardware_shader_support(false)
{	
	// #작업# 여기에 INI를 파일로부터 읽게 하자.
}
//	소멸자
CINI::~CINI()
{}
//	실좌표의 너비를 가져온다 : 해상도 및 윈도우 크기와는 다른 개념
int		CINI::getScreenWidth() 
{
	switch (_graphic_ratio)
	{
	case	RATIO_4_3:
		return 1200;
	case	RATIO_16_9:
		return 1600;
	case	RATIO_16_10:
		return 1440;
	default:
		//	약한 에러. 에러 정보만 기록한다
		CError e
		(	
			_T("경고04:\t화면 비율(4:3)에 대한 ini정보가 손실되었습니다. 잘못된 수정이 아닌가 의심됩니다."), 
			_T("해결방법: 이전의 텍스쳐를 지우고 새로운 텍스쳐로 덮어씁니다. 잘못된 그림이 출력될 수 있습니다."),
			_T(__FUNCTION__)
		);
		e.log();	
		return 1200;
	}
}
//	셰이더퀄리티에 따라서, 셰이더를 덮을 텍스쳐의 크기를 반환한다
float	CINI::getShaderWidth() 
{
	switch (_graphic_shader_quality)
	{
	case	SHADER_VERYLOW:
		switch (_graphic_ratio)
		{
		case	RATIO_4_3:
			return 160.0f;

		case	RATIO_16_9:
			return 213.0f;

		case	RATIO_16_10:
			return 192.0f;			

		default:
			//	약한 에러. 에러 정보만 기록한다
			CError e
			(	
				_T("경고11:\t SHADER_VERYLOW에서, 화면비율(GRAPHIC_RATIO) 값이 손실되었습니다. 가장 낮은 크기로 자동 세팅합니다."), 
				_T("해결방법:"),
				_T(__FUNCTION__)
			);
			e.log();	
			return 160.0f;
		}				

	case	SHADER_LOW:
		switch (_graphic_ratio)
		{
		case	RATIO_4_3:
			return 320.0f;

		case	RATIO_16_9:
			return 427.0f;

		case	RATIO_16_10:
			return 384.0f;		
		
		default:
			//	약한 에러. 에러 정보만 기록한다
			CError e
			(	
				_T("경고12:\t SHADER_LOW에서, 화면비율(GRAPHIC_RATIO) 값이 손실되었습니다. 가장 낮은 크기로 자동 세팅합니다."), 
				_T("해결방법:"),
				_T(__FUNCTION__)
			);
			e.log();	
			return 320.0f;
		}			
	case	SHADER_MID:
		switch (_graphic_ratio)
		{
		case	RATIO_4_3:
			return 640.0f;

		case	RATIO_16_9:
			return 853.0f;

		case	RATIO_16_10:
			return 768.0f;		

		default:
			//	약한 에러. 에러 정보만 기록한다
			CError e
			(	
				_T("경고13:\t SHADER_MID에서,화면비율(GRAPHIC_RATIO) 값이 손실되었습니다. 가장 낮은 크기로 자동 세팅합니다."), 
				_T("해결방법:"),
				_T(__FUNCTION__)
			);
			e.log();	
			return 640.0f;
		}	

	case	SHADER_HIGH:
		switch (_graphic_ratio)
		{
		case	RATIO_4_3:
			return 800.0f;

		case	RATIO_16_9:
			return 1067.0f;

		case	RATIO_16_10:
			return 960.0f;		

		default:
			//	약한 에러. 에러 정보만 기록한다
			CError e
			(	
				_T("경고14:\t SHADER_HIGH에서, 화면비율(GRAPHIC_RATIO) 값이 손실되었습니다. 가장 낮은 크기로 자동 세팅합니다."), 
				_T("해결방법:"),
				_T(__FUNCTION__)
			);
			e.log();	
			return 800.0f;
		}	

	case	SHADER_VERYHIGH:
		switch (_graphic_ratio)
		{
		case	RATIO_4_3:
			return 1024.0f;

		case	RATIO_16_9:
			return 1365.0f;

		case	RATIO_16_10:
			return 1229.0f;		

		default:
			//	약한 에러. 에러 정보만 기록한다
			CError e
			(	
				_T("경고15:\t SHADER_VERYHIGH에서, 화면비율(GRAPHIC_RATIO) 값이 손실되었습니다. 가장 낮은 크기로 자동 세팅합니다."), 
				_T("해결방법:"),
				_T(__FUNCTION__)
			);
			e.log();	
			return 1024.0f;
		}	

	default:
		//	약한 에러. 에러 정보만 기록한다
		CError e
		(	
			_T("경고16:\t 잘못된 SHADER의 품질정보. 가장 낮은 품질로 자동 세팅합니다."), 
			_T("해결방법:"),
			_T(__FUNCTION__)
		);
		e.log();
		switch (_graphic_ratio)
		{
		case	RATIO_4_3:
			return 160.0f;

		case	RATIO_16_9:
			return 213.0f;

		case	RATIO_16_10:
			return 192.0f;			

		default:
			//	약한 에러. 에러 정보만 기록한다
			CError e
			(	
				_T("경고17:\t 경고16에서, 화면비율(GRAPHIC_RATIO) 값이 손실되었습니다. 가장 낮은 크기로 자동 세팅합니다."), 
				_T("해결방법:"),
				_T(__FUNCTION__)
			);
			e.log();	
			return 160.0f;
		}				
	}
}
//	셰이더퀄리티에 따라서, 셰이더를 덮을 텍스쳐의 크기를 반환한다
float	CINI::getShaderHeight() 
{
	switch (_graphic_shader_quality)
	{
	case	SHADER_VERYLOW:
		return 120.0f;			

	case	SHADER_LOW:
		return 240.0f;			

	case	SHADER_MID:		
		return 480.0f;			

	case	SHADER_HIGH:		
		return 600.0f;			

	case	SHADER_VERYHIGH:		
		return 768.0f;			
	
	default:
		//	약한 에러. 에러 정보만 기록한다
		CError e
		(	
			_T("경고18:\t 셰이더 품질 값이 손실되었습니다. 가장 낮은 품질로 자동 세팅합니다."), 
			_T("해결방법:"),
			_T(__FUNCTION__)
		);
		e.log();					
		return 120.0f;			
	}
}
//	실좌표의 높이를 가져온다.
int		CINI::getScreenHeight() 
{ 
	return 900; 
}
// 해상도를 찾는 과정에서 끝까지 오류가 발생했을때 최종적으로, 기본값 (실행이 보장되는..)으로 돌림. 가장 낮은 그래픽 설정. 실행을 항상 보장하도록 한다
void	CINI::setDefaultVeryLow() 
{
	_graphic_window_mode = true;
	_graphic_height = 640;
	_graphic_width = 480;
	_graphic_ratio = RATIO_4_3;
	_graphic_vertical_synchronize = false;
	_graphic_32colorbit = false;
	_graphic_isShaderOn = false;
	setDefaultVeryLowShader();
}
//	셰이더를 "가장품질낮음" 으로 설정한다.
void	CINI::setDefaultVeryLowShader()
{
	_graphic_shader_quality = SHADER_VERYLOW;
}