
public:
	NETString& getPath();
	const NETString& getPath() const;
	HINSTANCE& getInstance();
	const HINSTANCE& getInstance() const;
	EntryPoint& getEntryPoint();
	const EntryPoint& getEntryPoint() const;
	
	//	인터페이스:
	//		상속
	//			NEObject:
public:
	virtual const NEClassBase& getClass() const;
	virtual void release();
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual type_result isValid() const;

private:
	virtual NEObject& clone() const;

	//		고유 함수:
public:
	bool isLoaded() const;

	//	내부함수:
private:	
	const DLLHeader& _assign(const DLLHeader& source);

	//	멤버변수:
protected:
	NETString _path;
	HINSTANCE _instance;
	EntryPoint _entrypoint;

public:
	static const NEClassBase& getClassStatically();
};