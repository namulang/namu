#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;
#include "Headers.hpp"
using namespace NE;
class MyMod : public NEModule
{
public:
	void setScript(type_code new1)
	{
		_scriptcode = new1;
	}
	NETArgument<NEIntKey> a;
	virtual type_result _onFetchArguments(NEArgumentList& tray)
	{		
		tray.push(a);

		return RESULT_SUCCESS;
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
	void setScript(type_code new1)
	{
		_scriptcode = new1;
	}
	NETArgument<NEIntKey> a;
	virtual type_result _onFetchArguments(NEArgumentList& tray)
	{		
		tray.push(a);
		
		return RESULT_SUCCESS;
	}

	virtual type_result _onInitialize()
	{
		a.setDefault( a.getDefault() + 1 );

		return RESULT_SUCCESS;
	}

	virtual type_result _onExecute()
	{
		a.setDefault(a.getDefault() * 2);

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
	if(ms.getLengthLastIndex() > 0)
		added.setScript(ms[ms.getLengthLastIndex()-1].getScriptCode()+1);
	added.setScript(0);
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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

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
			NECodeSet a(1);
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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

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
		const NEModule& outer = moduler.getModule(NEExportable::Identifier("MyMod", "kniz", 1));
		ms.push(outer);
		ms.push(outer);
		ms.push(outer);

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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

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
		mym.a.setDefault(1000);

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
				NECodeSet a(1);
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
				NECodeSet a(1);
				a.push(1);
				s.setCodeSet(a);
				s.setKeyName("sentence");			
			}
			NETStringKey& tk = (NETStringKey&) s.getKey();
			if(tk.getValue() != "gogoood!")
				return false;
		}

		MyMod& mym1 = (MyMod&) ns[1].getModuleSet()[0];
		if(mym1.a.getDefault() != 1000)	//	default는 변경될 수 있어야 한다.
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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

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
		kernal.getDebugManager().setDebugMode(true);	//	디버그 모드를 끈다. 로그 없앰
		kernal.getDebugManager().setConsoleEnabled(false);
		kernal.getDebugManager().setDebugWindowEnabled(true);

		if( ! &kernal.getNodeManager()	||
			! &kernal.getScriptManager())
			return false;

		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();
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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		NENode& node1 = ns[ns.push(NENode())];
		node1.getModuleSet().create(1);
		//	1. MyMod() 생성자 호출			; default = 0
		//	2. initailize에서 ++			; default = 1
		//	2. cloned = MyMod().clone();	; default 변경 불가 = 1
		//	3. cloned.initialize()			;			"
		MyMod2& mod = (MyMod2&) node1.getModuleSet()[node1.getModuleSet().push(MyMod2())];

		manager.execute();	//				;			"	= 2

		return mod.a.getDefault() == 2;	
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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		MyMod mine;
		mine.initialize();	//	initialize 안에서 _bindArgument가 호출된다.
		mine.a.setKeyName("age");
		mine.a.setDefault(18);

		NENode& node1 = ns[ns.push(NENode())];
		node1.getKeySet().create(1);
		node1.getKeySet().push(NEIntKey(5, "age"));
		node1.getModuleSet().create(1);
		MyMod& module1 = (MyMod&) node1.getModuleSet()[node1.getModuleSet().push(mine)];

		if(	mine.a.getDefault() != module1.a.getDefault()	||
			&mine.a == &module1.a							||
			mine.a.getKeyName() !=	
			module1.a.getKeyName()	)
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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		MyMod mine;
		mine.initialize();
		mine.a.setKeyName("age");
		mine.a.setDefault(18);

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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		manager.initialize();

		MyMod mine;
		mine.a.setDefault(18);
		mine.initialize();
		mine.a.setKeyName("age");

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

		if(module1.a.getValue() != 5)
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
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

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

class NECodeSetInsertionTest : public TestCase
{
public:
	NECodeSetInsertionTest() : TestCase("test NECodeSet's filtering functions.") {}
	virtual bool onTest() 
	{
		NECodeSet cs(5);
		for(int n=0; n < 5 ;n++)
			cs.push(n);
		
		cs.resize(10);
		type_index	result1 = cs.push(1);
		type_result result2 = cs.setElement(3, 2);

		return	result1 == NE_INDEX_ERROR			&& 
				NEResult::isActionAborted(result2);
	}
};


class NEKeyManagerTypeTest : public TestCase
{
public:
	NEKeyManagerTypeTest() : TestCase("is NEKeyManager accessible with some types?") {}
	virtual bool onTest() 
	{
		NEKeyManager& km = Kernal::getInstance().getKeyManager();
		NEIntKey ik(5);
		const NEKey	&	result1 = km.getKey(ik.getType()),
					&	result2 = km.getKey(ik.getTypeName());

		if(	result1.getType() != result2.getType()	||
			result1.getType() != NEType::NEINT_KEY	)
			return false;

		return true;
	}
};
class IndexedArrayReturningHeapMemory : public TestCase
{
public:
	IndexedArrayReturningHeapMemory() : TestCase("check that indexed-array returns heap memory on time") {}
	virtual bool onTest()
	{
		class MyInt : public NEObject
		{
		public:
			MyInt(int dd)	: datum(dd) {}			
			MyInt(const MyInt& src) : datum(src.datum) {}
			virtual NEObject& clone() const { return *(new MyInt(*this)); }
			virtual void release() {}
			virtual type_result isValid() const { return 0; }
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver; }
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader; }

