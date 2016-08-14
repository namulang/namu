#pragma once

#include "NETKey.inl"

namespace NE
{
	template <typename T>
	NETKey<T>::NETKey(const T& source, const NETString& keyname)
		: Super(keyname), _value(source)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETKey<T>::NETKey(const This& source)		
		: Super(source)
	{
		_value = source._value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETKey<T>::NETKey(const NEKey& source)
		: Super(source.getName())
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETKey<T>::~NETKey() 
	{
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	const NETKey<T>  & NETKey<T>::operator=(const This& source)
	{
		if(this == &source) return *this;

		Super::operator=(source);
		_value = source._value;
		return *this;
	}


	template <typename T>
	T& NETKey<T>::getValue()
	{
		return _value;
	}

	template <typename T>
	const T& NETKey<T>::getValue() const
	{
		return _value;	
	}


	template <typename T>
	void NETKey<T>::releaseValue()
	{
		_value = T();
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	void  NETKey<T>::release() 
	{
		Super::release();

		releaseValue();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NEBinaryFileSaver& NETKey<T>::serialize(NEBinaryFileSaver& saver) const  
	{
		Super::serialize(saver);

		return saver << _value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NEBinaryFileLoader& NETKey<T>::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _value;
	}
}