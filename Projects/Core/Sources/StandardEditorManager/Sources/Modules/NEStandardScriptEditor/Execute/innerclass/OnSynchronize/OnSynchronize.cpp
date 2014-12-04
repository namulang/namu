
#include "../../NEStandardScriptEditor.hpp"

namespace NE
{
	NEStandardScriptEditor::OnSynchronize::OnSynchronize(NEStandardScriptEditor& owner, bool is_insertion_mode, NECodeType::CodeType code_type)
		: _owner(owner), _is_insertion_mode(is_insertion_mode), _code_type(code_type) 
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
}