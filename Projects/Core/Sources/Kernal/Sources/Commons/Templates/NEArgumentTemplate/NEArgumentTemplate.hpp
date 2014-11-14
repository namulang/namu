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
		NEArgumentTemplate(typename const T::Trait& default_value);

	public:
		T& getBindedKey();
		const T& getBindedKey() const;
		T& getDefaultKey();
		const T& getDefaultKey() const;

	public:
		virtual NEObject& clone() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		typename T::Trait& getValue();
		typename T::Trait& getValue() const;
		typename const T::Trait& getDefault() const;
		typename T::Trait& getDefault();

	private:
		T _default;
	};
}

#include "NEArgumentTemplate.inl"