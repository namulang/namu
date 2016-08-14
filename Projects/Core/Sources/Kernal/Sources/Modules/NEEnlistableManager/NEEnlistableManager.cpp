#include "NEEnlistableManager.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
/*
	C4355경고 무시:
		경고가 나오는 이유:
			일반적으로, this 포인터를 넘기면, 넘긴쪽에서 생성자가 초기화되지
			않았는데도, 넘겨받은 쪽에서 사용할 여지가 있기 때문이다.
		무시하는 이유:
			아래와 같은 경우, 절대로 "생성자에서 호출 하지 않으"므로 사용한다.
*/
#pragma warning(push)	
#pragma warning(disable:4355)
	NEEnlistableManager::NEEnlistableManager()
		: Super(), _nodeset(*this), _moduleset(*this), _keyset(*this),
		_script_shortcutset(/*NECodeType::SCRIPT*/),
		_name_shortcutset(/*NECodeType::NAME*/),
		_group_shortcutset(/*NECodeType::GROUP*/),
		_priority_shortcutset(/*NECodeType::PRIORITY*/)
	{
		_release();
	}

	NEEnlistableManager::NEEnlistableManager(const NEEnlistableManager& source)
		: Super(source), _nodeset(*this), _moduleset(*this), _keyset(*this),
		_script_shortcutset(source._script_shortcutset),
		_name_shortcutset(source._name_shortcutset),
		_group_shortcutset(source._group_shortcutset),
		_priority_shortcutset(source._priority_shortcutset)
	{
		_assign(source);
	}
