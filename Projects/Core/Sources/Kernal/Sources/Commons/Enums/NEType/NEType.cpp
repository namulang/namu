#include "NEType.hpp"
#include "../../../Modules/NETString/NETString.hpp"

namespace NE
{
	namespace NEType
	{		
		//	supertype <= sub_type < super_type's max boundary
		bool NE_DLL isValidHierachy(int super_type, int sub_type)
		{
			//	pre:
			//	min-boundary 체크:	퍼포먼스 향상을 위해, min 값을 먼저 검사한다.
			if(super_type > sub_type) return false;
			if(sub_type == super_type) return true;


			//	post:
			//		여기까지 도달했다는 것은, child_type이 min 경계값보다 크다는 뜻이 된다. 따라서 max만 비교한다.
			return sub_type < _getMaxBoundary(super_type); // 작으면 true. 같아서는 false.			
		}


		int _getMaxBoundary(int x)
		{
			const int CACHE_SIZE = 10;
			static int cache[CACHE_SIZE] = { 1, 0, };
			if (!cache[1])
				for (int n = 1; n < CACHE_SIZE; n++)
					cache[n] = cache[n - 1] * 10;

			int valid = x;
			for (int cnt = 0; cnt < CACHE_SIZE; cnt++, x *= 0.1)
			{
				valid *= 0.1;
				if (valid * 10 != x)
					return (x + 1) * cache[cnt];
			}

			return -1;
		}

