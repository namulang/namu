///	@brief	A kind of @see NETCollector that manages element splitly.
///	@detail	This seems that @see NETVector, but this usually uses when you don't
///			need to concern order among elements.
///			for example, when you call, 
///
///				yourList += yourList
///
///			Next then, yourList's order of the elements are unpredictable.
///			new elements from the rigth hand "yourList" will be inserted to left handed
///			"yourList" from index 0	to "length-1" if it's vacant.
///
///			And, Of cource, this is like a traditional C array, it's far faster and got low
///			performance cost when you don't need not to make it space between elements.
//	---------------------------------------------------------------------------------
//	클래스명:	NETArray
//	설명	:	Array의 형태로 데이터를 관리하는 클래스.
//	관계	:	기반클래스.			NETReservedCollector
//	특성	:	배열의 특성을 그대로 구현한다. 각 엘리먼트는 추가/삽입/삭제의
//				부하가 큰 반면, "검색"에 강하다.//				
//	알고리즘:	만약 포인터를 삽입했을 경우, 해당 포인터로부터 가상복사생성자인 clone
//				을 호출해서 DeepCopy 한다.
//	사용방법:	정의 방법
//					:	템플릿 인자 T의 조건
//							조건 1.	NEObject를 상속해야한다. 
//									NEObject::clone()를 사용하기 때문이다.
//							조건 2. 
//				type_bool pointerUseNewInstance란?
//					:	false일때 T가 포인터일 경우, 포인터가 새로운 인스턴스를 가리키도록
//						하지않고, shallowcopy만을 사용하겠다는 의미다.
//						true일때는 NEPointerList.hpp를 참고하라.
//				기본적으로 NETCollector의 함수를 모두 사용가능하다. (참조 할 것)
//				기본 인터페이스
//					1. push(T*)			:	포인터의 형태로 삽입이 가능하다.
//					2. pushFront(T*)	:	포인터의 형태로 삽입이 가능하다.
//					3. push(NETList&)	:	리스트 전부를 통째로 삽입한다.
//					4. pushFront(NETList&)
/*
				외향(Outside)과 내향(Inside) 타입이 서로 다른 Collector 생성 방법:
					1. 타입이 다른 경우, NETArray은 추상클래스로서 선언된다.
					2. 다음의 함수들은 파생클래스에서 채워야한다.
						1. 복사생성자
						2. virtual release
						3. virtual insert
						3. virtual remove
						4. virtual getElement(index) const
						5. virtual getElement(index)
						6. virtual setElement
						7. virtual clone
						8. virtual find
*/
//	메모	:	
//	히스토리:	2013-01-10	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NETClass/NETClass.inl"
#include "../NETReservedCollector/NETReservedCollector.inl"
#include "../NETIterator/NETIterator.inl"

namespace NE
{
	template <typename T>
	class NETArray : public NETReservedCollector<T>
	{	
		typedef NETArray<T> _This;

		NE_DECLARE_CLASS(_This, NETReservedCollector<T>)

	protected:
		struct Node
		{
			type_bool is_occupied;
			T datum;
		};
		class Iterator : public NETIterator<T>
		{
			NE_DECLARE_CLASS_ONLY(Iterator, NETIterator<T>)

		public:
			Iterator(_This& owner, type_index new_index);

		public:
			type_bool operator==(const This& rhs) const;
			virtual type_bool operator<(const This& rhs) const;
			virtual type_bool operator>(const This& rhs) const;

		public:
			virtual const T& get() const;
			virtual T& get();
			virtual type_bool isEnd() const;
			virtual type_result next(type_index step_for_next);
			virtual type_result back(type_index step_for_back);
			//		NELengthedObject:
			virtual type_index getLength() const;
			//		NEObject:
			virtual void release();
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
			virtual type_result isValid() const;

		public:
			_This& getOwner();
			const _This& getOwner() const;
			type_result setIndex(type_index new_index);
			type_index getIndex() const;

		private:
			NETWeakBinder<_This> _owner;	//	we'll keep track of owner-instance for checking its validness.
			type_index _index;
		};
		class CIterator : public NETCIterator<T>
		{
			NE_DECLARE_CLASS_ONLY(CIterator, NETCIterator<T>)

		public:
			CIterator(const _This& owner, type_index new_index);

		public:
			type_bool operator==(const This& rhs) const;		
			virtual type_bool operator<(const This& rhs) const;
			virtual type_bool operator>(const This& rhs) const;	

		public:
			virtual const T& get() const;
			virtual type_bool isEnd() const;
			virtual type_result next(type_index step_for_next);
			virtual type_result back(type_index step_for_back);
			//		NELengthedObject:
			virtual type_index getLength() const;
			//		NEObject:
			virtual void release();
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
			virtual type_result isValid() const;

		public:
			const _This& getOwner() const;
			type_result setIndex(type_index new_index);
			type_index getIndex() const;

		private:
			NETWeakBinder<const _This> _owner;	//	we'll keep track of owner-instance for checking its validness.
			type_index _index;
		};

	public:
		friend class Iterator;
		friend class CIterator;

		//	생성자:
	public:
		NETArray();
		NETArray(type_count size);
		NETArray(const This& source);
		virtual ~NETArray();

		//	연산자 중첩:
	public:
		const This& operator=(const This& source); 
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;
		const This& operator+=(const This& source);
		This operator+(const This& source) const;

		//	Interfaces:
		//		Virtuals:
	public:
		//		NETReservedCollector:
		virtual type_result resize(type_index new_size);
		virtual type_result create(type_count new_size);		
		//			NETCollector
		virtual NETBinder<NETCIterator<T>> getIterator(type_index index) const;
		virtual NETBinder<NETIterator<T>> getIterator(type_index index);
		///	@brief	insert Element to designated index.
		///	@return	Iterator pointing inserted one.
		///			if there is already element to where you want to insert, this calls
		///			replace the element to pramaeter "source".
		virtual NETBinder<NETIterator<T>> insert(const NETCIterator<T>& where, const T& source);
		virtual NETBinder<NETIterator<T>> insert(const NETCIterator<T>& where, const NETCIterator<T>& from, const NETCIterator<T>& end);
		virtual NETBinder<NETIterator<T>> remove(const NETCIterator<T>& from, const NETCIterator<T>& end);
		//			We're overriding below ones because of optimization: 
		virtual T& getElement(type_index index);
		virtual const T& getElement(type_index index) const;
		//			NEObject:
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;

		//	내부함수:
	private:
		const This& _assign(const This& source);
		type_bool _isValid(const CIterator& iterator) const;
		void _release();

		//	멤버변수:
	protected:
		Node* _data;
	};
}