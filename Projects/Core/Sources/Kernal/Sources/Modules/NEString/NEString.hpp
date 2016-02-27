//	---------------------------------------------------------------------------------
//	클래스명:	NEString
//	설명	:	NEArrayTemplate를 통해서 구현된, 문자열 클래스.
//	관계	:	기반클래스.		NECharSet
//				외부라이브러리.	tchar.h
//	특성	:	형변환에 CRT를 사용하고 있다.
//	알고리즘:	NEArrayTemplate를 참고하라.
//	사용방법:	기본적인 인터페이스는 NEArrayTemplate를 참고하라.
//				추가 인터페이스
//					1. toInt()			:	문자열을 int형으로 변환한다. (_tstoi 사용)
//					2. toDouble()		:	문자열을 double로 변환한다.	(_tstof 사용)
//					3. toCHARPointer()	:	문자열을 LPTSTR로 변환한다.
//	메모	:	형변환이 많으면 모호성의 오류가 발생하기 때문에 대부분의 형변환은 
//				NEString에 위치하고 있다.
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

#include "../NECharSet/NECharSet.hpp"
#include "../NEWCharSet/NEWCharSet.hpp"
#include "../NEIntSet/NEIntSet.hpp"

namespace NE
{
	class NEWString;
	class NEString;
	class NEStringSet;

	class NE_DLL NEString : public NECharSet
	{
		//	생성자:
	public:
		NEString();		
		NEString(LPCSTR source);
		NEString(LPCWSTR source);
		NEString(const NEString& source);
		NEString(const NECharSet& source);
		NEString(const NEWString& source);
		NEString(const NEWCharSet& source);
		NEString(const type_int data);
		NEString(const type_uint data);
		NEString(const type_double data);
		NEString(const type_char data);
		NEString(const type_uchar data);
		NEString(const type_wchar data);
		NEString(const type_bool data);
		NEString(const type_int64 data);
		NEString(const type_uint64 data);

		//	소멸자:
	public:
		virtual ~NEString();

	public:
		const NEString& operator=(const NEString& source);
		bool operator==(const NEString& source) const;
		bool operator!=(const NEString& source) const;
		NEString operator+(const NEString& source) const;
		const NEString& operator+=(const NEString& source);

		//	인터페이스:
		//		상속:
		//			NEObject:
	public:
		virtual NEType::Type getType() const;
		virtual type_result isValid() const; 
		virtual NEObject& clone() const;

		//		고유 인터페이스:
	public:
		using NECharSet::find;
		NEIntSet find(const NEString& sample) const;
		type_result split(const NEString& delimiter, NE_OUT NEStringSet& buffer_from_outside) const;
		NEString extract(type_index start_index, type_index end_index) const;
		int toInt() const;
		double toDouble() const;
		bool toBoolean() const;
		char* toCharPointer();
		const char* const toCharPointer() const;
		type_result setLowerCase();
		NEString toLowerCase() const;
		type_result setUpperCase();
		NEString  toUpperCase() const;
		void from(const type_int data);
		void from(LPCSTR data);
		void from(LPCWSTR data);
		void from(const type_double data);
		void from(const type_bool data);
		void from(const type_uint data);
		void from(const type_uchar data);
		void from(const type_wchar data);
		void from(const type_char data);
		void from(const type_int64 data);
		void from(const type_uint64 data);

	private:
		void _convertString(LPCWSTR source);
		const NEString& _assign(LPCSTR source);		

	public:
		friend NEString NE_DLL operator+(LPCSTR source1, const NEString& source2);
	};

}
