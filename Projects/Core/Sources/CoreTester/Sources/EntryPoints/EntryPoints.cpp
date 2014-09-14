#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;
#include "Headers.hpp"
using namespace NE;
class MyMod : public NEModule
{
public:
	MyMod()	: a(28)
	{

	}
	void setScript(type_code new1)
	{
		_scriptcode = new1;
	}
	NEArgumentTemplate<NEIntKey> a;
	virtual type_result _onArgumentsFetched()
	{		
		getArguments().create(1);
		return getArguments().push(a);
	}

	virtual type_result _onExecute()
	{
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
class MyMod2 : public NEModule
{
public:
	MyMod2()
		: a(100)
	{

	}
	void setScript(type_code new1)
	{
		_scriptcode = new1;
	}
	NEArgumentTemplate<NEIntKey> a;
	virtual type_result _onArgumentsFetched()
	{
		a.getDefault().getValue()++;
		getArguments().create(1);
		return getArguments().push(a);
	}

	virtual type_result initialize()
	{
		NEModule::initialize();

		a.getDefault().getValue() += 5;
		return RESULT_SUCCESS;
	}

	virtual type_result _onExecute()
	{
		a.getDefault().getValue() *= 2;

		return RESULT_SUCCESS;
	}
	virtual const NEExportable::ModuleHeader& getHeader() const
	{
		static NEExportable::ModuleHeader _header;
		if(_header.getName().getLength() <= 0)
		{
			_header.getName() = "MyMod2";
			_header.getDeveloper() = "kniz";
			_header.setRevision(1);
		}

		return _header;
	}
	virtual NEObject& clone() const { return * (new MyMod2(*this)); }
};

enum SPECIAL_KEY
{
	CANCEL = 27,
	BACKSPACE = 8,
	CONFIRM = 13,
	ADD = 43,
	REMOVE = 45,
	MENU = 9,
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};



void init()
{
	NEModuleSet& ms = const_cast<NEModuleSet&>(Kernal::getInstance().getModuleManager().getModuleSet());
	ms.resize(ms.getLength() + 1);
	MyMod& added = (MyMod&) ms[ms.push(MyMod())];
	added.setScript(ms[ms.getLengthLastIndex()-1].getScriptCode()+1);
}

class Test1 : public TestCase
{
public:
	Test1() : TestCase("string conversion test (typecasting).") {}
	virtual bool onTest() 
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

		if(	a != "true"			||
			b != "12"			|| 
			c != "55555"		|| 
			d != "555555555"	|| 
			e != "4.500000"		) 
			return false;

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

			if(	a != "true"			||
				b != "12"			|| 
				c != "55555"		|| 
				d != "555555555"	|| 
				e != "4.500000"		) 
				return false;
		}

		return true;
	}
};
class Test2 : public TestCase
{
public:
	Test2()	: TestCase("arguments binder tests.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		NENode& tg = ns[ns.push(NENode())];
		NEKeyCodeSet& ks = tg.getKeySet();
		ks.create(1);
		ks.push(NEIntKey(5, "age"));
		NEModuleCodeSet& ms = tg.getModuleSet();
		ms.create(2);
		NEModule& m = ms[ms.push(MyMod())];
		m.getArguments()[0].setKeyName("age");

		manager.execute();
		ns.release();
		return true;
	}
};
class Test3 : public TestCase
{
public:
	Test3()	: TestCase("instance insertion and resizing of buffers.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		manager.initialize();
		ns.push(NENode());

		NENode& tg = ns[ns.push(NENode())];
		NEModuleCodeSet& ms = tg.getModuleSet();
		ns.push(NENode());
		ns.push(NENode());
		ns.push(NENode());
		if(ns.getLength() < 3) return false;

		ns.resize(5);
		if(ns.getLength() < 3 || ns.getSize() < 5) return false;
		ns.resize(7);
		if(ns.getLength() < 3 || ns.getSize() != 7) return false;
		ns.resize(3);

		ms.create(5);
		NEKeyCodeSet& ks = tg.getKeySet();
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());
		if(ms.getLength() != 4 || ms.getSize() != 5) return false;

