#pragma once

#include "../NEArgumentBase/NEArgumentBase.hpp"
#include "../NEBooleanSetKey/NEBooleanSetKey.hpp"
#include "../NEByteSetKey/NEByteSetKey.hpp"
#include "../NEUByteSetKey/NEUByteSetKey.hpp"
#include "../NEShortSetKey/NEShortSetKey.hpp"
#include "../NEUShortSetKey/NEUShortSetKey.hpp"
#include "../NEIntSetKey/NEIntSetKey.hpp"
#include "../NEUIntSetKey/NEUIntSetKey.hpp"
#include "../NEInt64SetKey/NEInt64SetKey.hpp"
#include "../NEFloatSetKey/NEFloatSetKEy.hpp"
#include "../NEDoubleSetKey/NEDoubleSetKey.hpp"
#include "../NEStringSetKey/NEStringSetKey.hpp"
#include "../NEWStringSetKey/NEWStringSetKey.hpp"
#include "../NENodeSelector/NENodeSelector.hpp"
#include "../NEModuleSelector/NEModuleSelector.hpp"
#include "../NEKeySelector/NEKeySelector.hpp"
#include "../NEModuleCodeSetKey/NEModuleCodeSetKey.hpp"
#include "../NENodeCodeSetKey/NENodeCodeSetKey.hpp"

namespace NE
{
	class NEKey;

	template <typename T>
	class NETArgument : public NEArgumentBase
	{
		NE_DECLARE_CLASS(NETArgument<T>, NEArgumentBase)

	public:	
		NETArgument(NEArgumentBase::Purpose limitation = NEArgumentBase::UNDEFINED);

	public:
		type_result setValue(typename const T::Trait& source);
		typename const T::Trait& getValue() const;
		type_result setDefault(typename const T::Trait& source);
		typename const T::Trait& getDefault() const;

	public:
		virtual NEKey& getDefaultKey();
		virtual const NEKey& getDefaultKey() const;

	public:
		virtual NEType::Type getType() const;
		virtual NEObject& clone() const;
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	

	private:
		mutable T _for_casting;
		T _default_key;
	};
}

#include "NETArgument.inl"