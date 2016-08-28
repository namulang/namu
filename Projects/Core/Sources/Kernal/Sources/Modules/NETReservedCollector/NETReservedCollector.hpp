#pragma once

#include "../NETCollector/NETCollector.hpp"
#include "NETReservedCollector.inl"
#include "NETPointerReservedCollector.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NETReservedCollector<OutsideType>, template <typename OutsideType>)

	template<typename OutsideType>
	NETReservedCollector<OutsideType>::NETReservedCollector()
		: NETCollector() // 클래스의 경우에는 int에 경우의 생성자를 생성해야 할지도 모른다S
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
	NETReservedCollector<OutsideType>::NETReservedCollector(type_index size)
		: NETCollector()
	{
		_release();
		_size = size;
	}	



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	NETReservedCollector<OutsideType>::~NETReservedCollector() 
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
	NETReservedCollector<OutsideType>::NETReservedCollector(const NETReservedCollector<OutsideType>& source)
		: NETCollector(source)
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
	const NETReservedCollector<OutsideType>  &NETReservedCollector<OutsideType>::operator=(const NETReservedCollector& source) 
	{	
		NETCollector<OutsideType>::operator=(source);

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	type_bool NETReservedCollector<OutsideType>::operator==(const NETReservedCollector<OutsideType>& source) const 
	{
		if(this == &source) return true;
		if(NETCollector<OutsideType>::operator!=(source)) return false;

		if(_size != source._size) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	type_bool NETReservedCollector<OutsideType>::operator!=(const NETReservedCollector<OutsideType>& source) const
	{
		return !(operator==(source));
	}


	
	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	변수가 존재한다면 복사생성자를 구현한다. 구현한 복사생성자는 파생클래스에서 호출됨
	template<typename OutsideType>	
	type_index	 NETReservedCollector<OutsideType>::getSize() const 
	{
		return _size;
	}	



	
	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>	
	type_index	 NETReservedCollector<OutsideType>::getSizeLastIndex() const 
	{
		return _size-1;
	}
	


	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>	
	void  NETReservedCollector<OutsideType>::release()   
	{
		NETCollector<OutsideType>::release();

		return _release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>	
	type_result  NETReservedCollector<OutsideType>::isValid() const 
	{		
		//	범위 체크:	템플릿클래스에는 Kernal헤더를 놓을 수 없으므로 매크로를
		//				사용할 수 없다. (헤더가 꼬일지도 모른다)
		type_result result = NETCollector<OutsideType>::isValid();
		if(NEResult::hasError(result)) return result;
		if(_size < 0) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY;
		if(_size < getLength()) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	NEBinaryFileSaver &NETReservedCollector<OutsideType>::serialize(NEBinaryFileSaver& saver) const
	{
		NETCollector<OutsideType>::serialize(saver);

		return saver << _size;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	NEBinaryFileLoader &NETReservedCollector<OutsideType>::serialize(NEBinaryFileLoader& loader)
	{
		NETCollector<OutsideType>::serialize(loader);

		return loader >> _size;
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
	const NETReservedCollector<OutsideType>& NETReservedCollector<OutsideType>::_assign(const NETReservedCollector<OutsideType>& source) // 이게 가장 상위 함수. 더이상 기반클래스함수를 호출하지 않는다
	{			
		if(this == &source) return *this;

		_size = source._size;
		
		return *this; 
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template<typename OutsideType>
	void NETReservedCollector<OutsideType>::_release()
	{
		_size = 0;
	}
}