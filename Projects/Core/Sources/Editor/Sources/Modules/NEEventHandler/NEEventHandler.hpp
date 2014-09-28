#pragma once

#include "../../Commons/NENodeCollector/NENodeCollector.hpp"

namespace NE
{
	
	class NEPanel;
	class NEDialog;
	class NEComponent;
	
	class NE_DLL NEEventHandler : public NEModule
	{
	public:
		NEEventHandler();
		NEEventHandler(const NEEventHandler& source);

	public:
		virtual ~NEEventHandler();

		//	인터페이스:
		//		상속:
		//			출력과 관련된 이벤트:	Standard로 묶을 수 없는 이벤트이다.
		//			프로그램 내부 형태의 이벤트:
	public:
		virtual type_result onCallingDialog(NEPanel& caller_of_panel, type_index component_index_to_call, NEDialog& dialog) = 0;
		virtual type_result onCallingPanel(NEPanel& panel, NEModule& module_to_be_modified) = 0;
		virtual type_result onModifyingKey(NEKey& key) = 0;
		//			메뉴 형태의 이벤트:
	public:	
		virtual type_result saveScriptFile(NETString& path_from_script_directory_without_extraction) const;
		virtual type_result loadScriptFile(NETString& path_from_script_directory_without_extraction);		
		virtual type_result initiateTest() = 0;
		virtual type_result pauseTest() = 0;
		virtual type_result resumeTest() = 0;
		virtual type_result stopTest() = 0;
		virtual type_result initializeNewFile() = 0;
		
	public:
		virtual NEType::Type getType() const;
		
	public:
		type_result onCallingDialog(NEPanel& caller_of_panel, type_index component_index_to_call, const NEExportable::Identifier& dialog_identifier);
		type_result onCallingDialog(NEPanel& caller_of_panel, NEComponent& caller_of_component, const NEExportable::Identifier& dialog_identifier);
	};
}
