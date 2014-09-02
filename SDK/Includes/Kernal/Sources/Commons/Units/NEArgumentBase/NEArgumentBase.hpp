#pragma once

#include "../NEKeyNameBinder/NEKeyNameBinder.hpp"

namespace NE
{
	class NE_DLL NEArgumentBase : public NEKeyNameBinder
	{
	public:
		typedef NEArgumentBase ThisClass;
		typedef NEKeyNameBinder SuperClass;

	public:
		NEArgumentBase(NEType::Type type);
		NEArgumentBase(const ThisClass& rhs);

	public:
		bool operator==(const NEArgumentBase& source) const;
		bool operator!=(const NEArgumentBase& source) const;

	public:
		NEType::Type getTypeToBeBinded() const;

	public:
		virtual NEObject& clone() const;
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	private:
		NEType::Type _type_validation;
	};
}