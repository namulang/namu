#include "../../NEStandardScriptEditor.hpp"

namespace NE
{
	NEStandardScriptEditor::OnSynchronize::OnSynchronize(NEStandardScriptEditor& owner, const NECode& to_be_manipulated, bool is_insertion_mode)
		: _owner(owner), _code(to_be_manipulated), _is_insertion_mode(is_insertion_mode)
	{

	}
	void NEStandardScriptEditor::OnSynchronize::_setCodesDirectly(NENode& target, const NECodeSet& new_codes) const
	{
		_owner._setCodesDirectly(target, new_codes);
	}
	const NECode& NEStandardScriptEditor::OnSynchronize::getCode() const
	{
		return _code;
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
			_owner._synchronizeCodesInKey(keyset[n], getCode(), _is_insertion_mode);

		return result;
	}
}