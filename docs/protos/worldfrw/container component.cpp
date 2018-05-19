//	Container:
//		All contianers in Worldlang are binders to Object, unlikely natvie C++ template container. (ex, vector<T>)
class Containable {
	//	we can gives container local variable:
	//		if we give local variable to container, Array().toStrong() 
	//		func will return heap cloned instance.
	//		if we give binded heap variable, Array().toStrong() func 
	//		will return shallow copied Strong binder.
	//
	//		example:
	//			Array arr, arr2;
	//			arr.push(Integer(3));
	//			arr2.push(Integer(3));
	//			arr[0] = 5
	//			Strong inted = Integer(5).toStrong();
	//			// same as 'Strong inted(new Integer(5));'
	//			Integer& int1 = *inted;
	//			arr.push(int1);
	//			arr2.push(int1);
	//			arr[1] = 10;
	//
	//			for(int n=0; n < 2 ;n++)
	//				cout << "arr[" << n << "] = " << arr[n] << ", arr[" << n << "] = " << arr2[n] << "\n";
	//
	//			output:
	//				arr[0] = 5, arr2[0] = 3
	//				arr[1] = 10, arr2[1] = 10
	virtual Result& set(const Iterator& pos, Node& to_bind) = 0;
	Result& set(const Iterator& pos, const Node& to_clone);
	Result& set(windex n, const Node& to_clone);
	Result& set(windex n, Node& to_bind);

	//	메소드 은닉을 위하여 virtual 메소드를 private로 만들어 redirection 한다.
	virtual Node& _get(windex n) = 0;
	Node& get(windex n) {
		WRD_IS_THIS(Node)
		return _get(n);
	}
	const Node& get(windex n) const {
		This& unconst = const_cast<This&>(this);
		return unconst.get(n);
	}

	virtual Result& insert(const Iterator& pos, Node& to_bind) = 0;
	Result& insert(const Iterator& pos, const Node& to_clone);
	Result& insert(windex n, Node& to_bind);
	Result& insert(windex n, const Node& to_clone);
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
	windex push(Node& to_bind);
	windex push(const Node& to_clone);
	windex push(const Iterator& its_start, const Iterator& its_end);
	windex push(<<<iterator from stl>>>)
	template <typename... Ts>
	windex push(Ts... args) {
		return insert(getTail(), args...);
	}
	Result& enq(Node& to_bind);
	Result& enq(const Node& to_clone);
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
	virtual TStrong<Iteration> _onCreateIteration(Container& origin, windex n) = 0;

	virtual wcount getSize() const = 0;

	virtual Iterator _getIterator(windex n) = 0;
	virtual CIterator _getIterator(windex n) const = 0;
	Iterator getIterator(windex n) { return _getIterator(n); }
	CIterator getIterator(windex n) const { return _getIterator(n); }

	Iterator getHead();
	CIterator getHead() const;
	Iterator getTail();
	CIterator getTail() const;

	Result& each(function<Result&(Node&)> lambda);
	Result& each(function<Result&(const Node&)> lambda) const;
	Result& each(Method& lambda);

	virtual const Class& getTrait() const = 0;
	
	//	this method can't be defined at Containable interface class:
	//		because this is interface class, it can't have metaclass.
	//		if it can't have metaclass, binder can't distinguish given 
	//		type parameter T is valid or not. so it can't be binded.
	virtual TStrong<Containable> deepclone() const = 0;
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
	class Proxy : public Instance {
		This(Container& origin);

		TWeak<Container> _origin;
		Container& getOrigin();
		const Container& getOrigin() const;
	};
	
	Node& operator[](windex n);
	const Node& operator[](windex n) const;
	operator+
	operator-
	operator<<
	operator>>
	operator+=(const Node& it);
	operator+=(Node& it);
	operator-=(const Node& it);

	template <typename T, typename S>
	class TProxy : public S
		T& getOrigin() { return static_cast<T&>(Super::getOrigin()); }
		const T& getOrigin() const { return static_csat<T&>(Super::getOrigin()); }
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

	virtual TStrong<Container> deepclone() const {
		TStrong<Container> ret = getClass().instantiate();
		each([&ret](const Node& e) {
			const Container& cont = e.cast<Container>();
			Strong newone = cont.isExists() ? cont.deepclone() : e.clone
			return ret.push(newone);
		})

		return ret;
	}
};

template <typename T, typename S>
class TContainer : public S {
	//	Native에서 편의를 위해 제공된다. 모든 메소드는 World invisible 하다.
	TIterator<T> getIterator(windex n) {
		return TIterator<T>(_onCreateInteration(*this, n));
	}
	TCIterator<T> getIterator(windex n) const {
		return TCIterator<T>(_onCreateInteration(*this, n));
	}
	T& operator[](windex n);
	T& get(windex n) { // get()이 nonvirtual이기에 여기서 공변이 달라도 된다.
		return static_cast<T&>(get(n));
	}
	const T& operator[](windex n) const;
	const T& get(windex n) const {
		return static_cast<T&>(get(n));
	}
	Result& each(function<Result&(T&)> lambda);
	Result& each(function<Result&(const T&)> lambda) const;
};


