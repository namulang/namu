#pragma once;

#include "../Texture/Texture.hpp"

namespace DX9Graphics
{
	class NE_DLL TabledTexture : public Texture
	{
	public:
		typedef Texture SuperClass;
		typedef TabledTexture ThisClass;

	public:
		NETArgument<NEIntKey>		arg_max_row;
		NETArgument<NEIntKey>		arg_max_column;
		NETArgument<NEIntKey>		arg_delay_per_frame;
		NETArgument<NEIntSetKey>	arg_column_count_per_row;

	protected:
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_max_row.setValue(1);
			arg_max_row.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_max_column.setValue(1);
			arg_max_column.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_delay_per_frame.setEnable(false);
			arg_delay_per_frame.setPurposeLimitation(NEArgumentBase::READ_BY);

			NEIntSet sample(1);
			sample.push(1);
			arg_column_count_per_row.getValue() = sample;
			arg_column_count_per_row.setEnable(false);
			arg_column_count_per_row.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			SuperClass::_onFetchArguments(tray);

			tray.push(arg_max_row);
			tray.push(arg_max_column);
			tray.push(arg_delay_per_frame);
			tray.push(arg_column_count_per_row);

			return RESULT_SUCCESS;
		}

	public:
		TabledTexture()
			: SuperClass()
		{
			_release();
		}
		TabledTexture(const ThisClass& source)
			: SuperClass(source)
		{
			_assign(source);
		}
		~TabledTexture()
		{

		}

	public:
		const ThisClass& operator=(const ThisClass& source)
		{
			SuperClass::operator=(source);

			return _assign(source);
		}
		bool operator==(const ThisClass& source) const
		{
			if(SuperClass::operator!=(source)) return false;
			if(_column_extracted_from_model != source._column_extracted_from_model) return false;
			if(_row_extracted_from_model != source._row_extracted_from_model) return false;

			return true;
		}
		bool operator!=(const ThisClass& source) const
		{
			return ! operator==(source);
		}

