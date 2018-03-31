class Containable {
	Node& operator[](windex n);
	const Node& operator[](windex n) const;
	operator+
	operator-
	operator<<
	operator>>
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
	virtual TStrong<Iteration> _onCreateIteration(windex n) = 0;

	virtual wcount getSize() const = 0;

	virtual Iterator getIterator(windex n) = 0;
	virtual CIterator getIterator(windex n) const = 0;
	Iterator getHead();
	CIterator getHead() const;
	Iterator getTail();
	CIterator getTail() const;

	template <typename T>
	Result& each(T lambda);
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
};

class Container : public Object, public Containable {
	class Bean : public Instance {
		This(Container& owner);

		TWeak<Container> _owner;
		Container& getOwner();
		const Container& getOwner() const;
	};

	template <typename T>
	class Proxy : public OccupiableObject {
		friend class Container;

		Proxy(T& bean);

		TStrong<T> _bean;
		T& _getBean() {
			WRD_IS_THIS(T)
			// ...
		}
		const T& _getBean() const {
			WRD_IS_THIS(T)
			// ...
		}
		Container& getOwner();
		const Container& getOwner() const;
		Result& _setIteration(Iteration& it) {
			_iteration = it;
			return Success;
		}
	};

	Container() : Super(), _trait(Node::getStaticClass()) {}
	Container(const Class& trait);

	virtual Iterator getIterator(windex n) {
		Iterator ret;
		ret._setIteration(_onCreateInteration(n));
		return ret;
	}
	virtual CIterator getIterator(windex n) const {
		CIterator ret;
		ret._setIteration(_onCreateIteration(n));
		return ret;
	}
	virtual wcount getSize() const { return _size; }
	Result& _setSize(wcount newone) { _size = newone; }
	wcount _size;
db
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
		TIterator<T> ret;
		ret._setIteration(_onTakeIteration(n));
		return ret;
	}
};


class Iteration : public Container::Bean, public Iteratable {
	Iteration(Container& owner);
};
template <typename O, wbool IS_CONST = ConstChecker<O>::IS>
class TIteration : public Iteration {
	O& getOwner() { return *_owner; } // Super::getOwner()는 virtual이 아니므로 이게 이 코드가 성립한다.
	const O& getOwner() const { return *_owner; }
};
template <typename O>
class TIteration<O, true> : public Iteration {
	const O& getOwner() const { return *_owner; }
};


class Iterator : public Container::Proxy<Iteration>, public Iteratable {
	virtual Result& move(wcount step) {
		Iteration& bean = getBean();
		WRD_IS_NULL(bean)

		return bean.move(step);
	}
	const Node& get() const {
		Iteration& bean = getBean();
		WRD_IS_NULL(bean, Nuller<const Node>::ref)

		return bean.get();
	}
	Node& getNode() {
		WRD_IS_CONST(Nuller<Node>::ref) 
		Iteration& bean = getBean();
		WRD_IS_NULL(bean, Nuller<Node>::ref)
		
		return bean.get();
	}
	virtual wbool isTail() const;
	virtual wbool isHead() const;
};
template <typename T, wbool IS_CONST = ConstChecker<T>::IS>
class TIterator : public Iterator {
	T& get() { return static_cast<T&>(Super::get()); }
	const T& get() { return static_cast<const T&>(Super::get()); }
	Container& getOwner() {
		WRD_IS_THIS(Container)
		return _owner;
	}
	const Container& getOwner() const {
		WRD_IS_THIS(const Container)
		return _owner;
	}
};
template <typename T>
class TIterator<T, true> : public Iterator {
	const T& get() { return static_cast<const T&>(Super::get()); }
};
