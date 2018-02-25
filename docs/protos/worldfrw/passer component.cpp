class Object : public Node {
	virtual 
};

class Refer : public Node {
	This();
	This(const Class& cls, wbool is_const = false)
	: Super(), _cls(cls), _is_const(is_const) {}
	This(Object& it)
	: Super(), _cls(it.getClass() {
		bind(it);	
	}
	This(const Object& it);
	This(const This& it);

	operator==() const;
	operator!=() const;
	operator=(const This& it);
	operator=(Object& it);
	operator=(const Object& it);
	Object& operator->();
	const Object& operator->() const;
	Object& operator*();
	const Object& operator*() const;

	virtual CStrong call(const Msg& msg) const { return _bean.call(msg); }
	virtual Strong call(const Msg& msg) { return _bean.call(msg); }

	Result& bind(Object& it) {
		const Class& cls = it.getClass();
		WRD_IS_NULL(cls)
		if( ! cls.isSub(_cls))
			return TypeInvalid.warn("...");

		unbind();
		WRD_IS_ERR(_bean.bind(it))
		_is_const = false;
		return Success;
	}
	Result& bind(const Object& it) const {
		This& unconst = const_cast<This&>(*this);
		Result& res = unconst.bind(const_cast<Object&>(it));
		WRD_IS_ERR(res)

		_is_const = true;
		return res;
	}
	Result& unbind() {
		Result& res = _bean.unbind();
		WRD_IS_ERR(res)

		_is_const = false;
		return Success;
	}
	Node& get() {
		WRD_IS_THIS(Object)
		WRD_IF(_is_const, InvalidCall, Nuller<Object>::ref)

		return _bean.get();
	}
	const Node& get() const {
		WRD_IS_THIS(Object)
		return _bean.get();
	}

	wbool isConst() const { return _is_const; }
	wbool _is_const;
	TStrong<Node> _bean;
	const Class& _cls;
};

class Method : public Object {
};
