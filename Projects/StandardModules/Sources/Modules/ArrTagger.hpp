#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ArrTagger : public NEModule
	{
	public:
		NETArgument<NEIntKey>	arg_method;
		NETArgument<NEKey>		arg_collector;
		NETArgument<NEIntKey>	arg_index;
		NETArgument<NEKey>		arg_unit;
		NETArgument<NEIntKey>	arg_size;
		NETArgument<NEIntKey>	arg_length;

		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;
			if (NEResult::hasError(_header.isValid()))
			{
				_header.getName() = "ArrTagger";
				_header.getDeveloper() = "kniz";
				_header.setRevision(2);
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2014-12-03";
				_header.getComment() =
					"NEByteSetKey, NEStringSetKey 등, Collector Key에 대하여,\n"
					"특정 index의 요소에 대해 get, insert, remove를 수행하는 Module 입니다.\n"
					"연산의 종류는 다음과 같습니다\n"
					"\t0:\tget. 주어진 index에 위치한 요소를 Unit Argument에 담습니다.\n"
					"\t1:\tset. 주어진 index에 UnitArgument를 할당합니다.\n"
					"\t2:\tinsert. 주어진 index에 Unit Argument의 값을 추가합니다.\n"
					"\t3:\tremove. 주어진 index에 있는 원소를 삭제합니다. 만약 Index Argument가 disabled 된 경우, Unit과 일치하는 원소를 삭제합니다.\n"
					"\t4:\tfind. Unit과 일치하는 값을 Collector에서 찾아 그 index를 저장합니다.못찾을 경우 -1이 나오게 됩니다.\n"
					"또한, 다음과 같은 속성들의 값을 가져올 수 있습니다.\n"
					"\tSize: Container의 크기 입니다.\n"
					"\tLength: Length 입니다.";
				NETStringSet& argcomments = _header.getArgumentsComments();
				argcomments.create(6);
				argcomments.push("Method\n연산의 종류입니다.\n0: get[기본값], 1: set, 2: insert, 2: remove, 3: find");
				argcomments.push("Collector\n연산을 수행할 Collector Key입니다.");
				argcomments.push("Index\n해당 Collector의 Index 입니다. insert에서 -1은 push, remove에서 -1은 pop이 됩니다.");
				argcomments.push("Unit\n연산에 따른 결과 및 인자로 사용됩니다.\nget에서는 index의 원소가 할당되어지고, insert에서는 주어진 index로 삽입됩니다.");
				argcomments.push("Length\n해당 Collector의 Length 속성을 가져옵니다.");
				argcomments.push("Size\n해당 Collector의 Size 속성을 가져옵니다,");
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
			if( ! collector_key_e && ! unit_key_e) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

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
#define MAKE_COLLECTOR_BRANCH(TYPE, COLL)	\
	if(	arg_length.isEnable()					&&	\
	collector_key_e->isSubClassOf(NEType::##TYPE##))	\
	_fetchLength<##COLL##::Trait>(static_cast<COLL&>(*collector_key_e).getValue());	\
	if( arg_size.isEnable()						&&	\
	collector_key_e->isSubClassOf(NEType::##TYPE##))	\
	_fetchSize<##COLL##::Trait>(static_cast<COLL&>(*collector_key_e).getValue());
				MAKE_COLLECTOR_BRANCH(NEBOOLEAN_SET_KEY, NEBooleanSetKey);
				MAKE_COLLECTOR_BRANCH(NEBYTE_SET_KEY, NEByteSetKey);
				MAKE_COLLECTOR_BRANCH(NEUBYTE_SET_KEY, NEUByteSetKey);
				MAKE_COLLECTOR_BRANCH(NESHORT_SET_KEY, NEShortSetKey);
				MAKE_COLLECTOR_BRANCH(NEUSHORT_SET_KEY, NEUShortSetKey);
				MAKE_COLLECTOR_BRANCH(NEINT_SET_KEY, NEIntSetKey);
				MAKE_COLLECTOR_BRANCH(NEUINT_SET_KEY, NEUIntSetKey);
				MAKE_COLLECTOR_BRANCH(NEINT64_SET_KEY, NEInt64SetKey);
				MAKE_COLLECTOR_BRANCH(NEFLOAT_SET_KEY, NEFloatSetKey);
				MAKE_COLLECTOR_BRANCH(NEDOUBLE_SET_KEY, NEDoubleSetKey);
				MAKE_COLLECTOR_BRANCH(NESTRING_SET_KEY, NEStringSetKey);
				MAKE_COLLECTOR_BRANCH(NEWSTRING_SET_KEY, NEWStringSetKey);
				MAKE_COLLECTOR_BRANCH(NECODE_SET_KEY, NECodeSetKey);
				MAKE_COLLECTOR_BRANCH(NESTRING_KEY, NEStringKey);
				MAKE_COLLECTOR_BRANCH(NEWSTRING_KEY, NEWStringKey);
#undef MAKE_COLLECTOR_BRANCH

				while (unit_key_e)
				{
					_executeKey(*collector_key_e, *unit_key_e);

					if (unit_key)
						unit_key_e = &unit_key->getKey();
					else
						break;
				}

				if (collector_key)
					collector_key_e = &collector_key->getKey();
				else
					break;
			}		

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_method.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_index.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_length.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_length.setEnable(false);
			arg_size.setPurposeLimitation(NEArgumentBase::WRITTEN);
			arg_size.setEnable(false);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_method);
			tray.push(arg_collector);
			tray.push(arg_index);
			tray.push(arg_unit);
			tray.push(arg_length);
			tray.push(arg_size);

			return RESULT_SUCCESS;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ArrTagger(*this));
		}

	private:
		void _executeKey(NEKey& collector, NEKey& unit)
		{
#define MAKE_COLLECTOR_BRANCH(TYPE, COLL, ELEM)	\
	if (collector.isSubClassOf(NEType::##TYPE##)) \
	return _operate<##COLL##::Trait, NEType::##TYPE##, ##ELEM##>(static_cast<COLL&>(collector).getValue(), arg_index.getValue(), unit)

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
			MAKE_COLLECTOR_BRANCH(NESTRING_KEY,			NEStringKey,		NECharKey);
			MAKE_COLLECTOR_BRANCH(NEWSTRING_KEY,		NEWStringKey,		NEWCharKey);
#undef MAKE_COLLECTOR_BRANCH
		}
		template <typename C, NEType::Type TYPE, typename UK>
		void _operate(C& c, type_index index, NEKey& unit)
		{
			switch (arg_method.getValue())
			{
			case 0:	//	GET
				if (index < 0 || index > c.getLengthLastIndex()) return;
				unit = UK(c[index]);
				break;

			case 1:	//	SET
				if (index < 0 || index > c.getLengthLastIndex()) return;
				c.setElement(index, UK(unit).getValue());
				break;

			case 2:	//	INSERT
				if (index < -1 || index > c.getLengthLastIndex()) return;
				if (index == -1) index = c.getLength();

				if (c.getLength() >= c.getSize())
					c.resize(c.getLength() + (c.getLength() * 0.5 + 1));

				c.insert(index, UK(unit).getValue());
				break;

			case 3:	//	REMOVE
				if (index < -1 || index > c.getLengthLastIndex()) return;
				if (index == -1) index = c.getLengthLastIndex();
				{
					type_index n = NE_INDEX_ERROR;
					if (!arg_index.isEnable())
						n = c.find(UK(unit).getValue());

					c.remove(n);
				}
				break;

			case 4:	//	FIND
				arg_index.setValue(c.find(UK(unit).getValue()));
				break;
			}

			return;
		}

		template <typename C>
		void _fetchLength(C& c)
		{
			if (arg_length.isEnable())
				arg_length.setValue(c.getLength());
			return;
		}
		template <typename C>
		void _fetchSize(C& c)
		{
			if (arg_size.isEnable())
				arg_size.setValue(c.getSize());
			return;
		}
	};
}
