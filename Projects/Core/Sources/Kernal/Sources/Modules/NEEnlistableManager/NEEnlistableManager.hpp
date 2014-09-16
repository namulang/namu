#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NEPriorityShortCutSet/NEPriorityShortCutSet.hpp"
#include "../NEGroupShortCutSet/NEGroupShortCutSet.hpp"
#include "../NEScriptShortCutSet/NEScriptShortCutSet.hpp"
#include "../NENameShortCutSet/NENameShortCutSet.hpp"
#include "../NEIndexedNodeSet/NEIndexedNodeSet.hpp"
#include "../NEIndexedModuleSet/NEIndexedModuleSet.hpp"
#include "../NEIndexedKeySet/NEIndexedKeySet.hpp"

namespace NE
{
	class NE_DLL NEEnlistableManager : public NEModule, public NEEnlistable
	{
		typedef NEModule SuperClass;
		typedef NEEnlistableManager ThisClass;
		typedef NEIndexedKeySet* NEIndexedKeySetPointer;

	public:
		friend class NENode;
		friend class NENodeSelector;
		friend class NEModuleDepthUnit;
		friend class NEKeyCodeSet;
		friend class NEModuleCodeSet;
		friend class NENodeCodeSet;
		friend class NENodeBinder;
		friend class NEModuleBinder;
		friend class NEKeyBinder;
		template <typename NodeSelector, NEType::Type type>
		friend class NEModuleSelectorTemplate;
		template <typename ModuleSelector, NEType::Type type>
		friend class NEKeySelectorTemplate;

	public:
		NEEnlistableManager();
		NEEnlistableManager(const NEEnlistableManager& source);
		~NEEnlistableManager();

	public:
		const ThisClass& operator=(const ThisClass& source);
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;

	public:
		const NEShortCutSet& getScriptShortCutSet() const;
		const NEShortCutSet& getNameShortCutSet() const;
		const NEShortCutSet& getGroupShortCutSet() const;
		const NEShortCutSet& getPriorityShortCutSet() const;
		const NEIndexedKeySet& getKeySet() const;
		const NEIndexedModuleSet& getModuleSet() const;
		const NEIndexedNodeSet& getNodeSet() const;
		bool isSynchronizationDisabled() const;

	public:
		virtual type_result initialize();

		//			NEObject:
	public:
		virtual void release();
		virtual NEType::Type getType() const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual type_result isValid() const;

		//	내부 함수:
	protected:	
		//		접근자:
		NEShortCutSet& _getScriptShortCutSet();
		NEShortCutSet& _getNameShortCutSet();
		NEShortCutSet& _getGroupShortCutSet();
		NEShortCutSet& _getPriorityShortCutSet();
		type_result _setSynchronizationDisabled(bool enable);
		NEIndexedKeySet& _getKeySet();
		NEIndexedModuleSet& _getModuleSet();
		NEIndexedNodeSet& _getNodeSet();	

	protected:
		virtual type_result _onChangeNameCode(NENode& target, type_code new_namecode);
		virtual type_result _onChangePriorityCode(NENode& target, type_code new_prioritycode);
		virtual type_result _onChangeGroupCode(NENode& target, const NECodeSet& new_groupcodeset);
		void _setScriptCode(NENode& target, type_code new_scriptcode) const;
		void _setNameCode(NENode& target, type_code new_namecode) const;
		void _setGroupCode(NENode& target, const NECodeSet& new_groupcode) const;
		void _setPriorityCode(NENode& target, type_code new_priority) const;

	protected:
		virtual type_result _enlist(NENode& target, type_index index = NE_INDEX_ERROR);
		virtual type_result _unlist(NENode& target, type_index index = NE_INDEX_ERROR);

	protected:
		type_index _searchRealNodeIndex(NENode& target) const;
		type_result _createShortCutSetAndFillWithShortCuts(NEShortCutSet& shortcutset, type_index size);
		void _release();

	private:
		const ThisClass& _assign(const ThisClass& source);

	private:
		NEIndexedKeySet _keyset;
		NEPriorityShortCutSet _priority_shortcutset;
		NEScriptShortCutSet _script_shortcutset;
		NEGroupShortCutSet _group_shortcutset;
		NENameShortCutSet _name_shortcutset;
		NEIndexedNodeSet _nodeset;
		NEIndexedModuleSet _moduleset;
		bool _is_synchronization_disabled;
	};
}