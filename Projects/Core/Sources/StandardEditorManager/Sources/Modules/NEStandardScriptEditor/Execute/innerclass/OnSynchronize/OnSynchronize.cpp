#include "../../NEStandardScriptEditor.hpp"

namespace NE
{
	NEStandardScriptEditor::OnSynchronize::OnSynchronize(NEStandardScriptEditor& owner, type_code to_be_manipulated, bool is_insertion_mode, NECodeType::CodeType code_type)
		: _owner(owner), _to_be_manipulated(to_be_manipulated), _is_insertion_mode(is_insertion_mode), _code_type(code_type) 
	{

	}
	void NEStandardScriptEditor::OnSynchronize::_setScriptCode(NENode& target, type_code new_scriptcode) const
	{
		_owner._setScriptCode(target, new_scriptcode);
	}
	void NEStandardScriptEditor::OnSynchronize::_setNameCode(NENode& target, type_code new_namecode) const
	{
		_owner._setNameCode(target, new_namecode);
	}
	void NEStandardScriptEditor::OnSynchronize::_setGroupCode(NENode& target, const NECodeSet& new_groupcode) const
	{
		_owner._setGroupCode(target, new_groupcode);
	}
	void NEStandardScriptEditor::OnSynchronize::_setPriorityCode(NENode& target, type_code new_priority) const
	{
		_owner._setPriorityCode(target, new_priority);
	}
	void NEStandardScriptEditor::OnSynchronize::_synchronizeCodesInKey(NEKey& key, type_code new_code)
	{
		_owner._synchronizeCodesInKey(key, _code_type, new_code, _is_insertion_mode);
	}

	type_code NEStandardScriptEditor::OnSynchronize::getCodeToBeManipulated() const
	{
		return _to_be_manipulated;
	}
	NECodeType::CodeType NEStandardScriptEditor::OnSynchronize::getCodeType() const
	{
		return _code_type;
	}
	bool NEStandardScriptEditor::OnSynchronize::isInserting() const
	{
		return _is_insertion_mode;
	}
	NEStandardScriptEditor& NEStandardScriptEditor::OnSynchronize::getOwner()
	{
		return _owner;
	}
	const NEStandardScriptEditor& NEStandardScriptEditor::OnSynchronize::getOwner() const
	{
		return _owner;
	}
	type_result NEStandardScriptEditor::OnSynchronize::synchronize(NENode& target)
	{
		type_result result = _onSynchronize(target);

		NEKeyCodeSet& keyset = target.getKeySet();
		for (int n = 0; n < keyset.getLength(); n++)
			_synchronizeCodesInKey(keyset[n], getCodeToBeManipulated());

		return result;
	}
}