			int datum;
		};
		NEIndexedArrayTemplate<MyInt*, true> arr;
		arr.create(5);
		arr.push(MyInt(1));
		arr.push(MyInt(2));
		arr.push(MyInt(3));
		arr.push(MyInt(4));
		arr.push(MyInt(5));
		arr.remove(2);
		return 
			! NEResult::hasError(arr.insert(2, MyInt(100)))	&&
			arr[2].datum == 100;
	}
};
class IndexedArrayFileSerializeTest : public TestCase
{
public:
	IndexedArrayFileSerializeTest() : TestCase("indexed array can be saved to/ loaded from file?") {}
	virtual bool onTest()
	{
		class MyInt : public NEObject
		{
		public:
			MyInt(int dd)	: datum(dd) {}			
			MyInt(const MyInt& src) : datum(src.datum) {}
			virtual NEObject& clone() const { return *(new MyInt(*this)); }
			virtual void release() {}
			virtual type_result isValid() const { return 0; }
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver << datum; }
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader >> datum; }

			int datum;
		};
		class MyContainer : public NEIndexedArrayTemplate<MyInt*, true> 
		{
		public:
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
			{
				NEIndexedArrayTemplate<MyInt*, true>::serialize(saver);

				for(int n=0; n < getSize(); n++)
					if(getOccupiedSet()[n])
						saver << getElement(n);

				return saver;
			}
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
			{
				NEIndexedArrayTemplate<MyInt*, true>::serialize(loader);

				_length = 0;

				for(int n=0; n < getSize() ;n++)
					if(getOccupiedSet()[n])
					{
						int datum = 0;
						loader >> datum;

						_occupiedset[n] = false;
						insert(n, MyInt(datum));
					}

				return loader;
			}
		};	
		MyContainer arr;
		arr.create(5);
		arr.pushFront(MyInt(1));
		arr.pushFront(MyInt(2));
		arr.pushFront(MyInt(3));
		arr.pushFront(MyInt(4));
		arr.pushFront(MyInt(5));
		
		NEBinaryFileSaver saver(_T("IndexedArrayFileSerializeTest.dat"));
		saver.open();
		saver << arr;
		saver.close();

		NEBinaryFileLoader loader(_T("IndexedArrayFileSerializeTest.dat"));
		loader.open();
		loader >> arr;
		loader.close();

		for(int n=0; n < arr.getLength() ;n++)
			if(arr[n].datum != n+1)
				return false;
		
		return true;
	}
};
class ArrayAssigningTest : public TestCase
{
public:
	ArrayAssigningTest() : TestCase("array assigning test.") {}
	virtual bool onTest()
	{
		NEArrayTemplate<int> arr, arr2;
		arr.create(3);
		arr.push(1);
		arr.push(2);
		arr.push(3);
		arr2.create(1);
		arr2.push(4);

		arr = arr2;

		return	arr.getSize() == arr2.getSize()		&&
				arr.getLength() == arr2.getLength() &&
				arr[0] == arr2[0] &&				
				arr[0] == 4;
	}
};
class PointerArrayAssigningTest : public TestCase
{
public:
	PointerArrayAssigningTest() : TestCase("pointer-array assigning test.") {}
	virtual bool onTest()
	{
		int a=0, b=1, c=2, d=4;
		NEArrayTemplate<int*, false> arr, arr2, temp;
		arr.create(3);
		arr.push(&a);
		arr.push(&b);
		arr.push(&c);
		arr2.create(1);
		arr2.push(&d);

		arr = arr2;

		return	arr.getSize() == arr2.getSize()		&&
				arr.getLength() == arr2.getLength() &&
				arr[0] == arr2[0]					&&
				arr[0] == 4;
	}
};
class HeapedPointerArrayAssigningTest : public TestCase
{
public:
	HeapedPointerArrayAssigningTest() : TestCase("array that manages instances with heap assigning test.") {}

