//	---------------------------------------------------------------------------------
//	클래스명:	NEModule
//	설명	:	하나의 기능을 제공하는 클래스. 모듈을 임의의 순서 / 배합을 통해서
//				지능적으로 반응하는 하나의 객체를 생성한다.
//	관계	:	기반클래스.	NENamedUnit
//				중첩클래스.	Header
//	특성	:	NEModuleManager에 friend 선언
//	알고리즘:	
//	사용방법:	execute()	:	담당하는 하나의 기능을 수행한다.
//				키를 다루는 방법은 2가지가 존재한다.
//					방법 1.	NEKeySet을 통해서 다룸.
//						:	이 경우 각 키의 타입을 읽어온 뒤에 캐스팅을 실시해야하고,
//							각 키가 "무슨 타입"이라는 건 알 수 있어도 "무슨 역할"을 
//							수행하는 가는 알 수 없다.
//					방법 2.	해당 모듈의 헤더를 통해서 모듈자체를 캐스팅한다.
//						:	이 경우 모듈의 BaseConnector를 이용하면 캐스팅 없이 사용이 
//							가능 하다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------

//	관련 이슈 및 정책:
//		_assign(const ThisClass& rhs):
//			Argument, Module, ArugmentInterface 3가지를 아우르는 "모듈의 인자" 컴포넌트의 최중요 함수다.
//			모든 책임이 여기서 이루어지게 된다. 여기서 이루어져야 하는 것들은,
//				- 각각의 독립적으로 따로 노는 클래스들을 유기적으로 조립시킨다.
//				- 클래스들의 매개체 역할을 수행해야 한다.
//			가 된다.
//
//		Argument Binding Policy:
//			-	인스턴스 생성시 바인딩에 필요한 정보는 복사 되어야 한다.
//			-	바인딩 결과물은 절대로 객체간에 공유하지 않는다. 해당 객체가 다시 바인딩을 시도해야 한다.
//				왜냐하면, 같은 데이터를 가지고도 객체갸 어떤 소유자 밑에 있느냐에 따라서 바인딩 결과가 
//				달라지기 때문이다.
//			-	Interface를 통해 Argument 생성도 인스턴스 생성과 동시에 한번 이루어진다.
//			-	바인딩은 성공할 때까지 시도된다.
//				왜냐하면, 아직 Node에 포함되지 않는 Module도 있을 수 있기 때문이다.
//				현재까지로는 NEModule 자체가, 어떤 Node가 자신을 가지고 있는지 추적 할 수 없다.
//
//		_onArgumentFetched:
//			-	인스턴스 생성시 호출된다. (로드, 복사생성, 기본생성)
//			-	여기에는 바인딩 정보만 넣어두는 것을 권장한다.
//				매번 인스턴스 생성시 호출되므로, default_value 등을 여기서 정의하면 default_value는 
//				외부 객체로부터 복사가 안 일어나는 것처럼 보이게 된다.
//				(예, MyMod::_onArgumentFetched() { default_value = 58; } 
//				MyMod rhs.default_value=19 일때, MyMod me(rhs)를 수행하면, 복사과정에서
//					1/	me.default_value = rhs._default_value; 가 수행되어 19로 되었다가,
//					2/	MyMod::_onArgumentFetched()가 실행되어 다시 58로 된다)
#pragma once

//	include:
#include "../../Commons/Interfaces/NEExportable/NEExportable.hpp"
#include "../NENamedUnit/NENamedUnit.hpp"
#include "../NEKeyCodeSet/NEKeyCodeSet.hpp"
#include "../NEArgumentSet/NEArgumentSet.hpp"
#include "../../Commons/Interfaces/NEArgumentInterfaceBase/NEArgumentInterfaceBase.hpp"

namespace NE
{
	class NE_DLL NEModule : public NENamedUnit, public NEExportable
	{
	public:
		typedef NENamedUnit SuperClass;
		typedef NEModule ThisClass;		

	public:
		//	프렌드 선언:
		friend class NEModuleManager;
		friend class NEScriptSet;
		friend class NEModuleCodeSet;
		friend NEBinaryFileLoader& NEArgumentSet::serialize(NEBinaryFileLoader& loader);

		//	생성자:
	public:		
		NEModule();
		NEModule(const NEModule& source);

		//	소멸자:
	public:
		virtual ~NEModule();

		//	연산자 중첩:
	public:
		const ThisClass& operator=(const ThisClass& rhs);
		bool operator==(const NEModule& source) const;
		bool operator!=(const NEModule& source) const;

		//	인터페이스:
	public:
		NEArgumentSet& getArguments() { return _arguments; }
		const NEArgumentSet getArguments() const { return _arguments; }

		//		상속:
	public:
		virtual type_result initialize();
		//			NEObject:
	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEType::Type getType() const;

	protected:
		virtual type_result _onModuleFetched();
		virtual type_result _onArgumentsFetched(NEArgumentInterfaceList& tray);

	protected:
		type_result _bindArguments();
		type_result _bindArguments(NEArgumentInterfaceList& args);

	private:
		ThisClass& _assign(const ThisClass& rhs);
		void _release();

	private:
		NEArgumentSet _arguments;
	};
}
