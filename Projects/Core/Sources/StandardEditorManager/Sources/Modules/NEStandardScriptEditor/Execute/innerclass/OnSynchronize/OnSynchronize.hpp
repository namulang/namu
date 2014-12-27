class NE_DLL OnSynchronize
{
public:
	OnSynchronize(NEStandardScriptEditor& owner, const NECode& to_be_manipulated, bool is_insertion_mode);

public:
	type_result synchronize(NENode& target);
	const NECode& getCode() const;
	bool isInserting() const;
	NEStandardScriptEditor& getOwner();
	const NEStandardScriptEditor& getOwner() const;

protected:
	void _setCodesDirectly(NENode& target, const NECodeSet& new_codes) const;
	virtual type_result _onSynchronize(NENode& node_to_be_synchronized) = 0;

private:
	NEStandardScriptEditor& _owner;
	bool _is_insertion_mode;
	NECode _code;
};
