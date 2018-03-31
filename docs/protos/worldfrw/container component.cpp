class Containable {
	Node& operator[](windex n);
	const Node& operator[](windex n) const;
	operator+
	operator-
	operator<<
	operator>>
	virtual Result& set(const Iterator& pos, const Node& it) = 0;
	Result& set(windex n, const Node& it);

	virtual Node& get(windex n) = 0;
	const Node& get(windex n) const {
		This& unconst = const_cast<This&>(this);
		return unconst;
	}

	virtual Result& insert(const Iterator& pos, const Node& it) = 0;
	Result& insert(windex n, const Node& it);
	Result& insert(const Iterator& pos, const Iterator& its_start, const Iterator& its_end);
	Result& insert(windex n, const Iterator& its_start, const Iterator& its_end);
	Result& insert(const Iterator& pos, <<<iterator from stl>>>);
	Result& insert(windex n, <<<iterator from stl>>>);
	template <typename... Ts>
	Result& insert(const Iterator& pos, Ts... args);
	template <typename... Ts>
	Result& insert(windex n, Ts... args) {
		return insert(getIterator(n), args...);
	}
	windex push(const Node& it);
	windex push(const Iterator& its_start, const Iterator& its_end);
	windex push(<<<iterator from stl>>>)
	template <typename... Ts>
	windex push(Ts... args) {
		return insert(getTail(), args...);
	}
	Result& enq(const Node& it);
	Result& enq(const Iterator& its_start, const Iterator& its_end);
	Result& enq(<<<iterator from stl>>>);
	template <typename... Ts>
	Result& enq(Ts... args) {
	}
	
	virtual Result& remove(const Iterator& start, const Iterator& end) = 0;
	Result& remove(const Node& it);
	Result& remove(windex n);
	template <typename T>
	Result& remove(const Iterator& pos, Ts... args) {
	}
	template <typename T>
	Result& remove(windex n, Ts... args) {
	}
	windex pop();
	Result& deq();
	
	//	사용자가 Iteration을 상속할 수 있도록 하기 위한 메소드.
	virtual TStrong<Iteration> _onCreateIteration(Container& owner, windex n) = 0;

	virtual wcount getSize() const = 0;

	virtual Iterator getIterator(windex n) = 0;
	virtual CIterator getIterator(windex n) const = 0;
	Iterator getHead();
	CIterator getHead() const;
	Iterator getTail();
	CIterator getTail() const;

	Result& each(function<Result&(Node&)> lambda);
	Result& each(function<Result&(const Node&)> lambda) const;
	Result& each(function<Result&(Iterator)> lambda);
	Result& each(function<Result&(CIterator)> lambda) const;
	Result& each(Method& lambda);

	virtual const Class& getTrait() const = 0;
};

class Iteratable {
	virtual Result& move(wcount step) = 0;
	This& operator++(int);
	This& operator++();
	This& operator--(int);
	This& operator--();
	Result& next();
	Result& prev();

	operator wbool() const;
	virtual wbool isTail() const = 0;
	virtual wbool isHead() const = 0;
	virtual wcount toIndex() const = 0;
};

class Container : public Object, public Containable {
	class Bean : public Instance {
		This(Container& owner);

		TWeak<Container> _owner;
		Container& getOwner();
		const Container& getOwner() const;
	};

	Container() : Super(), _trait(Node::getStaticClass()) {}
	Container(const Class& trait);

	virtual Iterator getIterator(windex n) {
		return Iterator(_onCreateInteration(*this, n));
	}
	virtual CIterator getIterator(windex n) const {
		return CIterator(_onCreateIteration(*this, n));
	}
	virtual wcount getSize() const { return _size; }
	Result& _setSize(wcount newone) { _size = newone; }
	wcount _size;

	virtual const Class& getTrait() const {
	//	삽입가능한 Class를 나타낸다.
		return *_trait;
	}
	TWeak<const Class> _trait;
};

template <typename T, typename S>
class TContainer : public S {
	//	Native에서 편의를 위해 제공된다. 모든 메소드는 World invisible 하다.
	TIterator<T> getTIterator(windex n) {
		return TIterator<T>(_onCreateInteration(*this, n));
	}
	TCIterator<T> getTIterator(windex n) const {
		return TCIterator<T>(_onCreateInteration(*this, n));
	}
	T& operator[](windex n);
	T& getT(windex n) {
		return static_cast<T&>(get(n));
	}
	const T& operator[](windex n) const;
	const T& getT(windex n) const {
		return static_cast<T&>(get(n));
	}
	Result& each(function<Result&(T&)> lambda);
	Result& each(function<Result&(const T&)> lambda) const;
	Result& each(function<Result&(TIterator<T>)> lambda);
	Result& each(function<Result&(TCIterator<T>)> lambda) const;
};


