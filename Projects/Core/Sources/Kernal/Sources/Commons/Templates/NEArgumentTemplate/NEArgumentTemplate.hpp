#pragma once

#include "../../Units/NEArgumentBase/NEArgumentBase.hpp"

namespace NE
{
	template <typename T>
	class NEArgumentTemplate : public NEArgumentBase
	{
	public:
		typedef NEArgumentTemplate ThisClass;
		typedef NEArgumentBase SuperClass;

	public:	
		NEArgumentTemplate() 
			: SuperClass(T().getType())
		{
			
		}

	public:
		T& getBindedKey() { return static_cast<T&>(getBinded()); }
		const T& getBindedKey() const { return static_cast<T&>(getBinded()); }

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		
	public:
		typename T::Trait& getValue() 
		{
			if(isBinded())
				return getBindedKey().getValue();
			else
				return _default.getValue();
		}
		virtual type_result bind()
		{
			if(isBinded())	return RESULT_SUCCESS | RESULT_ABORT_ACTION;

			type_result result = SuperClass::bind();
			if( NEResult::hasError(result)						||	
				! getBinded().isSubClassOf(getTypeToBeBinded())	)
				return RESULT_TYPE_ERROR | result;

			return result;
		}
		const T& getDefault() const
		{
			return _default;
		}
		T& getDefault()
		{
			return _default;
		}

	private:
		T _default;
	};
}