#pragma warning(pop)

	type_result NEEnlistableManager::_enlist(NENode& target, type_index index/*= NE_INDEX_ERROR*/)
	{
		if(index <= NE_INDEX_ERROR) 
			index = _searchRealNodeIndex(target);


		type_result result = _getShortCutSet(/*NECodeType::SCRIPT*/)._enlist(target, index);
		result |= _getShortCutSet(/*NECodeType::NAME*/)._enlist(target, index);
		result |= _getShortCutSet(/*NECodeType::GROUP*/)._enlist(target, index);
		return result |= _getShortCutSet(/*NECodeType::PRIORITY*/)._enlist(target, index);
	}

	type_result NEEnlistableManager::_unlist(NENode& target, type_index index/*= NE_INDEX_ERROR*/)
	{
		if(index <= NE_INDEX_ERROR) 
			index = _searchRealNodeIndex(target);



		type_result result = _getShortCutSet(/*NECodeType::SCRIPT*/)._unlist(target, index);
		result |= _getShortCutSet(/*NECodeType::NAME*/)._unlist(target, index);
		result |= _getShortCutSet(/*NECodeType::GROUP*/)._unlist(target, index);
		result |= _getShortCutSet(/*NECodeType::PRIORITY*/)._unlist(target, index);

		target._manager = NE_NULL;

		return result;
	}

	NEIndexedKeySet& NEEnlistableManager::_getKeySet()
	{
		return _keyset;
	}

	const NEIndexedKeySet& NEEnlistableManager::getKeySet() const
	{
		return _keyset;
	}

	NEIndexedModuleSet& NEEnlistableManager::_getModuleSet()
	{
		return _moduleset;
	}

	const NEIndexedModuleSet& NEEnlistableManager::getModuleSet() const
	{
		return _moduleset;
	}

	NEIndexedNodeSet& NEEnlistableManager::_getNodeSet()
	{
		return _nodeset;
	}

	const NEIndexedNodeSet& NEEnlistableManager::getNodeSet() const
	{
		return _nodeset;
	}

	void NEEnlistableManager::release()
	{
		Super::release();
	
		_release();
	}

	type_result NEEnlistableManager::isValid() const
	{
		type_result result = Super::isValid();
		result |= _priority_shortcutset.isValid();
		result |= _group_shortcutset.isValid();
		result |= _script_shortcutset.isValid();
		result |= _name_shortcutset.isValid();
		result |= _nodeset.isValid();
		result |= _moduleset.isValid();
		result |= _keyset.isValid();

		return result;
	}

	NEBinaryFileLoader& NEEnlistableManager::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);
		
		loader	>> _priority_shortcutset >> _script_shortcutset >> _group_shortcutset >> _name_shortcutset >> _nodeset >> _moduleset >> _keyset;
		
		return loader;
	}

	NEBinaryFileSaver& NEEnlistableManager::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver	<< _priority_shortcutset << _script_shortcutset << _group_shortcutset << _name_shortcutset << _nodeset << _moduleset << _keyset;
	}

	type_index NEEnlistableManager::_searchRealNodeIndex(NENode& target) const
	{
		const NEIndexedNodeSet& nodeset = getNodeSet();

		for(int n=0; n < nodeset.getSize() ;n++)
		{
			const NENode& node = nodeset.getElement(n);
			if(&node == &target)
				return n;
		}

		return NE_INDEX_ERROR;
	}

	type_result NEEnlistableManager::_onChangeCode(NENode& target, const NECodeSet& new_codes)
	{
		if(target.getCodes(new_codes.getCodeType()) == new_codes) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if (new_codes.getCodeType() == NECodeType::SCRIPT) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

		//	main:
		type_index real_index = _searchRealNodeIndex(target);
		NEShortCutSet& shortcutset = _getShortCutSet(new_codes.getCodeType());
		if (!&shortcutset)	return RESULT_TYPE_WARNING;
		type_result result = shortcutset._unlist(target, real_index);
		if (NEResult::hasError(result))
			ALERT_WARNING(" : 이미 unlist 되어있는 노드입니다.");		

		_setCodesDirectly(target, new_codes);

		return shortcutset._enlist(target, real_index);
	}

	type_result NEEnlistableManager::_createShortCutSetAndFillWithShortCuts(NEShortCutSet& shortcutset, type_index size)
	{
		if( ! &shortcutset)
		{
			KERNAL_ERROR(" : 숏컷셋이 없습니다");
			return RESULT_SUCCESS;
		}



		//	main:
		type_result result = RESULT_SUCCESS;
		result |= shortcutset.create(size);
		for(int n=0; n < shortcutset.getSize() ;n++)
			result |= shortcutset.push(NEShortCut());

		return result;
	}

	void NEEnlistableManager::_release()
	{
		_nodeset.release();
		_moduleset.release();		
		_keyset.release();
		_priority_shortcutset.release();
		_script_shortcutset.release();
		_group_shortcutset.release();
		_name_shortcutset.release();		
	}

	const NEEnlistableManager& NEEnlistableManager::operator=(const This& source)
	{
		Super::operator=(source);

		return _assign(source);
	}

	const NEEnlistableManager& NEEnlistableManager::_assign(const This& source)
	{
		if(this == &source) return *this;

		_priority_shortcutset = source._priority_shortcutset;
		_script_shortcutset = source._script_shortcutset;
		_group_shortcutset = source._group_shortcutset;
		_name_shortcutset = source._name_shortcutset;
		_nodeset = source._nodeset;
		_moduleset = source._moduleset;
		_keyset = source._keyset;

		return *this;
	}

	type_result NEEnlistableManager::initialize()
	{
		return RESULT_SUCCESS;
	}

	NEEnlistableManager::~NEEnlistableManager()
	{

	}

	type_bool NEEnlistableManager::operator==(const This& source) const
	{
		if(Super::operator!=(source)) return false;
		if(	_keyset != source._keyset											||
			_priority_shortcutset != source._priority_shortcutset				||
			_script_shortcutset != source._script_shortcutset					||
			_group_shortcutset != source._group_shortcutset						||
			_name_shortcutset != source._name_shortcutset						||
			_nodeset != source._nodeset											||
			_moduleset != source._moduleset										)
			return false;
		
		return true;
	}

	type_bool NEEnlistableManager::operator!=(const This& source) const
	{
		return ! operator==(source);
	}

	NEShortCutSet& NEEnlistableManager::_getShortCutSet(const NECodeType& type)
	{
		NEShortCutSet* nullpointer = 0x00;
		if( ! &type) 
			return *nullpointer;


// 		//	main:
// 		switch(type.getCodeType())
// 		{
// 		case NECodeType::ALL:
// 		case NECodeType::SCRIPT:	return _script_shortcutset;
// 		case NECodeType::NAME:		return _name_shortcutset;
// 		case NECodeType::GROUP:		return _group_shortcutset;
// 		case NECodeType::PRIORITY:	return _priority_shortcutset;
// 		}

		return *nullpointer;
	}

	const NEShortCutSet& NEEnlistableManager::getShortCutSet(const NECodeType& type) const
	{
		This* unconsted = const_cast<This*>(this);

		return unconsted->_getShortCutSet(type);
	}

	type_result NEEnlistableManager::_setCodesDirectly(NENode& target, const NECodeSet& new_codes) const
	{
		return target._setCodesDirectly(new_codes);
	}
}