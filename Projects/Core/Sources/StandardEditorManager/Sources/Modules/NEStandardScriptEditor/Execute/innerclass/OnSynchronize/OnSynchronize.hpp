class NE_DLL OnSynchronize
{
public:
	OnSynchronize(NEStandardScriptEditor& owner, type_code to_be_manipulated, bool is_insertion_mode, NECodeType::CodeType code_type);

public:
	type_result synchronize(NENode& target);
	type_code getCodeToBeManipulated() const;
	NECodeType::CodeType getCodeType() const;
	bool isInserting() const;
	NEStandardScriptEditor& getOwner();
	const NEStandardScriptEditor& getOwner() const;

protected:
	void _setScriptCode(NENode& target, type_code new_scriptcode) const;
	void _setNameCode(NENode& target, type_code new_namecode) const;
	void _setGroupCode(NENode& target, const NECodeSet& new_groupcode) const;
	void _setPriorityCode(NENode& target, type_code new_priority) const;
	void _synchronizeCodesInKey(NEKey& key, type_code new_code);
	virtual type_result _onSynchronize(NENode& node_to_be_synchronized) = 0;

private:
	NEStandardScriptEditor& _owner;
	bool _is_insertion_mode;
	NECodeType::CodeType _code_type;
	type_code _to_be_manipulated;
};
