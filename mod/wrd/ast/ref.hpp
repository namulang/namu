#pragma once

#include "node.hpp"

namespace wrd {

	class ref : public node, public tbindable<node> {
		WRD(ME(ref, node),
			INIT_META(me),
            CLONE(me))

	public:
		ref(const std::string& name = "");
		ref(const node& it, const std::string& name = "");
		ref(const node* it, const std::string& name = "");
		ref(const me& rhs);
		ref(const type& t, const std::string& name = "");
		ref(const node& it, const type& t, const std::string& name = "");
		ref(const node* it, const type& t, const std::string& name = "");
		ref(const me& rhs, const type& t);

    public:
        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;
            return _assign(rhs);
        }
        node* operator->() { return &get(); }
        node& operator*() { return get(); }
        const node* operator->() const WRD_UNCONST_FUNC(operator->())
        const node& operator*() const WRD_UNCONST_FUNC(operator*())

    public:
        const std::string& getName() const override { return _name; }
        void setName(const std::string& new1) { _name = new1; }

        const wtype& getType() const override {
            return (const wtype&) _ref.getType(); // always can cast to wtype.
        }

        using tbindable<node>::bind;
        wbool bind(const node& it) override {
            return _ref.bind(it);
        }

        void rel() override {
            _ref.rel();
        }

        using tbindable<node>::canBind;
        wbool canBind(const type& it) const override {
            return _ref.canBind(it);
        }

        wbool isBind() const override {
            return _ref.isBind();
        }

        node& get() { return _ref.get(); }
        const node& get() const WRD_UNCONST_FUNC(get())
        template <typename E>
        E& get() {
            node& got = get();
            if(nul(got)) return nulOf<E>();

            return got.template cast<E>();
        }
        template <typename E>
        const E& get() const WRD_UNCONST_FUNC(get<E>())

        ncontainer& subs() override {
            if(_ref)
                return _ref->subs();
            return nulOf<ncontainer>();
        }

        wbool canRun(const wtypes& typs) const override {
            if(_ref)
                return _ref->canRun(typs);
            return false;
        }

        str run(const containable& args) override {
            if(_ref)
                return _ref->run(args);
            return str();
        }

        wbool isRef() const override { return true; }

        const wtype& getEvalType() const override {
            if(_ref)
                return _ref->getEvalType();
            return super::getEvalType();
        }

        using super::cast;
        void* cast(const type& to) override {
            if(to == ttype<me>::get())
                return this;
            return _ref.cast(to);
        }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _ref == cast._ref;
        }

    private:
        void _setType(const type& t) {
            _ref._type = &t;
        }
        me& _assign(const me& rhs);

    private:
        // name is unique var:
        //  unique variable should not be assigned after creation.
        std::string _name;
        str _ref;
	};
}
