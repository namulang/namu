#pragma once

//	headers:
#include "../NETClass/NETClass.hpp"
#include "../NETReservedCollector/NETReservedCollector.hpp"
//		this includes all related headers. please refer NETCollector.hpp about 
//		this issue.
#include "NETVector.inl"	

namespace NE
{
#define _TEMPLATE	template <typename T>
#define _OWNERNAME	NETVector<T>	
#define _NAME		_OWNERNAME##::Iterator

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	_NAME::Iterator(_This& owner, type_index new_index)
		: Super(), _owner(owner), _index(new_index)
	{

	}			

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		//	When these binders are designating same object each other,
		//	we'll return true.
		return	_owner.get() == rhs._owner.get()	&&
			_index == rhs._index				;

	}

	_TEMPLATE
	type_bool _NAME::operator<(const This& rhs) const
	{
		return	_index < rhs._index;
	}

	_TEMPLATE
	type_bool _NAME::operator>(const This& rhs) const
	{
		return	_index > rhs._index;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		const T* nullpointer = NE_NULL;
		if( ! _owner.isBinded())
			return *nullpointer;		

		return _owner->getElement(_index);
	}

	_TEMPLATE
	T& _NAME::get()
	{
		const T* nullpointer = NE_NULL;
		if( ! _owner.isBinded())
			return *nullpointer;		

		return _owner->getElement(_index);
	}

	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		if( ! _owner.isBinded())
			//	Oops. Now, we got trouble.
			return true;

		return	_index >= _owner->getLength()	||
			_index < 0						;
	}

	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		_index += step_for_next;
		if(isEnd())
			_index = getLength();

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		_index -= step_for_back;
		if(isEnd())
			_index = -1;

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_index _NAME::getLength() const
	{
		return _owner.isBinded() ? _owner->getLength() : 0;
	}

	_TEMPLATE
	void _NAME::release()
	{
		_owner.release();
		_index = NE_INDEX_ERROR;
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _owner << _index;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _owner >> _index;
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if( ! _owner.isBinded()) return RESULT_TYPE_ERROR;
		if( isEnd()) return RESULT_TYPE_WARNING;		

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	_OWNERNAME& _NAME::getOwner() const
	{
		return _owner;
	}

	_TEMPLATE
	const _OWNERNAME& _NAME::getOwner() const
	{
		return _owner;
	}

	_TEMPLATE
	type_result _NAME::setIndex(type_index new_index) const
	{
		_node = new_index;

		return isValid();
	}

	_TEMPLATE
	type_index _NAME::getIndex() const
	{
		return _index;
	}

#undef _NAME	
#define _NAME	_OWNERNAME##::CIterator

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	_NAME::CIterator(const _This& owner, type_index new_index)
		: Super(), _owner(owner), _index(new_index)
	{

	}			

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		//	When these binders are designating same object each other,
		//	we'll return true.
		return	_owner.get() == rhs._owner.get()	&&
			_index == rhs._index				;

	}

	_TEMPLATE
	type_bool _NAME::operator<(const This& rhs) const
	{
		return	_index < rhs._index;
	}

	_TEMPLATE
	type_bool _NAME::operator>(const This& rhs) const
	{
		return	_index > rhs._index;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		const T* nullpointer = NE_NULL;
		if( ! _owner.isBinded())
			return *nullpointer;		

		return _owner->getElement(_index);
	}

	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		if( ! _owner.isBinded())
			//	Oops. Now, we got trouble.
			return true;

		return	_index >= _owner->getLength()	||
			_index < 0						;
	}

	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		_index += step_for_next;
		if(isEnd())
			_index = getLength();

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		_index -= step_for_back;
		if(isEnd())
			_index = -1;

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_index _NAME::getLength() const
	{
		return _owner.isBinded() ? _owner->getLength() : 0;
	}

	_TEMPLATE
	void _NAME::release()
	{
		_owner.release();
		_index = NE_INDEX_ERROR;
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _owner << _index;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _owner >> _index;
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if( ! _owner.isBinded()) return RESULT_TYPE_ERROR;
		if( isEnd()) return RESULT_TYPE_WARNING;		

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	const _OWNERNAME& _NAME::getOwner() const
	{
		return _owner;
	}

	_TEMPLATE
	type_result _NAME::setIndex(type_index new_index) const
	{
		_node = new_index;

		return isValid();
	}

	_TEMPLATE
	type_index _NAME::getIndex() const
	{
		return _index;
	}

#undef _NAME

	NE_DEFINE_INTERFACE_ONLY_2(_OWNERNAME, _TEMPLATE)

	_TEMPLATE
	_OWNERNAME::NETVector()
		: Super(), _data(NE_NULL)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_OWNERNAME::NETVector(type_count size)
		: Super(size), _data(NE_NULL)
	{
		create(size);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_OWNERNAME::NETVector(const _OWNERNAME& source)
		: Super(), _data(NE_NULL)
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_OWNERNAME::~NETVector()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _OWNERNAME& _OWNERNAME::operator=(const This& source)
	{
		if(this == &rhs) return *this;

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	원소만 같으 m면 true인건지, 사이즈까지 같아야 하는지에 대한 모호성이 
	//				있기때문에 그다지 추천하지 않는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	_TEMPLATE
	type_bool  _OWNERNAME::operator==(const This& source) const
	{
		if(this == &source) return true;
		if( ! Super::operator==(source)) return false;

		return isEqualElement(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _OWNERNAME::operator!=(const This& source) const
	{
		return ! operator==(source);
	}

	_TEMPLATE
	_OWNERNAME _OWNERNAME::operator+(const This& source) const
	{
		//	main:
		This buffer(source._length + _length);
		buffer.push(*this);
		buffer.push(source);

		// post:
		return buffer;
	}

	_TEMPLATE
	_OWNERNAME& _OWNERNAME::operator+=(const This& source)
	{	
		push(source);	//	resize automatically.

		return *this;
	}

	_TEMPLATE
	T& _OWNERNAME::getElement(type_index index) 
	{	
		//	pre:
		//		널 레퍼런스:
		T* null_pointer = NE_NULL;
		//		파라메터 검사:
		if(index < 0) return *null_pointer;
		if(index > getLengthLastIndex()) return *null_pointer;

		//	post:
		return _data[index];
	}

	_TEMPLATE
	const T& _OWNERNAME::getElement(type_index index) const 
	{	
		//	pre:
		//		널 레퍼런스:
		const T* null_pointer = NE_NULL;
		//		파라메터검사: 
		if(index < 0) return *null_pointer;
		if(index > getLengthLastIndex()) return *null_pointer;

		//	post:
		return _data[index];
	}

	_TEMPLATE
	NETBinder<NETIterator<T>> _OWNERNAME::insert(const NETCIterator<T>& where, const T& source) 
	{
		//	pre:
		NETBinder<NETIterator<T>> to_return;
		//		parameter checking:
		CIterator& wh = cast<CIterator>(where);
		if( ! _isValid(wh)	||
			! &source		)
			return to_return;
		//		resizing:
		if(_length >= _size) resize(_size * 2 + 1);


		//	main:
		//		extracting index:
		//			by passing wh.isValid() statement, it's gurranted that index from 
		//			wh is between always 0 and length.
		type_index index = wh.getIndex();
		for(int n=getLengthLastIndex(); n >= index ;n--)
			_data[n+1] = _data[n];


		//	post:
		//		Inserting:
		//			now e is pointing to same instance like where.
		_data[index] = source;
		_length++;
		//		Packaging the return:
		to_return.bind( *(new Iterator(*this, index)) );
		return to_return;
	}

	
	_TEMPLATE
	NETBinder<NETIterator<T>> _OWNERNAME::remove(const NETCIterator<T>& from, const NETCIterator<T>& end) 
	{
		//	pre:
		//		파라메터검사:
		NETBinder<NETIterator<T>> to_return;
		CIterator& fr = cast<CIterator>(from),
				 & ed = cast<CIterator>(end);
		if( ! _isValid(fr)	||
			! _isValid(ed)	||
			from > end		)	//	parameter reversed check.
			return to_return;


		//	main:
		//		Element realignment:
		//			move forward each elements.
		type_index	begin_n = fr.getIndex(),
		//		Please be advised this:
		//			in this end_n is excluded for removing.
		//			For example, let us assume that begin_n=2 and end_n=3.
		//			if so, the element removed actually is just 1. [2] element.
					end_n = ed.getIndex();
		//			count length to remove:
		type_count	length_to_remove = end_n - begin_n;
		//			in this procedure, what they want to remove is so does it by NETBinder.
		for(type_index n = begin_n; n < begin_n + length_to_remove ;n++)
			_data[n] = _data[n + length_to_remove];


		//	post:
		//		길이 감소:
		_length -= length_to_remove;
		return index;
	}

	_TEMPLATE 
	type_result _OWNERNAME::isValid() const  
	{
		//	상위 클래스의 valid 체크:
		type_result result = NETReservedCollector<T>::isValid();
		if( NEResult::hasError(result)) return result;
		//	멤버변수의 valid 체크:
		if(	_size > 0 && ! _data) return RESULT_TYPE_WARNING | RESULT_OUT_OF_MEMORY;
		//	Element checking:
		result = each([](const T& elem) {
			type_result result = elem.isValid();
			if(NEResult::hasError(result))
				return RESULT_ABORT_ACTION | result;

			return RESULT_SUCCESS;
		});
		if(	NEResult::hasError(result)) return result;


		return RESULT_SUCCESS;
	}			



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	void  _OWNERNAME::release()  
	{		
		_release();
		/*
			의도적인 역순 처리:
				여기에서는 _release와 상위클래스의 release를 호출하는 순서가 뒤바뀌어야 한다.
		*/

		return NETReservedCollector<T>::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileSaver  &_OWNERNAME::serialize(NEBinaryFileSaver& saver) const 
	{			
		//	pre:		
		Super::serialize(saver);


		//	main:
		//		실제 데이터 저장:
		for(type_index n=0; n < _length ;n++)
			saver << _data[n];


		//	post:
		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileLoader& _OWNERNAME::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		//		길이를 0으로 만드는 이유:
		//			create에서 release를 호출하고, NETVector<T, Q> 는 release에서 
		//			while(getLength()) pop()을 호출해야 하기 때문이다.
		//			create에서 release를 호출하는 것은 정당하고, release에서는 NETVector<T, Q>
		//			의 특성상 하위 클래스의 remove가 자동으로 호출되어야 하므로 역시 정당하다.
		//			serialize에서는 상위클래스의 serialize를 호출하지 않는 방법도 존재하나, 호환성을 
		//			위해서 생각해보면 상위클래스의 serialize함수에는 차후 길이 정보이외에도 다른 정보가
		//			있을 수 있다.
		//			따라서 release에서 영향을 받는 length 함수를 사전에 0으로 초기화 하는 것으로
		//			대처하는 것이 가장 효과적이라 볼 수 있다.
		type_index previous_length = getLength();
		Super::serialize(loader);
		

		//	main:
		//		메모리 버퍼공간 생성:
		//			길이 정보 저장:	create에서 초기화가 되버린다.
		type_index new_length = getLength();
		//			길이정보를 serialize 이전으로 되돌리기:
		//				create에서 호출하는 release와의 충돌을 막기 위해서다.
		_length = previous_length;
		create(getSize());
		//		데이터 로드:
		for(type_index n=0; n < new_length ;n++)
		{
			T buffer;
			loader >> buffer;
			_insert(getLength(), buffer);
		}



		//	post:
		return loader;
	}

	_TEMPLATE
	type_result _OWNERNAME::create(type_count size)
	{
		release();

		if(size > 0)
		{
			//	보통, T가 primitive일경우에, 0으로 대입을 해야한다. 이걸 배열로 표현하면
			//		new T[size] = {0, }; 
			//	가 된다는 건 알고있다.
			//	그러나 T가 클래스일경우에는, 위의 코드에서 int 생성자가 호출된다. 즉, 쓸데없는 int생성자를 만들지 않으면
			//	클래스를 이 템플릿클래스에 넣을 수 없다.
			//	그러나, new int(); 가 0으로 초기화가 된다는 사실에서 착안,
			//	밑의 코드는, T가 클래스이건, primitive이건 같은 생성자를 호출하게 만들어주는 단 하나의 코드다.			
			_data = new T[size](); // **주의**	T가 클래스의 경우, 기본생성자()가 필요하다.		

			_size = size;
			_length = 0;
		}

		return RESULT_SUCCESS;
	}	

	_TEMPLATE
	type_result _OWNERNAME::resize(type_count size) // 가지고있는 데이터는 보존한채 크기만 변경한다.
	{
		//	pre:
		if(size < 0) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;

		//	main:
		type_count new_length = size < getLength() ? size : getLength();
		This copied(*this); // use operator=
		create(size); // size도 내부에서 세팅됨.
		push(copied.getFirstIterator(), copied.getIterator(new_length-1));

		//	post:
		return RESULT_SUCCESS;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _OWNERNAME& _OWNERNAME::_assign(const _OWNERNAME& source)
	{	
		if(this == &source) return *this;

		create(source._size);
		push(source);
		return *this;
	}

	_TEMPLATE
	type_bool _OWNERNAME::_isValid(const CIterator& iterator) const
	{
		return	&iterator									&&	
				! NEResult::hasError(iterator.isValid())	&&
				iterator.getOwner() == this					;
	}

	_TEMPLATE
	void  _OWNERNAME::_release() 
	{	
		if(_data)
			delete [] _data;
		_data = NE_NULL;
	}

#undef _OWNERNAME
#undef _TEMPLATE
}