#pragma once

#include "../NEKeyNameBinder/NEKeyNameBinder.hpp"
#include "../../Interfaces/NEUpdatable/NEUpdatable.hpp"

namespace NE
{
	class NE_DLL NEArgumentBase : public NEKeyNameBinder, public NEUpdatable
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
		bool isNeedingUpdate() const;

	public:
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		bool isNeedingBinding() const;

	protected:
		void _setNeedingUpdate(bool needing_update);

	private:
		NEType::Type _type_validation;
		bool _is_needing_update;
	};
}