#pragma once

#include "../NEKeyNameBinder/NEKeyNameBinder.hpp"

namespace NE
{
	class NE_DLL NEArgumentBase : public NEObject
	{
	public:
		typedef NEArgumentBase ThisClass;
		typedef NEObject SuperClass;

	public:
		NEArgumentBase(NEType::Type type);

	public:
		bool operator==(const NEArgumentBase& source) const;
		bool operator!=(const NEArgumentBase& source) const;

	public:
		NEKeyNameBinder& getBinder();
		const NEKeyNameBinder& getBinder() const;
		NEType::Type getTypeToBeBinded() const;

	public:
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	private:
		NEKeyNameBinder _binder;
		NEType::Type _type_validation;
	};
}