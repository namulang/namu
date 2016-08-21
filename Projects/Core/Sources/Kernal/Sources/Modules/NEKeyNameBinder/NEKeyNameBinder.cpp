#include "../Kernal/Kernal.hpp"

namespace NE
{
	type_result NEKeyNameBinder::bind()
	{
		using namespace NEType;
		NENodeManager& noder = Kernal::getInstance().getNodeManager();				
		NENodeManager::LocalStack& stack = noder.getLocalStack();
		const NEKeyCodeSet& ks = stack.getRecentNode().getKeySet();	//	어쩌파 bind함수가 호출되는 시점은 NodeManager.execute()가 되는 시점뿐이기 때문에 _manager는 noder라고 가정한다.
		if(_keyname.getLength() <= 0) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_INVALID_DATA;

		//	main:
		if(_keyname[0] == TCHAR('$'))
			return _bindLocalKey();
		//		속해있는 Node.KeySet에서 탐색:
		for(int n=0; n < ks.getLength() ;n++)
			if(ks[n].getName() == _keyname)
				return Super::bind(ks[n]/*, NEType::NENODE_MANAGER*/);


		//	post:
		KERNAL_WARNING("KeyName 바인딩이 실패했습니다. 주어진 이름 %s이, 이 노드에 속하지 않은 것 같습니다.\n바인딩이 실패했으므로 기본값이 할당될 것입니다.", _keyname.toCharPointer());
		return RESULT_TYPE_WARNING;
	}

	type_result NEKeyNameBinder::_bindLocalKey()
	{
		//		LocalKeys에서 탐색:
		const NENodeManager::LocalStack::PersistentKeySet& local_keys = Kernal::getInstance().getNodeManager().getLocalStack().getLocalKeySet();
		for(int n = 0; n < local_keys.getLength(); n++)
		{
			const NEKey& key = local_keys[n];
			if (&key && key.getName().toLowerCase() == _keyname.toLowerCase())
			{
				type_result result = Super::bind(key/*, NEType::LOCALSTACK*/);

				if( ! NEResult::hasError(result))
					_manager_type = NEType::LOCALSTACK;

				return result;
			}
		}

		/*_manager_type = NEType::NENODE_MANAGER;*/
		return RESULT_TYPE_WARNING;
	}

	type_result NEKeyNameBinder::setKeyName(const NETString& new_keyname)
	{
		_keyname = new_keyname;

		//	Release Binding 정보:
		return unbind();
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

	NEKeyNameBinder::NEKeyNameBinder(const NEKeyNameBinder& rhs)
		: Super()	//	복사생성자를 호출하지 않는다. 자세한 사항은 _assign 참조
	{
		_assign(rhs);
	}

	NEKeyNameBinder& NEKeyNameBinder::operator=(const NEKeyNameBinder& rhs)
	{
		if(this == &rhs) return *this;

		//	Super::operator=(rhs);	상위클래스로 메소드 체이닝 하지 않는다. 자세한 사항은 _assign 참조.

		return _assign(rhs);
	}

	type_bool NEKeyNameBinder::operator==(const NEKeyNameBinder& rhs) const
	{
		return Super::operator==(rhs) && _keyname == rhs._keyname;
	}

	type_bool NEKeyNameBinder::operator!=(const NEKeyNameBinder& rhs) const
	{
		return ! operator==(rhs);
	}

	NEKeyNameBinder& NEKeyNameBinder::_assign(const This& rhs)
	{
		Super::release();
		//	왜 release()를 수행하는가:
		//		NEKeyNameBinder는 Module객체 안에서만 scope가 유효한 클래스다.
		//		따라서 다른 Module 객체에서는 다른 바인딩이 수행되어야 한다.
		//		(같은 KeyName을 소유하고 있다고 하더라도 NEKeyNameBinder를
		//		소유하고 있는 모듈이 다른 객체면, 다른 키가 바인딩 되어야 한다
		//		라는 얘기다)
		//		여기서 주어진 rhs는 외부 모듈의 NEKeyNameBinder일 수 있다.
		//		따라서 바인딩 정보는 할당하지 않고, keyname만 할당한다.
		//		만약, "rhs가 바인딩하는 키의 값"을 할당하고 싶은 거라면,
		//		this->getBinded() = rhs.getBinded(); 를 수행하면 된다.

		//	상위 클래스중 바인딩 정보에 속하지 않는 Enable만 여기서 별도로 할당해 준다
		setEnable(rhs.isEnable());

		_keyname = rhs._keyname;

		return *this;
	}

	void NEKeyNameBinder::release()
	{
		_keyname.release();
		Super::release();
	}

	type_result NEKeyNameBinder::isValid() const
	{
		type_result result = 0;
		if(result = _keyname.isValid())	return result;

		return Super::isValid();
	}

	NEBinaryFileLoader& NEKeyNameBinder::serialize(NEBinaryFileLoader& loader)
	{
		NESwitchableUnit::serialize(loader);
		//	중간 클래스(NEBinderBase부터 NEKeyBinder)의 바인딩결과 정보는 공유(저장 및 로드)할 수 없다.		

		return loader >> _keyname;
	}

	NEBinaryFileSaver& NEKeyNameBinder::serialize(NEBinaryFileSaver& saver) const
	{
		NESwitchableUnit::serialize(saver);
		//	중간 클래스(NEBinderBase부터 NEKeyBinder)의 바인딩결과 정보는 공유(저장 및 로드)할 수 없다.		

		return saver << _keyname;
	}
}