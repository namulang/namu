class Visitation : public Instance {
//  Visitor에 의해서 Bind 되어야 하기때문에 Instance 상속되어야 한다.
//  사용자들은 Visitation을 그대로 사용해서는 안된다. 
//  이는 tour, visited, onvisited를 적절한 시점에 cb해야 하는 동작이 TVisitation에 있기 때문이다. 
    enum Proximity {
        LEVEL_DEFAULT = 0,
        LEVEL_MAX = std::numeric_limits<int>::max(),
        LEVEL_NOT_COMPATIBLE = -1;
    };
    Visitation() : _visitor(NULL) {}
    Visitation(const This& rhs) : Super(), _visitor(NULL) {}
    virtual const Class& getTrait() const = 0;
    //  대상이 되는 클래스다.
    virtual Proximity getProximity(const Thing& trg) const = 0;
    //  주어진 trg이 클래스와 얼마나 호환이 되는지를 나타낸다. 작을 수록 좋다. 이는 trg과 trait가 서로 상속관계에 놓여져 있는 경우 등에 사용된다. 즉, 부모클래스에서 visitation이 있는 경우 자식클래스의 개발자는 자신의 Visitation을 작성하지 않아도 얼추 돌아가게는 할 수 있다는 것이다. 호환이 전혀 안되는 경우는 음수가, 일치하는 경우는 0이 나온다.
    virtual Result& visit(Thing& trg) const {
        if(getProximity(trg) < 0) return InvalidParam;
        return Success;
    }
    virtual Result& visit(const Thing& trg) const {
        return visit(const_cast<Thing&>(trg));
    }
    virtual const Classes& getOwnerables() const = 0;
    //  이 Visitation을 initialize할수있는 Visitor들을 개발자가 정해줘야 한다.
    friend class Visitor;
    //  _visitor를 위한 것이다.
    Visitor& getVisitor() const { *_visitor; }
    Result& _setVisitor(Visitor& newone) const { _visitor = &newone; }
    mutable Visitor* _visitor;
    //  mutable은 Visitation은 기본적으로 const객체를 전제로 하기 때문이다. Visitation은 이곳저곳에서 돌려쓰는데다가, 객체는 Unique성을 띈다. 게다가 왠만한 값은 static으로 보관해서 처리도 가능하기 때문에 이정도 limitation은 감수할 만 하다.
};


// Visitation은 각 클래스 개발자들이 "이 클래스가 들어오면 이런식으로 순회하라" 라는 정보를 기록해 놓은 것이다.
template <typename T, typename S = Visitation>
class TVisitation : public S {
    virtual Proximity getProximity(const Thing& trg) const {
        if( ! trg.isSubOf(T::getStaticClass())) return -1;
        return trg.getSupers().getLength() - getSupers().getLength();
    }
    virtual Class& getTrait() const {
        static TClass<T> cls;
        return cls;
    }
    virtual Result& visit(Thing& trg) const {
        Result& res = Super::visit(trg); 
        if(res) 
            return res;
        T& casted = static_cast<T&>(trg);
        _onVisit(casted);
        trg._tour(*this);
        return _onVisit(casted);
    }
    virtual Result& visit(const Thing& trg) const {
		//	pre:
		//		exception:
		const Visitor& owner = getVisitor();
		if(owner.isNull())
			return WrongBind.warn(".....");
		//		supering:
        Result& res = Super::visit(trg);
        if(res)
            return res;

		//	main:
        const T& casted = static_cast<const T&>(trg);
		_onVisit(casted);
		if(owner.isReculsive())
			trg._tour(*this);
        return _onVisited(casted);
    }
    virtual Result& _onVisit(T& trg) const {
    //  편의용 함수다.
        return _onVisit((const T&) trg);
    }
    virtual Result& _onVisit(const T& trg) const {
    //  _onVisit() 2개를 이런식으로 연결시켜놓으면 대부분의 시나리오에서 사용자는 둘중 하나만 오버라이딩해도 잘 동작되게 된다.
        return Success;
    }
    virtual Result& _onVisited(T& trg) const {
        return _onVisited(const T&) trg);
    }
    virtual Result& _onVisited(const T& trg) const {
        return Success;
    }
};