class Iteration : public Container::Proxy, public Iteratable {
	Iteration(Container& origin);

	//	get() 안에서 toIndex()를 쓰면 무한 루프를 돌게 된다.
	virtual windex toIndex() const {
		Container& origin = getOrigin();
		WRD_IS_NULL(origin, -1);
		
		windex n = -1;
		for(CIterator e=origin.getHead(); e; e++)
		{
			n++;
			if(&(*e) == &get())
				break;
		}

		return n;
	}
};
template <typename T>
using TIteration = TProxy<T, Iteration>


class CIterator : public OccupiableObject, public Iteratable {
	CIterator(const Iteration& bean)

	TStrong<Iteration> _bean;
	Iteration& _getProxy() {
		WRD_IS_THIS(T)
		return *_bean;
	}
	const T& _getProxy() const {
		WRD_IS_THIS(T)
		return *_bean;
	}

	const Container& getOrigin() const;

	virtual Result& move(wcount step) {
		Iteration& bean = getProxy();
		WRD_IS_NULL(bean)

		return bean.move(step);
	}
	const Node& step() {
		const Node& ret = get();
		move(1);
		return ret;
	}
	const Node& backstep() {
		const Node& ret = get();
		move(-1);
		return ret;
	}
	const Node& operator*() const;
	const Node* operator->() const;
	This& operator++();
	This& operator--();
	const Node& get() const {
		Iteration& bean = getProxy();
		WRD_IS_NULL(bean, Nuller<const Node>::ref)

		return bean.get();
	}
	virtual wbool isTail() const;
	virtual wbool isHead() const;
};
class Iterator : public CIterator {
	Node& operator*();
	Node* operator->();
	Container& getOrigin();
	Node& step() { return const_cast<Node&>(Super::step()); }
	Node& backstep() { return const_cast<Node&>(Super::backstep()); }
	Node& get() {
		WRD_IS_CONST(Nuller<Node>::ref) 
		Iteration& bean = getProxy();
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
	friend class Control; // for _conts and Control class.

	virtual TStrong<Iteration> _onCreateIteration(Container& origin, windex n) {
		class ChainIteration : public TIteration<Chain> {
			....
		};
		return new ChainIteration(origin);
	}

	class Control : public Container::Proxy, public Containable {
		#define _DEFINE_BEAN(RET)					\
			Chain& origin = getOriginContainers();	\
			WRD_IS_NULL(origin, RET)

		virtual Result& set(const Iterator& pos, Node& it) {
			_DEFINE_BEAN(nullerr)
			return origin.set(pos, it);
		}

		virtual Node& _get(windex n) {
			_DEFINE_BEAN(nullerr)
			return origin._get(n);
		}
			
		virtual Result& insert(const Iterator& pos, Strong it) {
			_DEFINE_BEAN(nullerr)
			return origin.insert(pos, it);
		}
		virtual Result& remove(const Iterator& pos) {
			_DEFINE_BEAN(nullerr)
			return origin.remove(pos);
		}
		virtual TStrong<Iteration> _onCreateIteration(windex n) {
			_DEFINE_BEAN(TStrong<Iteration>())
			return origin._onCreateIteration(n);
		}
		virtual wcount getSize() const {
			_DEFINE_BEAN(0)
			return origin.getSize();
		}
		virtual Iterator getIterator(windex n) {
			_DEFINE_BEAN(Iterator)
			return origin.getIterator(n);
		}
		virtual CIterator getIterator(windex n) const {
			_DEFINE_BEAN(CIterator)
			return origin.getIterator(n);
		}
		virtual const Class& getTrait() const {
			_DEFINE_BEAN(TNuller<Class>::ref)
			return origin.getTrait();
		}
		Containers& getOriginContainers() {
			Chain& chain = getOrigin().cast<Chain>();
			WRD_IS_NULL(chain, TNuller<Containers>::ref)

			return chain._conts;
		}
		const Containers& getOriginContainers() const {
			This& unconst = const_cast<This&>(*this);
			return unconst.getOriginContainers();
		}
		virtual TStrong<Container> deepclone() const {
			_DEFINE_BEAN(TStrong<Container>)
			return origin.deepclone();
		}
		#undef _DEFINE_BEAN
	};

	TStrong<Control> _control;
	Control& getControl() {
		if( ! _control)
			_control = _onCreateControl(*this);
		return *_control;
	}
	const Control& getControl() const {
		This* unconst = const_cast<This*>(this);
		return unconst->getControl();
	}
	//	사용자가 Control를 상속하여 사용할 수 있도록 한다.
	virtual TStrong<Control> _onCreateControl(Chain& origin) {
		return new Control(origin);
	}

	virtual Node& get(windex n);
	virtual Result& set(const Iterator& pos, const Node& it);
	virtual Result& insert(const Iterator& pos, Strong it);
	virtual Result& remove(const Iterator& pos);
}

template <typename T>
using TChain = TContainer<T, Chain>;
