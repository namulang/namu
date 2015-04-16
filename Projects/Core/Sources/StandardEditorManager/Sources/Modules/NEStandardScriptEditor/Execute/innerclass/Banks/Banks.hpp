class NE_DLL Banks : public NEScriptEditor::Banks
{
public:
	typedef NEStandardScriptEditor::Banks ThisClass;
	typedef NEScriptEditor::Banks SuperClass;	

public:
	virtual type_result initialize();
	virtual NEObject& clone() const;
};