	class MyInt : public NEObject
	{
	public:
		MyInt(int dd)	: datum(dd) {}			
		MyInt(const MyInt& src) : datum(src.datum) {}
		virtual NEObject& clone() const { return *(new MyInt(*this)); }
		virtual void release() {}
		virtual type_result isValid() const { return 0; }
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver << datum; }
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader >> datum; }

		int datum;
	};
	class MyContainer : public NEArrayTemplate<MyInt*, true> 
	{
	public:
	};

	virtual bool onTest()
	{
		MyContainer arr, arr2;
		arr.create(1);
		arr.push(MyInt(1));		
		arr2.create(3);
		arr2.push(MyInt(4));
		arr2.push(MyInt(2));
		arr2.push(MyInt(3));

		arr = arr2;

		return	arr.getSize() == arr2.getSize()	&&
			arr.getLength() == arr2.getLength() &&
			arr[0].datum == arr2[0].datum		&&
			arr[0].datum == 4;
	}
};
class IndexedArrayAssigningTest : public TestCase
{
public:
	IndexedArrayAssigningTest() : TestCase("indexed array assigning test.") {}
	virtual bool onTest()
	{
		NEIndexedArrayTemplate<int> arr, arr2;
		arr.create(3);
		arr.push(1);
		arr.push(2);
		arr.push(3);
		arr2.create(1);
		arr2.push(4);

		arr = arr2;

		return	arr.getSize() == arr2.getSize()		&&
				arr.getLength() == arr2.getLength() &&
				arr[0] == arr2[0] &&				
				arr[0] == 4;
	}
};
class PointerIndexedArrayAssigningTest : public TestCase
{
public:
	PointerIndexedArrayAssigningTest() : TestCase("pointer-indexed array assigning test.") {}
	virtual bool onTest()
	{
		int a=0, b=1, c=2, d=4;
		NEIndexedArrayTemplate<int*,false> arr, arr2, temp;
		arr.create(3);
		arr.push(&a);
		arr.push(&b);
		arr.push(&c);
		arr2.create(1);
		arr2.push(&d);

		arr = arr2;

		return	arr.getSize() == arr2.getSize()		&&
			arr.getLength() == arr2.getLength() &&
			arr[0] == arr2[0]					&&
			arr[0] == 4;
	}
};
class HeapedPointerIndexedArrayAssigningTest : public TestCase
{
public:
	HeapedPointerIndexedArrayAssigningTest() : TestCase("pointer-indexed one with heap assigning test.") {}

	class MyInt : public NEObject
	{
	public:
		MyInt(int dd)	: datum(dd) {}			
		MyInt(const MyInt& src) : datum(src.datum) {}
		virtual NEObject& clone() const { return *(new MyInt(*this)); }
		virtual void release() {}
		virtual type_result isValid() const { return 0; }
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver << datum; }
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader >> datum; }

		int datum;
	};
	class MyContainer : public NEIndexedArrayTemplate<MyInt*, true> 
	{
	public:
	};

	virtual bool onTest()
	{
		MyContainer arr, arr2;
		arr.create(1);
		arr.push(MyInt(1));		
		arr2.create(3);
		arr2.pushFront(MyInt(4));
		arr2.pushFront(MyInt(2));
		arr2.pushFront(MyInt(3));

		arr = arr2;

		return	arr.getSize() == arr2.getSize()	&&
			arr.getLength() == arr2.getLength() &&
			arr[0].datum == arr2[0].datum		&&
			arr[0].datum == 4;
	}
};
class StringFindingTest : public TestCase
{
public:
	StringFindingTest() : TestCase("does string finding algorithm work?") {}

	virtual bool onTest()
	{
		NEString testcase = "helloloothisampleadingoogleappleomaxe";
		NEString sample = "ple";

		NEIntSet output = testcase.find(sample);
		
		return output.getLength() == 2 && output[0] == 14 && output[1] == 29;
	}
};
class RelativityTestOnSynchronize : public TestCase
{
public:
	RelativityTestOnSynchronize() : TestCase("test Relativity when script sync. from scripteditor.") {}

