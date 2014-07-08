 #include <iostream>
 using namespace std;

#define DEVELOPER
#define CORES_BUILD_MODE
#include "../Kernal/Sources/EntryPoints/Headers.hpp"
using namespace NE;
#pragma comment(lib, "../../../Binaries/Core/Kernal.dev.dbg.lib")

template <typename T>
struct MKS : public T
{
	type_index g(int index) const { return _getElement(index); }
};
struct MES : public NENodeManager
{
	NEIndexedNodeSet& _getn() { return _getNodeSet(); }
	NEIndexedModuleSet& _getm() { return _getModuleSet(); }
	NEIndexedKeySet& _getk() { return _getKeySet(); }
};

void printSpace(int level = 0)
{
	for(int n=0; n < level ;n++)
		cout << " ";
}

void print(const NENodeCodeSet& ks, int level = 0);
void print(const NEModuleCodeSet& ks, int level = 0);
void print(const NEKeyCodeSet& ks, int level = 0);
void print(const NENode& ks, int level = 0);
void print(const NEIndexedNodeSet& ns, int level = 0);
void print(const NEIndexedModuleSet& ns, int level = 0);
void print(const NEIndexedKeySet& ns, int level = 0);

void print(const NENodeCodeSet& ks, int level)
{
	const MKS<NENodeCodeSet>& mks = (const MKS<NENodeCodeSet>&)(ks);
	cout << "NodeCodeSet[" << ks.getSize() << "] : \n";
	for(int n=0; n < ks.getLength() ;n++)
	{
		printSpace(level);
		cout << n << " : " << mks.g(n) << endl;
		print(ks[n], level+1);
	}
}

void print(const NEModuleCodeSet& ks, int level)
{
	const MKS<NEModuleCodeSet>& mks = (const MKS<NEModuleCodeSet>&)(ks);
	cout << "ModuleCodeSet:" << ks.getSize() << "\n";
	for(int n=0; n < ks.getLength() ;n++)
	{
		printSpace(level);
		cout << n << " : " << mks.g(n) << endl;
		const NEModule& m = ks[n];
		if(&m)
			cout << NEString(ks[n].getHeader().getName()).toCharPointer() << endl;
	}
}
void print(const NEModuleSet& ms, int level = 0)
{
	cout << "Modules:" << ms.getSize() << "\n";
	for(int n=0; n < ms.getLength() ;n++)
	{
		printSpace(level);
		cout << n << " : " << NEString(ms[n].getHeader().getName()).toCharPointer() << endl;
	}
}
void print(const NEKey& key, int level)
{
	if( ! &key) {
		cout << "null\n";
		return;
	}
	if(key.getType() == NEType::NEMODULE_CODESET_KEY)
		print(((const NEModuleCodeSetKey&)(key)).getValue(), level+1);
	else if(key.getType() == NEType::NENODE_CODESET_KEY)
		print(((const NENodeCodeSetKey&)(key)).getValue(), level+1);
}
void print(const NEKeyCodeSet& ks, int level)
{
	const MKS<NEKeyCodeSet>& mks = (const MKS<NEKeyCodeSet>&)(ks);
	cout << "KeyCodeSet:" << ks.getSize() << "\n";
	for(int n=0; n < ks.getLength() ;n++)
	{
		printSpace(level);
		cout << n << " : " << mks.g(n) << endl;
		const NEKey& key = ks[n];
		print(key, level+1);
	}
}

void print(char* string, const NEShortCutSet& shortcutset)
{
	cout << string << "(" << shortcutset.getLength() << "):\n";
	for(int n=0; n < shortcutset.getLength() ;n++)
	{
		cout << n << " : ";
		for(int n2=0; n2 < shortcutset[n].getLength() ;n2++)
			cout << shortcutset[n][n2] << ",\t";
		cout << endl;
	}
}

