#pragma once

#include "../NETReservedCollector/NETReservedCollector.hpp"
#include "NETArray.inl"

namespace NE
{
#define _TEMPLATE	template <typename T>
#define _OWNERNAME	NETArray<T>
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
		if(NEResult::hasError(isValid()))	goto FAILED;

		Node* nodes = _owner->_data;

		for(; step_for_next > 0 ;step_for_next--)
		{
			do
			{
				_index++;
				//	Left Nodes:	Node isn't element.
				type_count left_nodes = getSize() - _index;
				if(	step_for_next > left_nodes	||
					isEnd()						)
				{
					_index = getLength();
					return RESULT_ABORT_ACTION | RESULT_TYPE_WARNING;
				}
			} while( ! nodes[_index].is_occupied);
		}
		
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		if(NEResult::hasError(isValid()))	goto FAILED;

		Node* nodes = _owner->_data;

		for(; step_for_next > 0 ;step_for_next--)
		{
			do
			{
				_index--;
				//	Left Nodes:	Node isn't element.
				type_count left_nodes = _index+1;
				if(	step_for_next > left_nodes	||
					isEnd()						)
				{
					_index = NE_INDEX_ERROR;	//	this means "StartIterater".
					return RESULT_ABORT_ACTION | RESULT_TYPE_WARNING;
				}
			} while( ! nodes[_index].is_occupied);
		}

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
		if(NEResult::hasError(isValid()))	goto FAILED;

		Node* nodes = _owner->_data;

		for(; step_for_next > 0 ;step_for_next--)
		{
			do
			{
				_index++;
				//	Left Nodes:	Node isn't element.
				type_count left_nodes = getSize() - _index;
				if(	step_for_next > left_nodes	||
					isEnd()						)
				{
					_index = getLength();
					return RESULT_ABORT_ACTION | RESULT_TYPE_WARNING;
				}
			} while( ! nodes[_index].is_occupied);
		}

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		if(NEResult::hasError(isValid()))	goto FAILED;

		Node* nodes = _owner->_data;

