#include "NEIndexedNodeSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	type_id NEIndexedNodeSet::_last_generated_id = 0;

	NEIndexedNodeSet::NEIndexedNodeSet(NEEnlistableManager& manager)
		: Super(manager)
	{

	}

	NEIndexedNodeSet::NEIndexedNodeSet(type_count size)
		: Super(size)
	{

	}

	NEIndexedNodeSet::NEIndexedNodeSet(const This& source)
		: Super(source)
	{

	}

	NEIndexedNodeSet::~NEIndexedNodeSet()
	{

	}

	const NEIndexedNodeSet& NEIndexedNodeSet::operator+=(const This& source)
	{
		Super::operator+=(source);

		return *this;
	}

	NEIndexedNodeSet NEIndexedNodeSet::operator+(const NEIndexedNodeSet& source) const
	{
		This buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_id NEIndexedNodeSet::peekLastGeneratedId() const
	{
		return _last_generated_id;
	}

	type_id NEIndexedNodeSet::_generateId()
	{
		_last_generated_id++;
		if(_last_generated_id <= 0)
			KERNAL_ERROR(" : ");

		return _last_generated_id;
	}

	type_index NEIndexedNodeSet::insert(type_index index, const NENode* const source)
	{
		if( ! &source)
		{
			KERNAL_ERROR(" : 주어진 원본이 없습니다.");
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



		//	가상생성자로 인스턴스 생성:
		//		인스턴스 복사 알고리즘:
		//			뭐가 문제인가:
		//				1. 주어진 source는 _manager를 가지고 있다. 
		//				2. 주어진 source의 타입은 NEModule로써 이는 ADT이다. 따라서 source의
		//				실제 타입이 무엇인지는 알 수 없다.
		//				3. source의 실제타입에 상관없이 제대로 복사를 하는 함수로는 현재,
		//				clone(가상복사생성자)가 유일하다.
		//				4. clone은 어떠한 파라메터도 받지 않도록 작성되어있다.
		//				5. Super::insert에서는 clone로 생성된 T*를 보관해 두는데, 
		//				source.keyset은 clone을 통해서도 복사가 불가능하다.
		//				복사가 되려면, 복사생성된 객체에 manager가 할당되어 있어야 keyset이
		//				manager 포인터를 갖고 인스턴스를 등록하기 때문이다.
		//				6. clone은 원자연산이다.
		//				즉, 생성하고->manager를 set하고->복사한다는 식으로 구성할 수 없다.
		//
		//			어떤 해결방법이 있었는가:
		//				기존의 생성과 동시에 복사한다.----> 생성->manager set-> 복사
		//				의 형태로 중간에 manager를 set 할 수 있도록 하면 된다.
		//				따라서, 생각해보면, "생성과 동시에 set. 이후 복사" 나
		//				"생성 이후, manager set과 동시에 복사"를 생각해 볼 수 있다.
		//				전자의 경우는 생성자에서 manager를 넘겨준 이후에 복사시
		//				가상할당자(예를 들면 virtual assign(module))등을 새로 추가하는 
		//				방법이 되겠다.
		//				아니면 기존 virtual clone() 이외에도 virtual clone(manager)로 하나 더
		//				만드는 방법도 생각해 볼 수 있다.
		//				복사생성자에서 source의 _manager도 같이 복사하는 방법도 생각해 볼 수
		//				있겠으나, 이렇게 하면 복사된 인스턴스가 내쪽의 manager가 아닌, source쪽
		//				manager에 속해있게 되버리므로 적합치 못하다.
		//				이러한 방법도 있다. clone을 호출하면 멤버변수(keyset)은 할당되지 않더라도
		//				source의 모듈은 정확하게 복사 할 수 있다.
		//				그 이후에 manager를 set하고, 다시한번 operator=를 하는 방법이다.
		//					NEModule& cloned = source.clone();	//	모듈의 객체만 가상생성
		//					cloned.manager is my manager;		//	매니져 할당
		//					cloned.operator=(source)			//	이제 멤버변수를 복사
		//				다만 이 방법의 가장 큰 단점은 keyset에 속하지 않는 멤버변수는 복사 할 수 
		//				없다는 제약이 있다는 것이다.
		//			
		//			최종 해결방법은 무엇인가:
		//				객체 생성시, 상속계층을 거꾸로 올라가면서 생성자를 호출해간다.
		//				그 중간쯤에 manager를 관리하는 클래스가 있을 것이다. 그 생성자가 호출되었
		//				을때 외부에서 특정한 manager값을 전달하는 이벤트 핸들러만 있으면 될것이다.
		//				그래서 이를 해결하기 위해 static으로 global_manager라는 방법을 사용한다.
		//					static Manager* getGlobalManager();
		//					static setGlobalManager(Manager*);
		//				의 함수를 이용해서 해당하는 manager 멤버변수를 소유한 클래스가 호출 되었을때
		//				특별히 주어진 manager가 없을때 global_manager를 할당하는 방법이다.
		//				다만 이 globalmanager를 사용하는 생성자는 복사생성자로 제한한다.
		//				일반 생성자는 manager를 할당할 수 있는 함수가 이미 있으므로, 사용자가 manager
		//				외부로부터 할당하고 싶었는지 아닌지 의도를 파악할 수 있기 때문이다.
		//				
		//			예상되는 문제점:
		//				이 문제에 예상되는 문제점은 다음과 같다.
		//					1. static이긴 하나 생성자에서 메소드를 호출한다는 점에서 예상치못한 에러가
		//					있을 수 있다.	-> push pop의 개념을 적용하여 일정 부분 해결
		//					2. 할당한 global manager값을 해제해주지 않으면 전혀다른 객체가 생성될때도
		//					내 manager가 할당되버리는 오류가 발생할 것이다.	-> 코드 작성에 주의하면 
		//																	안정성 확보 가능
		//					3. 내가 소유할 하나의 객체를 위해 global_manager를 할당한다 하더라도 내부적으로
		//					다른 manager 영역에 있는 객체를 생성하고자 할때가 있을 수도 있다.
		//
		//			적용시점:
		//				Super인 IndexedArrayTemplate에서 clone이 사용되기 직전마다 _setGlobalManager
		//				를 해줘야한다. 최종적으로 적용 대상은 다음과 같다.
		//					1. insert
		//					2. resize
		//					3. setElement

		//	생성자 핸들러:	보다 자세한 내용은 NEIndexedModuleSet.cpp 참조하라
		//		전역 manager 셋:		
		//			타겟팅:
		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		//			연산:
		NEGlobalManagerOffer::_setGlobalManager(getManager());
		//		복사:
		type_index inputed_index = Super::insert(index, source);
		//		아이디 할당:
		//			타겟팅:
		NENode& node = getElement(inputed_index);
		if(&node)
			node._id = _generateId();
		//		되돌리기:
		NEGlobalManagerOffer::_setGlobalManager(push);

		//		모듈 초기화 여부 판단:	
		//			주어진 모듈이 초기화가 되어있는 지를 판단하고, 초기화가
		//			안되어있을때에는 초기화를 수행해야 키셋이 제대로 존재하게 된다.
		//
		//			왜 초기화를 해야 하는가:
		//				모듈이 enlist되지 않은 채로 키셋에 키를 넣을 수는 없기 때문이다.
		//				모듈의 키셋(코드)은 실제 인스턴스가 담겨야 하는 키셋(인스턴스)
		//				을 소유하는 매니져를 알고 있어야 한다.
		//				그러나 외부에서 정의된 모듈의 경우는 매니져가 없으므로 키셋에 
		//				어떠한 키도 넣을 수 없다.
		//					
		//			모듈 매니져는 모듈을 초기화를 수행할 수 없다:
		//				모듈매니져는 숏컷이나 instance 셋을 소유하지 않는다.
		//				이는 EnlistableManager로부터 상속을 받아야 하나, 모듈매니져는
		//				노드가 등록가능한 매니져의 일종이 아니므로 불가능하다.
		//				
		//			어떻게 초기화가 되었는지를 확인 하는가:
		//				검사 대상은 이미 추가된 인스턴스다. 따라서 요점은 "주어진 모듈이
		//				가지고 있는 키셋이 이미 초기화가 수행되었는지를 알 수 있는가"
		//				가 된다. 
		//					1. 모든 모듈은 NEKeyCodeSet을 가지고 있다.
		//					2. 모든 CodeSet은 enlist될때 반드시 자신의 Manager값을 할당받는다.
		//				따라서 위의 같은 사실을 이용하여, 모듈의 키셋의 매니져가 할당이
		//				되어 있지 않은 경우는 초기화가 필요한 경우라는 것을 알 수 있다.
		//
		//			시나리오 점검:
		//				모듈매니져로부터 push한 경우:
		//					1. 모듈매니져로부터 모듈을 하나 가져옴(복사X)
		//						모듈매니져의 모듈은 초기화가 안 되어있으므로, KeyCodeSet.manager 
		//						is 0x00이다.
		//					2. 해당 모듈을 enlisted 모듈셋에 push.
		//						모듈셋에서는 주어진 모듈을 복사생성. 복사생성시에 _manager 값은
		//						복사되지 않는 "인스턴스 우선"정책을 가지고 있다.
		//						(_is_rootnode)와 동일
		//					3. 성공적으로 모듈을 push되고 _onEnlist(Module) 호출
		//						주어진 모듈의 키셋의 manager = 0x00이므로 매니져를 셋 하면서,
		//						모듈을 초기화.


		return inputed_index;
	}

	type_result NEIndexedNodeSet::setElement(type_index index, const NENode* const source)
	{
		if( ! &source)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		NENode* const_casted = const_cast<NENode*>(source);

		type_id original_id = const_casted->getId();
		const_casted->_id = _generateId();

		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		NEGlobalManagerOffer::_setGlobalManager(getManager());

		type_result result = Super::setElement(index, source);

		NEGlobalManagerOffer::_setGlobalManager(push);

		const_casted->_id = original_id;

		return result;
	}

	NEBinaryFileSaver& NEIndexedNodeSet::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);
		
		for(int n=0; n < getSize() ;n++)
		{
			const NENode& node = getElement(n);
			if( ! &node) continue;

			saver << node;
		}
		
		return saver << _last_generated_id;
	}

	NEBinaryFileLoader& NEIndexedNodeSet::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		//		상위 함수 호출:
		//			내부에서 size, length와 _occupiedset을 load 해서 가지고 온다.
		Super::serialize(loader);
		

		//	main:
		type_index size = getSize();
		//		push를 위한 길이 정보 초기화:
		_length = 0;
		type_index occupied_n = -1;

		for(int n=0; n < size ;n++)
		{
			if( ! _occupiedset[n]) continue;

			//	push:
			//		push를 위해서 소유권을 일시 해제:
			_occupiedset[n] = false;
			//		삽입:
			insert(n, NENode());
			//		에러처리:
			NENode& inputed = getElement(n);
			if( ! &inputed)
			{
				KERNAL_ERROR(" : IndexedNodeSet에서 로드 도중에 노드를 생성하지 못했습니다.\n데이터를 버리고 다음 노드를 읽습니다.");
				//	버리기 위해 노드를 하나 생성:
				loader >> NENode();
				continue;
			}
			//		로드:
			loader >> inputed;
		}

		return loader >> _last_generated_id;
	}

	type_result NEIndexedNodeSet::remove(type_index index)
	{
		//	노드의 _unlist 호출:
		NENode& node = getElement(index);
		if( ! &node	|| ! getOccupiedSet()[index])
		{
			KERNAL_WARNING(" : IndexedNodeSet에서 존재하지 않는 노드를 삭제하려했습니다.")
			return RESULT_ABORT_ACTION | RESULT_TYPE_WARNING;
		}

		type_result result = node._onUnlisted();
		
		return result |= Super::remove(index);
	}

	type_result NEIndexedNodeSet::_onEnlisted()
	{
		return RESULT_SUCCESS;
	}

	type_result NEIndexedNodeSet::resize(type_count new_size)
	{
		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		NEGlobalManagerOffer::_setGlobalManager(getManager());
		
		type_result result = Super::resize(new_size);

		NEGlobalManagerOffer::_setGlobalManager(push);

		return result;
	}
}