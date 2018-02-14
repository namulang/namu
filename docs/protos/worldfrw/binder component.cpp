    class WeakInstanceBind : public Thing {
        Weak();
        Weak(const This& rhs);
        operator wbool() const { return isBinded(); }
        This& operator=(const This& rhs) {
            bind(rhs.get());
            //	Super::operator=()를 해서는 안된다.
            return *this;
        }
        This& operator=(const Instance& newone) {
            bind(newone);
            return *this;
        }
        wbool operator==(const This& rhs) const { 
            return &get()  == &rhs.get();
        }
        wbool operator!=(const This& rhs) const {
            return &get() != &rhs.get();
        }
		Instance& operator->() { return get(); }
		Instance& operator*() { return get(); }
		const Instance& operator->() const { return get(); }
		const Instance& operator*() const { return get(); }
        Instance& get() {
			WRD_CHK_THISPTR(Instance)
			const Instance& inst = World::get().getInstancer()[_id].getInstance();
			//	정확한 인터페이스가 나오지 않았다.
			if(inst.getSerial() != _serial) {
				unbind();
				WrongBind.warn("...");
				return Nuller<Instance>::ref;
			}

			return inst;
		}
        const Instance& get() const { 
			This& unconst = const_cast<This&>(*this);
			return unconst.get();
		}
        virtual Result& bind(const Instance& newone) {
            //	pre:
			//		param-validation:
			if(newone.isNull())
				return InvalidParam;
			InstanceBlock& blk = const_cast<InstanceBlock&>(newone.getBlock());
			if(blk.isNull())
				return InvalidParam; 

			//	main:
            unbind();
            _id = newone.getID();
			_serial = blk.getSerial();
            return Success;
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
    class StrongInstanceBind : public WeakInstanceBind {
        virtual Result& bind(const Instance& trg) {
			Result& res = Super::bind(trg);
			if(res)
				return res.dump("...");

			_getInstanceBlock()._increaseCount();
			//	처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며, 
			//	StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
			//	Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
			//	bind에 의해서 해제될 수 있게 된다.
			return res;
		}
		virtual Result& unbind() {
			InstanceBlock& blk = _getInstanceBlock();
			if(blk.isExist())
				blk._decreaseCount();
			return Super::unbind();	
		}
    };
    template <typename T, typename S>
    class TBind<T> : public S {
		//	S는 Super, T는 Trait
        TBind();
        TBind(const This& rhs);
        TBind(const Weak& rhs) {
            assign(rhs);
        }
        virtual const Result& assign(const Thing& rhs) {
            if(Super::assign(rhs)) return SuperCancel;
            //	...???...
        }
        operator=(const T&);
        T& get();
    }
    template <typename T>
    //	c++11 부터 지원되는 문법
    using TWeak = TBind<Weak, T>;
	using Weak = TBind<Weak, Node>;
    template <typename T>
    using TStrong = TBind<Strong, T>;
	using Strong = TBind<Strong, Node>;
