#include "NEModuleArray.hpp"
#include "../Kernal/Kernal.hpp"
#include "../NENodeCodeSet/NENodeCodeSet.hpp"

namespace NE
{
	type_id NEModuleArray::_last_generated_id = 0;

	NEModuleArray::NEModuleArray(NEEnlistableManager& manager)
		: Super(manager)
	{

	}

	NEModuleArray::NEModuleArray(type_count size)
		: Super(size)
	{

	}

	NEModuleArray::NEModuleArray(const This& source)
		: Super(source)
	{

	}

	NEModuleArray::~NEModuleArray()
	{

	}

	const NEModuleArray& NEModuleArray::operator+=(const This& source)
	{
		Super::operator+=(source);

		return *this;
	}

	NEModuleArray NEModuleArray::operator+(const This& source) const
	{
		This buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_id NEModuleArray::peekLastGeneratedId() const
	{
		return _last_generated_id;
	}

	type_id NEModuleArray::_generateId()
	{
		_last_generated_id++;
		if(_last_generated_id <= 0)
			KERNAL_ERROR(" : ");

		return _last_generated_id;
	}

	type_index NEModuleArray::insert(type_index index, const NEModule* const source)
	{
		if( ! source)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}
		if(_occupiedset[index])
		{
			type_result result = setElement(index, source);
			if(NEResult::hasError(result))
			{
				KERNAL_ERROR(" : ");
				return result;
			}
		}


		
		//	main:
		
		//		전역 manager 셋:		
		//			타겟팅:
		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		//			연산:
		NEGlobalManagerOffer::_setGlobalManager(getManager());
		//		복사:
		type_index inputed_index = Super::insert(index, source);
		//		아이디 할당:
		//			타겟팅:
		NEModule& module = getElement(inputed_index);
		module.initialize();
		if(&module)
			module._id = _generateId();	
		//		되돌리기:
		NEGlobalManagerOffer::_setGlobalManager(push);	
		
		return inputed_index;
	}

	type_result NEModuleArray::setElement(type_index index, const NEModule* const source)
	{
		if( ! source)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		NEModule* const_casted = const_cast<NEModule*>(source);

		type_id original_id = const_casted->getId();
		const_casted->_id = _generateId();

		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		NEGlobalManagerOffer::_setGlobalManager(getManager());

		type_result result = Super::setElement(index, source);

		NEGlobalManagerOffer::_setGlobalManager(push);

		const_casted->_id = original_id;

		return result;
	}