		LPCTSTR NE_DLL getTypeName(NEType::Type type)
		{
			switch(type)
			{
			case UNDEFINED:												return _T("Undefined");
			case NEOBJECT:												return _T("NEObject");
			case NEINNERCLASS:											return _T("NEInnerClass");
			case MODULE_DLL_HEADER:										return _T("ModuleDLLHeader");
			case SCRIPT_HEADER:											return _T("NEScriptHeader");
			case NENODE_DEPTH_UNIT:										return _T("NENodeDepthUnit");
			case NEMODULE_DEPTH_UNIT:									return _T("NEModuleDepthUnit");
			case PANEL_MANAGER_HEADER:									return _T("PanelManagerHeader");
			case SCRIPT_SELECTOR_CALLSTACK:								return _T("ScriptSelectorCallStack");
			case NESCRIPTEDITOR_BANKS:									return _T("NEScriptEditor::Banks");
			case KERNAL_SETTINGS:										return _T("Kernal::Settings");
			case KERNAL_MODIFIABLE_SETTINGS:							return _T("Kernal::ModifiableSettings");
			case KERNAL_FACTORY:										return _T("Kernal::Factory");
			case EDITOR_FACTORY:										return _T("Editor::Factory");
			case NEBINDER_BASE:											return _T("NEBinderBase");
			case NENODE_BINDER:											return _T("NENodeBinder");
			case NEMODULE_BINDER:										return _T("NEModuleBinder");
			case LOCALSTACK:											return _T("LocalStack");
			case IDENTIFIER:											return _T("Identifier");
			case HEADER:												return _T("Header");
			case MODULE_HEADER:											return _T("ModuleHeader");
			case NECODE:												return _T("NECode");
			case NECODE_TYPE:											return _T("NECodeType");
			case NECODE_KEY:											return _T("NECodeKey");
			case NECODE_SET_KEY:										return _T("NECodeSetKey");
			case EDITOR_MODIFIABLE_SETTINGS:							return _T("Editor::ModifiableSettings");
			case NEKEY_BINDER:											return _T("NEKeyBinder");
			case NEKEY_NAME_BINDER:										return _T("NEModule::NEKeyNameBinder");
			case NEARGUMENT_BASE:										return _T("NEArgumentBase");
			case NETARGUMENT:											return _T("NETArgument");			
			case NECOLLECTOR_TEMPLATE:									return _T("NECollectorTemplate");
			case NEARRAY_TEMPLATE:										return _T("NEArrayTemplate<T>");
			case NEBOOLEAN_SET:											return _T("NEBooleanSet");
			case NEBYTE_SET:											return _T("NEByteSet");
			case NECHAR_SET:											return _T("NECharSet");
			case NESTRING:												return _T("NEString");
			case NEDOUBLE_SET:											return _T("NEDoubleSet");
			case NEFLOAT_SET:											return _T("NEFloatSet");
			case NEINT64_SET:											return _T("NEInt64Set");
			case NEINT_SET:												return _T("NEIntSet");			
			case NECODE_SET:											return _T("NECodeSet");
			case NESHORT_SET:											return _T("NEShortSet");
			case NEUBYTE_SET:											return _T("NEUByteSet");
			case NEUSHORT_SET:											return _T("NEUShortSet");
			case NEUINT_SET:											return _T("NEUIntSet");
			case NEWCHAR_SET:											return _T("NEWCharSet");
			case NEWSTRING:												return _T("NEWString");
			case NEBANK:												return _T("NEBank");
			case NESHORTCUTSET:											return _T("NEShortCutSet");
			case NESTRING_SET:											return _T("NEStringSet");
			case NEWSTRING_SET:											return _T("NEWStringSet");
			case NEKEY_CODESET:											return _T("NEKeyCodeSet");
			case NEMODULE_CODESET:										return _T("NEModuleCodeSet");
			case NENODE_CODESET:										return _T("NENodeCodeSet");
			case NEROOT_NODE_CODESET:									return _T("NERootNodeCodeSet");
			case NEPOINTER_ARRAY_TEMPLATE:								return _T("NEArrayTemplate<T*, false>");
			case NEPOINTER_ARRAY_WITH_POLYMORPHISM_TEMPLATE:			return _T("NEArrayTemplate<T*, true>");
			case NEKEYSET:												return _T("NEKeySet");
			case NEPANELSET:											return _T("NEPanelSet");
			case NEMODULESET:											return _T("NEModuleSet");
			case NELIST_TEMPLATE:										return _T("NEListTemplate<T>");
			case NENODE_LIST:											return _T("NENodeList");			
			case NESTRING_LIST:											return _T("NEStringList");
			case NEWSTRING_LIST:										return _T("NEWStringList");
			case NEMODULE_DEPTH_LIST:									return _T("NEModuleDepthList");
			case NENODE_DEPTH_LIST:										return _T("NENodeDepthList");
			case NEPOINTER_LIST_TEMPLATE:								return _T("NEListTemplate<T*, false>");
			case NESHORTCUT:											return _T("NEShortCut");
			case NEPOINTER_LIST_WITH_POLY_MORPHISM_TEMPLATE:			return _T("NEListTemplate<T*, true>");
			case NEMODULE_LIST:											return _T("NEModuleList");
			case NEPANEL_LIST:											return _T("NEPanelList");
			case NEINDEXED_ARRAY_TEMPLATE:								return _T("NEIndexedArrayTemplate<T>");
			case NEINDEXED_NODESET:										return _T("NEIndexedNodeSet");
			case NEPOINTER_INDEXED_ARRAY_TEMPLATE:						return _T("NEIndexedArrayTemplate<T*, false>");
			case NEPOINTER_INDEXED_ARRAY_WITH_POLYMORPHISM_TEMPLATE:	return _T("NEIndexedArrayTemplate<T*, true>");
			case NEINDEXED_KEYSET:										return _T("NEIndexedKeySet");
			case NEINDEXED_MODULESET:									return _T("NEIndexedModuleSet");
			case NEUNIT:												return _T("NEUnit");
			case NESWITCHABLE_UNIT:										return _T("NESwitchableUnit");
			case NEEXCUTABLE_UNIT:										return _T("NEExecutableUnit");
			case NENAMED_UNIT:											return _T("NENamedUnit");
			case NEMODULE:												return _T("NEModule");
			case NEINI_MANAGER:											return _T("NEINIManager");
			case NEMODULE_MANAGER:										return _T("NEModuleManager");
			case NENODE_MANAGER:										return _T("NENodeManager");
			case NESCRIPT_MANAGER:										return _T("NEScriptManager");
			case NEDEBUG_MANAGER:										return _T("NEDebugManager");
			case KERNAL:												return _T("Kernal");
			case EDITOR:												return _T("Editor");
			case NESCRIPT_EDITOR:										return _T("NEScriptEditor");
			case NEPANEL_MANAGER:										return _T("NEPanelManager");
			case NEEVENT_HANDLER:										return _T("NEEventHandler");
			case NENODE:												return _T("NENode");
			case NEPANEL:												return _T("NEPanel");
			case NEDIALOG:												return _T("NEDialog");
			case NEKEY:													return _T("NEKey");
			case KIND_OF_ARITHMETIC_KEY:								return _T("Kind Of Arithmetic Key");
			case NEBOOLEAN_KEY:											return _T("NEBooleanKey");
			case NECHAR_KEY:											return _T("NECharKey");
			case NEBYTE_KEY:											return _T("NEByteKey");
			case NEUBYTE_KEY:											return _T("NEUByteKey");
			case NEWCHAR_KEY:											return _T("NEWCharKey");
			case NESHORT_KEY:											return _T("NEShortKey");
			case NEUSHORT_KEY:											return _T("NEUShortKey");
			case NEINT_KEY:												return _T("NEIntKey");
			case NEUINT_KEY:											return _T("NEUIntKey");			
			case NEINT64_KEY:											return _T("NEInt64Key");
			case NEFLOAT_KEY:											return _T("NEFloatKey");
			case NEDOUBLE_KEY:											return _T("NEDoubleKey");
			case KIND_OF_STRING_KEY:									return _T("Kind Of String Key");
			case NESTRING_KEY:											return _T("NEStringKey");
			case NEWSTRING_KEY:											return _T("NEWStringKey");
			case NEBOOLEAN_SET_KEY:										return _T("NEBooleanSetKey");
			case NEBYTE_SET_KEY:										return _T("NEByteSetKey");
			case NEUBYTE_SET_KEY:										return _T("NEUByteSetKey");
			case NESHORT_SET_KEY:										return _T("NEShortSetKey");
			case NEUSHORT_SET_KEY:										return _T("NEUShortSetKey");
			case NEINT_SET_KEY:											return _T("NEIntSetKey");
			case NEUINT_SET_KEY:										return _T("NEUIntSetKey");
			case NEINT64_SET_KEY:										return _T("NEInt64SetKey");
			case NEFLOAT_SET_KEY:										return _T("NEFloatSetKey");
			case NEDOUBLE_SET_KEY:										return _T("NEDoubleSetKey");
			case NESTRING_SET_KEY:										return _T("NEStringSetKey");
			case NEWSTRING_SET_KEY:										return _T("NEWStringSetKey");
			case NENODE_CODESET_KEY:									return _T("NENodeCodeSetKey");
			case NEMODULE_CODESET_KEY:									return _T("NEModuleCodeSetKey");			
			case NENODE_SELECTOR:										return _T("NENodeSelector");
			case NEMODULE_SELECTOR:										return _T("NEModuleSelector");
			case NEKEY_SELECTOR:										return _T("NEKeySelector");
			case NECOMPONENT:											return _T("NEComponent");
			case NETEXT_COMPONENT:										return _T("NETextComponent");
			case NELIST_COMPONENT:										return _T("NEListComponent");
			case NECHECKLIST_COMPONENT:									return _T("NECheckListComponenta");
			case NEMODIFIABLE_LIST_COMPONENT:							return _T("NEModifiableListComponent");
			case NESWITCH_COMPONENT:									return _T("NESwitchComponent");
			case NEBUTTON_COMPONENT:									return _T("NEButtonComponent");

			default:
				return _T("UNKNOWN");
			}
		}
	}
}
