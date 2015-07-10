#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Binder : public NEModule
	{
	public:
		typedef Binder ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEKey> arg_sources;
		NETArgument<NEKey> arg_targets;
		NETArgument<NEModuleCodeSetKey> arg_filters;

	protected:
		virtual type_result _onFetchModule()
		{
			arg_sources.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_targets.setPurposeLimitation(NEArgumentBase::WRITTEN);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_sources);
			tray.push(arg_targets);
			tray.push(arg_filters);

			return RESULT_SUCCESS;
		}

	protected:
		virtual type_result _onExecute()
		{
			NEKey& target = arg_targets.getValueKey();
			NEKey& source = arg_sources.getValueKey();
			if( ! target.isSubClassOf(NEType::NENODE_SELECTOR)	||
				! source.isSubClassOf(NEType::NENODE_SELECTOR)	)
				return ALERT_ERROR("주어진 Target 혹은 Source가 NodeSelector의 하위클래스가 아닙니다.");
			if (!target.isSubClassOf(source))
				return ALERT_ERROR("Target이 Source보다 하위클래스 혹은 같은 클래스가 아닙니다.");
			NENodeSelector& node_sel = static_cast<NENodeSelector&>(source);
			NEModuleCodeSet& filters = arg_filters.getValue();

			//	main:
			//		루프 시작:
			while(_moveForward(node_sel))
			{
				for(int n = 0; n < filters.getLength(); n++)
				{
					if (NEResult::hasFalse(filters[n].execute()))
						goto NextObject;
				}

				//	Found:
				target = source;
				break;

NextObject:;
			}			

			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _instance;

			if (_instance.isValid() != RESULT_NOTHING)
			{
				_instance.getName() = "Binder";
				_instance.getDeveloper() = "kniz";
				_instance.setRevision(1);
				_instance.getReleaseDate() = "2015/07/06";
				_instance.getComment() = "Source Selector가 가리키는 객체 중에 Filter를 통과(모두 true)한 객체가 있다면, Target Selector를 그때의 객체로 바인딩시킵니다.\n객체를 찾으면 Target Selector = Source Selector가 이루어지므로, Target Selector는 Source Selector와 같거나 더 구체적인 클래스타입이어야 합니다.";
				NETStringSet& args = _instance.getArgumentsComments();
				args.create(3);
				args.push("Source Selector\n바인딩 시킬 대상들을 가리키는 셀렉터입니다.");
				args.push("Target Selector\nSource Selector가 가리키는 객체 중에서, Filter를 모두 통과한 객체로 바인딩됩니다.\n만약 Target Selector에 NodeSelectorKey가 들어가면 Node객체만 바인딩됩니다.");
				args.push("Filter\n여기의 있는 모든 Module이 TRUE를 반환해야 Filter를 통과한 것으로 간주합니다.");				
			}

			return _instance;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	private:
		bool _moveForward(NENodeSelector& target)
		{
			target.unbind();

			bool is_there_more = false;
			if (target.isSubClassOf(NEType::NEKEY_SELECTOR))
				is_there_more = &(static_cast<NEKeySelector&>(target)).getKey() != 0x00;
			else if (target.isSubClassOf(NEType::NEMODULE_SELECTOR))
				is_there_more = &(static_cast<NEModuleSelector&>(target)).getModule() != 0x00;
			else
				is_there_more = &target.getNode() != 0x00;

			target.bind();

			return is_there_more;
		}
	};
}