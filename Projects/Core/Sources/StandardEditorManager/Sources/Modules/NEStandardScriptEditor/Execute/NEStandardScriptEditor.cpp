#include "NEStandardScriptEditor.hpp"
#include "../define/define.hpp"

namespace NE
{
	/*
		C4355경고 무시:
			경고가 나오는 이유:
				일반적으로, this 포인터를 넘기면, 넘긴쪽에서 생성자가 초기화되지
				않았는데도, 넘겨받은 쪽에서 사용할 여지가 있기 때문이다.
			무시하는 이유:
				아래와 같은 경우, 절대로 "생성자에서 호출 하지 않으"므로 사용한다.
	*/
#pragma warning(push)	
#pragma warning(disable:4355)
	NE_DLL NEStandardScriptEditor::NEStandardScriptEditor()
		: NEScriptEditor(), _scriptset(*this)	//	C4355 Warning.
	{
		_release();
	}
	NE_DLL NEStandardScriptEditor::NEStandardScriptEditor(const NEStandardScriptEditor& source)
		: NEScriptEditor(source), _scriptset(*this)	//	C4355 Warning.
	{
		_assign(source);
	}
#pragma warning(pop)

	NE_DLL NEStandardScriptEditor::~NEStandardScriptEditor()
	{
		_release();
	}

	const NEStandardScriptEditor NE_DLL &NEStandardScriptEditor::operator=(const NEStandardScriptEditor& source)
	{
		NEScriptEditor::operator=(source);
		
		return _assign(source);
	}
	bool NE_DLL NEStandardScriptEditor::operator==(const NEStandardScriptEditor& source) const
	{
		if(this == &source) return true;
		if(NEScriptEditor::operator==(source) == false) return false;
		if(_scriptset != source._scriptset) return false;
		if(_header != source._header) return false;
		if(_banks != source._banks) return false;
		if(isSynchronizationDisabled() != source.isSynchronizationDisabled()) return false;
		
		return true;
	}
	bool NE_DLL NEStandardScriptEditor::operator!=(const NEStandardScriptEditor& source) const
	{
		return !(operator==(source));
	}

