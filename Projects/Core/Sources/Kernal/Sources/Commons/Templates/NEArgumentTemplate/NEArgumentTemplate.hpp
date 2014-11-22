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
		NEArgumentTemplate();

	public:
		T& getBindedKey();
		const T& getBindedKey() const;

	public:
		virtual type_result update();

	public:
		virtual NEObject& clone() const;

	public:
		typename T::Trait& getValue();
		typename T::Trait& getValue() const;

	private:
		T _for_casting;
	};
}

#include "NEArgumentTemplate.inl"