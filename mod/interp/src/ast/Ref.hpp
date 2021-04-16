#pragma once

#include "Node.hpp"

namespace wrd {

    class Ref : public Node, public TBindable<Node> {
        WRD_CLASS(Ref, Node)

    public:
        Ref() {}
        explicit Ref(const Node& new1): _str(new1) {}
        explicit Ref(const Node* new1): _str(new1) {}

        // Node:
        NContainer& subs() override {
            if (!_str) return nulOf<NContainer>();
            return _str->subs();
        }

        using super::canRun;
        wbool canRun(const WTypes& types) const override {
            if (!_str) return false;
            return _str->canRun(types);
        }

        Str run(NContainer& args) override {
            if (!_str) return Str();
            return _str->run(args);
        }

        // TBindable:
        using TBindable::bind;
        wbool bind(const Node& it) override {
            return _str.bind(it);
        }

        using TBindable::unbind;
        wbool unbind() override {
            return _str.unbind();
        }

        using TBindable::canBind;
        wbool canBind(const Type& it) const override {
            return _str.canBind(it);
        }

        wbool isBind() const override {
            return _str.isBind();
        }

        using TBindable::get;
        Node& get() override {
            return _str.get();
        }

    private:
        Str _str;
    };
}
