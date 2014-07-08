class NE_DLL MouseSpyConnector : public NEModule::BaseConnector
{
public:
	MouseSpyConnector();

public:
	~MouseSpyConnector();

public:
	virtual type_result connect(NEKeySet& keyset);

public:
	NEIntKey& getCursorX();
	const NEIntKey& getCursorX() const;
	NEIntKey& getCursorY();
	const NEIntKey& getCursorY() const;

protected:
	void _release();

protected:
	NEIntKey* _cursor_x;
	NEIntKey* _cursor_y;
};