void print(NENodeManager& manager, int level = 0)
{
	MES& mes = (MES&)(manager);
	cout << "-------NENodeManager:-----------\n";
	print(mes.getRootNodes(), level+1);
	print("ScriptShortCut : ", mes.getScriptShortCutSet());
	print("NameShortCut : ", mes.getNameShortCutSet());
	print("GroupShortCut : ", mes.getGroupShortCutSet());
	print("PriorityShortCut : ", mes.getPriorityShortCutSet());
	print(mes._getn(), level+1);
	print(mes._getm(), level+1);
	print(mes._getk(), level+1);
}
void print(const NENode& node, int level)
{
	cout << "NENode :\n";
	node.isRootNode() ? cout << "ROOT!, " : cout << "SUB!, ";
	node.isEnlisted() ? cout << "Enlisted!\n" : cout << "NotEnlisted!\n";
	cout << "Manager* : " << &node.getManager() << ", Owner* : " << &node.getOwner();

	printSpace(level);
	print(node.getModuleSet(), level+1);
}
void print(const NEArgumentSet& set, int level)
{
	
	for(int n=0; n < set.getLength(); n++)
	{
		printSpace(level);
		cout << "(keyname:" << NEString(set[n].getBinder().getKeyName()).toCharPointer() << ", rindex:" << set[n].getBinder().getRealIndex();
	}
}
void print(const NEIndexedNodeSet& ns, int level)
{
	cout << "NEIndexedNodeSet : " << ns.getSize() << "\n";
	for(int n=0; n < ns.getSize(); n++)
	{
		if( & ns[n])
		{
			printSpace(level);
			cout << n << " : Alive!\n";
		}
	}
}
void print(const NEIndexedModuleSet& ns, int level)
{
	cout << "NEIndexedModuleSet :" << ns.getSize() << "\n";
	for(int n=0; n < ns.getSize(); n++)
	{
		if( & ns[n])
		{
			printSpace(level);
			if(NEString(ns[n].getHeader().getName()).toCharPointer())
				cout << n << " : " << NEString(ns[n].getHeader().getName()).toCharPointer() << "\n";
		}
	}
}
void print(const NEIndexedKeySet& ns, int level)
{
	cout << "NEIndexedKeySet :" << ns.getSize() << "\n";
	for(int n=0; n < ns.getSize(); n++)
	{
		if( & ns[n])
		{
			printSpace(level);
			cout << n << " : Alive!\n";
		}
	}
}

struct MyM : public NEModule
{
	NEObject& clone() const {return *(new MyM(*this));}
	type_result execute() { return RESULT_SUCCESS; }
	const NEExportable::ModuleHeader& getHeader() const {
		static NEExportable::ModuleHeader d; 

		d.getName() = "MyM";
		
		return d; 
	}

};

template <typename O, NEType::Type T>
void prn(NEArrayTemplate<type_code, false, O, T>& src) {
	cout << src.getTypeName() <<  "[" << src.getSize() << "] : ";
	
	for(int n=0; n < src.getLength(); n++)
		cout << &src[n] << "(" << src.getInnerElement(n) << "), ";

	cout << "\n";
}

class MyMod : public NEModule
{
public:
	void setScript(type_code new1)
	{
		_scriptcode = new1;
	}
	NEArgumentInterfaceTemplate<NEIntKey> a;
	virtual type_result _onArgumentsFetched(NEArgumentInterfaceList& tray)
	{
		a.getDefault().getValue() = 55;		
		return tray.push(&a);
	}

	virtual type_result execute()
	{
		a.getValue() = a.getValue()++;
		cout << (a.getValue() == 5 ? "SUCCESS!": "FAILURE") << "\n";

		return RESULT_SUCCESS;
	}
	virtual const NEExportable::ModuleHeader& getHeader() const
	{
		static NEExportable::ModuleHeader _header;
		if(_header.getName().getLength() <= 0)
		{
			_header.getName() = "MyMod";
			_header.getDeveloper() = "kniz";
			_header.setRevision(1);
		}

		return _header;
	}
	virtual NEObject& clone() const { return * (new MyMod(*this)); }
};

