#include "Bind.hpp"
#include "../watcher/BindTag.hpp"

namespace wrd { namespace memlite {

	WRD_DEF_THIS(Bind)

	wbool This::operator==(const This& rhs) const { return &get() == &rhs.get(); }
	wbool This::operator!=(const This& rhs) const { return ! operator==(rhs); }

	This& This::operator=(const This& rhs) {
        if(this == &rhs) return *this;

		_assign(rhs);
		return *this;
	}

	wbool This::bind(Instance& new1) {
		// type checking before binding only is required to Bind class.
		// Derived classes from this doesn't need it. because its type is specified.
		// prevent wrong type providing by compiler.
		if(!canBind(new1)) {
            WRD_W("can't bind new1(%s) instance", new1.getType().getName().c_str());
            return false;
        }

		return _bind(new1);
	}

	wbool This::isBind() const {
        const BindTag& tag = _getBindTag(_itsId);
        if(nul(tag)) return false;

        return tag.isBind();
    }

	wbool This::unbind() {
		_itsId.num = WRD_INDEX_ERROR;
		return true;
	}

	Id This::getItsId() const { return _itsId; }
	wbool This::canBind(const Type& type) const { return getBindable().isSuper(type); }

	wbool This::_bind(const Instance& it) {
	    unbind();
		//	regardless of result from _onStrong binder can bind:
		//		there are two reasons:
		//			because Block has equal lifecycle to what it bind, if there is
		//			a request by user to refer a bind for binding freed instance,
		//			user has responsibilty to treat wrongly.
		//			so, we should not consider such cases.
		//
		//		and:
		//			no matter how block reacts, anyway it won't refuse binder's
		//			refering. for instance, the scenario for binding non-heap allocated
		//			instance.
		_itsId = it.getId();
        WRD_DI("Bind(%x) binds Instance(%x) of %s class",
                this, &it, it.getType().getName().c_str());
	    return true;
	}

	Instance& This::_get() {
        Instance& ins = WRD_GETS(_getBindTag(_itsId),get());
        WRD_NUL_THEN_LOG(ins)

	    return ins;
	}

	wbool This::_assign(const This& rhs) {
	    if(this == &rhs) return true;

	    //    Only not available combination between this and rhs is,
	    //    when this is nonconst but rhs is const.
	    //    because when we accept this case, in consequence, rhs's binded one will loose their constness.
	    if(!isConst() && rhs.isConst()) {
            WRD_W("Bind assign failed. me.const=%d but rhs.isConst()=%d", isConst(), rhs.isConst());
	        return false; // the only case can't accept.
        }

	    return _bind(rhs.get());
	}

#undef This
}}
