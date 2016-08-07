#include "NEPackageManager.hpp"
#include "../Kernal/Kernal.hpp"
#include "define/define.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPackageManager::NEPackageManager()
		: Super()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPackageManager::NEPackageManager(const This& source)
		: Super(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPackageManager::~NEPackageManager()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEPackageManager NE_DLL &NEPackageManager::operator=(const This& source)
	{		
		if(this == &source) return *this;

		Super::operator=(source);

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEPackageManager::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(Super::operator==(source) == false) return false;
		if(_packages != source._packages) return false;
		if(_classes != source._classes) return false;
		
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEPackageManager::operator!=(const This& source) const
	{
		return !(operator==(source));
	}

namespace
{
	inline type_uint abs(type_int raw)	
	{
		return raw < 0 : -raw : raw;
	}
}


	const NEPackage& NEPackageManager::findPackage(const NETString& developer, NETString& name, type_int interface_revision) const
	{
		return findPackage(NEIdentifier(developer, name, interface_revision));
	}

	const NEClassBase& NEPackageManager::findClass(const NETString& developer, const NETString& name, type_int interface_revision) const
	{
		return findClass(NEIdentifier(developer, name, interface_revision));
	}

	const NEPackage& NEPackageManager::findPackage(const NEIdentifier& identifier) const
	{
		return static_cast<NEPackage&>(_findIdentifier(identifier, _packages));
	}

	const NEClassBase& NEPackageManager::findClass(const NEIdentifier& identifier) const
	{
		return static_cast<NEClassBase&>(_findIdentifier(identifier, _classes));
	}

	type_int _judgeIdentifierScore(const NEHeader& existing, const NEIdentifier& target) const
	{		
		if(	existing.getDeveloper() != target.getDeveloper()	||
			existing.getName() != target.getName()				)	return 0;
		if(existing.getInterfaceRevision() == target.getInterfaceRevision()) return 3;
		if(existing.getCompatibles().find(target.getInterfaceRevision()))
			return 2;

		return 1;
	}

	template <typename T, type_bool useHeap>
	const NEIdentifier& NEPackageManager::_findIdentifier(const NEIdentifier& target, NETArray<T, useHeap>& collector) const
	{
		//	pre:
		//		Fit:
		struct Fit
		{
			NEIdentifier* founded;
			type_int score;
		};
		Fit to_return = {NE_NULL, 0};
		

		//	main:		
		//		finding:
		for(type_index n=0; n < collector.getLength() ;n++)
		{
			const NEHeader& e = collector[n];
			type_int score = _judgeIdentifierScore(e, target);
			if(score < to_return.score) continue;
			if(score == 3) return collector[n];	//	just fit case.

			//	if we met new challenger,
			if(	score > to_return.score								||
				e.getRevisionCount() > to_return.getRevisionCount()	)
			{
				to_return.founded = &e;
				to_return.score = score;
			}
		}


		//	post:	모든 탐색을 실시했으나 최선책을 찾지 못했다.
		//			차선책으로 갱신된 인덱스가 가리키는 모듈을 내보낸다.
		if( ! to_return.founded)
		{
			//	차선책을 찾지 못했다면:	만약 차선책조차 찾지 못했다면 처음에 second_fit_index로 주어졌던
			//							더미모듈이 내보내질 것이다.		
			KERNAL_ERROR("E201011C44 : 일치하는 모듈 검색 실패\n주어진 모듈의 이름, 개발자와 일치하는 모듈이 없습니다. 모듈매니져는 더미모듈을 반환할 것입니다.\n찾으려는 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\tRevisionCount : %d\n\tVersionCount : %d", identifier.getName().toCharPointer(), identifier.getAuthor().toCharPointer(), identifier.getRevisionCount(), identifier.getVersionCount())
		
			NEIdentifier* null_pointer = NE_NULL;
			return *null_pointer;
		}		
		//		차선책을 찾았다면:		
		KERNAL_WARNING(" : We was supposed to provide NEPackage for your request, but couldn't find proper one. Instead of, we just prepare the alternative one for you. Its information is next following.\n\tName\t: %s\n\tAuthor\t: %s\n\tRevisionCount : %d\n\tVersionCount : %d\n\tPath\t: %s", found.getName().toCharPointer(), found.getAuthor().toCharPointer(), found.getRevisionCount(), found.getVersionCount(), found.getPath().toCharPointer());
		
		return *to_return.founded;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-16	이태훈	작성
	//	---------------------------------------------------------------------------------
	const NEPackageSet& NEPackageManager::getPackages() const
	{	
		return _packages;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	모듈 파일로부터 모듈을 가져온다
	type_result NE_DLL NEPackageManager::execute()
	{	
		if(_packages.getLength() > 0) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return initialize();
	}


	type_result NEPackageManager::_pushBuiltIns(NEPackageList& candidates)
	{
		//	create Kernel Package manually:
		//NEPackage kernel_package;
		//kernel_package....;		

		return RESULT_SUCCESS; //candidates.push(builtin);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEPackageManager::isValid() const
	{						
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result | NEMODULE_IS_NOT_VALID;
		result = _packages.isValid();
		if(NEResult::hasError(result)) return result | DLL_HEADERSET_IS_NOT_VALID;
		result = _packages.isValid();
		if(NEResult::hasError(result)) return result | MODULESET_IS_NOT_VALID;
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPackageManager::initialize()
	{
		//	pre:
		//		초기화:
		_release(); // release()를 하면 안된다.


		//	main:
		NEPackageList candidates;
		_pushBuiltIns(candidates);
		//		모듈 Fetch:
		_linkPackages(candidates);
		_fetchPackages(candidates);
	
		return RESULT_SUCCESS;
	}

	const NEPackageSet& NEPackageManager::getPackages() const
	{
		return _packages;
	}

	const NEClassBaseSet& NEPackageManager::getClasses() const
	{
		return _classes;
	}

	type_result NEPackageManager::_ownClasses(NEClassBaseList& candidates, NEPackage& package)
	{
		int n=0;
		for(NEClassBaseList::Iterator* e=candidates.getIterator(0); e ;e=e->getNext(), n++)
		{
			NEClassBase& klass = e->getValue();
			//	Package instance copying doesn't make the problem:
			//		NEPackage instances have prior to exist more than classes which were imported from them.
			//		So don't need to worry about assigning pointer of package directly in this code.
			//	class enrolling call "Module.onFetched" callback:
			if(NEResult::hasError(_enroll(klass)))
			{
				NEHeader& header = klass.getHeader();
				KERNAL_WARNING(": we've met errors while enrolling fetched class, %s.%s.%d\nSorry, but we've to choose not to load this class.", header.getDeveloper().toCharPointer(), header.getName().toCharPointer, header.getInterfaceRevision());
				candidates.remove(n);
				n--;
				e=candidates.getIterator(n);
				continue;
			}
		}


		//	post:
		//		make it own:
		NEClassBaseSet& classes = package.getClasses();
		classes.create(candidates.getLength());

		for(NEClassBaseList::Iterator* e=candidates.getIterator(0); e ;e=e->getNext())
			classes.push(e->getValue());

		return RESULT_SUCCESS;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEPackageManager::release()
	{
		//	멤버함수 초기화
		Super::release();

		return _release();
	}		


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-08	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEPackageManager& NEPackageManager::_assign(const This& source)
	{
		if(this == &source) return *this;

		_packages = source._packages;
		_classes = source._classes;

		return *this;
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEPackageManager::_release()
	{
		_packages.release();
		_classes.release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	연결된 DLL 파일로부터, 실행 엔트리포인트에 접근해서 모듈을 가져온다.
	//	동작조건:
	//	메모	:	가져온 모듈은 의존성을 고려해서 재 정렬한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEPackageManager::_fetchPackages(NEPackageList& candidates)
	{
		//	배경:	
		//		의존성:	
		//				모듈에는 의존성이라는 게 존재하는데,
		//				이는 초기화시에, 다른 모듈이 먼저 초기화되어있야 함을 의미한다.
		//	
		//				예를 들어, 윈도우의 DC를 얻어서 조작하는 모듈이 있을 경우,
		//				이 모듈은 윈도우를 생성하는 모듈이 먼저 초기화가 되어야만 초기화가 가능할 것이다.
		//				또한 소멸의 경우도, 윈도우 모듈이 먼저 소멸되어서는 안된다.
		

		//	main:
		//		버퍼에 데이터 축적:
		typedef NEPackageList::Iterator Iterator;
		int n=0;
		for(Iterator* e=candidates.getIterator(0), n=0; e ;e=e->getNext(), n++)
		{
			NEPackage& package = e->getValue();
			//	release:
			package.getClasses().release();
			package.NEHeader::release();
			//	enter at entrypoint:
			NEClassBaseList tray;
			if(NEResult::hasError(package.getEntryPoint()(package, tray)))
			{
				KERNAL_WARNING("error happen while loading %s module", package.getName().toCharPointer());
			}
			//	filtering:
			if(_isFiltered(package, candidates))
			{
				candidates.remove(n);
				n--;
				e = candidates.getIterator(n);
				continue;
			}
			//	make it own:
			_ownClasses(tray, package);
		}	
		
		
		//	post:
		return _ownPackages(candidates);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	최종적으로 의존성을 고려해서 정렬된 모듈리스트로부터 모듈을 복사한다.
	//	동작조건:
	//	메모	:	push되는 순서대로 모듈의 scriptcode를 부과한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료	
	//	---------------------------------------------------------------------------------
	type_result NEPackageManager::_ownPackages(NEPackageList& candidates)
	{	
		//	pre:
		if(	NEModuleList bucket.getLength() <= 0) return;



		//	main:
		_packages.create(candidates.getLength());

		//		candidates로부터의 복사:
		typedef NEPackageList::Iterator Iterator;
		for(Iterator* e=candidates.getIterator(0); e ;e=e->getNext())		
		{
			NEPackage& package = e->getValue();
			_packages.push(package);

			KERNAL_INFORMATION("'%s' package was added", package.getName().toCharPointer());
		}

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	추가하려는 모듈이 이미 존재하는 모듈이름을 갖고 있다면, 보다 최신버전
	//				만 넣으려 한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_bool NEPackageManager::_isDuplicated(const NEPackage& fetched, const NEPackageList& candidates) const
	{
		//	main:
		typedef NEPackageList::Iterator Iterator;

		int n=0;
		for(Iterator* e=candidates.getIterator(0); e ;e=e->getNext(), n++)
		{		
			//	대상1 추출:
			const NEIdentifier& source = e->getValue();
			//	대상1과 비교:	대상1과 같은 모듈이 있는지 확인한다
			if(source != fetched) continue;
			
			//	removal duplicated:				
			KERNAL_WARNING("W201011C41 : 동일한 모듈 복수 존재\n같은 식별자를 지닌 모듈이 2개 이상 존재합니다.\n모듈매니져는 나중에 식별한 모듈은 읽지 않을 것입니다.\n동일한 모듈의 식별자:\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d\n\tVersionCount : %d", target.getName().toCharPointer(), target.getAuthor().toCharPointer(), target.getRevisionCount(), target.getVersionCount())
			return true;
		}

		return false;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정된 폴더에 존재하는 DLL 파일을 검색한다.
	//	동작조건:
	//	메모	:	NEFileSystem의 검색기능을 사용한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEPackageManager::_linkPackages(NEPackageList& candidates)
	{
		//	main:
		_listupCandidatesToLink(candidates);
		//		루핑:	
		type_bool has_changed = false;
		do
		{
			has_changed = false;
			/*
				_linkDLLsUsingInputedPath()는 변경점이 존재할시에만 true를 반환한다
			*/
			typedef NEPackageList::Iterator Iterator;
			for(Iterator* e=candidates.getIterator(0); e ;e=e->getNext())
			{
				NEPackage& to_be_fetched = e->getValue();

				if( ! to_be_fetched.isLoaded())
					if(_linkPackage(to_be_fetched) == RESULT_SUCCESS)
						//	로드에 성공했다면:	변경점이 존재한것이 된다
						has_changed = true;

			}
		} while(has_changed);



		//	post:
		return _removePackagesFailedToLink();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	검색한 DLL 파일을 프로세스에 올리고, 엔트리포인트의 주소를 가져온다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEPackageManager::_linkPackage(NEPackage& to_be_fetched)
	{	//	배경:
		//		왜 push를 하고 참조자를 가져오는가:
		//			push하는 과정에서 소멸자와 복사생성자가 호출되기 때문이다.
		//			to_be_fetched의 소멸자는 FreeLibrary를 호출해서 연결한 DLL을 소멸시킨다.
		//			이런 오버헤드를 줄이기 위해서, 미리 값을 집어넣고 외부에서 조작한다


		//	pre:
		//		파라메터 검사:
		if( ! &to_be_fetched) return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		if( ! &(to_be_fetched.getPath())) return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | DLL_PATH_IS_NULLED;
		//		타겟팅:
		NEINIManager& ini = Kernal::getInstance().getINIManager();



		//	main:
		//		기본적인 정보 삽입:		
		//			인스턴스:
		/*
			LoadLibrary시 내부에서 발생하는 오류 메세지박스를 잠시 끄기 위해서, 
			SetErrorMode WINAPI를 사용한다
		*/
		SetErrorMode(SEM_FAILCRITICALERRORS);
		to_be_fetched.setInstance(LoadLibrary(to_be_fetched.getPath().toCharPointer()));
		/*
			다시 오류 메세지를 활성화 한다.
		*/
		SetErrorMode(NE_DEFAULT);

		//		조건1:	DLL을 못 읽었다면		
		if( ! to_be_fetched.getInstance())
			/*
				의존성 때문에 실패할 가능성이 있다. 일단 보류를 의미하는 FAILED_TO_ACCESS_DLL를 외부에 반환한다.
				외부에서는 FAILED_TO_ACCESS_DLL를 발견시, 버퍼에 남겨놓고 다른 DLL을 try 할것이다.
				모듈매니져는 최종적으로 다음과 같은 상황에, DLL 로드 sequence를 중단하게 된다.

					1. 모든 DLL을 로드 완료(버퍼의 길이가 0)
					2. 남은 버퍼를 0부터 마지막까지 try했으나, 변경점 없이 모두 fail시
			*/
			return RESULT_TYPE_ERROR | RESULT_ACCESS_DENIED | FAILED_TO_ACCESS_DLL;

		//		로드 성공:
		//			진입점을 가져옴:
		to_be_fetched.setEntryPoint(reinterpret_cast<EntryPoint>(GetProcAddress(to_be_fetched.getInstance(), _DLL_ENTRYPOINT_STRING)));

		//			조건1-1:	진입점을 가져오지 못했다면
		if( ! to_be_fetched.getEntryPoint())
		{	//			동작 실패:	로드는 성공했지만 엔트리포인트 등록에는 실패
			KERNAL_ERROR("E201011C39 : 실행 엔트리포인트 접근 실패\nDLL 확인 및 동적 DLL 연결에는 성공했으나 실행 엔트리 포인트에 연결하지 못했습니다.\n해당 모듈 개발자가 잘못된 엔트리포인트를 사용하고 있을 가능성이 있습니다.\n모듈매니져가 이 DLL을 제외할 것입니다.\n표준 엔트리포인트 : %s\n파일명 : %s", _T(_DLL_ENTRYPOINT_STRING), to_be_fetched.getPath().toCharPointer())

			return RESULT_TYPE_ERROR | RESULT_ACCESS_DENIED;
		}

		return RESULT_SUCCESS;
	}
	
	type_result NEPackageManager::_listupCandidatesToExamine(NEPackageList& candidates)
	{
		//	pre:
		//		타겟팅:
		NEINIManager& ini = Kernal::getInstance().getINIManager();
		//		버퍼 준비:
		NETString path = Kernal::getInstance().getSettings().getPackageDirectory() + _T("*.dll");



		//	main:
		//		검색 준비:
		NEFileSystem filesystem(path.toCharPointer(), true); //	테스트니까 일단 풀 경로를 지정한다. 릴리즈에서는 "Modules/*.dll" 만 하면 됨
		//		루핑:
		const NEHeader& header = getClassStatically().getHeader();
		while(true)
		{
			filesystem.findFile();
			const NEFileSystem::TaskUnit& task = filesystem.getLastElement();
			if( ! &task) break;

			//		읽기 가능 flag:
			//			버퍼 생성:
			NETString value;
			//			INI로부터 값 가져옴:
			type_result result = ini.readModuleIniString(header, task.getFilePath(), value);
			//		로드 여부 조건 검사:
			//			만약 에러가 발생했다면:
			if(NEResult::hasError(result))		
				ini.writeModuleIniString(header, task.getFilePath(), NETString(true));
			else	//	에러가 없다면:
				//			가져온 값이 false(로드 안함) 이라면:
				if( ! value.toBoolean())
				{
					KERNAL_INFORMATION("I201011C53 : DLL 동적 연결 취소\nINI를 통해서 발견한 DLL을 로드 하지 않기로 했습니다.\n로드하고 싶다면 INI의 키값을 false에서 true로 바꾸십시오.\n취소된 DLL 파일명 : %s", task.getFilePath())

					continue;
				}

			NEPackage new_one;
			new_one.getPath() = task.getFilePath();
			candidates.push(new_one);
		}

		return RESULT_SUCCESS;
	}

	type_result NEPackageManager::_removePackagesFailedToLink(NEPackageList& candidates)
	{
		typedef NEPackageList::Iterator Iterator;

		type_index n=0;
		for(Iterator* e=candidates.getIterator(0); e ;e=e->getNext(), n++)
		{
			NEPackage& package = candidates[n];

			if(package.isLoaded()) continue;			
				
			KERNAL_ERROR("E201011C40 : DLL 동적 연결 실패\nDLL은 찾았으나 동적 연결에 실패했습니다.\n올바른 DLL 파일이 아니거나, 릴리즈 / 디버그 모드가 다를 경우 이 메세지가 발생할 수 있습니다.\n다시 확인 해보십시오.\nKernal 빌드 모드 : Debug\n파일명 : %s", package.getPath().toCharPointer())

			candidates.remove(n);

			//	balance index and iterator*:
			e=candidates.getIterator(n);
			n--;
		}

		return RESULT_SUCCESS;
	}

	type_bool NEPackageManager::_isFiltered(const NEPackage& fetched, const NEPackageList& candidates) const
	{
		//	when we have more requirements to filter, it'll be added at here.
		return _isDuplicated(fetched, candidates);
	}

	type_result NEClassManager::_enroll(const NEClassBase& new_class)
	{
		//	pre:
		//		Acquire static instance:
		static NETClass<NEAdam> root;
		//		exception handlings:
		if( ! &new_class) return KERNAL_WARNING("...");
		if(new_class.isRegistered()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;


		//	main:
		//		enroll parent:
		const NEClassBase& super = new_class.getSuperClass();
		if( ! &super)
			//	if new_class is a NEAdam class, its returend 'super' is a instance of Null.
			return RESULT_SUCCESS;
		//		hee- ha! lets do this reculsively.
		_enroll(super);

		//		enrolls:
		//			supers: we can call this because Superclasses are all enrolled.
		new_class._enrollSuperClasses(super);	//	in this handler, each super classes receive sub classes.


		//	post:
		super._enrollChildClass(new_class);
		return _pushToManaged(new_class);
	}

	type_result NEPackageManager::_pushToManaged(const NEClassBase& new_class)
	{
		//	pre:
		//		resize:
		if(_classes.getLength() >= _classes.getSize())
			_classes.resize(_classes.getSize() * 2);


		//	main:
		type_index n = _classes.push(new_class);
		if (n == NE_INDEX_ERROR)
			return KERNAL_ERROR("...")


			//	post:
			//		give _class id as pushed index:
			//			there is no instance changing after inserted.
			//			(except for whole initializing)
			//			so, when new_class take new class id, it's ne
			//			ver get changed.
			new_class._getId() = n;
		return RESULT_SUCCESS;
	}
}