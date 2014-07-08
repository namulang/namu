//	---------------------------------------------------------------------------------
//	클래스명:	NEModuleManager::DLLHeader
//	설명	:	모듈매니져에 의해서 fetch되는 DLL의 헤더.
//				나중에 DLL을 닫을때 필요해 진다.
//	관계	:	기반클래스.	NEObject
//	특성	:	
//	알고리즘:	
//	사용방법:	
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
typedef NEModuleList (NE_FUNCTION_CALL *EntryPoint)(void);

class NE_DLL DLLHeader : public NEObject
{
	//	생성자:
public:
	DLLHeader();	
	DLLHeader(const DLLHeader& source);	

	//	소멸자:
public:
	~DLLHeader();

	//	연산자 중첩:
public:	
	const DLLHeader& operator=(const DLLHeader& source);
	bool operator==(const DLLHeader& source) const;
	bool operator!=(const DLLHeader& source) const;
	
public:
	NETString& getPath();
	const NETString& getPath() const;
	HINSTANCE& getInstance();
	const HINSTANCE& getInstance() const;
	EntryPoint& getEntryPoint();
	const EntryPoint& getEntryPoint() const;
	
	//	인터페이스:
	//		상속:
	//			NEObject:
public:
	virtual void release();
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual type_result isValid() const;
	virtual NEType::Type getType() const;

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
};