		for(; step_for_next > 0 ;step_for_next--)
		{
			do
			{
				_index--;
				//	Left Nodes:	Node isn't element.
				type_count left_nodes = _index+1;
				if(	step_for_next > left_nodes	||
					isEnd()						)
				{
					_index = NE_INDEX_ERROR;	//	this means "StartIterater".
					return RESULT_ABORT_ACTION | RESULT_TYPE_WARNING;
				}
			} while( ! nodes[_index].is_occupied);
		}

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
	_OWNERNAME::NETArray()
		: Super(), _data(NE_NULL)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_OWNERNAME::NETArray(type_count size)
		: Super(size), _data(NE_NULL)
	{
		create(size);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_OWNERNAME::NETArray(const This& source)
		: Super(), _data(NE_NULL)
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_OWNERNAME::~NETArray()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _OWNERNAME& _OWNERNAME::operator=(const This& source)
	{
		return _assign(source);
	}

	//	---------------------------------------------------------------------------------
	//	설명	:	원소만 같으면 true인건지, 사이즈까지 같아야 하는지에 대한 모호성이 
	//				있기때문에 그다지 추천하지 않는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	_TEMPLATE
	type_bool _OWNERNAME::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(Super::operator==(source) == false) return false;

		return isEqualElement(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool _OWNERNAME::operator!=(const This& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _OWNERNAME& _OWNERNAME::operator+=(const This& source)
	{
		if(this == &source)
		{
			This copyied(*this);
			push(copyied);
		}
		else
			push(source);

		return *this;
	}

	_TEMPLATE
	_OWNERNAME _OWNERNAME::operator+(const This& source) const
	{
		//	pre:
		//		파라메터 검사:
		if(source._length <= 0)	return This(*this);



		//	main:
		This buffer(source._length + _length);
		buffer.push(*this);
		buffer.push(source);



		// post:
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	T& _OWNERNAME::getElement(type_index index) 
	{	
		//	pre:
		//		널 레퍼런스:
		T* null_pointer = NE_NULL;
		//		파라메터 검사:
		if(index < 0) return *null_pointer;
		if(index > getSizeLastIndex()) return *null_pointer;

		//	post:
		Node& node = _data[index];
		return ! node.is_occupied ? *null_pointer : node.datum;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const T& _OWNERNAME::getElement(type_index index) const 
	{	
		//	pre:
		//		널 레퍼런스:
		const T* null_pointer = NE_NULL;
		//		파라메터검사: 
		if(index < 0) return *null_pointer;
		if(index > getSizeLastIndex()) return *null_pointer;

		//	post:
		const Node& node = _data[index];
		return ! node.is_occupied ? *null_pointer : node.datum;
	}

	_TEMPLATE
	NETBinder<NETIterator<T>> _OWNERNAME::insert(const NETCIterator<T>& where, const T& source)
	{
		//	pre:
		NETBinder<NETIterator<T>> to_return;
		CIterator& wh = cast<CIterator>(where);
		//		parameter checking:
		if( ! _isValid(wh)	||
			! &source		) 
			return to_return;
		//		current state checking:
		if(_length >= _size) return to_return;		
		

		//	main:
		//		packaging return:
		type_index index = wh.getIndex();
		Iterator& e = *(new Iterator(*this, index));
		to_return.bind(e);
		//		replacement checking:
		//			if there is element placed already, we'll find another vacant.
		//			in this precedure, we may reach the end of inner array, _data.
		//			Then, we keep searching once again from the front of it.
		if(*e)
		{	
			type_bool once_arounded = false;
			while((++e).isEnd())
			{
				if(once_arounded++)
					return to_return;
				
				e.setIndex(0);
			}
			//		Founded:	iterator e has been updated.
		}
		//		proclaim occupying:
		//			Why do we do this first?:
		//				Sometimes it happen to call NETArray::insert() again by source->clone()
		//				while on inserting this.
		//				So, if we don't occupy place first, eventually the later cloned instance
		//				tries to be inserted at same index like the former.
		//				And for sure, this cracks the job.
		Node& node = *e;
		node.is_occupied = true;		
		node.datum = source;
		//		길이 증가:
		_length++;

		
		//	post:
		return to_return;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_index _OWNERNAME::remove(type_index index) 
	{
		//	pre:
		NETBinder<NETIterator<T>> to_return;
		CIterator& wh = cast<CIterator>(where);
		//		parameter checking:
		if( ! _isValid(wh)	||
			! &source		) 
			return to_return;
		//		current state checking:
		if(_length >= _size) return to_return;		
		type_index index = wh.getIndex();
		if( ! _data[index].is_occupied)
			return to_return;

		
		//	main:
		//		return occupied:
		//			We don't need to set 0 what we'll return.
		_data[index].is_occupied = false;


		//	post:
		_length--;
		to_return.bind( *(new Iterator(*this, index)) );
		return to_return;
	}

	_TEMPLATE 
	type_result _OWNERNAME::isValid() const  
	{
		//	상위 클래스의 valid 체크:
		type_result result = Super::isValid();		
		if(NEResult::hasError(result) == true) return result;
		//	멤버변수의 valid 체크:
		if(	_size > 0 && ! _data) return RESULT_TYPE_WARNING | RESULT_OUT_OF_MEMORY;
		if( _size < _length) return RESULT_TYPE_WARNING;
		//	checks realdata and length:
		type_count n=0;
		each([&n](const T&){ 
			n++;
			return RESULT_SUCCESS;
		});
		if(n != _length) return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}			



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	void  _OWNERNAME::release()  
	{		
		_release();
		/*
			의도적인 역순 처리:
				여기에서는 _release와 상위클래스의 release를 호출하는 순서가 뒤바뀌어야 한다.
		*/

		return Super::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileSaver  &_OWNERNAME::serialize(NEBinaryFileSaver& saver) const 
	{			
		//	pre:
		NETReservedCollector::serialize(saver);		

		for(type_index n=0; n < getSize() ;n++)
		{
			Node& node = _data[n];
			saver << node.is_occupied;
			
			if(node.is_occupied)
				saver << node.datum;
		}

		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileLoader& _OWNERNAME::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		This::release();
		NETReservedCollector::serialize(loader);		

		//	main:
		create(_size);

		for(type_index n=0; n < getSize() ;n++)
		{
			Node& node = _data[n];
			loader >> node.is_occupied;

			if(node.is_occupied)
				loader >> node.datum;
		}

		return loader;
	}

	_TEMPLATE
	type_result _OWNERNAME::resize(type_count size) // 가지고있는 데이터는 보존한채 크기만 변경한다.
	{
		//	pre:
		if(size < 0) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;



		//	main:
		This copied(*this); // use operator=
		create(size); // size도 내부에서 세팅됨.
		push(copied);

		//	post:
		return RESULT_SUCCESS;
	}


	//	---------------------------------------------------------------------------------
	//	설명	:	지정한 크기만큼의 메모리 공간을 할당한다.
	//				이전에 존재하던 데이터는 모두 초기화되어서 메모리에서 해제 된다.
	//	동작조건:
	//	메모	:	만약 데이터를 유지한 채 크기를 조절하고 싶다면 resize를 사용하라.
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
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
			_data = new T[_size = size](); // **주의**	T가 클래스의 경우, 기본생성자()가 필요하다.
			_length = 0;
		}

		return RESULT_SUCCESS;
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _OWNERNAME& _OWNERNAME::_assign(const This& source)
	{	
		//	pre:
		if(this == &source) return *this;

		create(source._size);
		push(source);

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	void  _OWNERNAME::_release() 
	{	
		if(_data)
			delete [] _data;
		_data = NE_NULL;
	}
}