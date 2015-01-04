#pragma once

#include "NodeSelectorTaggerBase.hpp"

namespace NE
{
	class NE_DLL KeySelectorTagger : public NodeSelectorTaggerBase
	{
	public:
		typedef KeySelectorTagger ThisClass;
		typedef NodeSelectorTaggerBase SuperClass;

	public:
		NETArgument<NEKeySelector>	arg_target;
		NETArgument<NETStringKey>	arg_keyname;

	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_target);
			tray.push(arg_keyname);

			return SuperClass::_onFetchArguments(tray);
		}
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_keyname.setEnable(false);
			arg_keyname.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);

			return RESULT_SUCCESS;
		}

	protected:
		using SuperClass::_passPipes;
		type_result _passPipes(NEKeySelector& k)
		{
			type_result result = RESULT_SUCCESS;

			if(arg_keyname.isEnable())
			{
				if (arg_keyname.getPurpose() == NEArgumentBase::READ_BY)
					k.setKeyName(arg_keyname.getValue());
				else
					result |= arg_keyname.setValue(k.getKeyName());
			}

			return result;
		}
		virtual type_result _onExecute()
		{
			NEKeySelector& ks = arg_target.getValue();
			NENodeSelector& ns = ks;

			type_result result = _passPipes(ns);

			return result |= _passPipes(ks);
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				NEExportable::ModuleHeader supers = SuperClass::getHeader();

				_instance.getName() = "KeySelectorTagger";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/01/02";
				_instance.getComment() =
					"참조한 Key 객체들의 특정 속성값들을 가져오거나(get) 할당할 수 있습니다(set).\n"
					"\tTargets:\t참조할 객체들\n"
					"\tKey Name:\t속한 Node의 KeySet중 하나와 바인딩할 키 이름\n" +
					supers.getComment();
				NETStringSet& args = _instance.getArgumentsComments();
				const NETStringSet& super_args = supers.getArgumentsComments();

				args.create(super_args.getLength() + 2);
				args.push("Targets\n속성을 가져오거나 할당하게될 Module 들입니다.");
				args.push("KeyName\nKey 탐색시 사용하게될 이름입니다.");
				args.push(super_args);
			}

			return _instance;
		}
	};
}