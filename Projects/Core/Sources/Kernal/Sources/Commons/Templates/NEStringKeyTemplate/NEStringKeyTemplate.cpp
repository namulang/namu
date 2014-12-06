#pragma warning(push)
#pragma warning(disable : 4800)
#pragma warning(disable : 4804)
#pragma warning(disable : 4146)	//	unsigned에 -를 사용함
#include "NEStringKeyTemplate.hpp"
#include "../../../Modules/NEBooleanKey/NEBooleanKey.hpp"
#include "../../../Modules/NECharKey/NECharKey.hpp"
#include "../../../Modules/NEByteKey/NEByteKey.hpp"
#include "../../../Modules/NEUByteKey/NEUByteKey.hpp"
#include "../../../Modules/NEWCharKey/NEWCharKey.hpp"
#include "../../../Modules/NEShortKey/NEShortKey.hpp"
#include "../../../Modules/NEUShortKey/NEUShortKey.hpp"
#include "../../../Modules/NEIntKey/NEIntKey.hpp"
#include "../../../Modules/NEUIntKey/NEUIntKey.hpp"
#include "../../../Modules/NEInt64Key/NEInt64Key.hpp"
#include "../../../Modules/NEFloatKey/NEFloatKey.hpp"
#include "../../../Modules/NEDoubleKey/NEDoubleKey.hpp"
#include "../../../Modules/NEStringKey/NEStringKey.hpp"
#include "../../../Modules/NEWStringKey/NEWStringKey.hpp"

namespace NE
{
	template <>
	type_result NE_DLL NEStringKeyTemplate<NEString, NEType::NESTRING_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if( ! &source) return RESULT_TYPE_ERROR;
		if( this == &source) return RESULT_TYPE_ERROR;


		SuperClass::assign(source);

		//	main:
		switch(source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			_value = (static_cast<const NECharKey&>(source)).getValue();
			break;
		case NEType::NEBYTE_KEY:
			_value = static_cast<type_int>((static_cast<const NEByteKey&>(source)).getValue());
			break;
		case NEType::NEUBYTE_KEY:
			_value = static_cast<type_int>((static_cast<const NEUByteKey&>(source)).getValue());
			break;
		case NEType::NEWCHAR_KEY:
			_value = (static_cast<const NEWCharKey&>(source)).getValue();
			break;
		case NEType::NESHORT_KEY:			
			_value = static_cast<type_int>((static_cast<const NEShortKey&>(source)).getValue());
			break;
		case NEType::NEUSHORT_KEY:
			_value = (static_cast<const NEUShortKey&>(source)).getValue();;
			break;
		case NEType::NEINT_KEY:
			_value = (static_cast<const NEIntKey&>(source)).getValue();
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_int>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:
			_value = (static_cast<const NEFloatKey&>(source)).getValue();
			break;
		case NEType::NEDOUBLE_KEY:
			_value = (static_cast<const NEDoubleKey&>(source)).getValue();
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_int>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = (static_cast<const NEStringKey&>(source)).getValue();
			break;
		case NEType::NEWSTRING_KEY:
			_value = (static_cast<const NEWStringKey&>(source)).getValue();
			break;
		}

