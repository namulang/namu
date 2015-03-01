#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Instancer : public NEModule
	{
	public:
		typedef Instancer ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NENodeSelector> arg_targets;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_targets.getValue().setManager(NEType::NESCRIPT_MANAGER);
			arg_targets.setPurposeLimitation(NEArgumentBase::READ_OR_WRITTEN);
			arg_targets.setPurpose(NEArgumentBase::WRITTEN);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_targets);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			NENodeSelector& ns = arg_targets.getValue();

			type_result(ThisClass::*Function)(NENode&);
			if (arg_targets.getPurpose() == NEArgumentBase::READ_BY)
				Function = &ThisClass::_remove;
			else
				Function = &ThisClass::_insert;

			while (NENode* node = &ns.getNode())
				(this->*Function)(*node);

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Instancer";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2012/04/14";
				_instance.getComment() =
					"Manager에 Script 객체를 추가하거나, Node를 삭제할 수 있습니다.\n"
					"Target Argument의 Purpose를 READ로 하면 삭제를, WRITE로 하면 추가가 됩니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(1);
				args.push("Target\nNodeManager에 추가하거나, 삭제할 Node를 가리킵니다.\nPurpose가 READ이면 삭제를, WRITE이면 추가를 의미합니다.");
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		type_result _insert(NENode& node)
		{
			NENodeManager& nm = Kernal::getInstance().getNodeManager();
			if (!&nm)
				return ALERT_ERROR(" : NodeManager가 없습니다.");

			type_index n = nm.getRootNodes().push(node);
			if (n < 0)
				return ALERT_ERROR(" : 추가 도중 오류가 발생하였습니다.\n\t반환된 인덱스 값 : %d", n);

			return RESULT_SUCCESS;
		}
		type_result _remove(NENode& node)
		{
			NENodeCodeSet& ncs = node.getOwner();
			if (!&ncs)
				return ALERT_WARNING(" : ");

			for (int n = 0; n < ncs.getLength(); n++)
				if (&ncs[n] == &node)
				{
					type_result result = ncs.remove(n);
					if (NEResult::hasError(result))
						return ALERT_ERROR(" : ");

					return result;
				}

				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		}
	};
}