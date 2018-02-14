class Thing {
	//	Thing은 World의 최상위 객체
	virtual Result& release();
	template <typename T, typename S>
	friend class TVisitation;
	//	_tour를 위한 것이다.
	wbool isNull() const { return !this; }
	wbool isExist() const { return this; }
	virtual Result& _tour(Visitor& visitor) const { return Success; }
	//	Visitor에 의해서 하위 구성요소(ownee)들을 어떻게 순회시킬지를 정한다.
	virtual Result& _tour(Visitor& visitor) {
		const This* consted = const_cast<const This*>(this);
		return consted->_onTour(visitor);
	}
}
class Instance : Thing {
	//	Instance는 World에서 인스턴스 관리를 대신해준다. 여기서부터 bind가 가능하다.
	union ID {
		windex type;
		//	클래스의 종류
		windex index;
		//	해당 클래스 인스턴스 벡터의 몇번째인가.type과 index를 조합하면 어디서든 객체에 접근할 수 있다.
		wint64 number;
	} _id;
	virtual TStrong<?> clone() const;
	ID getID() const { return _id; }
	wcount getSerial() const { 
		Nexus::get().getInstancer()[_id].getSerial();
	}
	const InstanceBlock& getBlock() const {
		WRD_CHK_THISPTR(InstanceBlock)
		return Nexus::get().getInstancer()[_id];
	}
}
class Msg : public ? {
	String _name;
	String& getName() { return _name; }
	const String& getName() const { return _name; }
	Args _args;
	Args& getArgs() { return _args; }
	const Args& getArgs() const { return _args; }
	static mutable TStrong<Object> _thisptr;
	#Message는_name_thisptr_args를_모두_하나의_Array로_구성한다 
	friend class Object;
	// _thisptr 조작을 위해
	const Object& getThis() const { return *_thisptr; }
	Result& _setThis(const Object& newone) { _thisptr = newone; }
	static mutable TString<Object> _me;
	const Object& getMe() const { return *_me; }
	Result& _setMe(const Object& newone) { _me = newone; }
}
class Node : public ? {
	virtual Strong call(const Msg& msg) {
	}
}
