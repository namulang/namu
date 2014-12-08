#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL BinaryFiler : public NEModule
	{
	public:
		NETArgument<NEBooleanKey>		arg_is_load;
		NETArgument<NETStringKey>		arg_path;		
		NETArgument<NEIntKey>			arg_target0_manager_type;
		NETArgument<NENodeSelector>		arg_target1;
		NETArgument<NEModuleSelector>	arg_target2;
		NETArgument<NEKeySelector>		arg_target3;
		NETArgument<NEIntKey>			arg_mode;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;
			if (NEResult::hasError(_header.isValid()))
			{
				_header.getName() = "BinaryFiler";
				_header.getDeveloper() = "kniz";
				_header.setRevision(2);
				_header.getVersion() = "0.0.1a";
				_header.getReleaseDate() = "2014-12-03";
				_header.getComment() =
					"File을 로드 및 저장하는 모듈입니다.\n"
					"Binary 및 Text 형태로 저장/로드가 가능하며, \n"
					"Target으로 Manager 전체의 내용이나 Selector로 특정한 데이터만 선택할 수 있습니다.\n"
					"Target에는 총 4종류가 존재하며, disable될 시 연산에 적용되지 않습니다.\n\n"
					"ManagerType은 다음과 같습니다.\n"
					"\t0\t:\tNodeManager""\t1\t:\tScriptManager\n"
					"\t2\t:\tModuleManager""\t3\t:\tINIManager\n"
					"\t4\t:\tDebugManager""\t5\t:\tScriptManager\n"
					"\t6\t:\tPanelManager""\t7\t:\tEventHandler";
				NETStringSet& argcomments = _header.getArgumentsComments();
				argcomments.create(7);
				argcomments.push("연산종류\n주어진 대상에 대하여, Load(true), Save(false)인지를 정합니다.");
				argcomments.push("경로\n프로그램이 실행된 경로를 기준으로 파일의 위치를 적어줍니다. 이때, 파일명과 확장자까지 모두 적어줘야 합니다.\n예) ../resources/actor.bmp");
				argcomments.push("대상0\n시스템에 존재하는 Manager를 통채로 저장/로드 합니다.\n0: NodeManager, 1:ScriptManager, 2:ScriptEditor, 3:ModuleManager, 4:INIManager, 5:DebugManager, 6:PanelManager, 7:EventHandler");
				argcomments.push("대상1\nSelector로 가져온 대상에 대하여 연산을 합니다.\n대상0과 마찬가지로, disabled 되면 적용되지 않습니다.");
				argcomments.push("대상2\nSelector로 가져온 대상에 대하여 연산을 합니다.\n대상0과 마찬가지로, disabled 되면 적용되지 않습니다.");
				argcomments.push("대상3\nSelector로 가져온 대상에 대하여 연산을 합니다.\n대상0과 마찬가지로, disabled 되면 적용되지 않습니다.");
				argcomments.push("저장-옵션\n저장시, 이미 파일이 있는 경우에 대한 옵션입니다.\n0:이미 파일이 있으면 덮어씀[기본값], 1:있으면 끝에 추가, 2: 있으면 저장취소, 3:있을때만 저장");
			}

			return _header;
		}		

	protected:
		virtual type_result _onExecute()
		{
			NEFileSaverFlag flag = ! arg_mode.isEnable() ? NEFileSaverFlag::NEFILESAVERFLAG_OVERWRITE : NEFileSaverFlag(arg_mode.getValue());
			NEBinaryFileAccessor* accessor = 0x00;
			if(arg_is_load.getValue())
				accessor = &NEBinaryFileLoader(arg_path.getValue().toCharPointer());
			else
				accessor = &NEBinaryFileSaver(arg_path.getValue().toCharPointer(), flag);
			
			accessor->open();
			if( ! accessor->isFileOpenSuccess())
			{
				ALERT_ERROR("파일을 열 수 없었습니다.");

				return RESULT_TYPE_ERROR;
			}


			//	main:
			NEListTemplate<NEObject*> tray;

			if(arg_target0_manager_type.isEnable())
			{
				switch (arg_target0_manager_type.getValue())
				{
				case 0:	tray.push(Kernal::getInstance().getNodeManager());		break;
				case 1: tray.push(Kernal::getInstance().getScriptManager());	break;
				//case 2:	tray.push(Editor::getInstance().getScriptEditor());		break;
				case 2:	tray.push(Kernal::getInstance().getModuleManager());	break;
				case 3:	tray.push(Kernal::getInstance().getINIManager());		break;
				case 4:	tray.push(Kernal::getInstance().getDebugManager());		break;
				//case 6:	tray.push(Editor::getInstance().getPanelManager());		break;
				//case 7:	tray.push(Editor::getInstance().getEventHandler());		break;
				default:
					ALERT_WARNING("%d에 해당하는 Manager가 없습니다.", arg_target0_manager_type.getValue());

					return RESULT_TYPE_WARNING;
				}					
			}
			if(arg_target1.isEnable())
				while (NENode* e = &arg_target1.getValue().getNode())
					tray.push(e);
			if(arg_target2.isEnable())
				while (NEModule* e = &arg_target2.getValue().getModule())
					tray.push(e);
			if(arg_target3.isEnable())
				while (NEKey* e = &arg_target3.getValue().getKey())
					tray.push(e);


			//	post:
			NEBinaryFileLoader& casted_l = static_cast<NEBinaryFileLoader&>(*accessor);
			NEBinaryFileSaver& casted_s = static_cast<NEBinaryFileSaver&>(*accessor);

			for (NEListTemplate<NEObject*>::Iterator* e = tray.getIterator(0);
				e;
				e = e->getNext())
				if (accessor->isSaver())
					e->getValue().serialize(casted_s);
				else
					e->getValue().serialize(casted_l);

			return RESULT_SUCCESS;
		}

		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_is_load);
			tray.push(arg_path);
			tray.push(arg_target0_manager_type);
			tray.push(arg_target1);
			tray.push(arg_target2);
			tray.push(arg_target3);
			tray.push(arg_mode);
			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			arg_target1.setEnable(false);
			arg_target2.setEnable(false);
			arg_target3.setEnable(false);
			arg_is_load.setDefault(false);

			return RESULT_SUCCESS;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new BinaryFiler(*this));
		}
	};
}
