//	How were Template hpp/cpp files structured?:
//		All template classes are defined as seperated 2 files. ".inl" for declarations,
//		".hpp" for definitions.
//		and although specialized template class declaration was put into other file, 
//		(usually they are started with "NETPointer--" prefix.) by including non-specialized
//		template file(e.g, NETCollector.hpp / inl), related all other files will 
//		included too.
//	
//	Why do you seperate these?:
//		There are 2 reasons about we've done this. 
//			1) for a convenient of users.
//				generally, we often refer ".hpp" file when we're going to include something.
//				In order for users to do that, declarations of Template class are located to 
//				".inl" file, not ".hpp".
//				So, top of the contents of ".hpp" files of each Template classes,
//				they start with including all other related files.
//	
//			2) to prevent circular reculsive templating.
//				normally, when reculsion happens, usually we used to declare "Forward declaration".
//				But template class's declaration is get stuck with its implements, 
//				We have to divide declaration and implement onto seperated files 
//				to avoid reculsive templating.
#pragma once

#include "../NETClass/NETClass.hpp"
#include "NETCollector.inl"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NETCollector<T>, template<typename T>)

		template<typename T>
	NETCollector<T>::NETCollector()
		: NEObject() // 클래스의 경우에는 int에 경우의 생성자를 생성해야 할지도 모른다S
	{
		_release();
	}

	template<typename T>
	NETCollector<T>::NETCollector(const NETCollector<T>& source)
		: NEObject(source)
	{
		_assign(source);
	}

	template<typename T>
	NETCollector<T>::~NETCollector() 
	{
		_release();
	}		

	template<typename T>
	const NETCollector<T>  &NETCollector<T>::operator=(const NETCollector& source) 
	{	
		return _assign(source);
	}

	template<typename T>
	type_bool NETCollector<T>::operator==(const NETCollector<T>& source) const 
	{
		if(this == &source) return true;
		if(_length != source._length) return false;

		return true;
	}

	template<typename T>
	type_bool NETCollector<T>::operator!=(const NETCollector<T>& source) const
	{
		return !(operator==(source));
	}

	template <typename T>
	T& NETCollector<T>::operator[](type_index index)
	{
		return getElement(index);
	}

	template <typename T>
	const T& NETCollector<T>::operator[](type_index index) const
	{
		return getElement(index);
	}

	template <typename T>
	T& NETCollector<T>::getElement(type_index index)
	{
		NETIterator<T>& e = *getStartIterator();
		e.next(index);

		return e*;
	}

	template <typename T>
	const T& NETCollector<T>::getElement(type_index index) const
	{
		NETCIterator<T>& e = *getStartIterator();
		e.next(index);

		return e*;
	}

	template<typename T>	
	type_index NETCollector<T>::getLength() const 
	{
		return _length;
	}

	template<typename T>	
	void  NETCollector<T>::release()   
	{
		return _release();
	}

	template<typename T>	
	type_result  NETCollector<T>::isValid() const 
	{		
		//	범위 체크:	템플릿클래스에는 Kernal헤더를 놓을 수 없으므로 매크로를
		//				사용할 수 없다. (헤더가 꼬일지도 모른다)
		if(_length < 0) return RESULT_TYPE_WARNING | RESULT_WRONG_BOUNDARY;

		return RESULT_SUCCESS;
	}

	template<typename T>
	NEBinaryFileSaver &NETCollector<T>::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _length;
	}

	template<typename T>
	NEBinaryFileLoader &NETCollector<T>::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _length;
	}

	template <typename T>
	template <typename F>
	type_result NETCollector<T>::each(F functor)
	{
		type_result result = RESULT_SUCCESS;

		for(NETIterator<T>& e=*getStartIterator(); ! e.isEnd() ;e++)
			if(NEResult::isActionAborted(result |= functor(*e)))
				break;

		return result;
	}

	template <typename T>
	template <typename F>
	type_result NETCollector<T>::each(F functor) const
	{
		type_result result = RESULT_SUCCESS;

		for(NETCIterator<T>& e=*getStartIterator(); ! e.isEnd() ;e++)
			if(NEResult::isActionAborted(result |= functor(*e)))
				break;

		return result;
	}

	template<typename T>
	type_index NETCollector<T>::insert(type_index where, const T& source)
	{
		return insert(getIterator(where), source);
	}

	template<typename T>
	type_index NETCollector<T>::insert(type_index where, const This& source)
	{
		return insert(getIterator(where), source.getStartIterator(), source.getEndIterator());
	}

	template<typename T>
	NETBinder<NETIterator<T>> NETCollector<T>::remove(type_index where)
	{
		return remove(getIterator(where));
	}

	template<typename T>
	type_index NETCollector<T>::push(const T& source)
	{
		return insert(getEndIterator(), source);
	}

	template<typename T>
	type_index NETCollector<T>::push(const NETCIterator<T>& from, const NETCIterator<T>& end)
	{
		return insert(getEndIterator(), from, end);
	}

	template<typename T>
	type_index NETCollector<T>::push(const This& source)
	{
		return insert(getEndIterator(), source.getStartIterator(), source.getEndIterator());
	}

	template<typename T>
	type_index NETCollector<T>::pushFront(const T& source)
	{
		return insert(getStartIterator(), source);
	}

	template<typename T>
	type_index NETCollector<T>::pushFront(const NETCIterator<T>& from, const NETCIterator<T>& end)
	{
		return insert(getStartIterator(), from, end);
	}

	template<typename T>
	type_index NETCollector<T>::pushFront(const This& source)
	{
		return insert(getStartIterator(), source.getStartIterator(), source.getEndIterator());
	}

	template<typename T>
	NETBinder<NETIterator<T>> NETCollector<T>::pop()
	{
		return remove(getIterator(getLengthLastIndex()));
	}

	template <typename T>
	NETBinder<NETIterator<T>> NETCollector<T>::popFront()
	{
		return remove(getStartIterator());
	}

	template <typename T>
	NETBinder<NETCIterator<T>> NETCollector<T>::getStartIterator() const
	{
		return getIterator(0);
	}

	template <typename T>
	NETBinder<NETIterator<T>> NETCollector<T>::getStartIterator()
	{
		return getIterator(0);
	}

	template <typename T>
	NETBinder<NETCIterator<T>> NETCollector<T>::getEndIterator() const
	{
		return getIterator(getLength());
	}

	template <typename T>
	NETBinder<NETIterator<T>> NETCollector<T>::getEndIterator()
	{
		return getIterator(getLength());
	}

	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	assign은 현재 단계에서의 멤버변수의 할당만 담당한다.
	//	거슬러올라가면서 함수를 호출하는 건 복사생성자와 operator=에서 사용한다.
	//	멤버변수가 있다 -> assign 있음
	//	인스턴스 생성가능 -> 복사생성자, operator=에서 assign 호출
	template<typename T>
	const NETCollector<T>& NETCollector<T>::_assign(const NETCollector<T>& source) // 이게 가장 상위 함수. 더이상 기반클래스함수를 호출하지 않는다
	{			
		if(this == &source) return *this;

		_length = source._length;

		return *this; 
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename T>
	void NETCollector<T>::_release()
	{
		_length = 0;
	}
}