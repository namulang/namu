#pragma once

#include "../NEKeyNameBinder/NEKeyNameBinder.hpp"
#include "../../Interfaces/NEUpdatable/NEUpdatable.hpp"

namespace NE
{
	class NEArgumentBaseList;

	class NE_DLL NEArgumentBase : public NEKeyNameBinder, public NEUpdatable
	{
	public:
		friend class NEModule;

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
		bool isUpdateReserved() const;
		type_result reserveUpdate();

	public:
		virtual type_result unbind();

	public:
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		bool isNeedingBinding() const;

	protected:
		void _setUpdateReservedFlag(bool needing_update);

	private:
		NEType::Type _type_validation;
		bool _is_update_reserved;

	private:
		static NEArgumentBaseList& _getArguments();
	};
}