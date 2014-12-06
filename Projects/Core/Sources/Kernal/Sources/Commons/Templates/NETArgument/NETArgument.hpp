#pragma once

#include "../../../Modules/NEArgumentBase/NEArgumentBase.hpp"
#include "../../../Modules/NEBooleanSetKey/NEBooleanSetKey.hpp"
#include "../../../Modules/NEByteSetKey/NEByteSetKey.hpp"
#include "../../../Modules/NEUByteSetKey/NEUByteSetKey.hpp"
#include "../../../Modules/NEShortSetKey/NEShortSetKey.hpp"
#include "../../../Modules/NEUShortSetKey/NEUShortSetKey.hpp"
#include "../../../Modules/NEIntSetKey/NEIntSetKey.hpp"
#include "../../../Modules/NEUIntSetKey/NEUIntSetKey.hpp"
#include "../../../Modules/NEInt64SetKey/NEInt64SetKey.hpp"
#include "../../../Modules/NEFloatSetKey/NEFloatSetKEy.hpp"
#include "../../../Modules/NEDoubleSetKey/NEDoubleSetKey.hpp"
#include "../../../Modules/NEStringSetKey/NEStringSetKey.hpp"
#include "../../../Modules/NEWStringSetKey/NEWStringSetKey.hpp"
#include "../../../Modules/NENodeSelector/NENodeSelector.hpp"
#include "../../../Modules/NEModuleSelector/NEModuleSelector.hpp"
#include "../../../Modules/NEKeySelector/NEKeySelector.hpp"
#include "../../../Modules/NEModuleCodeSetKey/NEModuleCodeSetKey.hpp"
#include "../../../Modules/NENodeCodeSetKey/NENodeCodeSetKey.hpp"

namespace NE
{
	class NEKey;

	template <typename T>
	class NETArgument : public NEArgumentBase
	{
	public:
		typedef NETArgument ThisClass;
		typedef NEArgumentBase SuperClass;

	public:	
		NETArgument();

	public:
		type_result setValue(typename const T::Trait& source);
		typename const T::Trait& getValue() const;
		type_result setDefault(typename const T::Trait& source);
		typename const T::Trait& getDefault() const;

	public:
		virtual NEKey& getDefaultKey();
		virtual const NEKey& getDefaultKey() const;

	public:
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