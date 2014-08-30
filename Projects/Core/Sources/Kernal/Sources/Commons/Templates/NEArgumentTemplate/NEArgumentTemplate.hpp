#pragma once

#include "../../Units/NEArgumentBase/NEArgumentBase.hpp"

namespace NE
{
	template <typename T>
	class NEArgumentTemplate : public NEArgumentBase
	{
	public:
		typedef NEArgumentTemplate ThisClass;
		typedef ThisClass TArgument;
		typedef NEArgumentBase SuperClass;

	public:	
		NEArgumentTemplate() 
			: SuperClass(T().getType())
		{
			
		}

	public:
		T& getBindedKey() { return getBinded(); }
		const T& getBindedKey() const { return getBinded(); }

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		
	public:
		typename T::Trait& getValue() 
		{
			if( ! isBinded())
				bind(); 

			if(isBinded())
				return getValue();
			else
			{
				T::Trait* nullpoint = 0;
				return *nullpoint;
			}
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
	};
}