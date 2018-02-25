template <typename T>
class TWeak : public Thing {
	static_assert(T is not sub of Instance)

	TWeak();
	TWeak(T& it);
	TWeak(T* it);
	TWeak(const This& rhs);
	This& operator=(const This& rhs) {
		bind(rhs.get());
		//	Super::operator=()를 해서는 안된다.
		return *this;
	}
	This& operator=(T& newone) {
		bind(newone);
		return *this;
	}
	wbool operator==(const This& rhs) const { 
		return &get()  == &rhs.get();
	}
	wbool operator!=(const This& rhs) const {
		return &get() != &rhs.get();
	}
	operator wbool() const { return isBinded(); }
	T& operator->() const { return get(); }
	T& operator*() const { return get(); }
	virtual Result& bind(T& newone) {
		//	pre:
		//		param-validation:
		if(newone.isNull())
			return InvalidParam;
		InstanceBlock& blk = const_cast<InstanceBlock&>(newone.getBlock());
		if(blk.isNull())
			return InvalidParam; 

		//	main:ZZZZ
		unbind();
		_id = newone.getID();
		_serial = blk.getSerial();
		return Success;
	}
	Result& bind(T* newone) {
		return bind(*newone);
	}
	const T& get() const { 
		WRD_IS_THIS(T)
		const Instance& inst = World::get().getInstancer()[_id].getInstance();
		//	정확한 인터페이스가 나오지 않았다.
		if(inst.getSerial() != _serial) {
			unbind();
			WrongBind.warn("...");
			return Nuller<Instance>::ref;
		}

		return inst;
	}
	T& get() {
		return const_cast<T&>((const_cast<This*>(this))->get());
	}
	virtual Result& unbind() {
		_id.serial = 0;
		_serial = 0;
		return Success;
	}
	wbool isBinded() const {
		InstanceBlock& inst = _getInstanceBlock(); 
		return inst.isExist() && inst.getSerial() == _serial;
	}
	virtual Result& release() {
		unbind();
		return Super::release();
	}
	virtual ResultSet isValid() const???
	const InstanceBlock& _getInstanceBlock() const {
		return World::get().getInstancer()[_id];
	}
	InstanceBlock& _getInstanceBlock() {
		return World::get().getInstancer()[_id];
	}
	Instance::ID _id;
	wcount _serial;
};

template <typename T>
class TStrong : public TWeak<T> {
	TStrong();
	TStrong(T& it);
	TStrong(T* it);
	TStrong(TWeak<T>& it);

	virtual Result& bind(T& it) {
		Result& res = Super::bind(it);
		if(res) return res.dump("...");
		if( ! it.isHeap()) return InvalidParam.warn("it is local variable. couldn't bind it strongly.");

		_getInstanceBlock()._increaseCount();
		//	처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며, 
		//	StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
		//	Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
		//	bind에 의해서 해제될 수 있게 된다.
		return res;
	}
	virtual Result& unbind() {
		InstanceBlock& blk = _getInstanceBlock();
		if(blk.isNull()) {
			InvalidMember.warn("");
			return Super::unbind();	
		}
		if(blk.isHeap()) blk._decreaseCount();

EXIT:
		return Super::unbind();	
	}
};
using Weak = TWeak<Node>;
using CWeak = TWeak<const Node>;
//	c++11 부터 지원되는 문법
using Strong = TStrong<Node>;
using CStrong = TStrong<const Node>;

///////////////////////////////////////
///	Usage examples:
///////////////////////////////////////
//	Weak weak = new Integer(5);
//	{
//		Strong str = weak;
//		cout << *str;
//	}
//	if(!weak)
//		cout << "freed";