void init()
{
	NEModuleSet& ms = const_cast<NEModuleSet&>(Kernal::getInstance().getModuleManager().getModuleSet());
	ms.resize(ms.getLength() + 1);
	MyMod& added = (MyMod&) ms[ms.push(MyMod())];
	added.setScript(ms[ms.getLengthLastIndex()-1].getScriptCode()+1);
	
	
}
void main()
{
	NE_MEMORYLEAK;

	std::wcout.imbue( std::locale("korean") );
	
	Kernal::Factory factory;
	factory.getNodeManagerIdentifier() = NEExportable::Identifier("NEStandardNodeManager", "haku", 1);
	factory.getScriptManagerIdentifier() = NEExportable::Identifier("NEStandardScriptManager", "haku", 1);
	factory.getDefaultSettings().setModuleDirectory("../../../../../SDK/Libraries/Modules/");

	Kernal::setInstance( *(new Kernal(factory.create())) );

	Kernal& kernal = Kernal::getInstance();
	kernal.getDebugManager().setDebugMode(false);	//	디버그 모드를 끈다. 로그 없앰
	kernal.initialize();

	init();

	NENodeManager& manager = Kernal::getInstance().getNodeManager();
	NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
	const NEModuleSet& moduleset = moduler.getModuleSet();
	NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
	NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();
	ss.setMaxPriorityCodeIndex(5);
	ss.setMaxScriptCodeIndex(5);
	ss.setMaxGroupCodeIndex(2);
	NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
	NERootNodeCodeSet& ns = manager.getRootNodes();

	

	//	String 형변환 테스트:
	//		해당 기능은 2014-06-22 구현됨
	if(1)
	{
		NEWCharSet buf(3);
		buf.push(L'1');
		buf.push(L'2');
		buf.push(L'\0');
		NEString	a(true),
					b(buf),
					c( unsigned short(55555)),
					d( unsigned int(555555555)),
					e( float(4.5f) );

		cout << "String 형변환 테스팅 (샘플5) 결과 --> " << (a == "true" && b == "12" && c == "55555" && d == "555555555" && e == "4.500000" ? "SUCCESS!" : "FAILURE") << "\n";
		{
			NECharSet buf(3);
			buf.push(L'1');
			buf.push(L'2');
			buf.push(L'\0');
			NEWString	a(true),
						b(buf),
						c( unsigned short(55555)),
						d( unsigned int(555555555)),
						e( float(4.5f) );

			cout << "WString 형변환 테스팅 (샘플5) 결과 --> " << (a == "true" && b == "12" && c == "55555" && d == "555555555" && e == "4.500000" ? "SUCCESS!" : "FAILURE") << "\n";
		}
	}
	
	

	//	TEST0	:	모듈 Arugments 바인딩 & 깊은 복사 테스팅 -> NEModule::_bindArgument자동 바인딩, KeyNameBinding, 모듈execution, 복사까지. 
	if(0)
	{
		NENode& tg = ns[ns.push(NENode())];
		NEKeyCodeSet& ks = tg.getKeySet();
		ks.create(1);
		ks.push(NEIntKey("age", 5));
		NEModuleCodeSet& ms = tg.getModuleSet();
		ms.create(2);
		NEModule& m = ms[ms.push(MyMod())];
		m.getArguments()[0].getBinder().setKeyName("age");

		cout << "Argument Fetching & Binding 테스트 결과 --> ";
		manager.execute();

		ms.push(ms[0]);
		cout << "복사 테스트. 서로 일치 되는가?:\n";
		print(ms[0].getArguments(), 0);
		print(ms[1].getArguments(), 0);
		ns.release();
	}

	//	TEST1	:	인스턴스를 삽입하기
	if(0)
	{
		manager.initialize();
		cout << "Node Checking!----------------------- \n";
		ns.push(NENode());
		
		NENode& tg = ns[ns.push(NENode())];
		NEModuleCodeSet& ms = tg.getModuleSet();
		ns.push(NENode());
		ns.push(NENode());
		ns.push(NENode());
		
		prn(ns);
		ns.resize(5);
		prn(ns);
		ns.resize(7);
		prn(ns);		
		ns.resize(3);
		prn(ns);

		cout << "\nModuleChecking! -------------------------\n";
		ms.create(5);
		NEKeyCodeSet& ks = tg.getKeySet();
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());

		prn(ms);
		ms.resize(15);
		prn(ms);
		ms.resize(1);
		prn(ms);

		cout << "\nKey Chekcking! -------------------------\n";
		ks.create(5);
		ks.push(NEIntKey(5));
		ks.push(NEFloatKey(4.5f));
		ks.push(NETStringKey("gogoood!"));
		ks.push(NEBooleanKey(true));
		ks.push(NENodeSelector());
	
		prn(ks);
		ks.resize(9);		
		prn(ks);
		ks.resize(4);
		prn(ks);

		ns.release();
	}

	if(0)
	{
		manager.initialize();
		ns.push(NENode());

		NENode& tg = ns[ns.push(NENode())];
		NEModuleCodeSet& ms = tg.getModuleSet();
		{
			NECodeSet a(1);
			a.push(1);
			tg.setGroupCode(a);
		}
		ns.push(NENode());
		ns.push(NENode());
		ns.push(NENode());

		ns.resize(5);
			ns.resize(7);
		ns.resize(3);
		ms.create(5);
		NEKeyCodeSet& ks = tg.getKeySet();
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());

		ms.resize(15);
			ms.resize(1);
		
		ks.create(5);
		ks.push(NEIntKey(5));
		ks.push(NEFloatKey(4.5f));
		ks.push(NETStringKey("sentence", "gogoood!"));
		ks.push(NEBooleanKey(true));
		NENodeSelector& targ = (NENodeSelector&) ks[ks.push(NENodeSelector())];

		ks.resize(9);		
		ks.resize(4);
		
		NEKeySelector s;
		s.setNodeType(NECodeType::GROUP);
		{
			NEIntSet a(1);
			a.push(1);
			s.setCodeSet(a);
			s.setKeyName("sentence");			
		}
		NETStringKey& tk = (NETStringKey&) s.getKey();
		cout << "KeySelector 검색 테스트 결과 -->" << (tk.getValue() == "gogoood!" ? "데이터 검증완료" : "데이터 검증 실패") << ", " << (tk.getName() == "sentence" ? "키이름 검증 성공" : "키 이름 검증 실패") << "\n";
		
		
		ns.release();
	}

	if(1)
	{
		manager.initialize();
		cout << "TEST 4 : 저장 & 로드 테스팅 결과 --> ";
		ns.push(NENode());

		NENode& tg = ns[ns.push(NENode())];
		NEModuleCodeSet& ms = tg.getModuleSet();
		{
			NECodeSet a(1);
			a.push(1);
			tg.setGroupCode(a);
		}
		ns.push(NENode());
		ns.push(NENode());
		ns.push(NENode());

		ns.resize(5);
		ns.resize(7);
		ns.resize(3);
		ms.create(5);
		NEKeyCodeSet& ks = tg.getKeySet();
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());

		ms.resize(15);
		ms.resize(1);

		ks.create(5);
		ks.push(NEIntKey(5));
		ks.push(NEFloatKey(4.5f));
		ks.push(NETStringKey("sentence", "gogoood!"));
		ks.push(NEBooleanKey(true));
		NENodeSelector& targ = (NENodeSelector&) ks[ks.push(NENodeSelector())];

		ks.resize(9);		
		ks.resize(4);

		NEBinaryFileSaver saver(L"temp.dat", NEFILESAVERFLAG_OVERWRITE);
		saver.open();
		saver << manager;
		saver.close();

