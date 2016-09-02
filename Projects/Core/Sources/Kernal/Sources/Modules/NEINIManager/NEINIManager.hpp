//	---------------------------------------------------------------------------------
//	클래스명:	NEINIManager
//	설명	:	INI의 저장 / 로드를 수행한다.
//	관계	:	기반클래스.	NEModule
//	특성	:	다른 어떠한 Manager 클래스 보다 먼저 초기화 된다.
//				역시 모듈의 일종이다.
//				UNICODE 환경이라면 INI 역시 UNICODE로 작성 되므로, 언어가 다른 환경에서
//				호환성을 높였다.
//				INI는 통합적으로 관리되며, 따로 INI파일을 작성할 수는 없다.
//	알고리즘:	API를 사용한다.
//	사용방법:	크게 2가지 방법으로 분류된다.
//					방법 1.	모듈을 사용한 INI
//						:	이경우, 모듈별로 항목이 만들어져서 관리되므로 사용자가 INI
//							읽기가 편하다. 권장 방법.
//							readModuleIniString, writeModuleIniString을 사용하면 된다.
//					방법 2. 임의로 항목을 생성
//						:	권장하지 않는다. 
//							write, read를 사용한다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEModule/NEModule.hpp"
#include "../NEWString/NEWString.hpp"
#include "../NEString/NEString.hpp"
#include "../NETString/NETString.hpp"

namespace NE
{
	class NE_DLL NEINIManager : public NEModule
	{
		NE_DECLARE_MODULE(NEINIManager, NEModule)

	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"
		
		//	생성자:
	public:
		NEINIManager();
		NEINIManager(const This& source);

		//	소멸자:
	public:
		virtual ~NEINIManager();
		
	public:
		const This& operator=(const This& source);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

		//	인터페이스:
		//		상속:
		//			NEModule:
	public:
		virtual type_result initialize();
		//			NEExportable:
	public:
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;
		virtual const NEHeader& getHeader() const;
		//			NEUnit:
	private:
		virtual type_result execute();

		//		고유 인터페이스:
	public:		
		type_result readModuleIniString(const NEIdentifier& identifier, NETString keyword, NE_OUT NETString& loaded_data) const;
		type_result writeModuleIniString(const NEIdentifier& identifier, NETString keyword, NETString content) const;
		type_result write(const NETString& category, const NETString& title, const NETString& content) const;
		type_result read(const NETString& category, const NETString& title, NE_OUT NETString& loaded_data) const;

		//	내부함수:
	private:
		void _transformUnicode() const;
		type_bool _isUnicodeFile() const;
		void _createNewFileAsUTF16() const;
	};
}
