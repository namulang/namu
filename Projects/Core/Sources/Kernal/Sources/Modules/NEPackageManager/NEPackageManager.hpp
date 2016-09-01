//	---------------------------------------------------------------------------------
//	클래스명:	NEPackageManager
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
#include "../NEPackageSet/NEPackageSet.hpp"

namespace NE
{
	class NE_DLL NEPackageManager : public NEModule
	{
		NE_DECLARE_MODULE(NEPackageManager, NEModule)

	public:
		friend class Kernal;
		friend class Editor;

		//	생성자:
	public:
		NEPackageManager();
		NEPackageManager(const This& source);

		//	연산자 오버로딩:
	public:
		const This& operator=(const This& source);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

		//	소멸자:
	public:
		virtual ~NEPackageManager();

		//	접근자:
	public:
		const NEPackage& findPackage(const NETString& developer, NETString& name, type_int interface_revision) const;
		const NEPackage& findPackage(const NEIdentifier& package_identifier) const;
		const NEPackageSet& getPackages() const;
		const NEClassBase& findClass(const NETString& developer, NETString& name, type_int interface_revision) const;
		const NEClassBase& findClass(const NEIdentifier& identifier) const;
		const NEClassBaseSet& getClasses() const;

		//	인터페이스:git
		//		상속:
		//			NEExportable:
	public:
		virtual type_result initialize();
		//			NEUnit:
	private:
		virtual type_result execute();
		//			NEOject:
	public:
		virtual type_result isValid() const;
		virtual void release();

		//	내부함수:
	private:
		type_result _pushBuiltIns(NEPackageList& candidates);
		const This& _assign(const This& source);
		void _release();
		type_result _fetchPackages(NEPackageList& candidates);
		type_result _ownPackages(NEPackageList& candidates);
		type_bool _isFiltered(const NEPackage& fetched, const NEPackageList& candidates) const;
		type_bool _isDuplicated(const NEPackage& fetched, const NEPackageList& candidates) const;
		type_result _linkPackages(NEPackageList& candidates);
		type_result _listupCandidatesToLink(NEPackageList& candidates);
		type_result _linkPackage(NEPackage& to_be_fetched);
		type_result _removePackagesFailedToLink(NEPackageList& candidates);
		type_result _ownClasses(NEPackage& package);
		type_result _enroll(const NEClassBase& new_class);
		type_result _pushToManaged(const NEClassBase& new_class);
		type_int _judgeIdentifierScore(const NEHeader& existing, const NEIdentifier& target) const;
		template <typename T, type_bool useHeap>
		const NEIdentifier& _findIdentifier(const NEIdentifier& target, NETArray<T, useHeap, T>& collector) const;

		//	멤버변수:		
	private:		
		NEPackageSet _packages;
		NEClassBaseSet _classes;
	};
}