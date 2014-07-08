#include "../../../Modules/Kernal/Kernal.hpp"

namespace NE
{
	type_result NEKeyNameBinder::bind()
	{
		using namespace NEType;
		NENodeManager& noder = Kernal::getInstance().getNodeManager();				
		const NEKeyCodeSet& ks = noder.getLocalStack().getRecentNode().getKeySet();	//	어쩌파 bind함수가 호출되는 시점은 NodeManager.execute()가 되는 시점뿐이기 때문에 _manager는 noder라고 가정한다.


		//	main:		
		for(int n=0; n < ks.getLength() ;n++)
			if(ks[n].getName() == _keyname)
				return SuperClass::bind(ks[n], NEType::NENODE_MANAGER);


		//	post:
		KERNAL_WARNING("KeyName 바인딩이 실패했습니다. 주어진 이름 %s이, 이 노드에 속하지 않은 것 같습니다.\n바인딩이 실패했으므로 기본값이 할당될 것입니다.", _keyname.toCharPointer());
		return RESULT_TYPE_WARNING;
	}

	type_result NEKeyNameBinder::setKeyName(const NETString& new_keyname)
	{
		_keyname = new_keyname;
		
		//	Release Binding 정보:
		_real_index = NE_INDEX_ERROR;
		_comparing_id = NE_INDEX_ERROR;

		return RESULT_SUCCESS;
	}

	const NETString& NEKeyNameBinder::getKeyName() const
	{	
		return _keyname;
	}

	NEKeyNameBinder::NEKeyNameBinder()
	{

	}

	NEKeyNameBinder::NEKeyNameBinder(const NETString& new_keyname)
		: _keyname(new_keyname)
	{

	}

}