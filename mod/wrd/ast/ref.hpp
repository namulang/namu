#pragma once

#include "node.hpp"

namespace wrd {

	class ref : public node, public tbindable<node> {
		WRD(ME(ref, node),
			INIT_META(me),
            CLONE(me))

	public:
		ref(const std::string& name = "");
		ref(const node& it, const std::string& name);
		ref(const node* it, const std::string& name);
		ref(const me& rhs);

        /// on copyctor, all unique variables, name and type, will be copied.
        ref(const type& t, const std::string& name = "");
        ref(const type& t, const node& it, const std::string& name);
        ref(const type& t, const node* it, const std::string& name);
        ref(const type& t, const me& rhs);

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
        wbool setName(const std::string& new1) override {
            _name = new1;
            return true;
        }

        const wtype& getType() const override {
            return (const wtype&) _ref.getType(); // always can cast to wtype.
        }
        void setType(const type& t) { _ref._type = &t; }

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

        nucontainer& subs() override {
            if(_ref)
                return _ref->subs();
            return nulOf<nucontainer>();
        }

        wbool canRun(const ucontainable& args) const override {
            if(_ref)
                return _ref->canRun(args);
            return false;
        }

        str run(const ucontainable& args) override {
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
        me& _assign(const me& rhs);

    private:
        // name is unique var:
        //  unique variable should not be assigned after creation.
        std::string _name;
        str _ref;
	};
}