		ms.resize(15);
		if(ms.getLength() != 4 || ms.getSize() != 15) return false;
		ms.resize(1);

		ks.create(5);
		ks.push(NEIntKey(5));
		ks.push(NEFloatKey(4.5f));
		ks.push(NETStringKey("gogoood!"));
		ks.push(NEBooleanKey(true));
		ks.push(NENodeSelector());
		if(ks.getLength() < 5)	return false;

		ks.resize(9);		
		if(ks.getLength() < 5)	return false;
		ks.resize(4);
		if(ks.getLength() < 4)	return false;

		ns.release();
		return true;
	}
};
class Test4 : public TestCase
{
public:
	Test4()	: TestCase("key_selector validation test.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

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
		const NEModule& outer = Kernal::getInstance().getModuleManager().getModuleSet()[4];
		ms.push(MyMod());
		ms.push(outer);
		ms.push(MyMod());
		ms.push(MyMod());

		ms.resize(15);
		ms.resize(3);

		ks.create(5);
		ks.push(NEIntKey(5));
		ks.push(NEFloatKey(4.5f));
		ks.push(NETStringKey("gogoood!", "sentence"));
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
		if( ! &tk) return false;
		bool result = (tk.getValue() == "gogoood!") ? true : false;

		ns.release();
		return result;
	}
};
class Test5 : public TestCase
{
public:
	Test5() : TestCase("module_selector validation test")	{}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

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
		const NEModule& outer = Kernal::getInstance().getModuleManager().getModuleSet()[4];
		ms.push(MyMod());
		ms.push(outer);
		ms.push(MyMod());
		ms.push(MyMod());

		ms.resize(15);
		ms.resize(3);

		ks.create(5);
		ks.push(NEIntKey(5));
		ks.push(NEFloatKey(4.5f));
		ks.push(NETStringKey("gogoood!", "sentence"));
		ks.push(NEBooleanKey(true));
		NENodeSelector& targ = (NENodeSelector&) ks[ks.push(NENodeSelector())];

		ks.resize(9);		
		ks.resize(4);

		NEModuleSelector ms1;
		ms1.setNodeType(NECodeType::GROUP);
		NECodeSet ii(1);
		ii.push(1);
		ms1.setCodeSet(ii);
		ms1.initializeReferingPoint();
		NECodeSet is(1);
		ms1.setModuleType(NECodeType::SCRIPT);
		is.push(outer.getScriptCode());
		ms1.setModuleCodeSet(is);

		NEModule& found = ms1.getModule();
		if( ! &found) return false;
		bool result = (found.getHeader().getName() == outer.getHeader().getName()) ? true : false;

		ns.release();
		return result;
	}
};
class Test6 : public TestCase
{
public:
	Test6()	: TestCase("saving and loading a script file.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		manager.initialize();
		ns.push(NENode());

		NENode& tg = ns[ns.push(NENode())];
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
		NEModuleCodeSet& ms = ns[1].getModuleSet();
		ms.create(5);
		NEKeyCodeSet& ks = tg.getKeySet();
		ms.push(MyMod());
		ms.push(MyMod());
		ms.push(MyMod());

		ms.resize(15);
		ms.resize(1);
		ms.push(MyMod());
		MyMod& mym = (MyMod&) ms[0];
		mym.a.getDefault().getValue() = 1000;

		ks.create(5);
		ks.push(NEIntKey(5));
		ks.push(NEFloatKey(4.5f));
		ks.push(NETStringKey("gogoood!", "sentence"));
		ks.push(NEBooleanKey(true));
		NENodeSelector& targ = (NENodeSelector&) ks[ks.push(NENodeSelector())];

		ks.resize(9);		
		ks.resize(4);

		NEBinaryFileSaver saver(L"temp.dat", NEFILESAVERFLAG_OVERWRITE);
		saver.open();
		saver << manager;
		saver.close();

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
			if( ! &tk) return false;
			if(tk.getValue() != "gogoood!") return false;
		}		