	virtual bool onTest()
	{
		NEScriptEditor& ed = Editor::getInstance().getScriptEditor();
		NEScriptManager& sm = Kernal::getInstance().getScriptManager();

		ed.insertNameCode(1);
		ed.insertNameCode(2);
		ed.getScriptHeader().getName() = "RelativityTest";
		ed.getScriptHeader().getDeveloper() = "CoreTester";
		NENodeCodeSet& ncs = ed.getScriptNodes();
		ncs.create(3);
		{
			NENode& node = ncs[ncs.push(NENode())];
			NEKeyCodeSet& ks = node.getKeySet();
			ks.create(1);
			NENodeSelector nsel;
			nsel.setNodeType(NECodeType::NAME);
			NECodeSet is(2);
			is.push(1);
			is.push(2);
			nsel.setCodeSet(is);
			ks.push(nsel);
		}
		{
			NENode node;
			node.setNameCode(1);
			ncs.push(node);
		}
		{
			NENode node;
			node.setNameCode(2);
			ncs.push(node);
		}

		if(    ncs.getLength() != 3        ||
			ncs[0].getNameCode() != 0    ||
			ncs[1].getNameCode() != 1    ||
			ncs[2].getNameCode() != 2    )
			return false;

		NECodeSet is(2);
		is.push(1);
		is.push(2);
		NENodeSelector nsel;
		{            
			nsel.setManager(NEType::NESCRIPT_EDITOR);
			nsel.setCodeSet(is);
			nsel.setNodeType(NECodeType::NAME);

			while(NENode* i = &nsel.getNode())
			{
				switch(i->getNameCode())
				{
				case 1:
					if(i != &ncs[1])
						return false;
					break;

				case 2:
					if(i != &ncs[2])
						return false;
					break;
				}
			}
		}

		ed.synchronizeTo(sm);

		{
			const NENodeCodeSet& ncs = sm.getScriptNodes();
			NENodeSelector nsel;
			nsel.setManager(NEType::NESCRIPT_MANAGER);
			nsel.setCodeSet(is);
			nsel.setNodeType(NECodeType::NAME);

			while(NENode* i = &nsel.getNode())
			{
				switch(i->getNameCode())
				{
				case 1:
					if(i != &ncs[1])
						return false;
					break;

				case 2:
					if(i != &ncs[2])
						return false;
					break;
				}
			}
		}

		ed.release();
		ed.synchronizeFrom(sm);

		{
			NENodeCodeSet& ncs1 = ed.getScriptNodes();
			if(ncs.getLength() <= 0) return false;

			NEKeyCodeSet& ks = ncs1[0].getKeySet();
			if(ks.getLength() < 0) return false;
			NEKey& k = ks[0];
			if( ! k.isSubClassOf(NEType::NENODE_SELECTOR))
				return false;

			NENodeSelector& nsel1 = (NENodeSelector&) k;
			const NECodeSet& cs = nsel1.getCodeSet();
			if(    cs.getLength() < 2    ||
				cs[0] != 1            ||
				cs[1] != 2            )
				return false;
		}

		return true;
	}
};
class SelectorAssignOperatorTest : public TestCase
{
public:
	SelectorAssignOperatorTest() : TestCase("can SELECTORS accept/assign to other keys?") {}
	virtual bool onTest()
	{
		NENodeSelector b;
		NEModuleSelector d;
		NEKeySelector e;
		NEIntKey a(55, "age");
		NEFloatKey c(3.5f, "grade");

		b = a; // 에러
		d = b;
		e = b;
		//b.NEKey::operator=(a); OK
		//c == a;
		return true;
	}
};

class KeySelectorAssigningTest : public TestCase
{
public:
	KeySelectorAssigningTest()	: TestCase("does key selector cast itself implcitly when be assigned") {}
	virtual bool onTest() 
	{
		NENodeManager& nm = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ncs = nm.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		nm.initialize();

		ncs.create(3);
		NEFloatKey* grade;
		NEIntKey* age_2nd, *age;
		{
			NENode& node = ncs[ncs.push(NENode())];
			NEKeyCodeSet& ks = node.getKeySet();
			ks.create(1);
			age = ((NEIntKey*) &ks[ks.push(NEIntKey(22, "age"))]);
		}
		{
			ncs.push(ncs[0]);
			ncs[1].getKeySet().resize(2);
			age_2nd = (NEIntKey*) &ncs[1].getKeySet()[0];
			grade = (NEFloatKey*) & ncs[1].getKeySet()[ncs[1].getKeySet().push(NEFloatKey(4.0, "grade"))];
		}
		NECodeSet ic(1);
		ic.push(0);
		{
			NEKeySelector k1;			
			k1.setNodeType(NECodeType::NAME);
			k1.setCodeSet(ic);
			k1.setKeyName("age");
			NEKey* fetched = &k1.getKey();

			if(age != fetched)
				return false; // 탐색 포인터가 하나 증가되었다.

			NEKeySelector k2;
			k2.setNodeType(NECodeType::NAME);
			k2.setCodeSet(ic);
			k2.setKeyName("grade");

			k1 += k2;	//	extend
			if(age_2nd->getValue() != 22)	// KeySelector 끼리는 연산이 불가능하다. (무한 루프 이슈)
				return false;
			k1 += *grade;
			if(	age_2nd->getValue() != 26	|| 
				age->getValue() != 22		)
				return false;
			k1 = *grade;
			if(age_2nd->getValue() != 4)
				return false;
		}

		return true;
	}
};
class GenericArgumentBindingTest : public TestCase
{
public:
	GenericArgumentBindingTest() : TestCase("check out generic argument can be binded.") {}
	virtual bool onTest() 
	{
		class Temp : public NEModule
		{
		public:
			NETArgument<NEKey> generic;

			virtual type_result _onFetchArguments(NEArgumentList& tray)
			{
				tray.push(generic);

				return 0;
			}
			virtual NEObject& clone() const
			{
				return *(new Temp(*this));
			}
			virtual const NEExportable::ModuleHeader& getHeader() const
			{
				static NEExportable::ModuleHeader _header;

				if (NEResult::hasError(_header.isValid()))
				{
					_header.getName() = "Temp";
					_header.getDeveloper() = "kniz";
				}

				return _header;
			}
		};

		NENodeManager& nm = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ncs = nm.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		nm.initialize();
		Temp* temp = 0x00;
		{
			NENode& n = ncs[ncs.push(NENode())];
			{
				NEKeyCodeSet& ks = n.getKeySet();
				ks.create(2);
				ks.push(NEIntKey(22, "age"));
				ks.push(NEStringKey("chales", "name"));
			}
			{
				NEModuleCodeSet& ms = n.getModuleSet();
				ms.create(1);
				temp = (Temp*) &ms[ms.push(Temp())];
				temp->generic.setKeyName("age");								
			}
			n.execute();
		}

		if(	temp->generic.getValueKey().getName() != "age"				||
			!temp->generic.getValueKey().isSubClassOf(NEType::NEINT_KEY)	)
			return false;

		return true;
	}
};

