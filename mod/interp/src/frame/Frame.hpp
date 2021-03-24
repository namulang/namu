#pragma once

#include "../ast/Node.hpp"

namespace wrd {

    class Frame : public Node { // TODO: may be Obj, not Node.
        WRD_CLASS(Frame, Node)

    public:
        const NChain& getObjs() const { return *_objs; }
        const NChain& getLocals() const { return *_locals; }

        wbool setObjs(NChain& objScope) {
            if(!_objs.bind(objScope)) return false;

            if(_locals)
                return _locals->link(objScope);
            return true;
        }

        wbool addLocals(NArr& localScope) {
            NChain* new1 = new NChain(localScope);
            NChain& newNext = _locals ? *_locals : *_objs;

            new1->link(newNext);
            return _locals.bind(new1);
        }

        // Node:
        NContainer& subs() override { return *_locals; }
        wbool canRun(const WTypes& types) const override { return false; }
        Str run(NContainer& args) override { return Str(); }
        void rel() override {
            _objs.unbind();
            _locals.unbind();

            Super::rel();
        }

    private:
        TStr<NChain> _objs;
        TStr<NChain> _locals;
    };

}
