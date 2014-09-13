#include "NEModuleManager.hpp"
#include "../Kernal/Kernal.hpp"
#include "define/define.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleManager::NEModuleManager()
		: NEModule()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleManager::NEModuleManager(const NEModuleManager& source)
		: NEModule(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModuleManager::~NEModuleManager()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEModuleManager NE_DLL &NEModuleManager::operator=(const NEModuleManager& source)
	{		
		NEModule::operator=(source);

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModuleManager::operator==(const NEModuleManager& source) const
	{
		if(this == &source) return true;
		if(NEModule::operator==(source) == false) return false;
		if(_dllheaderset != source._dllheaderset) return false;
		if(_moduleset != source._moduleset) return false;
		
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModuleManager::operator!=(const NEModuleManager& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 모듈식별자로 모듈을 검색한다.
	//	알고리즘:	최선책과 차선책에 대해서
	//					:	최선책이란 모듈이름, 제작자와 개정횟수까지 일치하는 걸 말하며,
	//						완벽하게 같은 모듈임을 입증하는 것을 말한다. 
	//						검색 우선순위 1 순위다.
	//						차선책은 검색 우선순위 2순위로, 최선책이 존재하지 않을때 결정
	//						한다.
	//						조건은 "모듈이름", "제작자"는 같은나 버전은 다른 경우를 말한다.
	//						대개, 이때의 개정횟수은 "제시한 개정횟수보다 높은 버전"이며,
	//						target의 호환성(compatibilities)에 source의 버전이 포함된 경우를
	//						말한다.
	//	동작조건:	
	//	메모	:	식별자란, "이름", "개정번호", "제작자"를 말한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEModule NE_DLL &NEModuleManager::getModule(const NEExportable::Identifier& identifer) const
	{
		//	pre:
		NEModule* null_pointer = NE_NULL;


		//	main:
		type_index	second_fit_index = -1; // 이름과 차선책. 만약 차선책조차 없다면 -1이 유지된다.
		int	second_fit_revision = 0; // 차선책의 개정횟수

		for(type_index n=0; n < _moduleset.getLength() ;n++)
		{
			const NEExportable::ModuleHeader& header = _moduleset.getElement(n).getHeader();

			//	만약 제작자와 이름이 같다면:
			if(identifer.isSameModule(header))
			{
				//	같은 종류의 모듈을 발견한 경우:
				//		개정횟수마져 일치하면:
				if(header.getRevision() == identifer.getRevision())
				{
					//		최선책 발견:	더이상 검색할 이유가 없다.
					return _moduleset.getElement(n);
				}
				else //	차선책 경합:
				{
					//		보다 최신 모듈인지 판단:	현재 알고있는 차선책의 개정횟수보다 큰가?
					if(header.getRevision() > second_fit_revision)
					{
						//		호환성 판단:	호환이 가능한 버전인지 확인할 필요성이 생겼다.
						const NEIntSet& compatibilities = header.getRevisionCompatibilities();

						for(type_index iterator=0; iterator < compatibilities.getLength() ;iterator++)
						{
							//		만약 타겟의 호환 가능한 개정횟수에, 인자로 주어진 모듈의 개정횟수가 포함된다면,					
							if(identifer.getRevision() == compatibilities.getElement(iterator))
							{
								//		타겟이 보다 높은 버전일 가능성이 크다.
								//		차선책 갱신:	차선책을 갱신할 필요가 있다.
								second_fit_revision = header.getRevision();
								second_fit_index = n;
							}
						}
					}
				}
			}
		}



		//	post:	모든 탐색을 실시했으나 최선책을 찾지 못했다.
		//			차선책으로 갱신된 인덱스가 가리키는 모듈을 내보낸다.
		//		차선책을 찾았다면:
		if(second_fit_index != -1)
		{
			KERNAL_WARNING("W201011C45 : 비슷한 모듈만 검색됨\n주어진 모듈의 이름, 개발자, 개정번호까지 일치하는 모듈은 없었습니다.\n개발자와 이름이 같은 것으로 보아, 동일한 모듈로 보이나, 개정번호가 다른 모듈은 찾았습니다.\n모듈 매니져는 이 모듈을 반환할 것입니다.\n찾으려는 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d\n대신 찾은 모듈의 개정번호 : %d", identifer.getName().toCharPointer(), identifer.getDeveloper().toCharPointer(), identifer.getRevision(), _moduleset.getElement(second_fit_index).getHeader().getRevision())
			return _moduleset.getElement(second_fit_index);
		}
		else//	차선책을 찾지 못했다면:	만약 차선책조차 찾지 못했다면 처음에 second_fit_index로 주어졌던
			//							더미모듈이 내보내질 것이다.
		{		
			KERNAL_ERROR("E201011C44 : 일치하는 모듈 검색 실패\n주어진 모듈의 이름, 개발자와 일치하는 모듈이 없습니다. 모듈매니져는 더미모듈을 반환할 것입니다.\n찾으려는 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d", identifer.getName().toCharPointer(), identifer.getDeveloper().toCharPointer(), identifer.getRevision())
			return *null_pointer;
		}
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-16	이태훈	작성
	//	---------------------------------------------------------------------------------
	const NEModuleManager::DLLHeaderList NE_DLL &NEModuleManager::getDllHeaderSet() const
	{	
		return _dllheaderset;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-16	이태훈	작성
	//	---------------------------------------------------------------------------------
	const NEModuleSet NE_DLL &NEModuleManager::getModuleSet() const
	{	
		return _moduleset;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	모듈 파일로부터 모듈을 가져온다
	type_result NE_DLL NEModuleManager::execute()
	{		
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEModuleManager::getType() const
	{
		return NEType::NEMODULE_MANAGER;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEObject NE_DLL &NEModuleManager::clone() const
	{		
		return *(new NEModuleManager(*this));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEModuleManager::isValid() const
	{						
		type_result result = NEModule::isValid();
		if(NEResult::hasError(result)) return result | NEMODULE_IS_NOT_VALID;
		result = _dllheaderset.isValid();
		if(NEResult::hasError(result)) return result | DLL_HEADERSET_IS_NOT_VALID;
		result = _moduleset.isValid();
		if(NEResult::hasError(result)) return result | MODULESET_IS_NOT_VALID;
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEModuleManager::initialize()
	{
		//	pre:		
		//		초기화:
		_release(); // release()를 하면 안된다.

		

		//	main:
		//		모듈 Fetch:
		_linkDLL();
		_linkModule();
		
		return RESULT_SUCCESS;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEModuleManager::release()
	{
		//	멤버함수 초기화
		NEModule::release();

		return _release();
	}		



	//	---------------------------------------------------------------------------------
	//	설명	:	모듈의 헤더를 내보낸다. 헤더는 클래스에 이미 정의되어서 컴파일된다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExportable::ModuleHeader NE_DLL &NEModuleManager::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			//	아직 초기화가 안되었음
			_header.getName() = _T(_NAME );
			_header.getDeveloper() = _T(_DEVELOPER);;
			_header.setRevision(_REVISION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getVersion()  = _T(_VERSION);
			_header.getComment() = _T(_COMMENT);
			_header.setMaxErrorCodeCount(NEModuleManager::END_OF_ERROR_CODE - 1);
		}

		return _header;
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-03	이태훈	작성
	//	---------------------------------------------------------------------------------
	LPCTSTR NE_DLL NEModuleManager::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
 		case NEMODULE_IS_NOT_VALID:			return _T("잘못된 모듈");
 		case DLL_HEADERSET_IS_NOT_VALID:	return _T("잘못된 DLL 헤더셋");
 		case MODULESET_IS_NOT_VALID:		return _T("잘못된 모듈셋");
		case INVALID_DLL_PATH:				return _T("DLL 경로가 잘못되었다");
		case DLL_PATH_IS_NULLED:			return _T("DLL 경로가 NULL이다");
		case FAILED_TO_ACCESS_DLL:			return _T("DLL에 접근하지 못했다");
		case FAILED_TO_ACCESS_ENTRY_POINT:	return _T("DLL에는 접근했으나 EntryPoint에 접근하지 못했다");
		default:
			return _T("알수 없는 에러");
		}
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-08	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEModuleManager& NEModuleManager::_assign(const NEModuleManager& source)
	{
		if(this == &source) return *this;

		_dllheaderset = source._dllheaderset;
		_moduleset = source._moduleset;

		return *this;
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEModuleManager::_release()
	{
		_moduleset.create(1); // 자기자신을 담기 위해서 1로 설정한다.
		_dllheaderset.release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	연결된 DLL 파일로부터, 실행 엔트리포인트에 접근해서 모듈을 가져온다.
	//	동작조건:
	//	메모	:	가져온 모듈은 의존성을 고려해서 재 정렬한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEModuleManager::_linkModule()
	{
		//	배경:	
		//		의존성:	
		//				모듈에는 의존성이라는 게 존재하는데,
		//				이는 초기화시에, 다른 모듈이 먼저 초기화되어있야 함을 의미한다.
		//	
		//				예를 들어, 윈도우의 DC를 얻어서 조작하는 모듈이 있을 경우,
		//				이 모듈은 윈도우를 생성하는 모듈이 먼저 초기화가 되어야만 초기화가 가능할 것이다.
		//				또한 소멸의 경우도, 윈도우 모듈이 먼저 소멸되어서는 안된다.
		//
		//		의존성 재정렬:
		//				이러한 의존성을 사전에 파악, 초기화가 일어나기 전에 정렬해,
		//				배치하는 것을 말한다.
		//				초기화는 0번부터 일어나므로, 의존성이 적은 모듈일 수록 앞자리에 위치하게 된다.
		//				소멸은 뒷자리부터 일어나게 된다.


		//	main:
		//		임시 버퍼 생성:
		NEModuleList bucket; // 나중에 _moduleset로 값을 넘겨줄 리스트. DLL 엔트리 포인트로부터 여기에 모듈을 채우게 된다.			
		//		버퍼에 데이터 축적:
		for(type_index n=0; n < _dllheaderset.getLength() ;n++)
			bucket.push( _dllheaderset[n].getEntryPoint()() ); // entrypoint로부터 NEListTemplate가 넘어온다.
		//		중복 제거 필터링:
		_filterNestedName(bucket);
		//		의존성 재정렬:
		_resorting(bucket);
		//		모듈셋에 데이터 축적:	정렬된 임시버퍼를 복사한다
		_pushModuleSet(bucket);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	최종적으로 의존성을 고려해서 정렬된 모듈리스트로부터 모듈을 복사한다.
	//	동작조건:
	//	메모	:	push되는 순서대로 모듈의 scriptcode를 부과한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료	
	//	---------------------------------------------------------------------------------
	void NEModuleManager::_pushModuleSet(NEModuleList& buffer)
	{	
		//	pre:
		if(buffer.getLength() <= 0) return;



		//	main: buffer의 담긴 모듈을 최종적으로 _moduleset에 넣는다		
		//		모듈셋의 버퍼공간 생성:
		//			왜 1을 더하는가:
		//				모듈매니져인 자기 자신의 주소값을 넣기 위해서다.
		//				이때 주의할 점은, 또하나의 인스턴스가 만들어지지 않고 주소값이 다이렉트
		//				로 들어간다는 점이다.
		_moduleset.create(buffer.getLength());

		//		buffer로부터의 복사:
		for(NEModuleList::Iterator* iterator = buffer.getIterator(0); iterator != NE_NULL ;iterator = iterator->getNext())		
		{
			NEModule& target = iterator->getValue();
			_moduleset.push(target);	//	내부에서 Module.id, _onArgumentFetched, _onModuleFetched가 각각 호출 됨.

			KERNAL_INFORMATION(" 모듈 추가됨\n모듈명: %s", target.getHeader().getName().toCharPointer());
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	fetch한 모듈을 의존성을 고려해서 재정렬한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEModuleManager::_resorting(NEModuleList& source) // const가 아님에 주목하라
	{		
		//	main:
		//		의존성 모듈 추출:	dependencies를 갖고 있는 모듈을 분리시킨다.
		//			의존성 모듈 버퍼 생성:	
		NEModuleList extracted_dependency_module;

		NEModuleList::Iterator* iterator = source.getIterator(0);
		for(int n=0; n < source.getLength() ;n++)
		{
			//	에러 검사:
			if(iterator == NE_NULL)
			{
				KERNAL_ERROR("E201011C54 : 모듈 버퍼의 길이와 실제 데이터의 불일치\n버퍼에 담긴 모듈을 재정렬하는 중, 길이와 데이터의 불일치로 인해서, 작업을 끝까지 완수하지 못했습니다.")
				break;
			}

			//	의존성 파악:
			//		헤더 가져옴:	의존성정보가 헤더에 있다
			NEModule& target = iterator->getValue();
			const NEExportable::ModuleHeader& header = target.getHeader();
			//		조건1:	의존성이 있다면
			if(header.getModuleDependencies().getLength() > 0)
			{
				//		추출:	source로부터 분리해서 extracted로 추출한다
				//			의존성 버퍼에 추가:
				extracted_dependency_module.push(target); // 내부에서 clone 호출
				//			주어진 목록에서 삭제:
				source.remove(n); // iterator = iterator->getNext(); 를 하지 않는다.
			}
			else
				iterator = iterator->getNext();
		} 


		//		의존성 모듈 재정렬:	분리된 모듈을 의존성을 고려해서 재배치한다.
		while(extracted_dependency_module.getLength() > 0)
		{	//	배경:
			//		무한 루프 탐지를 위한 길이 변수:	
			//			무한 루프를 도는 건지 감지하기 위한 변수. 
			//			만약, 무한 루프를 돈다면, 의존성 모듈의 버퍼 길이가 변화 없을 것이다.
			//		
			//		왜 이렇게 검사변수를 두는가:
			//			한바뀌 for 문을 돌았다고 해서, 모든 추출한 모듈이 push되는게 아니끼 때문이다.
			//			때로는 extracted_module 중에서 앞쪽 모듈이 뒤쪽 모듈에 의존성이 있을수도 있다. 
			//			그렇기 때문에 변화가 없을때까지 계속해서 extracted_module을 검사한다.

			type_index infinite_loop_checker = extracted_dependency_module.getLength();


			//	재정렬:
			for(type_index n=0; n < extracted_dependency_module.getLength() ;n++)
			{
				//	인덱스 찾기:	의존성을 보장하는 최소 인덱스를 가져온다
				type_index index = _searchModuleIndexWithDependencies(extracted_dependency_module[n], source); // 만약의 index가 getLengthLastIndex + 1일 경우에는 insert 내부에서 push가 실행된다.

				//	조건1:	인덱스를 찾았다면
				if(index > NE_INDEX_ERROR)
				{
					//	원래버퍼에 삽입:
					source.insert(index, extracted_dependency_module[n]);
					//	의존성 모듈 버퍼에서 삭제:
					extracted_dependency_module.remove(n);						
					//	길이변수(= infinite_loop_check )와 실제길이가 어긋나게 되었다.						
				}
			}

			//	조건2:	길이변수가 변화가 없다면 (= 모든 모듈을 훓어봤으나 더이상 의존성을 정렬할수 없다 )
			if(extracted_dependency_module.getLength() == infinite_loop_checker)
			{	
				//	에러:	분명, 의존성모듈이 존재하나 알수없는 이유로 이 이상 의존성을 정렬할 수가 없다									
				KERNAL_ERROR("E201011C43 : 일부 의존적 모듈의 읽기 실패\n일부 모듈을 의존성을 고려하여 배치하지 못했습니다.\n모듈매니져는 배치하지 못한 모듈들을 제외할 것입니다.\n제외된 의존적인 모듈의 갯수 : %d", extracted_dependency_module.getLength())
					break;
			}							
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 모듈의 의존성을 고려해서 searching_target의 최소한 어느 인덱스
	//				이후로 자리잡아야 하는지 리턴한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_index NEModuleManager::_searchModuleIndexWithDependencies(NEModule& module, NEModuleList& searching_target)
	{	//	배경:
		//		의존성 정보:
		//			NETString header::module_dependencies[]의 형태로 담겨져 있다.
		//			이 함수에서는 의존성을 만족시킬때마다 해당 정보(= NETString )을 하나씩 지울것이다.
		//			그래서 모든 의존성 정보가 사라지는 순간을 최적의 인덱스로 판단한다.



		//	main:
		//		헤더 복사:	헤더에 의존성 정보들이 담겨있다
		NETStringSet dependency_checklist = module.getHeader().getModuleDependencies(); // 모듈의 헤더로부터 복사된다. 종속성을 만족시키는 인덱스를 찾게될때마다 크기가 하나씩 줄어들어, 이 체크리스트의 크기가 0이 되면 최종적으로 적합한 인덱스가 된다.

		//		최적의 인덱스 검색:
		for(type_index index=0; index < searching_target.getLength() ;index++)
		{	//		모듈 이름 추출:	의존성이 있다면, dependency_checklist 어딘가에 있을 것이다
			const NETString& target_name = searching_target[index].getHeader().getName();

			//		의존성 여부 판단:
			for(type_index dependency_index=0; dependency_index < dependency_checklist.getLength() ;dependency_index++)
			{	//	조건1:	의존성이 있다면
				if(dependency_checklist[dependency_index] == target_name)
				{	//	일치하는 의존성 삭제:	복사한 의존성정보(dependency_checklist)에서 일치하는 의존성을 삭제한다
					dependency_checklist.remove(dependency_index);
					dependency_index--;
				}
			}

			//	조건2:	현재 인덱스(count)에서 모든 의존성이 사라졌는가
			if(dependency_checklist.getLength() <= 0) // 모든 종속성을 만족하는 최소 인덱스를 찾았다.
			{
				//	검색성공:
				return index + 1; // index + 1에다 넣어야한다. index에다 넣으면, index자리에 있던게 index + 1로 밀려나게 되니까.
			}
		}



		//	post:
		//		검색실패:	최적의 인덱스를 찾지 못했다
#ifdef DEVELOPER
		const NEExportable::Identifier& identifier = module.getHeader();
		KERNAL_ERROR("E201011C42 : 모듈의 의존성을 고려한 위치 판단 실패\n주어진 모듈의 의존성을 고려하여 최적의 배치(최소의 인덱스)를 검색했으나, 실패했습니다.\n모듈의 식별자 :\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d", identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision())
#endif
			return NE_INDEX_ERROR;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	추가하려는 모듈이 이미 존재하는 모듈이름을 갖고 있다면, 보다 최신버전
	//				만 넣으려 한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEModuleManager::_filterNestedName(NEModuleList& source)
	{
		//	main:
		for(type_index n=0; n < source.getLength() ;n++)
		{		
			//	대상1 추출:
			const NEExportable::ModuleHeader& source_header = source[n].getHeader();

			//	대상1과 비교:	대상1과 같은 모듈이 있는지 확인한다
			for(type_index target_index = n+1; target_index < source.getLength() ; target_index++)
			{
				//	대상2 추출:
				const NEExportable::ModuleHeader& target_header = source[target_index].getHeader();

				//	조건1:	완전히 같은 모듈을 발견했다면
				if(source_header == target_header)
				{	
					//	추가 하지 않는다:
					source.remove(target_index); 
#ifdef DEVELOPER
					const NEExportable::Identifier& identifier = target_header;
					KERNAL_WARNING("W201011C41 : 동일한 모듈 복수 존재\n같은 식별자를 지닌 모듈이 2개 이상 존재합니다.\n모듈매니져는 나중에 식별한 모듈은 읽지 않을 것입니다.\n동일한 모듈의 식별자:\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d", identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision())
#endif
						break;
				}
			}
		}

	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정된 폴더에 존재하는 DLL 파일을 검색한다.
	//	동작조건:
	//	메모	:	NEFileSystem의 검색기능을 사용한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEModuleManager::_linkDLL()
	{			
		//	pre:
		_pushDLLPathToDLLHeaderSet();



		//	main:
		//		검색 준비:	
		/*
			변경점이 존재한다면 전에 load 실패했던 DLL도 다시 로드 가능할 지도 모른다.
		*/
		int index = 0;
		//		루핑:	
		while(true)
		{
			/*
				_linkDLLsUsingInputedPath()는 변경점이 존재할시에만 true를 반환한다
			*/
			bool has_changed = _linkDLLsUsingInputedPath();
			if(! has_changed)
				break;
		}



		//	post:
		_reportErrorsIfThereAreModulesNotFeched();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	검색한 DLL 파일을 프로세스에 올리고, 엔트리포인트의 주소를 가져온다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEModuleManager::_pushDLLHeader(NEModuleManager::DLLHeader& header)
	{	//	배경:
		//		왜 push를 하고 참조자를 가져오는가:
		//			push하는 과정에서 소멸자와 복사생성자가 호출되기 때문이다.
		//			Header의 소멸자는 FreeLibrary를 호출해서 연결한 DLL을 소멸시킨다.
		//			이런 오버헤드를 줄이기 위해서, 미리 값을 집어넣고 외부에서 조작한다


		//	pre:
		//		파라메터 검사:
		if(! &header) return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		if( ! &(header.getPath())) return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | DLL_PATH_IS_NULLED;
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
		header.getInstance() = LoadLibrary(header.getPath().toCharPointer());
		/*
			다시 오류 메세지를 활성화 한다.
		*/
		SetErrorMode(NE_DEFAULT);

		//		조건1:	DLL을 못 읽었다면		
		if( ! header.getInstance())
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
		header.getEntryPoint() = reinterpret_cast<EntryPoint>(GetProcAddress(header.getInstance(), _DLL_ENTRYPOINT_STRING));

		//			조건1-1:	진입점을 가져오지 못했다면
		if( ! header.getEntryPoint())
		{	//			동작 실패:	로드는 성공했지만 엔트리포인트 등록에는 실패
			KERNAL_ERROR("E201011C39 : 실행 엔트리포인트 접근 실패\nDLL 확인 및 동적 DLL 연결에는 성공했으나 실행 엔트리 포인트에 연결하지 못했습니다.\n해당 모듈 개발자가 잘못된 엔트리포인트를 사용하고 있을 가능성이 있습니다.\n모듈매니져가 이 DLL을 제외할 것입니다.\n표준 엔트리포인트 : %s\n파일명 : %s", _T(_DLL_ENTRYPOINT_STRING), header.getPath().toCharPointer())

			return RESULT_TYPE_ERROR | RESULT_ACCESS_DENIED;
		}

		return RESULT_SUCCESS;
	}
	
	void NEModuleManager::_pushDLLPathToDLLHeaderSet()
	{
		//	pre:
		//		타겟팅:
		NEINIManager& ini = Kernal::getInstance().getINIManager();
		//		버퍼 준비:
		NETString path = Kernal::getInstance().getSettings().getModuleDirectory() + _T("*.dll");



		//	main:
		//		검색 준비:
		NEFileSystem filesystem(path.toCharPointer(), true); //	테스트니까 일단 풀 경로를 지정한다. 릴리즈에서는 "Modules/*.dll" 만 하면 됨
		//		루핑:
		
		while(true)
		{
			filesystem.findFile();
			const NEFileSystem::TaskUnit& task = filesystem.getLastElement();
			if( ! &task) break;

			//		읽기 가능 flag:
			//			버퍼 생성:
			NETString value;
			//			INI로부터 값 가져옴:
			type_result result = ini.readModuleIniString(getHeader(), task.getFilePath(), value);
			//		로드 여부 조건 검사:
			//			만약 에러가 발생했다면:
			if(NEResult::hasError(result))		
				ini.writeModuleIniString(getHeader(), task.getFilePath(), NETString(true));
			else	//	에러가 없다면:
				//			가져온 값이 false(로드 안함) 이라면:
				if(value.toBoolean() == false)
				{
					KERNAL_INFORMATION("I201011C53 : DLL 동적 연결 취소\nINI를 통해서 발견한 DLL을 로드 하지 않기로 했습니다.\n로드하고 싶다면 INI의 키값을 false에서 true로 바꾸십시오.\n취소된 DLL 파일명 : %s", task.getFilePath())

					continue;
				}

			NEModuleManager::DLLHeader header;
			header.getPath() = task.getFilePath();
			_dllheaderset.push(header);
		}
	}

	/*
		변경점이 존재한다면 true를 반환한다
	*/
	bool NEModuleManager::_linkDLLsUsingInputedPath()
	{
		bool has_changed = false;

		for(int n=0; n < _dllheaderset.getLength() ;n++)
		{
			NEModuleManager::DLLHeader& header = _dllheaderset[n];

			if( ! header.isLoaded())
				if(_pushDLLHeader(header) == RESULT_SUCCESS)
					//	로드에 성공했다면:	변경점이 존재한것이 된다
					has_changed = true;

		}

		return has_changed;
	}

	void NEModuleManager::_reportErrorsIfThereAreModulesNotFeched()
	{
		for(int n=0; n < _dllheaderset.getLength() ;)
		{
			NEModuleManager::DLLHeader& header = _dllheaderset[n];

			if( ! header.isLoaded())
			{
#ifdef _DEBUG
				KERNAL_ERROR("E201011C40 : DLL 동적 연결 실패\nDLL은 찾았으나 동적 연결에 실패했습니다.\n올바른 DLL 파일이 아니거나, 릴리즈 / 디버그 모드가 다를 경우 이 메세지가 발생할 수 있습니다.\n다시 확인 해보십시오.\nKernal 빌드 모드 : Debug\n파일명 : %s", header.getPath().toCharPointer())
#else
				KERNAL_ERROR("E201011C40 : DLL 동적 연결 실패\nDLL은 찾았으나 동적 연결에 실패했습니다.\n올바른 DLL 파일이 아니거나, 릴리즈 / 디버그 모드가 다를 경우 이 메세지가 발생할 수 있습니다.\n다시 확인 해보십시오.\nKernal 빌드 모드 : Release\n파일명 : %s", header.getPath().toCharPointer())
#endif		
				_dllheaderset.remove(n);
			}
			else
				n++;
		}
	}
}