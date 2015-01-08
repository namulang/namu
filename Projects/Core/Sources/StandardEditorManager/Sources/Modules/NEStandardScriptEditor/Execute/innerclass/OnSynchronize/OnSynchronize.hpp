class NE_DLL OnSynchronize
{
public:
	OnSynchronize(NEStandardScriptEditor& owner, const NECode& to_be_manipulated, bool is_insertion_mode);

public:
	const NECode& getCode() const;
	bool isInserting() const;
	NEStandardScriptEditor& getOwner();
	const NEStandardScriptEditor& getOwner() const;
	virtual type_result synchronize(NENodeCodeSet& ncs);
	virtual type_result synchronize(NEModuleCodeSet& mcs);
	virtual type_result synchronize(NEKey& key);
	virtual type_result synchronize(NECodeSet& cs);
	virtual bool synchronize(NECode& code);

protected:
	void _setCodesDirectly(NENode& target, const NECodeSet& new_codes) const;
	virtual type_result _onSynchronize(NENode& node_to_be_synchronized) = 0;	
	
protected:
	NEStandardScriptEditor& _owner;
	bool _is_insertion_mode;
	NECode _code;
	bool _stop_finding;
};
