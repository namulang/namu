#include "../../NEStandardScriptEditor.hpp"

namespace NE
{
	void NEStandardScriptEditor::OnSynchronize::_setScriptCode(NEStandardScriptEditor& owner, NENode& target, type_code new_scriptcode) const
	{
		owner._setScriptCode(target, new_scriptcode);
	}
	void NEStandardScriptEditor::OnSynchronize::_setNameCode(NEStandardScriptEditor& owner, NENode& target, type_code new_namecode) const
	{
		owner._setNameCode(target, new_namecode);
	}
	void NEStandardScriptEditor::OnSynchronize::_setGroupCode(NEStandardScriptEditor& owner, NENode& target, const NECodeSet& new_groupcode) const
	{
		owner._setGroupCode(target, new_groupcode);
	}
	void NEStandardScriptEditor::OnSynchronize::_setPriorityCode(NEStandardScriptEditor& owner, NENode& target, type_code new_priority) const
	{
		owner._setPriorityCode(target, new_priority);
	}
}