		return RESULT_SUCCESS;
	}
	template <>
	type_result NE_DLL NEStringKeyTemplate<NEWString, NEType::NEWSTRING_KEY>::assign(const NEKey& source)
	{
		//	pre:
		if( ! &source) return RESULT_TYPE_ERROR;
		if( this == &source) return RESULT_TYPE_ERROR;


		SuperClass::assign(source);

		//	main:
		switch(source.getType())
		{
		case NEType::NEBOOLEAN_KEY:
			_value = (static_cast<const NEBooleanKey&>(source)).getValue();
			break;
		case NEType::NECHAR_KEY:
			_value = (static_cast<const NECharKey&>(source)).getValue();
			break;
		case NEType::NEBYTE_KEY:
			_value = static_cast<type_int>((static_cast<const NEByteKey&>(source)).getValue());
			break;
		case NEType::NEUBYTE_KEY:
			_value = static_cast<type_int>((static_cast<const NEUByteKey&>(source)).getValue());
			break;
		case NEType::NEWCHAR_KEY:
			_value = (static_cast<const NEWCharKey&>(source)).getValue();
			break;
		case NEType::NESHORT_KEY:
			_value = (static_cast<const NEShortKey&>(source)).getValue();
			break;
		case NEType::NEUSHORT_KEY:
			_value = static_cast<type_int>((static_cast<const NEUShortKey&>(source)).getValue());
			break;
		case NEType::NEINT_KEY:
			_value = (static_cast<const NEIntKey&>(source)).getValue();
			break;
		case NEType::NEUINT_KEY:
			_value = static_cast<type_int>((static_cast<const NEUIntKey&>(source)).getValue());
			break;
		case NEType::NEFLOAT_KEY:			
			_value = (static_cast<const NEFloatKey&>(source)).getValue();
			break;
		case NEType::NEDOUBLE_KEY:
			_value = (static_cast<const NEDoubleKey&>(source)).getValue();
			break;
		case NEType::NEINT64_KEY:
			_value = static_cast<type_int>((static_cast<const NEInt64Key&>(source)).getValue());
			break;
		case NEType::NESTRING_KEY:
			_value = (static_cast<const NEStringKey&>(source)).getValue();
			break;
		case NEType::NEWSTRING_KEY:
			_value = (static_cast<const NEWStringKey&>(source)).getValue();
			break;
		}

		return RESULT_SUCCESS;
	}

	template <>
	bool NEStringKeyTemplate<NEString, NEType::NESTRING_KEY>::isLower(const NEKey& source) const
	{
		//	pre:
		if( ! &source) return false;



		//	main:
		//		버퍼 정의:
		ThisClass buffer;
		//		버퍼에 할당:
		type_result result = buffer.assign(source);
		if(NEResult::hasError(result))
			return false;
		


		//	post:
		//		버퍼 비교:
		//			타겟팅:
		const NEString	&source_string = getValue(),
						&target_string = buffer.getValue();		
		//			사전 예외처리:
		if(target_string.getLength() <= 0) return false;
		type_index length_of_source = getValue().getLength();
		//			루핑:
		for(int n=0; n < length_of_source ;n++)
		{
			//			예외처리:
			/*
							비교대상(= 타겟)이 길이가 작을경우에는, 탐색을 중단하고 이전
							까지의 결과가 true였으므로 "true"를 반환한다.

							그러나 타겟이 길이가 0이라면, for루프 전에서 사전 예외처리를 
							통해 false가 반환될 것이다.
			*/
			if(n > target_string.getLengthLastIndex()) break;

			//			문자 비교:
			//				문자 추출:
			char	source_character = source_string[n],
					target_character = target_string[n];
			//				비교:
			/*
								정상적으로 추출한 두개의 문자를 비교해서 "원본 >= 비교대상"이 
								되는, 순간에는 false를 반환한다.
			*/
			if(source_character >= target_character)
				return false;
		}

		return true;
	}

	template <>
	bool NEStringKeyTemplate<NEWString, NEType::NEWSTRING_KEY>::isLower(const NEKey& source) const
	{
		//	pre:
		if( ! &source) return false;



		//	main:
		//		버퍼 정의:
		ThisClass buffer;
		//		버퍼에 할당:
		type_result result = buffer.assign(source);
		if(NEResult::hasError(result))
			return false;
		


		//	post:
		//		버퍼 비교:
		//			타겟팅:
		const NEWString	&source_string = getValue(),
						&target_string = buffer.getValue();		
		//			사전 예외처리:
		if(target_string.getLength() <= 0) return false;
		type_index length_of_source = getValue().getLength();
		//			루핑:
		for(int n=0; n < length_of_source ;n++)
		{
			//			예외처리:
			/*
							비교대상(= 타겟)이 길이가 작을경우에는, 탐색을 중단하고 이전
							까지의 결과가 true였으므로 "true"를 반환한다.

							그러나 타겟이 길이가 0이라면, for루프 전에서 사전 예외처리를 
							통해 false가 반환될 것이다.
			*/
			if(n > target_string.getLengthLastIndex()) break;

			//			문자 비교:
			//				문자 추출:
			wchar_t	source_character = source_string[n],
					target_character = target_string[n];
			//				비교:
			/*
								정상적으로 추출한 두개의 문자를 비교해서 "원본 >= 비교대상"이 
								되는, 순간에는 false를 반환한다.
			*/
			if(source_character >= target_character)
				return false;
		}

		return true;
	}
}

#pragma warning(pop)