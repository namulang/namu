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

        str run(ncontainer& args) override {
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

        using tbindable::canBind;
        wbool canBind(const type& it) const override {
            return _str.canBind(it);
        }

        wbool isBind() const override {
            return _str.isBind();
        }

        using tbindable::get;
        node& get() override {
            return _str.get();
        }

    private:
        str _str;
    };
}
