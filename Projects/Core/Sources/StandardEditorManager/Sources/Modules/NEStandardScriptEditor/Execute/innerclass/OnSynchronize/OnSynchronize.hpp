class NE_DLL OnSynchronize
{
public:
	virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated) = 0;
	
protected:
	void _setScriptCode(NEStandardScriptEditor& owner, NENode& target, type_code new_scriptcode) const;
	void _setNameCode(NEStandardScriptEditor& owner, NENode& target, type_code new_namecode) const;
	void _setGroupCode(NEStandardScriptEditor& owner, NENode& target, const NECodeSet& new_groupcode) const;
	void _setPriorityCode(NEStandardScriptEditor& owner, NENode& target, type_code new_priority) const;
};