	type_result NE_DLL NEStandardScriptEditor::execute()
	{
		Kernal& kernal = Kernal::getInstance();
		if( ! &kernal)
		{
			ALERT_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		NEScriptManager& scripter = kernal.getScriptManager();
		if( ! &scripter)
		{
			ALERT_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}

		return synchronizeTo(scripter);
	}	

	NERootNodeCodeSet NE_DLL &NEStandardScriptEditor::getScriptNodes()
	{
		return _scriptset;
	}

	const NERootNodeCodeSet NE_DLL &NEStandardScriptEditor::getScriptNodes() const
	{
		return _scriptset;
	}
	
	NEScriptManager::ScriptHeader NE_DLL &NEStandardScriptEditor::getScriptHeader()
	{
		return _header;
	}

	const NEScriptManager::ScriptHeader NE_DLL &NEStandardScriptEditor::getScriptHeader() const
	{
		return _header;
	}

	const NEScriptEditor::Banks& NEStandardScriptEditor::getBanks() const
	{
		return _banks;
	}

	NEScriptEditor::Banks& NEStandardScriptEditor::getBanks()
	{
		return _banks;
	}

	NEBinaryFileSaver NE_DLL &NEStandardScriptEditor::serialize(NEBinaryFileSaver& saver) const
	{
		NEModule::serialize(saver);
		
		return saver << _scriptset << _header << _banks;
	}
	NEBinaryFileLoader NE_DLL &NEStandardScriptEditor::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		release();
		NEModule::serialize(loader);
	
		_setSynchronizationDisabled(true);

		loader >> _scriptset >> _header >> _banks;

		_setSynchronizationDisabled(false);

		return loader;
	}
	type_result NE_DLL NEStandardScriptEditor::initialize()
	{
		SuperClass::release();
		SuperClass::initialize();
		
		//	main:
		//		루트 노드코드셋 초기화:
		getScriptNodes().create(5000);
		//		버퍼 초기화:
		_getNodeSet().create(5000);
		_getModuleSet().create(50000);
		_getKeySet().create(100000);
		//		헤더 초기화:
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		header.release();	//	0으로 초기화되므로, 0에 해당하는 code가 자동으로 부여된다.
		//			헤더 세팅:
		header.setMaxNameCodeIndex(0);
		header.setMaxGroupCodeIndex(0);
		header.setMaxScriptCodeIndex(-1);	//	스크립트는 하단에 push를 통해서 1이 증가되므로, 여기서는 -1로 만든다.
		header.setMaxPriorityCodeIndex(0);
		if(NEResult::hasError(_initializeWithHeader()))
		{
			ALERT_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}

		//		메인 노드 자동 생성:
		//			메인 노드 초기화:	_synchronize() 함수가 제대로 동작하기 위해서는 Editor에 Manager로써 등록이 되어야 한다(왜냐하면 Selector를 사용하고 있으므로)
		//								다시말하면, 초기화 과정중에는 _synchronize()함수가 제대로 동작하기 힘들다는 것.
		//								그래서 여기서 강제로 id 값을 0으로 만들어줘야 한다.
		NENode main_node;
		_setScriptCode(main_node, 0);
		return getScriptNodes().push(main_node);
	}
	const NEExportable::ModuleHeader NE_DLL &NEStandardScriptEditor::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			//	아직 초기화가 안되었음
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getVersion()  = _T(_VERSION);			
			_header.getComment() = _T(_COMMENT);
			_header.setMaxErrorCodeCount(NEStandardScriptEditor::END_OF_ERROR_CODE - 1);
		}

		return _header;
	}
	LPCTSTR NE_DLL NEStandardScriptEditor::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case NEMODULE_IS_NOT_VALID:
			return _T("잘못된 모듈");
		case SCRIPT_NAMEBANK_IS_NOT_VALID:
			return _T("잘못된 스크립트코드 이름 데이터");
		case NAME_NAMEBANK_IS_NOT_VALID:
			return _T("잘못된 네임코드 이름 데이터");
		case GROUP_NAMEBANK_IS_NOT_VALID:
			return _T("잘못된 그룹코드 이름 데이터");
		case PRIORITY_NAMEBANK_IS_NOT_VALID:
			return _T("잘못된 우선권코드 이름 데이터");
		case SCRIPT_NAMEBANK_DOES_NOT_CORRESPOND_TO_MAX_SCRIPT_COUNT:
			return _T("스크립트코드 이름 데이터의 갯수와, 실제 존재하는 스크립트의 갯수와의 불일치");
		case NAME_NAMEBANK_DOES_NOT_CORRESPOND_TO_MAX_NAME_COUNT:
			return _T("네임코드 이름 데이터의 갯수와, 실제 존재하는 네임코드의 갯수와의 불일치");
		case GROUP_NAMEBANK_DOES_NOT_CORRESPOND_TO_MAX_GROUP_COUNT:
			return _T("그룹코드 이름 데이터의 갯수와, 실제 존재하는 그룹코드의 갯수와의 불일치");
		case PRIORITY_NAMEBANK_DOES_NOT_CORRESPOND_TO_MAX_PRIORITY_COUNT:
			return _T("우선권 코드 이름 데이터의 갯수와, 실제 존재하는 우선권코드의 갯수와의 불일치");
		default:
			return _T("알 수 없는 에러");
		}
	}
	type_result NE_DLL NEStandardScriptEditor::isValid() const
	{
		//	상위 클래스 검사:
		type_result result = NEScriptEditor::isValid();
		if(NEResult::hasError(result)) return result | NEMODULE_IS_NOT_VALID;
		result = _scriptset.isValid();
		if(NEResult::hasError(result)) return result;
		result = _banks.isValid();
		if(NEResult::hasError(result)) return result;
		
		return RESULT_SUCCESS;
	}
	NEObject NE_DLL &NEStandardScriptEditor::clone() const
	{
		return *(new NEStandardScriptEditor(*this));
	}
	NE_DLL void NEStandardScriptEditor::release()
	{
		//	왜 release 순서가 뒤바뀌어야 하는가:
		//		NENodeCodeSet이 release가 될때 내부에서 while(length) pop();을 수행하므로
		//		실제 인스턴스가 있는지 참조하려 들기 때문이다.
		//		실제 인스턴스는 SuperClass에 들어있으므로 이를 먼저 초기화 해버리면
		//		널포인트 참조가 되버려서 에러가 발생한다.
		_release();

		SuperClass::release();
	}


	
	type_result NE_DLL NEStandardScriptEditor::synchronizeFrom(const NEScriptManager& source)
	{
		//	배경:
		//		왜 동기화 과정이 필요한가?:
		//			ScriptManager는 기본적으로 노드셋으로 스크립트를 관리한다.
		//			이는 배열의 특성을 그대로 가지고 있게 된다.
		//			일단 데이터가 들어가면 탐색에 유용하지만, 새로운 데이터 입력 및
		//			기존 데이터 삭제에는 부하가 많이 걸린다.
		//			(수많은 노드셋키를 가지고 있는 노드를 "insert, remove"로 인해서
		//			swap하는 과정을 떠올려보라)
		//			때문에 효율을 위해서 리스트의 형태로 스크립트를 입력 받는다.
		//			스크립트가 Kernal::ScriptManager에 존재해야하는 경우가 생기는데,
		//			(= 예를 들면, 테스트의 실행이나 세이브)
		//			이 순간에는 동기화를 통해서 일관성있는 데이터를 제공해야 한다.

		//	pre:
		//		타겟팅:
		if( ! &source)
		{
			ALERT_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		const NEScriptManager::ScriptHeader& source_header = source.getScriptHeader();
		const NERootNodeCodeSet& kernal_scriptset = source.getScriptNodes();



		//	main:		
		release();
		/*
			뱅크는 ScriptManager로부터 완벽하게 synchronize가 불가능 하다.
			때문에 여기서는 데이터를 모두 초기화시켜버린다. 뱅크는 차후에 데이터를 넣어야 할것이다.
		*/
		//		버퍼 초기화:
		_getNodeSet().create(5000);
		_getModuleSet().create(50000);
		_getKeySet().create(100000);
		_scriptset.create(5000);
		//		헤더 할당:
		_header = source_header;
		//		헤더에 맞게 초기화:
		_initializeWithHeader();		
		//		스크립트셋 동기화:
		_setSynchronizationDisabled(true);
		//			동기화 스위치 끄기:
		/*
						Scripter[0]에서 Scripter[1]의 연관성을 가지고 있다면 [0]을 추가할때
						동기화가 발생하므로 [0]의 연관성이 사라지도록 동기화가 되어버린다.
						또한 효율도 안좋다.
						저번 실행에서 이미 동기화가 되어있는 상태에서 save를 했다고 가정하고
						load시에는 동기화를 수행하지 않는다.
						자세한 사항은 관련문서 참조하라.
		*/				
		//			데이터:
		//				카운트 변수 정의:
		type_index index = 0;
		//				탐색 & 적용:
		_scriptset.push(kernal_scriptset);
		

		//	post:		
		_setSynchronizationDisabled(false);
		return RESULT_SUCCESS;
	}
	
	
	type_result NE_DLL NEStandardScriptEditor::synchronizeTo(NEScriptManager& scripter) const
	{
		//	배경:
		//		왜 동기화 과정이 필요한가?:
		//			ScriptManager는 기본적으로 노드셋으로 스크립트를 관리한다.
		//			이는 배열의 특성을 그대로 가지고 있게 된다.
		//			일단 데이터가 들어가면 탐색에 유용하지만, 새로운 데이터 입력 및
		//			기존 데이터 삭제에는 부하가 많이 걸린다.
		//			(수많은 노드셋키를 가지고 있는 노드를 "insert, remove"로 인해서
		//			swap하는 과정을 떠올려보라)
		//			때문에 효율을 위해서 리스트의 형태로 스크립트를 입력 받는다.
		//			스크립트가 Kernal::ScriptManager에 존재해야하는 경우가 생기는데,
		//			(= 예를 들면, 테스트의 실행이나 세이브)
		//			이 순간에는 동기화를 통해서 일관성있는 데이터를 제공해야 한다.
		
		
		//	pre:
		//		타겟팅:
		if( ! &scripter)
		{
			ALERT_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		NEScriptManager::ScriptHeader& script_manager_header = _getScriptHeaderFrom(scripter);
		NERootNodeCodeSet& kernal_scriptset = _getScriptNodesFrom(scripter);



		//	main:
		/*
			동기화시에는 반드시 스크립트헤더부터 할당해야만 한다.
			왜냐하면 노드를 enroll할때 스크립트 헤더에 저장된 뱅크로부터 max_code를 가져와서
			valid를 검사하기 때문이다.
		*/
		//		ScriptHeader 할당:
		//			스크립트 헤더 작성:
		NEScriptManager::ScriptHeader& header = const_cast<NEScriptManager::ScriptHeader&>(getScriptHeader());
		//				정확한 노드/모듈/키의 크기를 할당:
		//					헤더의 일부 정보는 시스템이 자동으로 채워줘야 한다.
		//					인스턴스 셋:
		header.setMaxNodeLength(getNodeSet().getLength());
		header.setMaxModuleLength(getModuleSet().getLength());
		header.setMaxKeyLength(getKeySet().getLength());
		//				오류 검사:
		if(NEResult::hasError(header.isValid()))
		{
			ALERT_ERROR(" : 스크립트헤더에 문제가 있어서 동기화를 중지합니다.");
			return RESULT_TYPE_ERROR;
		}
		//				스크립트 할당:
		script_manager_header = header;
		//				스크립트로 매니져를 초기화:
		//					ScriptManager::intiailize에서는 내부에서 NENodeSet, NEModuleSet, NEKeySet의 버퍼를 초기화 한다.
		//					숏컷을 헤더에 명시된 만큼 확보한다.
		//					NEScriptSet을 초기화 한다.
		scripter.initialize();
		//		스크립트셋 동기화:
		//			데이터:
		kernal_scriptset.create(getScriptNodes().getLength());
		kernal_scriptset.push(getScriptNodes());	//	내부적으로 NENode::operator=(source)가 호출되고, enlist된다.
		
		
		//	post:				
		return RESULT_SUCCESS;
	}
	
		

	const NEStandardScriptEditor& NEStandardScriptEditor::_assign(const NEStandardScriptEditor& source)
	{
		if(this == &source) return *this;

		_scriptset = source._scriptset;
		_header = source._header;
		_banks = source._banks;

		return *this;
	}
	void NEStandardScriptEditor::_release()
	{
		_setSynchronizationDisabled(true);

		_scriptset.release();
		_header.release();
		_banks.release();

		_setSynchronizationDisabled(false);
	}

	void NEStandardScriptEditor::_createBank(NETStringList& bank, type_index max_code_to_create)
	{
		/*
			max_code_to_resize 라는 건, Length가 아니라 index의 개념이다.
			예를들어, max_code_to_resize가 3일 경우 bank.getLength() 가 3이 될때까지가 아니라,
			bank.getLengthLastIndex()가 3이 될때까지 인스턴스를 생성하라는 의미가 된다.
		*/
		//	pre:
		//	main:
		//		길이 구하기:
		type_count	length = max_code_to_create + 1;
		//		뱅크 초기화:		
		bank.release();
		//		뱅크에 데이터 삽입:
		/*
					뱅크의 길이로 max_code를 인지하기 때문에, 아무런 이름이 주어져 있지 않은 
					코드라고 해도 생성은 해야 한다.
		*/		
		for(int n=0; n < length ;n++)
			bank.push(NETString(""));
	}

	type_result NE_DLL NEStandardScriptEditor::_onModuleFetched()
	{
		return RESULT_SUCCESS;
	}

	type_result NEStandardScriptEditor::insertNameCode(type_code new_namecode)
	{
		class Inserter : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				if(node_to_be_synchronized.getNameCode() >= to_be_manipulated)
					_setNameCode(owner, node_to_be_synchronized, node_to_be_synchronized.getNameCode()+1);

				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code_to_be = header.getMaxNameCodeIndex() + 1;	//	추가는 삭제와 달리 최대인덱스 + 1까지 가능하다. (이해가 안 될 경우, push를 떠올려보라)
		NEShortCutSet& shortcutset = _getNameShortCutSet();
		
		type_result result = 0;
		if(NEResult::hasError(result = _synchronize(Inserter(), new_namecode, max_code_to_be, NECodeType::NAME, true)))
			return result;

		//	post:
		shortcutset.resize(shortcutset.getSize() + 1);
		shortcutset.insert(new_namecode, NEShortCut());
		header.setMaxNameCodeIndex(max_code_to_be);
		return getBanks().getNameBank().insert(new_namecode, NETString("unamed"));		
	}

	type_result NEStandardScriptEditor::insertGroupCode(type_code new_groupcode)
	{
		class Inserter : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				NECodeSet codeset = node_to_be_synchronized.getGroupCode();
				for(int n=0; n < codeset.getLength() ;n++)
					if(codeset[n] >= to_be_manipulated)
						codeset[n]++;

				_setGroupCode(owner, node_to_be_synchronized, codeset);

				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code_to_be = header.getMaxGroupCodeIndex() + 1;	//	추가는 삭제와 달리 최대인덱스 + 1까지 가능하다. (이해가 안 될 경우, push를 떠올려보라)
		NEShortCutSet& shortcutset = _getGroupShortCutSet();

		type_result result = 0;
		if(NEResult::hasError(result = _synchronize(Inserter(), new_groupcode, max_code_to_be, NECodeType::GROUP, true)))
			return result;

		//	post:
		shortcutset.resize(shortcutset.getSize() + 1);
		shortcutset.insert(new_groupcode, NEShortCut());
		header.setMaxGroupCodeIndex(max_code_to_be);
		return getBanks().getGroupBank().insert(new_groupcode, NETString("unamed"));
	}

	type_result NEStandardScriptEditor::insertPriorityCode(type_code new_prioritycode)
	{
		class Inserter : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				if(node_to_be_synchronized.getPriority() >= to_be_manipulated)
					_setPriorityCode(owner, node_to_be_synchronized, node_to_be_synchronized.getPriority()+1);

				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code_to_be = header.getMaxPriorityCodeIndex() + 1;	//	추가는 삭제와 달리 최대인덱스 + 1까지 가능하다. (이해가 안 될 경우, push를 떠올려보라)
		NEShortCutSet& shortcutset = _getPriorityShortCutSet();

		type_result result = 0;
		if(NEResult::hasError(result = _synchronize(Inserter(), new_prioritycode, max_code_to_be, NECodeType::PRIORITY, true)))
			return result;


		//	post:
		shortcutset.resize(shortcutset.getSize() + 1);
		shortcutset.insert(new_prioritycode, NEShortCut());
		header.setMaxPriorityCodeIndex(max_code_to_be);
		return getBanks().getPriorityBank().insert(new_prioritycode, NETString("unamed"));
	}

	type_result NEStandardScriptEditor::_insertScriptCode(type_code new_scriptcode)
	{
		class Inserter : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				if(node_to_be_synchronized.getScriptCode() >= to_be_manipulated)
					_setScriptCode(owner, node_to_be_synchronized, node_to_be_synchronized.getScriptCode()+1);

				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code_to_be = header.getMaxScriptCodeIndex() + 1;	//	추가는 삭제와 달리 최대인덱스 + 1까지 가능하다. (이해가 안 될 경우, push를 떠올려보라)
		NEShortCutSet& shortcutset = _getScriptShortCutSet();

		type_result result = _synchronize(Inserter(), new_scriptcode, max_code_to_be, NECodeType::SCRIPT, true);
		if(NEResult::hasError(result))
			return result;


		//	post:
		shortcutset.resize(shortcutset.getSize() + 1);
		shortcutset.insert(new_scriptcode, NEShortCut());
		header.setMaxScriptCodeIndex(max_code_to_be);
		return getBanks().getScriptBank().insert(new_scriptcode, NETString("unamed"));
	}

	type_result NEStandardScriptEditor::_removeScriptCode(type_code scriptcode)
	{
		class Remover : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				if(node_to_be_synchronized.getScriptCode() == to_be_manipulated)
					_setScriptCode(owner, node_to_be_synchronized, -1);
				else if(node_to_be_synchronized.getScriptCode() > to_be_manipulated)
					_setScriptCode(owner, node_to_be_synchronized, node_to_be_synchronized.getScriptCode()-1);

				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code = header.getMaxScriptCodeIndex();
		NEShortCutSet& shortcutset = _getScriptShortCutSet();

		_synchronize(Remover(), scriptcode, max_code, NECodeType::SCRIPT, false);


		//	post:
		header.setMaxScriptCodeIndex(max_code-1);
		shortcutset.remove(scriptcode);
		shortcutset.resize(shortcutset.getLength());
		return getBanks().getScriptBank().remove(scriptcode);
	}

	type_result NEStandardScriptEditor::removeNameCode(type_code namecode)
	{
		class Remover : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				if(node_to_be_synchronized.getNameCode() == to_be_manipulated)
					node_to_be_synchronized.setNameCode(0);
				else if(node_to_be_synchronized.getNameCode() > to_be_manipulated)
					_setNameCode(owner, node_to_be_synchronized, node_to_be_synchronized.getNameCode()-1);

				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code = header.getMaxNameCodeIndex();
		NEShortCutSet& shortcutset = _getNameShortCutSet();
		
		_synchronize(Remover(), namecode, max_code, NECodeType::NAME, false);

		
		//	post:
		header.setMaxNameCodeIndex(max_code-1);
		shortcutset.remove(namecode);
		shortcutset.resize(shortcutset.getLength());
		return getBanks().getNameBank().remove(namecode);
	}

	type_result NEStandardScriptEditor::removeGroupCode(type_code groupcode)
	{
		class Remover : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				NECodeSet codeset = node_to_be_synchronized.getGroupCode();
				for(int n=0; n < codeset.getLength() ;n++)
					if(codeset[n] == to_be_manipulated)
					{
						codeset.remove(n);
						n--;	//	n을 지우면, 아직 검사하지 않은 n+1이 n에 위치하게 된다. n은 for문의 증가식 때문에 강제적으로 증가되므로, 미리 n을 하나 빼서 다음 루프때 n이 검사되도록 한다.						
					}
					else if(codeset[n] > to_be_manipulated)
						codeset[n]--;
				//	배열에 남는 공간이 없도록 Compact 하게 만든다:
				if(codeset.getLength() < codeset.getSize())
					codeset.resize(codeset.getLength());

				_setGroupCode(owner, node_to_be_synchronized, codeset);				
				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code = header.getMaxGroupCodeIndex();
		NEShortCutSet& shortcutset = _getGroupShortCutSet();

		_synchronize(Remover(), groupcode, max_code, NECodeType::GROUP, false);


		//	post:
		header.setMaxGroupCodeIndex(max_code-1);
		shortcutset.remove(groupcode);
		shortcutset.resize(shortcutset.getLength());
		return getBanks().getGroupBank().remove(groupcode);
	}

	type_result NEStandardScriptEditor::removePriorityCode(type_code prioritycode)
	{
		class Remover : public OnSynchronize
		{
			virtual type_result onSynchronize(NEStandardScriptEditor& owner, NENode& node_to_be_synchronized, type_code to_be_manipulated)
			{
				if(node_to_be_synchronized.getPriority() == to_be_manipulated)
					node_to_be_synchronized.setPriority(0);
				else if(node_to_be_synchronized.getPriority() > to_be_manipulated)
					_setPriorityCode(owner, node_to_be_synchronized, node_to_be_synchronized.getPriority()-1);

				return RESULT_SUCCESS;
			}
		};
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_code max_code = header.getMaxPriorityCodeIndex();
		NEShortCutSet& shortcutset = _getPriorityShortCutSet();

		_synchronize(Remover(), prioritycode, max_code, NECodeType::PRIORITY, false);


		//	post:
		header.setMaxPriorityCodeIndex(max_code-1);
		shortcutset.remove(prioritycode);
		shortcutset.resize(shortcutset.getLength());
		return getBanks().getPriorityBank().remove(prioritycode);
	}

	type_result NEStandardScriptEditor::_enlist(NENode& target, type_index index/*= NE_INDEX_ERROR*/)
	{
		//	pre:
		if(isSynchronizationDisabled()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if( ! &target)
		{
			ALERT_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		if(index <= NE_INDEX_ERROR) 
		{
			index = _searchRealNodeIndex(target);
			
			if(index <= NE_INDEX_ERROR)
			{
				ALERT_ERROR(" : ");
				return RESULT_TYPE_ERROR;
			}
		}



		//	main:
		/*
		//		n추정 알고리즘:	생성될 target이 몇번째 code가 되어야 하는지 알아낸다
		//						ALL은 Script 모드와 동일한 탐색 알고리즘을 지니기 때문에, 
		//						매번 n++ 하여 주어진 target이 n번째 스크립트 인지를 예상할 수 있다.
		NENodeSelector sel(getType());		
		sel.setNodeType(NECodeType::ALL);	
		int n = 0;	//	n번째 스크립트
		while(NENode* itr = &sel.getNode())
		{
			if(itr == &target)
				break;
			//		알고리즘 검증:	이 n추정 알고리즘이 제대로 작동하는지 확인한다.
			if(itr->getScriptCode() != n)
			{
				ALERT_ERROR("n추정 알고리즘이 제대로 동작하지 않는다:\n\t실제 스크립트코드: %d\n\t추정 스크립트 코드: %d", target.getScriptCode(), n)
				goto END;
			}

			n++;
		}	

			테스트 결과:		n 추정 알고리즘은 사용할 수 없다.
			알고리즘 파기 이유:	셀렉터가 노드를 가져오기 위해서는 노드가 이미 enlist 되어 있어야 하기 때문에,
								"어디에 enlist 하여야 하는가"에 사용할 수가 없다.
			대처:				따라서, 직접 모든 노드/모듈/키를 재귀함수로 돌면서 위치를 찾는 방법을 택했다.
		*/
		type_code to_be_found = 0;
		_searchInDeepForScriptCode(getScriptNodes(), target, to_be_found);	//	앞서 언급한 재귀함수다.
		if(to_be_found == NE_INDEX_ERROR)
		{
			ALERT_ERROR(" : 주어진 Target에 할당될 스크립트 코드를 찾지 못했습니다.");
			return RESULT_TYPE_ERROR;
		}
		//		스크립트 코드 추가:
		_insertScriptCode(to_be_found);


		//	post:
		//		지금 집어넣은 노드의 동기화:	
		//			지금 넣은 노드는 아직 동기화가 수행되지 않았다.
		//
		//			왜 Target노드는 마지막에 동기화를 수행하는가:
		//				동기화를 하기 위해서는 일단 등록이 되어야 Selector를 사용할 수 있다.
		//				그런데 등록을 할려면 일단 ShortCutSet을 확장시키고, 다른 노드를 먼저 
		//				동기화해야만 한다. 
		//				즉 "전화선을 만들어야 그 사람과 대화를 하는데, 대화를 할려면 전화선을 만들어야 하는"
		//				딜레마다.
		//
		//			순서에 주의하기 바람:
		//					-	비어있는 코드를 부여
		//					-	그 코드로 등록(enlist)
		//					-	등록후 셀렉터 사용하여 내부의 데이터 동기화
		//				이러한 순서를 거치는 이유는, 삽입한 노드의 내부 데이터 동기화 작업을 이미 작성/검증된 
		//				셀렉터 코드로 동작시키기 위함이다.
		//
		//			삽입한 노드의 새로운 스크립트코드를 부여:	부여한 스크립트코드에는 다른 노드가 없는 비어있는 곳이다.
		_setScriptCode(target, to_be_found);
		//			Enlist:	위에서 코드를 부여했으므로 이제 enlist가 가능해졌다.
		type_result result = _getScriptShortCutSet()._enlist(target, index);
		result |= _getNameShortCutSet()._enlist(target, index);
		result |= _getGroupShortCutSet()._enlist(target, index);
		result |= _getPriorityShortCutSet()._enlist(target, index);
		//			노드 안에 데이터들을 동기화:	enlist과정이 끝나면 Selector를 사용 할 수 있다.
		NENodeSelector sel(getType());
		sel.setNodeType(NECodeType::ALL);
		NENode* itr = 0;
		while(itr = &sel.getNode())
		{
			NEKeyCodeSet& kset = itr->getKeySet();
			for(int n=0; n < kset.getLength() ;n++)
				_synchronizeCodesInKey(kset[n], NECodeType::SCRIPT, to_be_found, true);
		}

		return RESULT_SUCCESS;
	}

	type_result NEStandardScriptEditor::_unlist(NENode& target, type_index index/*= NE_INDEX_ERROR*/)
	{
		//	pre:
		if(isSynchronizationDisabled()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if( ! &target)
		{
			ALERT_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		if(index <= NE_INDEX_ERROR) 
		{
			index = _searchRealNodeIndex(target);

			if(index <= NE_INDEX_ERROR)
			{
				ALERT_ERROR(" : ");
				return RESULT_TYPE_ERROR;
			}
		}


		//	main:
		//		스크립트 동기화:
		_removeScriptCode(target.getScriptCode());


		//	post:
		//		기타 숏컷 처리:
		type_result result = _getNameShortCutSet()._unlist(target, index);
		result |= _getGroupShortCutSet()._unlist(target, index);
		return result |= _getPriorityShortCutSet()._unlist(target, index);
	}

	type_result NEStandardScriptEditor::_initializeWithHeader()
	{
		//		숏컷 정보 초기화:
		NEScriptManager::ScriptHeader& header = getScriptHeader();
		type_result result = RESULT_SUCCESS;
		result |= _createShortCutSetAndFillWithShortCuts(_getScriptShortCutSet(), header.getMaxScriptCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getNameShortCutSet(), header.getMaxNameCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getGroupShortCutSet(), header.getMaxGroupCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getPriorityShortCutSet(), header.getMaxPriorityCodeIndex() + 1);
		//		뱅크 초기화:
		NEScriptEditor::Banks& banks = getBanks();		
		_createBank(banks.getScriptBank(), header.getMaxScriptCodeIndex());
		_createBank(banks.getNameBank(), header.getMaxNameCodeIndex());
		_createBank(banks.getGroupBank(), header.getMaxGroupCodeIndex());
		_createBank(banks.getPriorityBank(), header.getMaxPriorityCodeIndex());

		return result;
	}

	type_result NEStandardScriptEditor::_synchronizeCodesInKey(NEKey& key, NECodeType::CodeType codetype, type_code new_code, bool insertion_mode)
	{
		if(isSynchronizationDisabled()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if( ! &key)
		{
			ALERT_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		if(	codetype == NECodeType::UNDEFINED		||
			codetype <= NECodeType::CODETYPE_START	||
			codetype >= NECodeType::CODETYPE_END	)
		{
			ALERT_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}



		//	main:
		if(key.isSubClassOf(NEType::NENODE_SELECTOR))
		{
			NENodeSelector& selector = static_cast<NENodeSelector&>(key);
			if(selector.getNodeType() == codetype)
			{
				//	복사:
				NEIntSet codeset = selector.getCodeSet();
				//	코드셋 변경:
				__synchronizeCodeSetInKey(codeset, new_code, insertion_mode);
				//	변경한 코드셋 적용:
				selector.setCodeSet(codeset);
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NEStandardScriptEditor::__synchronizeCodeSetInKey(NEIntSet& codeset, type_code new_code, bool insertion_mode)
	{
		if(isSynchronizationDisabled()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		if(insertion_mode)
		{
			for(int n=0; n < codeset.getLength() ;n++)				
				if(codeset[n] >= new_code)					
					codeset[n]++;
		}
		else
		{
			for(int n=0; n < codeset.getLength() ;)
			{
				if(codeset[n] == new_code)
				{
					codeset.remove(n);
					continue;
				}
				else if(codeset[n] > new_code)
					codeset[n]--;
				n++;
			}
		}

		return RESULT_SUCCESS;
	}

	type_code NEStandardScriptEditor::_searchInDeepForScriptCode(NENodeCodeSet& nodeset, NENode& target, type_code& start_scriptcode)
	{
		for(int n=0; n < nodeset.getLength() ;n++)
		{
			if(&nodeset[n] == &target)
				return start_scriptcode;
			else
			{
				type_code found = _searchInDeepForScriptCode(nodeset[n].getKeySet(), target, ++start_scriptcode);
				if(found != NE_INDEX_ERROR)
					return found;
			}			
		}

		return NE_INDEX_ERROR;
	}

	type_code NEStandardScriptEditor::_searchInDeepForScriptCode(NEKeyCodeSet& kset, NENode& target, type_code& start_scriptcode)
	{
		for(int kn=0; kn < kset.getLength() ;kn++)
		{
			NEKey& key = kset[kn];
			if(key.isSubClassOf(NEType::NENODE_CODESET_KEY))
			{
				NENodeCodeSetKey& nodesetkey = static_cast<NENodeCodeSetKey&>(key);
				type_code found = _searchInDeepForScriptCode(nodesetkey.getValue(), target, start_scriptcode);
				if(found != NE_INDEX_ERROR)
					return found;
			}
		}

		return NE_INDEX_ERROR;
	}

	type_result NEStandardScriptEditor::_insertShortCutOrExpand(type_code code_to_expand)
	{
		NEShortCutSet& shortcutset = _getScriptShortCutSet();
		type_result result = RESULT_SUCCESS;

		if(shortcutset.getLengthLastIndex() < code_to_expand)
		{
			//	크기 확장:	인스턴스도 추가한다
			result |= shortcutset.resize(code_to_expand + 1);
			while(shortcutset.getLength() < shortcutset.getSize())
				result |= shortcutset.push(NEShortCut());
		}

		getScriptHeader().setMaxScriptCodeIndex(shortcutset.getLengthLastIndex());

		return result;
	}

	type_result NEStandardScriptEditor::_synchronize(OnSynchronize& handler, type_code to_be_manipulated, type_code max_code, NECodeType::CodeType type_of_code, bool is_inserting)
	{
		//	pre:
		//		Boundary Check:
		if(	to_be_manipulated < 0			||
			to_be_manipulated > max_code	)
		{
			ALERT_ERROR(" : 삭제하려는 네임코드가 허용된 범위를 넘어섰습니다.\n\t허용된 범위 : 0 ~ %d\n\t삭제하려던 네임코드: %d", max_code, to_be_manipulated);
			return RESULT_TYPE_ERROR;
		}
		//	왜 스크립트는 0번도 삭제할 수 있는가:
		//		다른 코드와 마찬가지로 스크립트0번은 메인 노드로써, 반드시 있어야 하는 게 원칙이다.
		//		그러나 실제로는 노드가 하나도 없는 NEScriptCodeSet도 존재하게 된다. (대표적인
		//		예가, .release()나 .serialize()나 초기화할때) 따라서 0번 삭제를 막아버리면, 
		//		특수한 경우마다 매번 충돌하게 되므로, 여기서는 차라리 스크립트코드만 예외로 0번을
		//		삭제할 수 있도록 처리하였다.
		if( type_of_code != NECodeType::SCRIPT	&&
			to_be_manipulated == 0				)
		{
			ALERT_ERROR(" : 스크립트코드가 아닌 모든 코드는 0번에 추가/삭제할 수 없습니다.\n0번은 \"네임이 존재하지 않는\" 미등록된 노드들을 위한 코드입니다.\n작업을 취소합니다.");
			return RESULT_TYPE_ERROR;
		}
		if(	is_inserting				&&
			to_be_manipulated >= max_code)
			return RESULT_SUCCESS;


		//	main:
		//		삽입 모드인지:
		//			추가의 경우(push)는 마지막의 처리 하나만 수행하면 된다.
		//			노드의 이동:
		NENodeSelector selector(getType());
		selector.setNodeType(NECodeType::ALL);

		NENode* node = NE_NULL;
		while(node = &selector.getNode())
			handler.onSynchronize(*this, *node, to_be_manipulated);

		selector.initializeReferingPoint();
		while(node = &selector.getNode())
		{
			NEKeyCodeSet& keyset = node->getKeySet();
			for(int n=0; n < keyset.getLength() ;n++)
				_synchronizeCodesInKey(keyset[n], type_of_code, to_be_manipulated, is_inserting);
		}

		return RESULT_SUCCESS;
	}
}

/*
	_unlist할때마다 노드의 값을 0으로 만들기.
*/