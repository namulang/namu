#include "AnimatedModel.hpp"
#include "../DX9/DX9.hpp"
#include "../Texture/Texture.hpp"
#include "../TabledTexture/TabledTexture.hpp"

namespace DX9Graphics
{
	type_result AnimatedModel::_onExecute()
	{
		SuperClass::_onExecute();

		Texture& texture = getTexture();

		static type_code tabled_code = -1;
		if (tabled_code == -1)
			tabled_code = Kernal::getInstance().getModuleManager().getModule(NEExportable::Identifier("TabledTexture.kniz")).getScriptCode();

		if(	! &texture									||
			texture.getScriptCode() != tabled_code	) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;


		//	main:
		TabledTexture& tabled = static_cast<TabledTexture&>(texture);

		_adjustValuesBy(tabled);
		return _updateDelayBy(tabled);
	}

	type_result AnimatedModel::_adjustValuesBy(const TabledTexture& tabled)
	{
		type_int	index = arg_animation_index.getValue(),
			frame = arg_key_frame.getValue(),
			delay_per_frame = arg_delay_per_frame.getValue(),
			max_delay_per_frame = tabled.arg_delay_per_frame.getValue(),
			delay = getDelay(),
			max_row = tabled.arg_max_row.getValue(),
			max_column = tabled.arg_max_column.getValue();

		bool is_adjusted = false;
		if(index < 0)
		{
			arg_animation_index.setValue(0);
			is_adjusted = true;
		}
		else if(index >= max_row)
		{
			arg_animation_index.setValue(max_row);
			is_adjusted = true;
		}
		if(frame < 0)
		{
			arg_key_frame.setValue(0);
			is_adjusted = true;
		}
		else if(frame >= max_column)
		{
			arg_key_frame.setValue(max_column);
			is_adjusted = true;
		}
		if(delay_per_frame < -2)
		{
			arg_delay_per_frame.setValue(-2);
			is_adjusted = true;
		}
		else if(delay_per_frame > max_delay_per_frame)
		{
			arg_delay_per_frame.setValue(max_delay_per_frame);
			is_adjusted = true;
		}


		//	post:
		if(is_adjusted)
			return ALERT_WARNING("AnimationIndex, Frame등 일부 값이 지정한 텍스쳐의 범위를 넘어서므로\n일부 오차를 조정했습니다");

		return RESULT_SUCCESS;
	}

	type_result AnimatedModel::_updateDelayBy(const TabledTexture& tabled)
	{
		if( ! arg_delay_per_frame.isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		type_int	delay_count = arg_delay_per_frame.getValue();		
		if (delay_count == -2)	//	Auto
		{
			if( ! tabled.arg_delay_per_frame.isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

			delay_count = tabled.arg_delay_per_frame.getValue();
		}			
		if(delay_count == -1)	//	Infinite
			return RESULT_SUCCESS;

		_delay++;
		if(_delay > delay_count)
		{
			const type_int& max_frame_count = tabled.arg_column_count_per_row.getValue()[arg_animation_index.getValue()];
			if( ! &max_frame_count)
			{
				arg_animation_index.setValue(0);
				return ALERT_WARNING("Animation Index가 잘못되었습니다.");
			}

			arg_key_frame.setValue(arg_key_frame.getValue() + 1);
			if(arg_key_frame.getValue() >= max_frame_count)
				arg_key_frame.setValue(0);

			_delay = 0;
		}

		return RESULT_SUCCESS;
	}
}