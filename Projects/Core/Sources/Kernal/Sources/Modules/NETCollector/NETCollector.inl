//	---------------------------------------------------------------------------------
//	클래스명:	NETCollector
//	설명	:	데이터를 관리하는 자료구조를 나타낸다.
//	관계	:	기반클래스.	NEObject
//	특성	:	데이터를 관리하는 핵심적인 함수가 가상함수로 되어있기 때문에 쉽게 
//				다형성이 가능하다.
//	알고리즘:	
//	사용방법:	기본 인터페이스
//					1.	getSize()	:	데이터의 최종 크기
//					2.	getLength()	:	데이터의 현재 길이
//					3.	push()		:	데이터를 제일 뒤에 추가
//					4.	pushFront()	:	데이터를 가장 앞에 추가
//					5.	pop()		:	가장 뒤의 데이터를 하나 삭제
//					6.	popFront()	:	맨 앞의 데이터를 하나 삭제
//
//				가상 함수
//					1.	insert()	:	데이터를 임의의 인덱스에 위치에 삽입
//					2.	remove()	:	임의의 인덱스에 위치하는 데이터를 삭제
//					3.	match()		:	주어진 원소와 일치하는 원소를 Collector에서
//										검색. (내부적으로 operator==를 실시한다)
//					4.	getElement():	주어진 인덱스에 해당하는 원소에 접근한다.
//					5.	setElement():	주어진 인덱스와 엘리먼트로 데이터를 대체한다.
//										추가가 아니다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEObject/NEObject.hpp"
#include "../NETClass/NETClass.inl"

namespace NE
{
	template<typename T>
	class NETCollector : public NELengthedObject 
	{
		NE_DECLARE_INTERFACE_ONLY(NETCollector<T>, NELengthedObject)

		//	생성자:
	public:
		NETCollector();
		NETCollector(const NETCollector& source);

		//	소멸자:
	public:
		virtual ~NETCollector();

		//	Operator overloadings:
	public:
		const NETCollector<T>& operator=(const NETCollector<T>& source); 
		type_bool operator==(const NETCollector<T>& source) const;
		type_bool operator!=(const NETCollector<T>& source) const;
		T& operator[](type_index index);
		const T& operator[](type_index index) const;

		//	Inherited:
	public:
		virtual NETBinder<NETCIterator<T>> getIterator(type_index index) const = 0; 
		virtual NETBinder<NETIterator<T>> getIterator(type_index index) = 0;
		virtual NETBinder<NETIterator<T>> insert(const NETCIterator<T>& where, const T& source) = 0;
		virtual NETBinder<NETIterator<T>> insert(const NETCIterator<T>& where, const NETCIterator<T>& from, const NETCIterator<T>& end) = 0;
		virtual type_result remove(NETCIterator<T> from, const NETCIterator<T>& end) = 0;
		virtual T& getElement(type_index index) = 0;
		virtual const T& getElement(type_index index) const = 0;
		//			NELengthedObject:
		virtual type_index getLength() const;
		//			NEObject:
		virtual void release(); 
		virtual type_result isValid() const; 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//	Methods:
	public:
		template <typename F>
		type_result each(F functor);
		template <typename F>
		type_result each(F functor) const;

		NETBinder<NETIterator<T>> insert(type_index where, const T& source);
		NETBinder<NETIterator<T>> insert(type_index where, const This& source);
		type_result remove(type_index where);
		NETBinder<NETIterator<T>> push(const T& source);
		NETBinder<NETIterator<T>> push(const NETCIterator<T>& from, const NETCIterator<T>& end);
		NETBinder<NETIterator<T>> push(const This& source);
		NETBinder<NETIterator<T>> pushFront(const T& source);
		NETBinder<NETIterator<T>> pushFront(const NETCIterator<T>& from, const NETCIterator<T>& end);
		NETBinder<NETIterator<T>> pushFront(const This& source);
		type_result pop();
		NETBinder<NETCIterator<T>> getStartIterator() const;
		NETBinder<NETIterator<T>> getStartIterator();
		NETBinder<NETCIterator<T>> getEndIterator() const;
		NETBinder<NETIterator<T>> getEndIterator();

		//	내부함수:
	private: 
		const NETCollector<T>& _assign(const NETCollector<T>& source);
		void _release();

		//	멤버변수:
	protected:
		type_index _length;
	};
}