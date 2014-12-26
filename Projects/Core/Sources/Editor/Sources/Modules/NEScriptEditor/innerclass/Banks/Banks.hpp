class NE_DLL Banks : public NEArrayTemplate<NEBank>
{
public:
	typedef NEScriptEditor::Banks ThisClass;
	typedef NEArrayTemplate<NEBank> SuperClass;

public:
	const NEBank& getBank(const NECodeType& type) const;
	NEBank& getBank(const NECodeType& type);

public:
	virtual NEType::Type getType() const;
	virtual NEObject& clone() const;
};