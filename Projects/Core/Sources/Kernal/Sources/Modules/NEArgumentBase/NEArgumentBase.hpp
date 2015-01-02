//	NEArgumentBase::PurPose 정책:
//		총 5 종류로 되어있다.
//			UNDEFINED:	
//				정의되지 않은 상태이다. setPurposeLimitation으로 정의가 가능하며,
//				한번 정의된 PurposeLimitaion은 이후 변경 할 수 없다.
//				UNDEFINED시의 동작은 NOT_CONCERNED와 동일하다.
//
//			NOT_CONCERNED:	
//				고려하지 않겠다고 선언하는 것이다.
//				
//			READ_BY:
//			WRITTEN:
//				이 인자의 용도를 명시해둔다. 모듈개발자 입장에서는 아무런 득이 없고, 
//				Editor프로그램과 사용자UI에 이득이 있다.
//				여기서 주의할 점은, READ_BY, WRITTEN은 어디까지나 주체가 
//				System 혹은 Module이라는 점이다.
//
//			READ_BY_OR_WRITTEN:
//				사용자는 인자에 대한 키와 함께 어떠한 용도로 사용되는지 명시도 요구
//				되어진다.
#pragma once

#include "../NEKeyNameBinder/NEKeyNameBinder.hpp"

namespace NE
{
	class NEArgumentBaseList;

	class NE_DLL NEArgumentBase : public NEKeyNameBinder
	{
	public:
		friend class NEModule;

	public:
		enum Purpose
		{
			UNDEFINED = 0,
			NOT_CONCERNED,
			READ_OR_WRITTEN,
			READ_BY,
			WRITTEN
		};

	public:
		typedef NEArgumentBase ThisClass;
		typedef NEKeyNameBinder SuperClass;

	public:
		NEArgumentBase(NEType::Type type, Purpose limitation = UNDEFINED);
		NEArgumentBase(const ThisClass& rhs);

	public:
		~NEArgumentBase();

	public:
		bool operator==(const NEArgumentBase& source) const;
		bool operator!=(const NEArgumentBase& source) const;

	public:
		NEType::Type getTypeToBeBinded() const;
		bool isValidToBind(const NEObject& to_be_bind) const;
		const NEKey& getValueKey() const;
		NEKey& getValueKey();
		Purpose getPurpose() const { return _purpose; }
		Purpose getPurposeLimitation() const { return _limitation; }
		type_result setPurpose(Purpose new_purpose) {

			type_result result = RESULT_SUCCESS;
			switch(_limitation)
			{
			case READ_BY:
				new_purpose = READ_BY;
				result = RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
				break;

			case WRITTEN:
				new_purpose = WRITTEN;
				result = RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
				break;

			case NOT_CONCERNED:
			case UNDEFINED:
				new_purpose = NOT_CONCERNED;
			}

			_purpose = new_purpose;
			return result;
		}
		type_result setPurposeLimitation(Purpose new_limitation)
		{
			if(_limitation == UNDEFINED)
			{
				_limitation = new_limitation;

				setPurpose(_purpose);

				return RESULT_SUCCESS;
			}

			return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		}

	public:		
		virtual type_result bind();
		virtual NEKey& getDefaultKey() = 0;
		virtual const NEKey& getDefaultKey() const = 0;

	public:
		virtual NEType::Type getType() const;
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		bool isNeedingBinding() const;

	private:
		void _release();
		ThisClass& _assign(const ThisClass& source);

	private:
		NEType::Type	_type_validation;
		Purpose			_purpose, 
						_limitation;
	};
}
