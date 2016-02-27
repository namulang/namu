//	---------------------------------------------------------------------------------
//	클래스명:	NEKey
//	설명	:	모듈안에 존재하는 외부에 공개되는 변수인 "키" 를 나타낸다.
//	관계	:	기반클래스.	NEObject
//	특성	:	추상클래스
//	알고리즘:	getType()으로 키의 종류를 판단하고 연산을 수행한다.
//	사용방법:	다른 키와 +, = 연산을 수행할 수 있다.
//					+	:	_extend(NEKey*)
//					=	:	_assign(NEKey*)
//	메모	:	
//	히스토리:	2011-06-05	이태훈	개발 완료.
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEUnit/NEUnit.hpp"
#include "../NETString/NETString.hpp"

namespace NE
{
	class NE_DLL NEKey : public NEUnit
	{
	public:
		friend class NEKeyCodeSet;

		//	생성자:
	public:		
		NEKey(const NETString& new_keyname = "");
		NEKey(const NEKey& source);

		//	소멸자:
	public:
		virtual ~NEKey();

		//	연산자 중첩:
	public:
		NEKey& operator=(const NEKey& source);
		NEKey& operator+=(const NEKey& source);
		NEKey& operator-=(const NEKey& source);
		NEKey& operator*=(const NEKey& source);
		NEKey& operator/=(const NEKey& source);
		bool operator==(const NEKey& source) const;
		bool operator!=(const NEKey& source) const;
		bool operator<(const NEKey& source) const;
		bool operator<=(const NEKey& source) const;
		bool operator>(const NEKey& source) const;
		bool operator>=(const NEKey& source) const;
		NEKey& operator++(int);
		NEKey& operator--(int);

	public:
		NETString& getName();
		const NETString& getName() const;
		NEKeyCodeSet& getOwner();
		const NEKeyCodeSet& getOwner() const;

	public:
		virtual void releaseValue() = 0;

	public:
		virtual type_result increase();
		virtual type_result decrease();
		virtual type_result assign(const NEKey& source);
		virtual type_result add(NEKey& result, const NEKey& operand2) const;
		virtual type_result multiply(NEKey& result, const NEKey& operand2) const;
		virtual type_result makeReciprocal();
		virtual type_result negate();
		virtual bool isEqualTo(const NEKey& source) const;
		virtual bool isLower(const NEKey& source) const;

	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

	public:
		type_result divide(NEKey& result, const NEKey& operand2) const;
		type_result sub(NEKey& result, const NEKey& operand2) const;

	private:
		NETString _name;
		NEKeyCodeSet* _owner;
	};
}