	//	---------------------------------------------------------------------------------
	//	설명:		모듈을 파일로부터 저장한다.
	//				PC의 환경이 바뀌면 모듈이 존재하지 않게 되고, 이때 존재하지 않는 모듈의
	//				멤버변수를 파일로부터 읽어들이는 건 불가능하다.
	//				또한, 존재하지 않는 모듈의 메모리 크기를 알기도 힘들다.
	//				그래서 Case By Skip Load을 사용한다.
	//	동작조건:	
	//	메모:		Case By Skip Load란?
	//					:	모듈을 로드하기 전에, "모듈이 존재하지 않을 경우, 이동할 주소"를
	//						기록한다. 그래서 모듈이 존재하지 않는다면 파일의 포인터를 바로
	//						그쪽으로 이동하는 방법이다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-07-10	이태훈	추가
	//					:	Case By Skip Load를 추가해서 모듈의 보다 독립적인 환경을 만들었다.
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver& NEModuleArray::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);



		//	main:
		for(int n=0; n < getSize() ;n++)
		{
			const NEModule& module = getElement(n);
			if( ! &module)
				continue;
			//		스킵 주소를 기록할 주소 획득:	
			//			스킵주소는 해당 모듈이 로드 되기전에 기록되어야한다.
			//			하지만, 스킵주소를 기록하려면 다음 모듈이 저장되는 시점을
			//			알아야 하므로 모듈이 저장되기 전에 기록할 수 없다.
			//			그래서, 일단 주소가 기록될 공간을 비워두고, 모듈이 저장되면
			//			다시 앞으로 돌아와서 스킵주소를 기록한다.
			//
			//			현재 주소 획득:
			long int place_for_skip_address = saver.getPosition(); // place_for_skip_address가 가리키는 곳에 다음모듈이 기록되는 위치를 적어야 한다.
			//			주소를 비워둠:	나중에 기록할 수 있도록, 지금은 일단 점프한다.
			saver.setPosition(place_for_skip_address + sizeof(place_for_skip_address)); // 현재 모듈이 기록되는 위치 = 현재 위치 + 주소의 크기
			//		모듈 기록:
			//			모듈의 식별자 기록:	로드시, 이 식별자를 이용해서 모듈의 인스턴스를 가져올 것이다.
			module.getHeader().NEIdentifier::serialize(saver);
			
			saver << module;
			//		스킵주소 기록:	현재 파일포인터의 위치가 place_for_skip_address에 기록해야하는 주소다.
			//						돌아가기 전에 현재의 위치를 기억하자.
			//			주소 획득:
			long int skip_address = saver.getPosition(); // 이 주소를 place_for_skip_address가 가리키는 곳에 저장하면 된다.
			//			회귀:	이전 주소로 돌아가서 스킵주소를 기록한다.
			saver.setPosition(place_for_skip_address);
			saver << skip_address;
			//			복귀:	다시 원래대로 돌아온다.
			saver.setPosition(skip_address);
		}

		return saver << _last_generated_id;
	}



	//	---------------------------------------------------------------------------------
	//	설명:		모듈을 파일로부터 로드한다.
	//				PC의 환경이 바뀌면 모듈이 존재하지 않게 되고, 이때 존재하지 않는 모듈의
	//				멤버변수를 파일로부터 읽어들이는 건 불가능하다.
	//				또한, 존재하지 않는 모듈의 메모리 크기를 알기도 힘들다.
	//				그래서 Case By Skip Load을 사용한다.
	//	동작조건:	이미 모듈셋의 인스턴스가 외부로부터 발생했어야 한다.
	//					1. 스크립트 파일의 경우	:	NENode::serialize로부터 인스턴스 발생
	//					2. 노드 파일의 경우		:	NENodeSet::serialize로부터 인스턴스 발생
	//	메모:		Case By Skip Load란?
	//					:	모듈을 로드하기 전에, "모듈이 존재하지 않을 경우, 이동할 주소"를
	//						기록한다. 그래서 모듈이 존재하지 않는다면 파일의 포인터를 바로
	//						그쪽으로 이동하는 방법이다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-07-10	이태훈	추가
	//					:	Case By Skip Load를 추가해서 모듈의 보다 독립적인 환경을 만들었다.
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader& NEModuleArray::serialize(NEBinaryFileLoader& loader)
	{
		//	TEST: 아무런 조치를 취하지 않고도 insert, remove에 넣은 enlist, unlist로 
		//			serialize 도중에 무사히 enlist, unlist가 동작되는지?
		//	pre:
		//		타겟팅:
		const NEPackageManager& moduler = Kernal::getInstance().getModuleManager();
		//		상위 함수 호출:
		Super::serialize(loader);



		//	main:
		type_index size = getSize();
		//		길이 정보 초기화:	push를 사용하기 위해서
		_length = 0;
		//		Occupied 탐색 인덱스 초기화:
		//			occupiedSet에서 index로부터 순서대로 올림차순으로 검색한다.
		//			가장 가까운 것중에 OccupiedSet[index] == true인 것이 모듈을 추가해야하는 
		//			부분이 된다.
		type_index occupied_index = -1;

		for(int n=0; n < size ;n++)
		{
			if( ! _occupiedset[n])
				continue;
			//		스킵 주소 획득:	만약 모듈이 현재 PC에 존재하지 않았다면 더미 모듈일 테고,
			//						더미 모듈이라면 스킵주소로 바로 이동한다.
			long int next_module_to_skip = 0;
			loader >> next_module_to_skip;
			//		로드가능한 모듈 판단:	식별자를 로드해서 만약, 존재하지 않는다면, 로드하지 못하는 
			//								모듈이라는 게 된다.
			//								즉, 스크립트 파일에 해당 모듈의 데이터가 존재하나, 현재 PC에는
			//								모듈이 존재하지 않는 상태.
			//								따라서, 파일포인터를 스킵해야한다.
			//			식별자 로드:
			NEIdentifier identifier;
			loader >> identifier;
			//			식별자로 인스턴스 fetch:	만약 더미모듈이 나오면, fetch에 실패 했다는 걸 말한다.
			const NEModule& module = moduler.getModule(identifier);
			//			만약 더미모듈이라면:
		
			if( ! &module							/*||*/
/*				module.getType() == NEType::UNDEFINED*/)
			{
				//	더미 삽입:				
				KERNAL_ERROR(" : 더미 모듈을 삽입해야하는데, 현재 설계로는 삽입이 쵸금 곤란함");
			}
			else	//	로드한 모듈중 하나라면:
			{
				//			모듈 로드:	정상적으로 모듈을 로드한다.
				//				모듈 삽입을 위해서 소유권을 박탈:
				_occupiedset[n] = false;
				//				주어진 모듈 삽입: 
				//					push에서 NEModule::clone을 호출
				//					NEModule::NEModuleCodeSet이 복사되면서 push(NEModuleCodeSet&)을 호출
				//					push(NEModuleCodeSet&)에서 NEKeyArray으로부터 clone으로 키를 복제
				NEEnlistableManager* nullpointer = NE_NULL;
				insert(n, module);				
				//				데이터 로드:
				//					여기서 NEModuleCodeSet::serialize를 호출
				//					serialize에서 NEKeyCodeSetjuyhg
				loader >> getElement(n); // 여기서 다시 NEModule::serialize()에서 initialize를 호출한다
			}
			//	스킵로드:
			//		스킵을 사용하는가?:	파일포인터가 다음 모듈시작점과 다르다면
			if(loader.getPosition() != next_module_to_skip)
			{
				//		스킵:	
				//			주소를 스킵하고 다음 위치로 이동한다.
				//			만약 이 모듈이 마지막 모듈이었다면, 파일 포인터가 위치한 지점부터, 
				//			다음 NENode 혹은, NENode를 로드할 것이다.
				//			참고 : 더미 모듈은 로드가 필요없다.
				KERNAL_ERROR("E100031C77 : 모듈셋의 어긋난 파일포인터\n모듈셋에서 모듈의 인스턴스를 생성하는 중, 파일포인터가 어긋났습니다.\n파일포인터가 어긋나면 다음 모듈을 로드할 수 없으므로, 파일포인터를 강제로 보정합니다.\n현재 파일포인터 위치: %d\n예상했던 파일포인터 위치 : %d\n에러가 발생한 모듈의 식별자 : \n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d",loader.getPosition(), next_module_to_skip, identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision());

				loader.setPosition(next_module_to_skip);
			}			
		}

		return loader >> _last_generated_id;
	}

	type_result NEModuleArray::_onEnlisted()
	{
		return RESULT_SUCCESS;
	}

	type_result NEModuleArray::resize(type_index new_size)
	{
		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		NEGlobalManagerOffer::_setGlobalManager(getManager());

		type_result result = Super::resize(new_size);

		NEGlobalManagerOffer::_setGlobalManager(push);
		return result;
	}
}