		manager.initialize();

		NEBinaryFileLoader loader(L"temp.dat");
		loader.open();
		loader >> manager;
		loader.close();

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
			if(tk.getValue() != "gogoood!")
				return false;
		}

		MyMod& mym1 = (MyMod&) ns[1].getModuleSet()[0];
		if(mym1.a.getDefault().getValue() != 1000)
			return false;

		return true;
	}
};
class Test7 : public TestCase
{
public:
	Test7()	: TestCase("validate string splition with test samples.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		NEString str = "wow/this/is/a//test";
		NEStringSet split;
		str.split("/", split);

		if(split[0] != "wow") return false;
		if(split[1] != "this") return false;
		if(split[2] != "is") return false;
		if(split[3] != "a") return false;
		if(split[4] != "test") return false;

		return true;

	}
};
class Test8 : public TestCase
{
public:
	Test8()	: TestCase("initiating a kernel.") {}
	virtual bool onTest() 
	{
		Kernal::Factory factory;
		factory.getNodeManagerIdentifier() = NEExportable::Identifier("NEStandardNodeManager", "haku", 1);
		factory.getScriptManagerIdentifier() = NEExportable::Identifier("NEStandardScriptManager", "haku", 1);
		factory.getDefaultSettings().setModuleDirectory("Modules");
		Kernal created = factory.create();
		Kernal::setInstance( *(new Kernal(created)) );

		Kernal& kernal = Kernal::getInstance();
		kernal.initialize();
		kernal.getDebugManager().setDebugMode(false);	//	디버그 모드를 끈다. 로그 없앰

		if( ! &kernal.getNodeManager()	||
			! &kernal.getScriptManager())
			return false;

		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();
		ss.setMaxPriorityCodeIndex(5);
		ss.setMaxScriptCodeIndex(5);
		ss.setMaxGroupCodeIndex(2);
		return true;
	}
};
class Test9 : public TestCase
{
public:
	Test9()	: TestCase("module argument copy policy test") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		NENode& node1 = ns[ns.push(NENode())];
		node1.getModuleSet().create(1);
		//	1. MyMod() 생성자 호출			; value = 100
		//	2. cloned = MyMod().clone();	; value = 100
		//	3. cloned.initialize()			; value = 105
		//	3-1. cloned.onArgumentFetched()	; value = 106
		MyMod2& mod = (MyMod2&) node1.getModuleSet()[node1.getModuleSet().push(MyMod2())];

		mod.execute();	//					; value = 212

		return mod.a.getDefault().getValue() == 212;
	}
};
class Test10 : public TestCase
{
public:
	Test10() : TestCase("argument interface deep copy test.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		MyMod mine;
		mine.initialize();	//	initialize 안에서 _bindArgument가 호출된다.
		mine.a.setKeyName("age");
		mine.a.getDefault().getValue() = 18;

		NENode& node1 = ns[ns.push(NENode())];
		node1.getKeySet().create(1);
		node1.getKeySet().push(NEIntKey(5, "age"));
		node1.getModuleSet().create(1);
		MyMod& module1 = (MyMod&) node1.getModuleSet()[node1.getModuleSet().push(mine)];

		if(	mine.a.getDefault().getValue() != module1.a.getDefault().getValue())
			return false;
		return true;			
	}
};
class Test11 : public TestCase
{
public:
	Test11() : TestCase("argument deep copy test.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		MyMod mine;
		mine.a.setKeyName("age");
		mine.a.getDefault().getValue() = 18;

		NENode& node1 = ns[ns.push(NENode())];
		node1.getKeySet().create(1);
		node1.getKeySet().push(NEIntKey(5, "age"));
		node1.getModuleSet().create(1);
		MyMod& module1 = (MyMod&) node1.getModuleSet()[node1.getModuleSet().push(mine)];

		if(	mine.a.getKeyName() != module1.a.getKeyName())
			return false;

		return true;			
	}
};
class Test12 : public TestCase
{
public:
	Test12() : TestCase("argument binding test.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		MyMod mine;
		mine.a.setKeyName("age");
		mine.a.getDefault().getValue() = 18;

		NENode& node1 = ns[ns.push(NENode())];
		node1.getKeySet().create(1);
		node1.getKeySet().push(NEIntKey(5, "age"));
		node1.getModuleSet().create(1);
		//	바인딩 정책:
		//		0.0.1a.2014.08.31	현재, 바인딩은 Manager객체에 의해 NEModule::execute()가 이루어 져야 실시된다.
		//		바인딩이 되지 않았으나 getValue를 호출하면 기본값이 나오게 된다.
		MyMod& module1 = (MyMod&) node1.getModuleSet()[node1.getModuleSet().push(mine)];
		if(module1.a.getValue() != 18)	//	아직 바인딩이 되지 않았으므로, 기본값이 나와야 한다
			return false;
		
		manager.execute();	//	바인딩이 실시된다

		if(module1.a.getValue() == 18)
			return false;


		return true;
	}
};

