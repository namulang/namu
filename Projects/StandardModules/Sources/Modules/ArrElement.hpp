#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ArrElementer : public NEModule
	{
	public:
		NETArgument<NEIntKey>	arg_method;
		NETArgument<NEKey>		arg_collector;
		NETArgument<NEIntKey>	arg_index;
		NETArgument<NEKey>		arg_unit;

		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;
			if (NEResult::hasError(_header.isValid()))
			{
				_header.getName() = "ArrElementer";
				_header.getDeveloper() = "kniz";
				_header.setRevision(2);
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2014-12-03";
				_header.getComment() =
					"NEByteSetKey, NEStringSetKey 등, Collector Key에 대하여,\n"
					"특정 index의 요소에 대해 get, insert, remove를 수행하는 Module 입니다.\n"
					"연산의 종류는 다음과 같습니다\n"
					"\t0:\tget. 주어진 index에 위치한 요소를 Unit Argument에 담습니다.\n"
					"\t1:\tinsert. 주어진 index에 Unit Argument의 값을 추가합니다.\n"
					"\t2:\tremove. 주어진 index에 있는 원소를 삭제합니다. 만약 Index Argument가 disabled 된 경우, Unit과 일치하는 원소를 삭제합니다.\n"
					"\t3:\tfind. Unit과 일치하는 값을 Collector에서 찾아 그 index를 저장합니다.못찾을 경우 -1이 나오게 됩니다.\n";
				NETStringSet& argcomments = _header.getArgumentsComments();
				argcomments.create(4);
				argcomments.push("Method\n연산의 종류입니다.\n0: get[기본값], 1: insert, 2: remove, 3: find");
				argcomments.push("Collector\n연산을 수행할 Collector Key입니다.");
				argcomments.push("Index\n해당 Collector의 Index 입니다.");
				argcomments.push("Unit\n연산에 따른 결과 및 인자로 사용됩니다.\nget에서는 index의 원소가 할당되어지고, insert에서는 주어진 index로 삽입됩니다.");
			}

			return _header;
		}

	protected:
		virtual type_result _onExecute()
		{
			NEKey			*collector_key_e = &arg_collector.getValueKey(),
				*unit_key_e = &arg_unit.getValueKey();
			NEKeySelector	*collector_key		= 0,
				*unit_key			= 0;
			if (!collector_key_e || !unit_key_e) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

			if (arg_collector.getValueKey().isSubClassOf(NEType::NEKEY_SELECTOR))
			{
				collector_key = static_cast<NEKeySelector*>(&arg_collector.getValueKey());
				collector_key_e = &collector_key->getKey();
			}
			if (arg_unit.getValueKey().isSubClassOf(NEType::NEKEY_SELECTOR))
			{
				unit_key = static_cast<NEKeySelector*>(&arg_unit.getValueKey());
				unit_key_e = &unit_key->getKey();
			}


			//	main:
			while (collector_key_e)
			{
				while (unit_key_e)
				{
					_executeKey(*collector_key_e, *unit_key_e);

					if (unit_key)
						unit_key_e = &unit_key->getKey();
				}

				if (collector_key)
					collector_key_e = &collector_key->getKey();
			}

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_method.setPurposeLimitation(NEArgumentBase::READ_BY);
			return arg_index.setPurposeLimitation(NEArgumentBase::READ_BY);
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_method);
			tray.push(arg_collector);
			tray.push(arg_index);
			tray.push(arg_unit);
			return RESULT_SUCCESS;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ArrElementer(*this));
		}

	private:
		void _executeKey(NEKey& collector, NEKey& unit)
		{
#define MAKE_COLLECTOR_BRANCH(TYPE, COLL, ELEM)	\
	if (collector.isSubClassOf(NEType::##TYPE##)) \
	return _operate<##COLL##, NEType::##TYPE##, ##ELEM##>(collector, arg_index.getValue(), unit)

			MAKE_COLLECTOR_BRANCH(NEBOOLEAN_SET_KEY,	NEBooleanSetKey,	NEBooleanKey);
			MAKE_COLLECTOR_BRANCH(NEBYTE_SET_KEY,		NEByteSetKey,		NEByteKey);
			MAKE_COLLECTOR_BRANCH(NEUBYTE_SET_KEY,		NEUByteSetKey,		NEUByteKey);
			MAKE_COLLECTOR_BRANCH(NESHORT_SET_KEY,		NEShortSetKey,		NEShortKey);
			MAKE_COLLECTOR_BRANCH(NEUSHORT_SET_KEY,		NEUShortSetKey,		NEUShortKey);
			MAKE_COLLECTOR_BRANCH(NEINT_SET_KEY,		NEIntSetKey,		NEIntKey);
			MAKE_COLLECTOR_BRANCH(NEUINT_SET_KEY,		NEUIntSetKey,		NEUIntKey);
			MAKE_COLLECTOR_BRANCH(NEINT64_SET_KEY,		NEInt64SetKey,		NEInt64Key);
			MAKE_COLLECTOR_BRANCH(NEFLOAT_SET_KEY,		NEFloatSetKey,		NEFloatKey);
			MAKE_COLLECTOR_BRANCH(NEDOUBLE_SET_KEY,		NEDoubleSetKey,		NEDoubleKey);
			MAKE_COLLECTOR_BRANCH(NESTRING_SET_KEY,		NEStringSetKey,		NEStringKey);
			MAKE_COLLECTOR_BRANCH(NEWSTRING_SET_KEY,	NEWStringSetKey,	NEWStringKey);
			MAKE_COLLECTOR_BRANCH(NECODE_SET_KEY,		NECodeSetKey,		NECodeKey);
#undef MAKE_COLLECTOR_BRANCH
		}
		template <typename CK, NEType::Type TYPE, typename UK>
		void _operate(NEKey& ck, type_index index, NEKey& unit)
		{
			if( ! ck.isSubClassOf(TYPE)) return;
			CK& casted = static_cast<CK&>(ck);
			if(index < 0 || index > casted.getValue().getLengthLastIndex()) return;

			switch(arg_method.getValue())
			{
			case 0:	//	GET
				unit = UK(casted.getValue()[index]);
				break;

			case 1:	//	INSERT				
				casted.getValue().insert(index, UK(unit).getValue());
				break;

			case 2:	//	REMOVE
				{
					type_index n = NE_INDEX_ERROR;
					if (!arg_index.isEnable())
						n = casted.getValue().find(UK(unit).getValue());

					casted.getValue().remove(n);
				}
				break;

			case 3:	//	FIND
				arg_index.setValue(casted.getValue().find(UK(unit).getValue()));
				break;
			}


			//	post:
			return;
		}
	};
}
