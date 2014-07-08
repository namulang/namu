#include "AnimatedModel.hpp"
#include "define.hpp"
#include "../DX9/DX9.hpp"
#include "../Texture/Texture.hpp"
#include "../TabledTexture/TabledTexture.hpp"

namespace DX9Graphics
{
	const NEExportable::ModuleHeader& AnimatedModel::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getComment() = _T(_COMMENT);
			_header.getVersion()  = _T(_VERSION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	type_result AnimatedModel::execute()
	{
		static type_code tabled_code = Kernal::getInstance().getModuleManager()
			.getModule(TabledTexture().getHeader()).getScriptCode();
		SuperClass::execute();
		if( ! isRenderable()) return RESULT_SUCCESS;
		NEModuleSelector& tex_sel = getTextureSelector();
		NEModule& module = tex_sel.getModule();
		tex_sel.initializeReferingPoint();
		if( ! &module)
		{
			ALERT_ERROR("텍스쳐가 바인딩 되지 않아서 Animation execution 실패");
			return RESULT_TYPE_ERROR;
		}
		if(module.getScriptCode() != tabled_code) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

		//	main:
		TabledTexture& tabled = static_cast<TabledTexture&>(module);
		
		_adjustValuesBy(tabled);
		return _updateDelayBy(tabled);
	}

	type_result AnimatedModel::_adjustValuesBy(const TabledTexture& tabled)
	{
		type_int&	index = getAnimationIndex(),
				&	frame = getKeyFrame(),
				&	delay_per_frame = getDelayPerFrame();
		type_int	max_delay_per_frame = tabled.getDelayPerFrame(),
					delay = getDelay(),
					max_row = tabled.getMaxRow(),
					max_column = tabled.getMaxColumn();
	
		bool is_adjusted = false;
		if(index < 0)
		{
			index = 0;		
			is_adjusted = true;
		}
		else if(index >= max_row)
		{
			index = max_row;
			is_adjusted = true;
		}
		if(frame < 0)
		{
			frame = 0;
			is_adjusted = true;
		}
		else if(frame >= max_column)
		{
			frame = max_column;
			is_adjusted = true;
		}
		if(delay_per_frame < -2)
		{
			delay_per_frame = -2;
			is_adjusted = true;
		}
		else if(delay_per_frame > max_delay_per_frame)
		{
			delay_per_frame = max_delay_per_frame;
			is_adjusted = true;
		}


		//	post:
		if(is_adjusted)
		{
			ALERT_WARNING("AnimationIndex, Frame등 일부 값이 지정한 텍스쳐의 범위를 넘어서므로\n일부 오차를 조정했습니다");
			return RESULT_TYPE_WARNING;
		}
		
		return RESULT_SUCCESS;
	}

	type_result AnimatedModel::_updateDelayBy(const TabledTexture& tabled_has_max_delay)
	{
		type_int	delay_count = getDelayPerFrame();		
		if(delay_count == -2)	//	Auto
			delay_count = tabled_has_max_delay.getDelayPerFrame();
		if(delay_count == -1)	//	Infinite
			return RESULT_SUCCESS;

		_delay++;
		if(_delay > delay_count)
		{
			type_int& frame = getKeyFrame();
			const type_int& max_frame_count = tabled_has_max_delay.getColumnCountPerRow()[getAnimationIndex()];
			if( ! &max_frame_count)
			{
				ALERT_WARNING("Animation Index가 잘못되었습니다.");
				getAnimationIndex() = 0;
				return RESULT_TYPE_WARNING;
			}

			frame++;
			if(frame >= max_frame_count)
				frame = 0;

			_delay = 0;
		}

		return RESULT_SUCCESS;
	}
}