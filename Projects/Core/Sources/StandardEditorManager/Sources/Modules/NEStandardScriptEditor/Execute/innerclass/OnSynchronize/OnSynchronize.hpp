class NE_DLL OnSynchronize
{
public:
	OnSynchronize(NEStandardScriptEditor& owner, bool is_insertion_mode, NECodeType::CodeType code_type);

	virtual type_result onSynchronize(NENode& node_to_be_synchronized, type_code to_be_manipulated) = 0;

protected:
	void _setScriptCode(NENode& target, type_code new_scriptcode) const;
	void _setNameCode(NENode& target, type_code new_namecode) const;
	void _setGroupCode(NENode& target, const NECodeSet& new_groupcode) const;
	void _setPriorityCode(NENode& target, type_code new_priority) const;
	void _synchronizeCodesInKey(NEKey& key, type_code new_code);

private:
	NEStandardScriptEditor& _owner;
	bool _is_insertion_mode;
	NECodeType::CodeType _code_type;
};
