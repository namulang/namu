class Class : public Object { //	World에 visible해야 하기 때문이다.
	wbool operator==(const This& rhs) const {
		return &getName() == &rhs.getName();
	}
	wbool operator!=(const This& rhs) const {
		return &getName() != &rhs.getName();
	}
	virtual const Class& getClass() const {
		return *this;
	}
	virtual Result& _setInitialized(wbool newone) = 0;
	virtual wbool isTemplate() const = 0;
	virtual wbool isAbstract() const = 0;
	TStrong<Object> instantiate() const = 0;
	virtual const String& getName() const = 0;
	const Class& getSuper() const {
		return getSupers()[0];
	}
	virtual const Classes& getSupers() const = 0;
	virtual const Classes& getSubs() const = 0;
	virtual Result& initialize() {
		//	pre:
		//		exception:
		if(isInitialized())
			return Cancel.info(..);
		Super::initialize();

		//	main:
		//		Object class should not initialize explicitly:
		//			or This makes recursive call.
		//			Because if we make a instance of TClass<Object>, it triggers Class::initialize inside of it.
		if(&getName() == &TClass<Thing>::getStaticName())
			return _setInitialized(true);

		//  main:
		//        get Supers info from Super:
		//                at this point TClass<Super> is instantiated, and "Super" also does all of this sequences.
		Class& super = const_cast<Class&>(getSuper());
		super.initialize();
		//        constructing SuperClass:
		ClassSet& my_supers = _getSupers();
		my_supers = super._getSupers();
		my_supers.push(&super);
		//        notify to super:
		super._getSubs().push(*this);

		return _setInitialized(true);
	}
	virtual wbool isSuper(const Class& it) const {
		//  checking class hierarchy algorithm:
		//        Use the "Tier" of the class hierarchy info to check it.
		//        "Tier" means that how this class are inherited far from the Root class, that is, Object.
		//        So, if the "this" is a super of given object "it", its "tier"th super class
		//        would must be the class of "this".
		if(it.isNull()) return false;
		const Classes& its_supers = it.getSupers();
		wcount 	my_tier = getClass().getSupers().size(),
				its_tier = its_supers.size();
		if(my_tier > its_tier) return false;


		//  main:
		const ClassBase& target = its_tier == my_tier ? it :
			static_cast<const Class&>(its_supers[my_tier]);

		return getClass() == target;//  Remember. We're using Class as "Monostate".
	}
	Classes& _getSupers() {
		return const_cast<Classes&>(getSupers());
	}
	Classes& _getSubs() {
		return const_cast<Classes&>(getSubs());
	}
	const Classes& getLeafs() const {
		static Classes inner;
		
	}
};

template <typename T>
class ConcreteClass : public Class {
	virtual wbool isAbstract() const { return false; }
	virtual TStrong<Object> instantiate() const {
		return TStrong<Object>(new T());
	}
};

template <typename T>
class InterfaceClass : public Class {
	virtual wbool isAbstract() const { return true; }
	virtual TStrong<Object> instantiate() const {
		NotDefined.warn("...");
		return TStrong<Object>();
	}
};

template <typename T>
class TClass : public TADTChecker<T>::TypeClass {
	TClass() { this->initialize(); }
	virtual wbool isTemplate() const { return TTemplateChecker<T>::IS; }
	virtual const String& getName() const { return getStaticName(); }
	virtual const Classes& getSupers() const { return getStaticSupers(); }
	virtual const Classes& getSubs() const { return getStaticSubs(); }
	static wbool _is_initialized;
	virtual wbool isInitialized() const { return _is_initialized; }
	wbool isOccupiable() const { return getStaticOccupiable(); }
	virtual Result& _setInitialized(wbool newone) {
		_is_initialized = newone;
		return Success;
	}
	static const String& getStaticName() {
		static String inner;
		if(inner.getLength() <= 0) {
			int status = 0;
			wchar* demangled = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
			inner = demangled;
			free(demangled);
		}

		return inner;
	}
	static const Classes& getStaticSupers() {
		static Classes inner;
		return inner;
	}
	static const Classes& getStaticSubs() {
		static Classes inner;
		return inner;
	}
	static wbool isStaticOccupiable() {
		static wbool inner = isSub(OccupiableObject::getStaticClass());
		return inner;
	}
};