class ArgumentConversionTest : public TestCase
{
public:
	ArgumentConversionTest() : TestCase("test arguments conversion.") {}
	virtual bool onTest() 
	{
		class Temp : public NEModule
		{
		public:
			NETArgument<NEFloatKey> grade;

			virtual type_result _onFetchArguments(NEArgumentList& tray)
			{
				tray.push(grade);

				return 0;
			}
			virtual type_result _onExecute()
			{
				grade.setValue(grade.getValue() / 2.0f);

				return RESULT_SUCCESS;
			}
			virtual NEObject& clone() const
			{
				return *(new Temp(*this));
			}
			virtual const NEExportable::ModuleHeader& getHeader() const
			{
				static NEExportable::ModuleHeader _header;

				if (NEResult::hasError(_header.isValid()))
				{
					_header.getName() = "Temp";
					_header.getDeveloper() = "kniz";
				}

				return _header;
			}
		};
		class Temp2 : public NEModule
		{
		public:
			NETArgument<NEModuleSelector> temp;

			virtual type_result _onFetchArguments(NEArgumentList& tray) {
				tray.push(temp);
				return 0;
			}
			virtual type_result _onExecute() {
				temp.getValue().initializeReferingPoint();
				Temp& t = (Temp&)temp.getValue().getModule();				
				if (temp.isBinded() && &t)
					t.grade.setValue(t.grade.getValue() * 10);

				return RESULT_SUCCESS;
			}
			virtual NEObject& clone() const { return *(new Temp2(*this)); }
			virtual const NEExportable::ModuleHeader& getHeader() const {
				static NEExportable::ModuleHeader _header;
				if (NEResult::hasError(_header.isValid())) {
					_header.getName() = "Temp2";
					_header.getDeveloper() = "kniz";
				}
				return _header;
			}
		};

		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();
		manager.initialize();

		ns.create(1);
		NENode& n = ns[ns.push(NENode())];		
		NEKeySelector* kk=0;
		{
			NEKeyCodeSet& ks = n.getKeySet();
			ks.create(4);
			ks.push(NEIntKey(4, "fake_grade"));
			ks.push(NEFloatKey(8.0f, "real_grade"));
			ks.push(NEModuleSelector("temp selector"));
			kk = (NEKeySelector*)&ks[ks.push(NEKeySelector("ks"))];
		}
	
		Temp* temp = 0x00;
		Temp2* temp2 = 0x00;
		{
			NEModuleCodeSet& ms = n.getModuleSet();
			ms.create(2);
			temp = (Temp*) &ms[ms.push(Temp())];
			temp->grade.setKeyName("ks");
			temp2 = (Temp2*)&ms[ms.push(Temp2())];			
		}

		kk->setKeyName("fake_grade");

		n.execute();
		if (temp->grade.getValue() != 2)					//	바인딩 테스트
			return false;				

		temp->grade.setKeyName("real_grade");		
		
		n.execute();		
		if (temp->grade.getValue() != 4.0f)					//	keyname을 변경시, 재 바인딩 하는가
			return false;		


		temp->grade.setKeyName("fake_grade");
		temp2->temp.setKeyName("temp selector");
		n.execute();		
		if (temp->grade.getValue() != 10.0f)				//	다른 모듈에서 셀렉터를 통해 인자에 접근한 경우도 conversion과 update가 완료되는가?
			return false;

		temp->grade.setValue(temp->grade.getValue() * 2.0f);//	모듈 밖 외부에서 Implicit Key Conversion Update가 동작하는가

		n.execute();
		if (temp->grade.getValue() != 100.0f)
			return false;

		return true;
	}
};
class ArgumentConstantLiteralTest : public TestCase
{
public:
	ArgumentConstantLiteralTest() : TestCase("test that default of argument interface is modifiable.") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		manager.initialize();
		{
			NENode& n = ns[ns.push(NENode())];
			NEModuleCodeSet& ms = n.getModuleSet();

			MyMod* temp = 0x00;
			ms.create(1);
			{
				temp = (MyMod*)&ms[ms.push(MyMod())];
			}
			n.execute();

			if (temp->a.getValue() != 0)	//	바인딩이 안돼있다면 디폴트값인 0이 나오는가
				return false;

			temp->a.setDefault(8);
			n.execute();
			if (temp->a.getValue() != 8)
				return false;
			temp->a.setEnable(false);
			if (temp->a.isEnable()) return false;
		}

		NETString filename = "ArgumentConstantLiteralTest.dat";
		NEBinaryFileSaver saver(filename.toCharPointer());
		saver.open();
		if (!saver.isFileOpenSuccess())	return false;
		saver << manager;
		saver.close();

