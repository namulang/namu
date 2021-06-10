#pragma once

#include "node.hpp"

namespace wrd {

    class ref : public node, public tbindable<node> {
        WRD_CLASS(ref, node)

    public:
        ref() {}
        explicit ref(const node& new1): _str(new1) {}
        explicit ref(const node* new1): _str(new1) {}
        ref(const me& rhs): super(rhs) {
            bind(*rhs);
        }

        node* operator->() { return &get(); }
        node& operator*() { return get(); }
        const node* operator->() const WRD_UNCONST_FUNC(operator->())
        const node& operator*() const WRD_UNCONST_FUNC(operator*())

        // node:
        ncontainer& subs() override {
            if (!_str) return nulOf<ncontainer>();
            return _str->subs();
        }

        using super::canRun;
        wbool canRun(const wtypes& types) const override {
            if (!_str) return false;
            return _str->canRun(types);
        }

        str run(const ncontainer& args) override {
            if (!_str) return str();
            return _str->run(args);
        }

        // tbindable:
        using tbindable::bind;
        wbool bind(const node& it) override {
            if(!it.getType().isImmutable())
                return _str.bind(it);
            return _str.bind((node*) it.clone());
        }

        using tbindable::unbind;
        wbool unbind() override {
            return _str.unbind();
        }

        node& get() {
            return _str.get();
        }
        const node& get() const WRD_UNCONST_FUNC(get())
        template <typename E>
        E& get() {
            node& got = get();
            if(nul(got)) return nulOf<E>();

            return got.template cast<E>();
        }
        template <typename E>
        const E& get() const WRD_UNCONST_FUNC(get<E>())

        using tbindable::canBind;
        wbool canBind(const type& it) const override {
            return _str.canBind(it);
        }

        wbool isBind() const override {
            return _str.isBind();
        }

    private:
        str _str;
    };
}
