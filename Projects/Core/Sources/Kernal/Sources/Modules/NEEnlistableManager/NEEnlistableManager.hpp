#pragma once

#include "../NEModule/NEModule.hpp"
#include "../NEShortCutSet/NEShortCutSet.hpp"
#include "../NEIndexedNodeSet/NEIndexedNodeSet.hpp"
#include "../NEIndexedModuleSet/NEIndexedModuleSet.hpp"
#include "../NEIndexedKeySet/NEIndexedKeySet.hpp"

namespace NE
{
	class NE_DLL NEEnlistableManager : public NEModule, public NEEnlistable
	{
		NE_DECLARE_MODULE(NEEnlistableManager, NEModule)
		
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
		template <typename NodeSelector>
		friend class NETModuleSelector;
		template <typename ModuleSelector>
		friend class NETKeySelector;

	public:
		NEEnlistableManager();
		NEEnlistableManager(const This& source);
		~NEEnlistableManager();

	public:
		const This& operator=(const This& source);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

	public:
		const NEShortCutSet& getShortCutSet(const NECodeType& type) const;
		const NEIndexedKeySet& getKeySet() const;
		const NEIndexedModuleSet& getModuleSet() const;
		const NEIndexedNodeSet& getNodeSet() const;

	public:
		virtual type_result initialize();

		//			NEObject:
	public:
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual type_result isValid() const;

		//	내부 함수:
	protected:	
		//		접근자:
		NEShortCutSet& _getShortCutSet(const NECodeType& type);
		NEIndexedKeySet& _getKeySet();
		NEIndexedModuleSet& _getModuleSet();
		NEIndexedNodeSet& _getNodeSet();	

	protected:
		virtual type_result _onChangeCode(NENode& target, const NECodeSet& new_code);
		type_result _setCodesDirectly(NENode& target, const NECodeSet& new_code) const;

	protected:
		virtual type_result _enlist(NENode& target, type_index index = NE_INDEX_ERROR);
		virtual type_result _unlist(NENode& target, type_index index = NE_INDEX_ERROR);

	protected:
		type_index _searchRealNodeIndex(NENode& target) const;
		type_result _createShortCutSetAndFillWithShortCuts(NEShortCutSet& shortcutset, type_index size);
		void _release();

	private:
		const This& _assign(const This& source);

	private:
		NEIndexedKeySet _keyset;
		NEShortCutSet _priority_shortcutset;
		NEShortCutSet _script_shortcutset;
		NEShortCutSet _group_shortcutset;
		NEShortCutSet _name_shortcutset;
		NEIndexedNodeSet _nodeset;
		NEIndexedModuleSet _moduleset;
	};
}