// 		cout << "저장된 Node Structure:\n";
// 		print(manager, 0);
// 		cout << "\n키셀렉터로 데이터를 찾습니다 : \n";
		{
			NEKeySelector s;
			s.setNodeType(NECodeType::GROUP);
			{
				NEIntSet a(1);
				a.push(1);
				s.setCodeSet(a);
				s.setKeyName("sentence");			
			}
			NETStringKey& tk = (NETStringKey&) s.getKey();
			cout << "사전 검증 실시 -->" << (tk.getValue() == "gogoood!" ? "데이터 검증완료" : "데이터 검증 실패") << ", " << (tk.getName() == "sentence" ? "키이름 검증 성공" : "키 이름 검증 실패") << "\n";
		}		

		cout << "데이터 초기화...";
		manager.initialize();
		
		NEBinaryFileLoader loader(L"temp.dat");
		loader.open();
		loader >> manager;
		loader.close();
		cout << "데이터 로드 완료...\n";
		
		{
			NEKeySelector s;
			s.setNodeType(NECodeType::GROUP);
			{
				NEIntSet a(1);
				a.push(1);
				s.setCodeSet(a);
				s.setKeyName("sentence");			
			}
			NETStringKey& tk = (NETStringKey&) s.getKey();
			cout << "사후 검증 실시 -->" << (tk.getValue() == "gogoood!" ? "데이터 검증완료" : "데이터 검증 실패") << ", " << (tk.getName() == "sentence" ? "키이름 검증 성공" : "키 이름 검증 실패") << "\n";
		}
	}
	
	Kernal::saveSettings();
	delete &kernal;

	system("pause");
}
// 
// class Mine : public NEArrayTemplate<int, false, NEString>
// {
// public:
// 	typedef NEArrayTemplate<int, false, NEString> SuperClass;
// 	typedef int InnerType;
// 	typedef NEString OuterType;
// 	Mine() : SuperClass() {}
// 	Mine(const Mine& src) : SuperClass(src) {
// 		create(src.getSize());
// 		push(src);
// 	}
// 
// 	NEObject& clone() const { return *(new Mine(*this)); }
// 	NEString& getElement(type_index index) {
// 		return *(new NEString(_getElement(index)));
// 	}
// 	const NEString& getElement(type_index index) const {
// 		return *(new NEString(_getElement(index)));
// 	}
// 	type_result setElement(type_index index, const NEString& src) {
// 		return _getElement(index) = src.toInt();
// 	}
// 	type_index find(const NEString& src) const {
// 		return _find(src.toInt());
// 	}
// 	type_index insert(type_index idx, const NEString& src) {
// 		return _insert(idx, ++count);
// 	}
// 	type_index remove(type_index idx) {
// 		return _remove(idx);
// 	}
// 
// 	type_result resize(type_count new_size) {
// 		//	pre:
// 		//		이 방식은 인스턴스를 shallow copy함으로써 효율을 높이는 알고리즘이다.
// 		//		따라서 만약 전보다 크기를 축소시키는 resize라면, 그 차이만큼 인스턴스를 삭제해야한다.
// 		int instance_count = getLength() - new_size;	//	삭제하게될 인스턴스 갯수
// 		if(instance_count > 0)
// 			for(int n=0; n < instance_count ;n++)
// 				pop();	//	당연히 삭제되는 건 항상 뒤에서부터다. 
// 
// 		//	main:
// 		//		얇은 복사를 수행한다:	버퍼를 만든다. ArrayTemplate을 사용할 수 없다.
// 		int length = getLength();
// 		InnerType* buffer = new InnerType[_length];
// 		for(int n=0; n < length ;n++)
// 			buffer[n] = _data[n];	
// 		//		resize:
// 		_length = 0;
// 		create(new_size);	//	앞서 _length = 0을 했으므로 InnerElement를 delete하는 
// 		//	release()가 호출되지 않게 된다.		
// 		//	post:
// 		for(int n=0; n < length ;n++)
// 			_data[n] = buffer[n];
// 		_length = length;
// 		return RESULT_SUCCESS;
// 
// 	}
// 
// 	public: static int count;
// };
// 
// int Mine::count = 0;
// 
// void print(const Mine& src)
// {
// 	cout << "[" << src.getSize() << "] : ";
// 	for(int n=0; n < src.getLength(); n++)
// 		cout << src[n].toCharPointer() << "(" << src.getInnerElement(n) << "), ";
// 	cout << "\n";
// }
// 
// void main()
// {
// 	Mine a;
// 	a.create(5);
// 	a.push("1");
// 	a.push("2");
// 	a.push("3");
// 	a.push("4");
// 	a.push("5");
// 
// 	print(a);
// 
// 	a.resize(3);
// 
// 	print(a);
// }