		manager.release();

		NEBinaryFileLoader loader(filename.toCharPointer());
		loader.open();
		if (!loader.isFileOpenSuccess()) return false;
		loader >> manager;
		loader.close();

		{
			NENodeCodeSet& ns = manager.getRootNodes();
			if (ns.getLength() <= 0)	return false;

			NEModuleCodeSet& ms = ns[1].getModuleSet();
			if (ms.getLength() <= 0)	return false;

			MyMod& temp = dynamic_cast<MyMod&>(ms[0]);
			if ( ! &temp) return false;

			if(temp.a.isBinded()) return false;
			if (temp.a.getValue() != 8)
				return false;
			if (temp.a.isEnable()) return false;
		}

		return true;
	}
};
class ArgumentInterfaceCanBeSaved : public TestCase
{
public:
	ArgumentInterfaceCanBeSaved() : TestCase("can be default-value of argument saved?") {}
	virtual bool onTest() 
	{
		NENodeManager& manager = Kernal::getInstance().getNodeManager();
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		NERootNodeCodeSet& ns = manager.getRootNodes();
		NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModuleSet& moduleset = moduler.getModuleSet();
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();

		manager.initialize();
		{
			NEModuleCodeSet& ms = ns[0].getModuleSet();
			ms.create(1);
			MyMod& m = (MyMod&) ms[ms.push(MyMod())];
			NEIntKey& ik = dynamic_cast<NEIntKey&>(m.a.getDefaultKey());
			ik.getValue() = 100;
		}

		NEBinaryFileSaver saver(_T("arg-default-value-test.dat"));
		saver.open();
		if (!saver.isFileOpenSuccess())
			return false;
		saver << manager;
		saver.close();

		NEBinaryFileLoader loader(_T("arg-default-value-test.dat"));
		loader.open();
		if (!loader.isFileOpenSuccess())
			return false;
		loader >> manager;
		loader.close();

		MyMod& m = (MyMod&)manager.getRootNodes()[0].getModuleSet()[0];
		if (!&m) return false;
		if (m.a.getDefault() != 100)
			return false;

		return true;
	}
};

class CodeSynchroTest : public TestCase
{
public:
	CodeSynchroTest() : TestCase("is codes synchronized when you insert/remove?") {}
	virtual bool onTest() 
	{
		NEScriptEditor& manager = Editor::getInstance().getScriptEditor();
		NERootNodeCodeSet& ns = manager.getScriptNodes();
		NEScriptHeader& header = manager.getScriptHeader();

		manager.initialize();

		manager.insertNameCode(1);
		manager.insertGroupCode(1);
		manager.insertPriorityCode(1);

		class Temp : public NEModule
		{
		public:
			NETArgument<NEModuleSelector> ms;
			NETArgument<NENodeSelector> ns_group;
			NETArgument<NENodeSelector> ns_name;

		public:
			virtual const NEExportable::ModuleHeader& getHeader() const
			{
				static NEExportable::ModuleHeader _header;

				if(NEResult::hasError(_header.isValid()))
				{
					_header.getName() = "Temp";
					_header.getDeveloper() = "kniz";				
				}

				return _header;
			}
			virtual type_result _onExecute()
			{
				return RESULT_SUCCESS;
			}
			virtual type_result _onFetchArguments(NEArgumentList& tray)
			{
				tray.push(ns_group);
				tray.push(ns_name);
				return tray.push(ms);
			}
			virtual NEObject& clone() const { return *(new Temp(*this)); }
		};

		Temp* t;
		NENode* src;
		NENodeSelector* key_ns;
		{
			src = &ns[ns.push(NENode())];
			{
				NEKeyCodeSet& ks = src->getKeySet();
				ks.create(1);
				key_ns = (NENodeSelector*) &ks[ks.push(NENodeSelector())];
			}

			src->setPriority(1);
			NECodeSet c(2);
			c.push(0);
			c.push(1);
			src->setGroupCode(c);
			src->setNameCode(1);
			{
				NEModuleCodeSet& m = src->getModuleSet();
				m.create(1);
				t = (Temp*) &m[m.push(Temp())];				
				NEModuleSelector* nms = &t->ms.getDefault();
				nms->setManager(NEType::NESCRIPT_EDITOR);
				nms->setNodeType(NECodeType::SCRIPT);
				NECodeSet is(1);
				is.setCodeType(NECodeType::SCRIPT);
				is.push(1);
				nms->setCodeSet(is);

				NENodeSelector& ns_name = t->ns_name.getDefault();
				ns_name.setManager(NEType::NESCRIPT_EDITOR);
				ns_name.setNodeType(NECodeType::NAME);
				is.setCodeType(NECodeType::NAME);
				is[0] = 1;
				ns_name.setCodeSet(is);

				NENodeSelector& ns_group = t->ns_group.getDefault();
				ns_group.setManager(NEType::NESCRIPT_EDITOR);
				ns_group.setNodeType(NECodeType::GROUP);
				is.setCodeType(NECodeType::GROUP);
				is.resize(2);
				is.push(1);
				if (is.getLength() > 1	&&
					is[0] == is[1]		)	//	중복은 안된다.
					return false;
				is.push(0);
				ns_group.setCodeSet(is);


				key_ns->setManager(NEType::NESCRIPT_EDITOR);
				key_ns->setNodeType(NECodeType::PRIORITY);
				is.setCodeType(NECodeType::PRIORITY);
				is.create(1);
				is.push(1);
				key_ns->setCodeSet(is);
			}

			if (&t->ms.getValue().getNode() != src)	//	SCRIPT
				return false;
			if (&t->ns_name.getValue().getNode() != src) // NAME
				return false;
			if (&key_ns->getNode() != src) // PRIOR
				return false;
			if (&t->ns_group.getValue().getNode() != src) // GROUP
				return false;

			t->ms.getValue().initializeReferingPoint();
			t->ns_name.getValue().initializeReferingPoint();
			t->ns_group.getValue().initializeReferingPoint();
			key_ns->initializeReferingPoint();
		}

		NENode* after;
		{
			after = &ns[ns.pushFront(NENode())];
			NECodeSet ic(1);
			ic.setCodeType(NECodeType::GROUP);
			ic.push(1);
			after->setGroupCode(ic);
		}

		manager.insertNameCode(1);
		manager.insertGroupCode(1);
		manager.insertPriorityCode(1);

		//	src의 예상 상태:
		//		NAME = 1		->	2
		//		GROUP = 0,1		->	0, 2
		//		PRIOR = 1		->	2
		//		SCRIPT= 1		->	2
		if (src->getNameCode() != 2)
			return false;
		if (src->getGroupCode().getLength() != 2)
			return false;
		if (src->getGroupCode()[1] != 2)
			return false;
		if (src->getPriority() != 2)
			return false;
		if(src->getScriptCode() != 2)
			return false;

		//	Key의 동기화 체크:
		if (!key_ns)
			return false;
		if (key_ns->getCodeSet().getLength() < 1)
			return false;
		if(key_ns->getCodeSet()[0] != 2)
			return false;

		//	Argument 체크:
		if (t->ms.getValue().getCodeSet()[0] != 2)
			return false;
		if (t->ns_name.getValue().getCodeSet()[0] != 2)
			return false;
		if (t->ns_group.getValue().getCodeSet().getLength() != 2	||
			t->ns_group.getValue().getCodeSet()[0] != 2				||
			t->ns_group.getValue().getCodeSet()[1] != 0				)
			return false;		

		return true;
	}
};