	public:
		type_int getRowExtractedFromModel() const { return _row_extracted_from_model; }
		type_int getColumnExtractedFromModel() const { return _column_extracted_from_model; }		
		RECT createTexelPosition(type_int animation_index, type_int frame_index) const
		{
			RECT to_return = {0, };
			if(_isFrameIndexOverflowed(animation_index, frame_index))
			{
				ALERT_WARNING("지정한 animation_index, frame_index가 ColumnTable 범위를 넘어섰습니다:\n임의로 (U, V)=(0, 0)를 내보냅니다.\n\t입력한 (animation, frame)=(%d, %d)", animation_index, frame_index);
				to_return.left = 0;
				to_return.top = 0;
				to_return.right = getWidth();
				to_return.bottom = getHeight();
				return to_return;
			}



			//	main:
			type_float	width_per_1_frame		= static_cast<type_float>(getWidth()) / arg_max_column.getValue(),
				height_per_1_animation	= static_cast<type_float>(getHeight()) / arg_max_row.getValue();
			to_return.left = static_cast<LONG>(frame_index * width_per_1_frame);
			to_return.top = static_cast<LONG>(animation_index * height_per_1_animation);
			to_return.right = static_cast<LONG>((frame_index+1) * width_per_1_frame);
			to_return.bottom = static_cast<LONG>((animation_index+1) * height_per_1_animation);

			return to_return;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if (_header.isValid() != RESULT_NOTHING)
			{
				const NEExportable::ModuleHeader& supers = SuperClass::getHeader();
				_header.getName() = "TabledTexture";
				_header.getDeveloper() = "kniz";
				_header.setRevision(1);
				_header.getComment() = supers.getComment() +
					"TabledTexture는 이런 기존의 Texture 기능에, Animation의 기능을 제공합니다.\n"
					"TabledTexture는 여러개의 Animation으로 이루어져 있고, 이는 행(row)으로 구분됩니다."
					"각 Animation은 여러개의 KeyFrame 들로 이루어져 있고 이는 각 행의 열(column)으로 구분됩니다.\n"
					"예를들어, 2번째 Animation의 5번째 KeyFrame의 그림은 다음과 같이 구해집니다.\n"
					"주어진 그림(.bmp, .jpg 등)의 몇개의 행이 있는지(row_cnt), 최대 몇개의 열이 있는지(column_cnt)"
					"를 구한 뒤, 그림을 각 행과 열의 숫자로 표(table)처럼 나눕니다.\n"
					"그리고 2번째행의 5번째열 영역을 Texture로 사용하게 됩니다.";					
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2013-08-10";
				NETStringSet& args = _header.getArgumentsComments();
				args = supers.getArgumentsComments();
				args.resize(args.getLength() + 3);
				args.push("MaxRow\nTexture를 표의 형태의 영역으로 나눌때 몇개의 행인지 지정합니다.");
				args.push("MaxColumn\nTexture를 표의 형태의 영역으로 나눌때 몇 개의 열인지 지정합니다.");
				args.push("DelayPerFrame\nAnimation이 한 KeyFrame이 넘어갈때 걸리는 시간입니다.\n-1 혹은 disabled면 딜레이 무한대 입니다.");
				args.push("Customized Key Frame\nAnimation 마다 KeyFrame이 다를 경우, 각 Animation에 대한 KeyFrame 수를 입력합니다.\nEnable일때만 사용합니다.");
			}

			return _header;
		}
		virtual type_uint getWidthOfOneFrame() const
		{
			type_count max = arg_max_column.getValue();
			if(arg_column_count_per_row.isEnable())
			{
				const NEIntSet& set = arg_column_count_per_row.getValue();
				for (int n = 0; n < set.getLength(); n++)
					if(set[n] > max)
						max = set[n];
			}

			return getWidth() / max;
		}
		virtual type_uint getHeightOfOneFrame() const
		{
			type_count max = arg_max_row.getValue();

			if(arg_column_count_per_row.isEnable())
			{
				const NEIntSet& set = arg_column_count_per_row.getValue();

				max = set.getLength() > max ? set.getLength() : max;
			}

			return getHeight() / max;
		}
		virtual type_result dock(Model& model);
		virtual RECT createSourceRect() const 
		{
			return createTexelPosition(_row_extracted_from_model, _column_extracted_from_model);
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual type_result isValid() const
		{
			//	pre:
			type_result result = SuperClass::isValid();
			if(NEResult::hasError(result)) return result;
			//		사용중인 Row당 Col수 체크:
			const NEIntSet& columns = arg_column_count_per_row.getValue();
			type_int	max_column = arg_max_column.getValue(),
				max_row = arg_max_row.getValue();
			if(columns.getSize() > (type_int) max_row)
				return ALERT_ERROR("사용중인 Row의 수가 최대 Row Count를 넘었습니다.");

			for(int n=0; n < columns.getSize() ;n++)
				if(columns[n] < 0 || columns[n] > max_column)
					return ALERT_ERROR("사용중인 Column의 수가 최대 Column Count를 넘었습니다.");

			return RESULT_SUCCESS;
		}
		virtual void release()
		{
			SuperClass::release();

			_release();
		}

	private:
		bool _isFrameIndexOverflowed(type_int animation_index, type_int frame_index) const
		{
			const NEIntSet& table = arg_column_count_per_row.getValue();
			if(animation_index < 0 || animation_index > static_cast<type_int>(table.getSizeLastIndex())) return true;
			type_int max_frame_index = table[animation_index] - 1;
			if(frame_index < 0 || frame_index > max_frame_index)	return true;

			return false;
		}
		ThisClass& _assign(const ThisClass& source)
		{
			if(this == &source) return *this;

			_row_extracted_from_model = source._row_extracted_from_model;
			_column_extracted_from_model = source._column_extracted_from_model;
			arg_max_row = source.arg_max_row;
			arg_max_column = source.arg_max_column;
			arg_delay_per_frame = source.arg_delay_per_frame;
			arg_column_count_per_row = source.arg_column_count_per_row;

			return *this;
		}
		void _release()
		{
			_row_extracted_from_model = 0;
			_column_extracted_from_model = 0;
		}
		void _validate()
		{
			if(arg_max_row.getValue() <= 0)
				arg_max_row.setValue(1);
			if(arg_max_column.getValue() <= 0)
				arg_max_column.setValue(1);
		}

	private:
		type_int _row_extracted_from_model;
		type_int _column_extracted_from_model;
	};
}