class Visitor : public Thing {
	Visitor(wbool is_reculsive = true) : Super(), _is_reculsive(is_reculsive) {}
	//	is_reculsive를 false로 해두면, tour()가 호출되지 않는다.
	wbool isReculsive() const { return _is_reculsive; }
	Result& setReculsive(wbool newone) { 
		_is_reculsive = newone;
		return Success;
	}
    virtual const Class& getVisitationBase() const = 0;
    const Visitation& getVisitation(const Class& cls) const {
        struct {
            Proximity lv;
            TWeak<Visitation> found;
        } ret;
        ret.lv = LEVEL_MAX;
        for(auto e : _visits) {
            Proximity lv = e->getProximity(cls);
            if(lv < 0 || lv > ret.lv) continue;
            if( ! lv) return (*e)->get();
            ret.lv = lv;
            ret.found = *e;
        }
        return *ret.found
    }
    template <typename T>
    Result& visit(T& trg) const {
        //  const T&건, const T*건, T*건, TNativeTypeWrapper는 다 처리 가능한 클래스다.
        TNativeTypeWrapper<T> wrapped(trg);
        Visitation& v = getVisitation(T::getStaticClass());
        v._setVisitor(*this);
        return v.visit(wrapped);
    }
    template <typename T>
    This& visit(const T& trg) const {
        const TNativeTypeWrapper<const T> wrapped(trg);
        //  Wrapper를 const로 감싸는 이유는 Visitation의 const 함수로 빠지게 하기 위함이다.
        Visitation& v = getVisitation(T::getStaticClass());
        v._setVisitor(*this);
        v.visit(wrapped);
        return *this;
    }
    virtual Result& initialize() {
        if (_visits.length() > 0)
            return AlreadyDone;
        return _initialize();
    }
    Result& _initialize() {
        for(auto e : getVisitationBase().getSubsButConcretesOnly()) {
            //  Class의 자식클래스중 모든 구체클래스에 대해서,
            this->_visits.push_back(e->instantiate<Visitation>());
        }
        return Success;
    }
    static vector<TStrong<Visitation> > _visits;
	wbool _is_reculsive;
}

template <typename T>
class TVisitor : public Visitor {
//	편의 클래스
	virtual const Class& getVisitationBase() const {
		return T::getStaticClass();
	}
};

//////////////////////////////////////////////////////
// An example to use
//////////////////////////////////////////////////////
class Saver : public Visitor {
    class SaverVisitation : public Visitation {};
    //  정의만 되어있어도 된다. 이것은 단순히, visitor가 gethering을 하기 위한 것이다. Saving을 위한 추가 API가 getVisitor()로 접근해서 사용하면 된다.
    virtual const Class& getVisitationBase() const {
        static TClass<SaverVisitation> cls;
        return cls;
    }
    BinaryFileStream& getSaveStream() { return _saver; }
    //  ...open()
    //  ...initialoize()
    //  ...setPath()...and so on.
    BinaryFileStream _saver;
};
class MyClass : public Object {
    /* friend class MyAsciiVisitation : public TVisitation<MyClass, SaverVisitation> {
    MyClass가 visit당했을때 어떻게 해야하는지를 정의한다. SaverVisitation으로부터 상속받는다.
        virtual Result& _onVisit(const MyClass& trg) const {
            // getVisitor().getSaveStream() << "name=" << 
            이렇게 직접해도 되지만
            // getVisitor().visit(String("name="));
            // getVisitor().visit(name);
            이렇게 "String에 대해서 어떻게 SaverVistation을 수행할것인지를 다른 Visitation에게 떠넘기면서(= 재사용하면서) 가는게 더 좋다.
            // getVisitor() << age;
            이렇게도 된다.
            return Success;
        }
        // nonconst 버전을 정의하지않아도, nonconst는 const를 디폴트로 따라가게 된다.
    }; */
    //  이 클래스는 그냥 이렇게 정의만 해놓으면 된다. 알아서 Visitor가 잡순다.그리고 사실, 이 클래스는 정의할 필요가 없는데, 그 이유는 primitive와 같은 int, 대부분의 Object들은 알아서 visitation에 의해서 save, load가 이루어질 것이기 때문이다. 이 클래스에서 해줘야 하는 것은 int*나 cache를 만든다던가, 이벤트를 동작하는 것과 같이 자동으로는 도저히 될 수 없는, 사람의 손길이 타야만 하는 것들을 정의하면 된다.
    friend class MyAsciiLoadVisitation : public TVisitation<MyClass, LoaderVisitation> {
        virtual Result& _onVisit(MyClass& trg) const {
            delete trg._ageptr;
            //  사실 _onVisited() 에서 이걸 해도 된다.
            return Success;
            //  보면, aage는 일체 건드리지 않는걸 알 수 있을 것이다.aage는 Integer이며, Object의 일종이기 때문에 당연히 Visitation이 어딘가에 있다._tour()가 시작되면 visitor는 aage를 받아먹을 것이기 때문에 여기서 처리할 필요가 없는 것이다.
        }
        //  _onVisit(const MyClass& trg) const 는 정의하지 않는 걸 알 수 있다.저 함수의 기본 동작은 "Success"만 찍는 거로서, 실제로 Load를 하는 입장에서 const가 주어지면 할 수 있는게 아무것도 없기에 올바른 기본 동작이다.
        virtual Result& _onVisited(MyClass& trg) const {
        //  tour가 끝나면 다시 이리로 온다.
            trg._ageptr = new int(trg._age);
            return Success;
        }
    };
    virtual Result& _tour(Visitor& visitor) {
        return visitor << _age << aage;
    }
    virtual Result& _tour(Visitor& visitor) const {
        return visitor << _age << aage;
    }
    int _age;
    int* _ageptr;
    Integer aage;
};
