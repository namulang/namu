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
		: SuperClass(rhs)
	{
		_assign(rhs);
	}

	NEKeyNameBinder& NEKeyNameBinder::operator=(const NEKeyNameBinder& rhs)
	{
		if(this == &rhs) return *this;

		SuperClass::operator=(rhs);

		return _assign(rhs);
	}

	bool NEKeyNameBinder::operator==(const NEKeyNameBinder& rhs) const
	{
		return SuperClass::operator==(rhs) && _keyname == rhs._keyname;
	}

	bool NEKeyNameBinder::operator!=(const NEKeyNameBinder& rhs) const
	{
		return ! operator==(rhs);
	}

	NEKeyNameBinder& NEKeyNameBinder::_assign(const ThisClass& rhs)
	{
		SuperClass::release();
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

		_keyname = rhs._keyname;

		return *this;
	}

	void NEKeyNameBinder::release()
	{
		_keyname.release();
		SuperClass::release();
	}

	type_result NEKeyNameBinder::isValid() const
	{
		type_result result = 0;
		if(result = _keyname.isValid())	return result;

		return SuperClass::isValid();
	}

	NEBinaryFileLoader& NEKeyNameBinder::serialize(NEBinaryFileLoader& loader)
	{
		//	상위클래스의 바인딩결과 정보는 공유(저장 및 로드)할 수 없다.

		return loader >> _keyname;
	}

	NEBinaryFileSaver& NEKeyNameBinder::serialize(NEBinaryFileSaver& saver) const
	{
		//	상위클래스의 바인딩결과 정보는 공유(저장 및 로드)할 수 없다.

		return saver << _keyname;
	}

	NEObject& NEKeyNameBinder::clone() const
	{
		return *(new ThisClass(*this));
	}

	NEType::Type NEKeyNameBinder::getType() const
	{
		return NEType::NEKEY_NAME_BINDER;
	}
}