class NodeSelectorTest : public TestCase
{
public:
	NodeSelectorTest() : TestCase("validate node-selector with various sample tests.") {}
	virtual bool onTest() 
	{
		NEScriptEditor& manager = Editor::getInstance().getScriptEditor();
		NERootNodeCodeSet& rns = manager.getScriptNodes();

		manager.initialize();

		manager.insertNameCode(1);		
		manager.insertNameCode(2);
		manager.insertNameCode(3);
		manager.insertGroupCode(1);
		manager.insertGroupCode(2);
		manager.insertPriorityCode(1);

		NENode	*n0 = &rns[rns.push(NENode())],
			*n1 = &rns[rns.push(NENode())], 
			*n2 = &rns[rns.push(NENode())],
			*n3 = &rns[rns.push(NENode())],
			*n4 = &rns[rns.push(NENode())];
		NECodeSet is(1);
		is.setCodeType(NECodeType::GROUP);
		is.push(0);
		{
			//	0
			n0->setGroupCode(is);
		}
		{
			//	1
			is.create(1);
			is.push(1);
			n1->setNameCode(1);
			n1->setGroupCode(is);
			n1->setPriority(1);
		}
		{
			//	0, 1, 2
			is.resize(3);
			is.push(0);
			is.push(2);
			n2->setNameCode(2);
			n2->setGroupCode(is);
			n2->setPriority(1);
		}
		{
			//	0, 2
			is.create(2);
			is.push(0);
			is.push(2);
			n3->setNameCode(3);
			n3->setGroupCode(is);
			n3->setPriority(1);
		}
		{
			//	1, 2
			is.create(2);
			is.push(1);
			is.push(2);
			n4->setNameCode(3);
			n4->setGroupCode(is);
			n4->setPriority(1);
		}

		NENodeSelector ns;
		ns.setManager(NEType::NESCRIPT_EDITOR);
		ns.setNodeType(NECodeType::GROUP);
		NECodeSet is2(2);
		is2.push(0);
		is2.push(2);
		ns.setCodeSet(is2);
		ns.setUsingAndOperation(false);	//	OR 연산으로 처리.
		ns.setCountLimit(2);

		NEArrayTemplate<NENode*> pointers(8);
		//	예상 되는 pointers의 내용:
		//		[0]	=	n0		
		//		[1]	=	n2
		//		[2]	=	0x00
		//		[3]	=	n3
		//		[4] =	n4
		//		[5]	=	0x00
		//		[6]	=	n0
		//		[7]	=	n2
		//		[8]	=	0x00
		for (int n = 0; n < pointers.getSize(); n++)
			pointers.push(&ns.getNode());

		if (pointers.getLength() != pointers.getSize()) return false;
		if (&pointers[0] != n0) return false;
		if (&pointers[1] != n2) return false;
		if (&pointers[2] != 0x00) return false;
		if (&pointers[3] != n3) return false;
		if (&pointers[4] != n4) return false;
		if (&pointers[5] != 0x00) return false;
		if (&pointers[6] != n0) return false;
		if (&pointers[7] != n2) return false;

		pointers.create(12);
		ns.setNodeType(NECodeType::ALL);
		ns.setUsingAndOperation(false);
		ns.setCountLimit(2);
		for (int n = 0; n < pointers.getSize(); n++)
			pointers.push(&ns.getNode());

		if (pointers.getLength() != pointers.getSize()) return false;
		//	pointers[0]은 처음 intialize시 추가된다.
		if (&pointers[1] != n0) return false;
		if (&pointers[2] != 0x00) return false;
		if (&pointers[3] != n1) return false;
		if (&pointers[4] != n2) return false;
		if (&pointers[5] != 0x00) return false;
		if (&pointers[6] != n3) return false;
		if (&pointers[7] != n4) return false;
		if (&pointers[8] != 0x00) return false;
		//if (&pointers[] != n3) return false;
		if (&pointers[10] != n0) return false;
		if (&pointers[11] != 0x00) return false;


		return true;
	}
};

