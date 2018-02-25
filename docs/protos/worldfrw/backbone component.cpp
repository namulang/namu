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
	virtual wbool isSuper(const Class& it) const {
		return getClass().isSuper(it);
	}
	wbool isSuper(const Thing& it) const {
		return getClass().isSuper(it.getClass());
	}
	template <typename T>
	wbool isSuper() const {
		return getClass().isSuper(T::getStaticClass());
	}
	wbool isSub(const Thing& it) const {
		return it.getClass().isSuper(getClass());
	}
	wbool isSub(const Class& it) const {
		return it.isSuper(getClass());
	}
	template <typename T>
	wbool isSub() const {
		return T::getStaticClass().isSuper(getClass());
	}
	const Class& getClass();
	virtual Refer to(const Class& cls) {
		return Refer();
	}
	virtual const Refer
	template <typename T>
	TRefer<T> to() {
		return Refer<T>(to(T::getStaticClass()));
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

	Instance() {
		//	TODO: we need to optimize this. this ganna hotspot.
		Nexus::get().getInstancer().stamp(*this);
	}

	virtual TStrong<?> clone() const;
	ID getID() const { return _id; }
	wcount getSerial() const { 
		Nexus::get().getInstancer()[_id].getSerial();
	}
	const InstanceBlock& getBlock() const {
		WRD_IS_THIS(InstanceBlock)
		return Nexus::get().getInstancer()[_id];
	}
	wbool isHeap() const {
		MemoryMap& mmap = Nexus::get().getInstancer().getMemoryMap();
		WRD_IS_NULL(mmap, false)

		return 	mmap.getStartAddress() <= this 	&&
				this << mmap.getEndAddress()	;
	}
}
class Msg : public Thing {
	String _name;
	String& getName() { return _name; }
	const String& getName() const { return _name; }

	Args _args;
	Args& getArgs() { return _args; }
	const Args& getArgs() const { return _args; }

	static Object* _thisptr; // Message는_name_thisptr_args를_모두_하나의_Array로_구성한다 
	friend class Object; // _thisptr 조작을 위해
	static Object& getThis() { return *_thisptr; }
	static Result& _setThis(Object& newone) { _thisptr = &newone; }

	static Method* _me;
	friend class Method;
	static const Method& getMe() const { return *_me; }
	static Result& _setMe(Method& newone) { _me = newone; }
}
class Node : public ? {
	virtual Refer call(const Msg& msg) {
	}
	virtual Refer call(const Msg& msg) const {
	}
}
