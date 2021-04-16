#pragma once

#include "../ast/Node.hpp"

namespace wrd {

    class Frame : public Node { // TODO: may be Obj, not Node.
        WRD_CLASS(Frame, Node)

    public:
        ~Frame() {
            _rel();
        }

        wbool push(NContainer& con) {
            NChain* chn = &con.cast<NChain>();
            if(nul(chn))
                chn = new NChain(con);

            return push(*chn);
        }

        wbool push(NChain& new1) {
            WRD_DI("Stack(%x).push(Chain(%x))", this, &new1);

            if(_links)
                new1.link(*_links);
            return _links.bind(new1);
        }

        TStr<NChain> pop() {
            TStr<NChain> ret;
            if(_links) {
                ret.bind(*_links);
                _links.bind(_links->getNext());
            }
            WRD_DI("Stack(%x).pop(%x), .next=%x", &ret.get(), &*_links);
            return ret;
        }

        // Node:
        using Node::subs;
        NContainer& subs() override { return *_links; }
        wbool canRun(const WTypes& types) const override { return false; }
        Str run(NContainer& args) override { return Str(); }
        void rel() override {
            _rel();
            super::rel();
        }

    private:
        void _rel() {
            _links.unbind();
        }

        TStr<NChain> _links;
    };

}