class Test13 : public TestCase
{
public:
	Test13() : TestCase("does inner binding of keys works well?") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		NENode& node1 = ns[ns.push(NENode())];
		node1.getKeySet().create(5);
		node1.getKeySet().push(NEIntKey());
		node1.getKeySet().push(NEFloatKey());
		node1.getKeySet().push(NEDoubleKey());
		node1.getKeySet().push(NENodeSelector());		
		node1.getKeySet().push(NEModuleCodeSetKey(NEModuleCodeSet(), "modulecodeset"));
		
		for(int n=0; n < node1.getKeySet().getLength() ;n++)
			if(&node1.getKeySet()[n].getOwner() != &node1.getKeySet())
				return false;
		return true;
	}
};
class Test14 : public TestCase
{
public:
	Test14()	: TestCase("initiating a editor.") {}
	virtual bool onTest() 
	{
		Editor::Factory factory;
		factory.getPanelManagerIdentifier() = NEExportable::Identifier("NEStandardPanelManager", "haku", 1);
		factory.getScriptEditorIdentifier() = NEExportable::Identifier("NEStandardScriptEditor", "haku", 1);
		factory.getEventHandlerIdentifier() = NEExportable::Identifier("CooeeHandler", "kniz", 1);
		factory.getDefaultSettings().setPanelDirectory("Panels");
		Editor created = factory.create();
		Editor::setInstance( *(new Editor(created)) );

		NEINIManager& ini = Kernal::getInstance().getINIManager();

		Editor& editor = Editor::getInstance();
		editor.initialize();
		
		if( ! &editor.getPanelManager()	||
			! &editor.getScriptEditor()	||
			! &editor.getEventHandler()	)
			return false;
		
		return true;
	}
};
//class Test : public TestCase
//{
//public:
//	Test()	: TestCase("") {}
//	virtual bool onTest() 
//	{
//		NENodeManager& manager = Kernal::getInstance().getNodeManager();
//		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
//		NERootNodeCodeSet& ns = manager.getRootNodes();
//		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
//		const NEModuleSet& moduleset = moduler.getModuleSet();
//		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
//		NEScriptManager::ScriptHeader& ss = (NEScriptManager::ScriptHeader&) scripter.getScriptHeader();
//
//	}
//};

void main()
{
	cout	<< "CoreTester.		v0.0.1a build on 2014.08.16\n"
			<< "This program will test kernel with some sequencial jobs. It can takes a minutes by circumstances.\n"
			<< "If test has been successed, the result will be announced in front of test statement with color green. And the processing time will be displayed next of it.\n\n";

	NE_MEMORYLEAK;

	std::wcout.imbue( std::locale("korean") );

	Test8().test();
	Test14().test();
	init();	
	Test1().test();
	Test13().test();
	Test2().test();
	Test3().test();
	Test4().test();
	Test5().test();
	Test6().test();
	Test7().test();
	Test9().test();
	Test10().test();
	Test11().test();
	Test12().test();

	Kernal::saveSettings();
	delete &Kernal::getInstance();

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