class KeyConversionTest : public TestCase
{
public:
	KeyConversionTest()	: TestCase("has key function to be converted to others?") {}
	virtual bool onTest() 
	{
		NEScriptEditor& ed = Editor::getInstance().getScriptEditor();
		ed.initialize();

		NENodeCodeSet& ns = ed.getScriptNodes();
		NENode& n = ns[ns.push(NENode())];
		n.getKeySet().create(2);
		NEIntKey& ik = (NEIntKey&) n.getKeySet()[n.getKeySet().push(NEIntKey(33, "k1"))];
		NEKeySelector& kk = (NEKeySelector&) n.getKeySet()[n.getKeySet().push(NEKeySelector("k2"))];

		kk.setKeyName("k1");
		n.execute();

		NEStringKey sk("hello", "k2");

		NEFloatKey fk(3.14f, "k3");
		ik.multiply(ik, fk);
		if(ik.getValue() != 99)
			return false;
		ik += NEStringKey("1");
		if(ik.getValue() != 100)
			return false;

		fk.negate();
		if(	fk.getValue() < -3.14f - 0.001f ||
			fk.getValue() > -3.14f + 0.001f	)
			return false;
		fk = ik;
		if(fk.getValue() != 100.0f)
			return false;
		fk.makeReciprocal();
		if( 0.01-0.0001f > fk.getValue()	||
			0.01+0.0001f < fk.getValue()	)
			return false;

		return true;
	}
};

class ModuleOwnerTest : public TestCase
{
public:
	ModuleOwnerTest()	: TestCase("a module has owner.") {}
	virtual bool onTest() 
	{
		NEScriptEditor& manager = Editor::getInstance().getScriptEditor();
		NERootNodeCodeSet& ns = manager.getScriptNodes();
		
		manager.initialize();
		NENode& n = ns[ns.push(NENode())];
		n.getModuleSet().create(2);
		n.getModuleSet().push(MyMod());
		NEModule&m = n.getModuleSet()[n.getModuleSet().push(MyMod())];
		m.execute();
		if(&m.getOwner() != &n.getModuleSet())
			return false;
		const NENodeManager::LocalStack& ls = Kernal::getInstance().getNodeManager().getLocalStack();
		if(ls.getRecentModuleSetIndex() != 1)
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
//		NEScriptHeader& ss = (NEScriptHeader&) scripter.getScriptHeader();
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
	init();
	Test14().test();
	system("pause");
	system("cls");
	StringFindingTest().test();
	ArrayAssigningTest().test();
	PointerArrayAssigningTest().test();
	HeapedPointerArrayAssigningTest().test();
	IndexedArrayAssigningTest().test();
	PointerIndexedArrayAssigningTest().test();
	HeapedPointerIndexedArrayAssigningTest().test();
	IndexedArrayReturningHeapMemory().test();
	IndexedArrayFileSerializeTest().test();
	Test1().test();
	NECodeSetInsertionTest().test();
	NEKeyManagerTypeTest().test();
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
	RelativityTestOnSynchronize().test();
	SelectorAssignOperatorTest().test();
	KeySelectorAssigningTest().test();
	GenericArgumentBindingTest().test();
	ArgumentConversionTest().test();
	ArgumentConstantLiteralTest().test();
	ArgumentInterfaceCanBeSaved().test();
	CodeSynchroTest().test();
	NodeSelectorTest().test();
	KeyConversionTest().test();
	ModuleOwnerTest().test();

	Kernal::saveSettings();
	delete &Editor::getInstance();
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