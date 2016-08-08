//	---------------------------------------------------------------------------------
//	클래스명:	Kernal
//	설명	:	필수 모듈을 포함하는 싱글톤 클래스. 어디에서나 불러오는 게 가능하다.
//	관계	:	기반클래스.	NEModule
//	특성	:	역시 모듈의 일종이다.
//	알고리즘:	싱글톤
//	사용방법:	Kernal::getInstance()를 실행하고, 프로그램이 끝나기 직전 
//				Kernal::terminate()를 실행한다.
//				동적 할당을 사용하는 싱글톤 클래스는 메모리 해제를 하지 않아도 프로그램
//				종료와 동시에 소멸한다고 하나, 안전한 종료를 위해서 명시적으로 terminate
//				하는 것을 권장한다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEINIManager/NEINIManager.hpp"
#include "../NEDebugManager/NEDebugManager.hpp"
#include "../NEPackageManager/NEPackageManager.hpp"
#include "../NEScriptManager/NEScriptManager.hpp"
#include "../NENodeManager/NENodeManager.hpp"
#include "../NEKeyManager/NEKeyManager.hpp"

namespace NE
{
	//	use dinamic-singleton
	//	스레드를 돌리기 전에 반드시 getInstance가 먼저 실행되어야만 한다.
	//	(스레드실행이, Kernal의 멤버변수이므로 문제는 없을 듯 하다.
	class NE_DLL Kernal : public NEModule
	{
		NE_DECLARE_MODULE(Kernal, NEModule)

	public:
#include "innerclass/Settings/Settings.hpp"
#include "innerclass/ModifiableSettings/ModifiableSettings.hpp"
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/Factory/Factory.hpp"

	public:
		friend class Kernal::Factory;

		//	생성자:
	private:
		Kernal();

	public:
		Kernal(const This& source);

		//	소멸자:
	public:
		virtual ~Kernal();

		//	연산자 오버로딩:
	public:
		const This& operator=(const This& source);
		bool operator==(const This& source) const;
		bool operator!=(const This& source) const;

		//	인터페이스:
		//		상속:
		//			NEExportable:
	public:
		virtual type_result initialize();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;
		//			NEUnit:
	private:
		virtual type_result execute();
		//			NEObject:	
	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

		//		고유 인터페이스:
	public:
		NEINIManager& getINIManager();
		const NEINIManager& getINIManager() const;
		NEDebugManager& getDebugManager();
		const NEDebugManager& getDebugManager() const;
		NEKeyManager& getKeyManager();
		const NEKeyManager& getKeyManager() const;
		NEPackageManager& getModuleManager();
		const NEPackageManager& getModuleManager() const;
		NENodeManager& getNodeManager();
		const NENodeManager& getNodeManager() const;
		NEScriptManager& getScriptManager();
		const NEScriptManager& getScriptManager() const;
		const ModifiableSettings& getSettings();
		const ModifiableSettings& getDefaultSettings() const;
		type_result loadSettings();

		//	내부함수:
	private:
		const This& _assign(const This& source);
		void _release();
		type_result _pointManagerInstance();
		void _releaseManagerPointer();
		void _initializeSettings();
		void _initializeSettingsToDefaultSettingsOrReleaseBoth();

		//	멤버변수:	
	protected:
		//		매니져 인스턴스:
		NEINIManager _ini_manager;
		NEKeyManager _key_manager;
		NEPackageManager _module_manager;
		ModifiableSettings _settings;
		ModifiableSettings _default_settings;
		NEExportable::Identifier _node_manager_identifier;
		NEExportable::Identifier _script_manager_identifier;
		bool _is_setting_initialized;
		NEDebugManager _debug_manager;
				
		//		매니져 포인터:
	protected:
		NEScriptManager* _script_manager;
		NENodeManager* _node_manager;

		//	전역 함수:
	public:
		//		차후에 커널 스위칭을 위해서는 밑의 코드가 변경될 필요가 있다.
		//		커널스위칭이란:	(미지원)
		//			복수의 커널을 팩토리를 통해 만들 수 있다. 이 만들어진 복수의 커널을 static 함수인 setInstance(This&)를 사용해서 
		//			상황에 따라서 스위칭 하는 기법을 말한다.
		//			각 커널은 다른 INI를 로드할 수 도 있고, 다른 모듈폴더를 fetch 할 수도 있다.
		//			(에디터 패키지에서 테스트를 할때 사용할 수 도 있을 것이다)
		static type_result setInstance(This& new_instance_to_set); // 내부에서 새로운 인스턴스를 생성한다.
		static This& getInstance();		
		static type_result saveSettings();

		//	전역 변수:
	protected:
		static This* _instance; // 얇은 복사되는 인스턴스다.
	};
}
