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

	public:
		virtual NEObject& clone() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		typename T::Trait& getValue();
		virtual type_result bind();
		const T& getDefault() const;
		T& getDefault();

	private:
		T _default;
	};
}

#include "NEArgumentTemplate.inl"