class Iteration : public Container::Bean, public Iteratable {
	Iteration(Container& owner);

	virtual windex toIndex() const {
		windex n = -1;
		getOwner().find([&windex](const Node& target)
	}
};
template <typename O>
class TIteration : public Iteration {
	O& getOwner() { return *_owner; } // Super::getOwner()는 virtual이 아니므로 이게 이 코드가 성립한다.
	const O& getOwner() const { return *_owner; }
};


class CIterator : public OccupiableObject, public Iteratable {
	CIterator(const Iteration& bean)

	TStrong<Iteration> _bean;
	Iteration& _getBean() {
		WRD_IS_THIS(T)
		return *_bean;
	}
	const T& _getBean() const {
		WRD_IS_THIS(T)
		return *_bean;
	}

	const Container& getOwner() const;

	virtual Result& move(wcount step) {
		Iteration& bean = getBean();
		WRD_IS_NULL(bean)

		return bean.move(step);
	}

	const Node& operator*() const;
	const Node* operator->() const;
	const Node& get() const {
		Iteration& bean = getBean();
		WRD_IS_NULL(bean, Nuller<const Node>::ref)

		return bean.get();
	}
	virtual wbool isTail() const;
	virtual wbool isHead() const;
};
class Iterator : public CIterator {
	Node& operator*();
	Node* operator->();
	Container& getOwner();
	Node& get() {
		WRD_IS_CONST(Nuller<Node>::ref) 
		Iteration& bean = getBean();
		WRD_IS_NULL(bean, Nuller<Node>::ref)
		
		return bean.get();
	}
};
template <typename T>
class TIterator : public Iterator {
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
	T& get() { return static_cast<T&>(Super::get()); }
	const T& get() const { return static_cast<const T&>(Super::get()); }
};
template <typename T>
class TCIterator<T> : public CIterator {
	const T& operator*() const;
	const T* operator->() const;
	const T& get() const { return static_cast<const T&>(Super::get()); }
};



class Chain : public Container {
	//vector<TStrong<Container> > _containers;
	typedef TArray<Container> Containers;
	Containers _conts;
	friend class Control; // for _conts.

	virtual TStrong<Iteration> _onCreateIteration(Container& owner, windex n) {
		class ChainIteration : public TIteration<Chain> {
			....
		};
		return new ChainIteration(owner);
	}

	class Control : public Container::Bean<Control>, public Containable {
		#define DEFINE_BEAN(RET)				\
			Containers& origin = _getOrigin();	\
			WRD_IS_NULL(origin, RET)

		virtual Result& set(const Iterator& pos, const Node& it) {
			DEFINE_BEAN(nullerr)
			return origin.set(pos, it);
		}

		virtual Node& get(windex n)
			
		virtual Result& insert(const Iterator& pos, const Node& it) {
			DEFINE_BEAN(nullerr)
			return origin.insert(pos, it);
		}
		virtual Result& remove(const Iterator& pos) {
			DEFINE_BEAN(nullerr)
			return origin.remove(pos);
		}
		virtual TStrong<Iteration> _onCreateIteration(windex n) {
			DEFINE_BEAN(TStrong<Iteration>())
			return origin._onCreateIteration(n);
		}
		virtual wcount getSize() const {
			DEFINE_BEAN(0)
			return origin.getSize();
		}
		virtual Iterator getIterator(windex n) {
			DEFINE_BEAN(Iterator)
			return origin.getIterator(n);
		}
		virtual CIterator getIterator(windex n) const {
			DEFINE_BEAN(CIterator)
			return origin.getIterator(n);
		}
		virtual const Class& getTrait() const {
			DEFINE_BEAN(TNuller<Class>::ref)
			return origin.getTrait();
		}
		Containers& _getOrigin() {
			Chain& chain = getBean().cast<Chain>();
			WRD_IS_NULL(chain, TNuller<Containers>::ref)

			return chain._conts;
		}
		const Containers& _getOrigin() const {
			This& unconst = const_cast<This&>(*this);
			return unconst._getOrigin();
		}
	};
	TStrong<Control> _control;
	Control& getControl() {
		if( ! _control)
			_control = _onCreateControl(*this);
		return *_control;
	}
	//	사용자가 Control를 상속하여 사용할 수 있도록 한다.
	virtual TStrong<Control> _onCreateControl(Chain& owner) {
		return new Control(owner);
	}

	virtual Node& get(windex n);
	virtual Result& set(const Iterator& pos, const Node& it);
	virtual Result& insert(const Iterator& pos, const Node& it);
	virtual Result& remove(const Iterator& pos);
}

template <typename T>
using TChain = TContainer<T, Chain>;
