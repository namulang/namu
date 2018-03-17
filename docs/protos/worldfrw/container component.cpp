class Iteration : public ConstableInstance {
	virtual result& move(wcount step) = 0;
	virtual Node& getNode() = 0;
	virtual const Node& getNode() = 0;
	virtual wbool isEnd() const = 0;
	Container& getOwner() {
		return _getOwner();
	}
	const Container& getOwner() const {
		return _getOwner();
	}
	virtual Container& _getOwner() = 0;
	const Container& _getOwner() const {
		This& unconst = const_cast<This&>(*this);
		return unconst._getOwner();
	}
};
template <typename O, wbool IS_CONST = ConstChecker<O>::IS>
class TIteration : public Iteration {
	TWeak<O> _owner;
	virtual Container& _getOwner() { return *_owner; }
	O& getOwner() { return *_owner; }
	const O& getOwner() const { return *_owner; }
};
template <typename O>
class TIteration<O, true> : public Iteration {
	TWeak<O> _owner;
	virtual Container& _getOwner() { return *_owner; }
	const O& getOwner() const { return *_owner; }
};
class Iterator : public OccupiableObject {
//	Object여야 World에서 다룰 수 있게 된다.
	friend class Container;

	operator wbool() const;
	This& operator++(int);
	This& operator++();
	This& operator--(int);
	This& operator--();

	Result& move(wcount step) {
		WRD_IS_NULL(_iteration)

		return _iteration.move(step);
	}
	const Node& get() const {
		WRD_IS_THIS(const Node)
		WRD_IS_NULL(_iteration, Nuller<const Node>::ref)

		return _iteration.getNode();
	}
	Node& get() {
		WRD_IS_THIS(Node)
		WRD_IS_CONST(Nuller<Node>::ref) 
		WRD_IS_NULL(_iteration, Nuller<Node>::ref)
		
		return _iteration.getNode();
	}
	wbool isEnd() const;
	Container& getOwner() {
		WRD_IS_THIS(Container)
		WRD_IS_CONST(Nuller<Container>::ref)

		return _owner;
	}
	const Container& getOwner() const {
		WRD_IS_THIS(const Container)
		return _owner;
	}
	Result& _setIteration(Iteration& it) {
		_iteration = it;
		return Success;
	}
	TStrong<Iteration> _iteration;
	TWeak<Container> _owner;
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

class Containable {
	virtual Result& insert(const Iterator& pos, const Node& it) = 0;
	virtual Result& remove(const Iterator& pos, const Node& trg) = 0;
	virtual Iterator getIterator(windex n) = 0;
	virtual CIterator getIterator(windex n) const = 0;
	virtual wcount getSize() const = 0;
};
class Container : public Object, public Containable {
	Container() : Super(), _trait(Node::getStaticClass()) {
	}
	Container(const Class& trait);

	Node& operator[](windex n);
	const Node& operator[](windex n) const;
	operator+
	operator-
	operator<<
	operator>>
	//	World에서 Container로 사용해야 하므로 Object로부터 상속받아야 한다.
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

	Result& remove(const Node& it);
	Result& remove(windex n);
	Result& remove(const Iterator& start, const Iterator& end);
	template <typename T>
	Result& remove(const Iterator& pos, Ts... args) {
	}
	template <typename T>
	Result& remove(windex n, Ts... args) {
	}
	windex pop();
	Result& deq();

	virtual Iterator getIterator(windex n) {
		Iterator ret;
		ret._setIteration(_onTakeIteration(n));
		return ret;
	}
	virtual CIterator getIterator(windex n) const {
		CIterator ret;
		ret._setIteration(_onTakeIteration(n));
		return ret;
	}
	virtual TStrong<Iteration> _onTakeIteration(windex n) = 0;
	Iterator getHead();
	CIterator getHead() const;
	Iterator getTail();
	CIterator getTail() const;

	template <typename T>
	Result& each(T lambda);
	Result& each(Method& lambda);

	virtual wcount getSize() const { return _size; }
	Result& _setSize(wcount newone) { _size = newone; }
	wcount _size;

	const Class& getTrait() const {
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
