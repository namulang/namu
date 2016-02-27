//	---------------------------------------------------------------------------------
//	클래스명:	NEModuleManager
//	설명	:	모듈을 관리하는 관리자 클래스.
//	관계	:	기반클래스.	NEModule
//	특성	:	노드엔진에 기본적으로 포함되는 모듈클래스다.
//	알고리즘:	NEFileSystem의 검색 기능을 사용해서 모듈(*.dll)을 찾고, 내부에서 미리 
//				지정된 엔트리포인트로 모듈을 가져온다.
//				그 후, 종속성을 고려해서 모듈을 재배치한다.
//				또한 모듈을 외부에서 접근 할 수 있도록 인터페이스를 제공한다.
//	사용방법:	getLength()	:	모듈의 갯수
//				getModule(type_id)
//					:	모듈의 아이디를 통해서 접근한다. 권장하지 않는다. 모듈의 아이디
//						(fetch 되는 순서)는 환경에 따라 달라지기 때문이다.
//						그보다는 헤더를 통해서 모듈을 가져오는 방법을 권장한다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NENode/NENode.hpp"
#include "../NEModuleSet/NEModuleSet.hpp"
#include "../NEModuleList/NEModuleList.hpp" // innerclass에서 사용하기 위해서

namespace NE
{
	class NE_DLL NEModuleManager : public NEModule
	{
	public:
		friend class Kernal;

		//	내부클래스:
	public:
#include "innerclass/DLLHeader/DLLHeader.hpp"
#include "innerclass/ErrorCode/ErrorCode.hpp"

		//	typedef:
		typedef class NE_DLL NETList<NEModuleManager::DLLHeader> DLLHeaderList;

		//	생성자:
	public:
		NEModuleManager();
		NEModuleManager(const NEModuleManager& source);

		//	연산자 오버로딩:
	public:
		const NEModuleManager& operator=(const NEModuleManager& source);
		bool operator==(const NEModuleManager& source) const;
		bool operator!=(const NEModuleManager& source) const;

		//	소멸자:
	public:
		virtual ~NEModuleManager();

		//	접근자:
	public:
		const NEModule& getModule(const NEExportable::Identifier& identifer) const;
		const DLLHeaderList& getDllHeaderSet() const;
		const NEModuleSet& getModuleSet() const;
		
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
		//			NEOject:
	public:
		virtual NEType::Type getType() const;
		virtual NEObject& clone() const;
		virtual type_result isValid() const;
		virtual void release();

		//	내부함수:
	private:
		const NEModuleManager& _assign(const NEModuleManager& source);
		void _release();
		void _linkModule();
		void _pushModuleSet(NEModuleList& buffer);
		void _resorting(NEModuleList& source);
		type_index _searchModuleIndexWithDependencies(NEModule& module, NEModuleList& searching_target);
		void _filterNestedName(NEModuleList& source);
		void _linkDLL();
		void _pushDLLPathToDLLHeaderSet();
		bool _linkDLLsUsingInputedPath();
		type_result _pushDLLHeader(NEModuleManager::DLLHeader& header);
		void _reportErrorsIfThereAreModulesNotFeched();

		//	멤버변수:		
	protected:		
		DLLHeaderList _dllheaderset;
		NEModuleSet _moduleset;
	};

	template 
	class NE_DLL NETList<NEModuleManager::DLLHeader, false>;
}