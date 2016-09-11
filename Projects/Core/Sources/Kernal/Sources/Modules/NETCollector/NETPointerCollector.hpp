#pragma once

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NETCollector<OutsideType*>, template <typename OutsideType>)

	template<typename OutsideType>
	NETCollector<OutsideType*>::NETCollector()
		: NEObject() // 클래스의 경우에는 int에 경우의 생성자를 생성해야 할지도 모른다S
	{
		_release();
	}
	
	
	
	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	NETCollector<OutsideType*>::~NETCollector() 
	{
		_release();
	}		



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	NETCollector<OutsideType*>::NETCollector(const NETCollector<OutsideType*>& source)
		: NEObject(source)
	{
		_assign(source);
	}
	
	
	
	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	const NETCollector<OutsideType*>  &NETCollector<OutsideType*>::operator=(const NETCollector<OutsideType*>& source) 
	{	
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	type_bool NETCollector<OutsideType*>::operator==(const NETCollector<OutsideType*>& source) const 
	{
		if(this == &source) return true;
		if(_length != source._length) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	type_bool NETCollector<OutsideType*>::operator!=(const NETCollector<OutsideType*>& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>	
	type_index	 NETCollector<OutsideType*>::getLength() const 
	{
		return _length;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>	
	void  NETCollector<OutsideType*>::release()   
	{
		return _release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>	
	type_result  NETCollector<OutsideType*>::isValid() const 
	{		
		//	범위 체크:	템플릿클래스에는 Kernal헤더를 놓을 수 없으므로 매크로를
		//				사용할 수 없다. (헤더가 꼬일지도 모른다)
		if(_length < 0) return RESULT_TYPE_WARNING | RESULT_WRONG_BOUNDARY;
		
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	NEBinaryFileSaver &NETCollector<OutsideType*>::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _length;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	NEBinaryFileLoader &NETCollector<OutsideType*>::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _length;
	}



	template <typename OutsideType>
	type_result NETCollector<OutsideType*>::push(const OutsideType& source)
	{
		return push(&source);
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
	template<typename OutsideType>
	const NETCollector<OutsideType*>& NETCollector<OutsideType*>::_assign(const NETCollector<OutsideType*>& source) // 이게 가장 상위 함수. 더이상 기반클래스함수를 호출하지 않는다
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
	template<typename OutsideType>
	void NETCollector<OutsideType*>::_release()
	{
		_length = 0;
	}

	template <typename OutsideType>
	template <typename Functor>
	OutsideType& NE::NETCollector<OutsideType*>::match(Functor functor, type_index& matched_index) const
	{
		matched_index = NE_INDEX_ERROR;

		type_index n=0;
		for(NETIterator<T> e=getIterator(); ! e.isEnd() ;e.next(), n++)
		{
			if(functor(*e))
			{
				matched_index = n;
				return casted;
			}
		}

		OutsideType* nullptr = NE_NULL;
		return *nullptr;
	}

	template <typename OutsideType>
	template <typename Functor>
	const OutsideType& NE::NETCollector<OutsideType*>::match(Functor functor, NE_OUT type_index& matched_index) const
	{
		This* casted = const_cast<This*>(this);

		return casted->match(functor, matched_index);
	}

	template <typename OutsideType>
	type_result NETCollector<OutsideType*>::push(const NETCollector<OutsideType*>& source)
	{
		//	pre:
		if(this == &source) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if(! &source) return RESULT_TYPE_ERROR;

		//	main:
		for(NETIterator<OutsideType*> e; ! e.isEnd() ;e++)
			push(*e);

		return RESULT_SUCCESS;
	}

	template <typename OutsideType>
	const NETIterator<OutsideType*> NETCollector<OutsideType*>::getIterator() const
	{
		return getIterator(0);
	}

	template <typename OutsideType>
	NETIterator<OutsideType*> NETCollector<OutsideType*>::getIterator()
	{
		return getIterator(0);
	}
}