#pragma once

#include "../ast/node.hpp"
#include "scopeStack.hpp"
#include "../builtin/res/tpair.hpp"

struct frameTest;

namespace wrd {

    class frame : public node { // TODO: may be obj, not node.
        WRD(CLASS(frame, node))
        friend struct ::frameTest;

    public:
        ~frame() {
            _rel();
        }

        /// @return returns tpair<node, itsOwner>. the owner has the container holding the node
        ///         which can run with given name & argument.
        tpair<str, str> subAndOwner(const std::string& name, const containable& args) {
            nchain& chn = subs().cast<nchain>();
            if(nul(chn)) return tpair<str, str>();

            for(auto e=chn.beginChain(); e ;++e) {
                node& owner = _getOwnerFrom(*e);
                if(nul(owner)) {
                    WRD_W("couldn't find owner from chain[%x]", &e.get());
                    continue;
                }

                node& ret = owner.sub(name, args);
                if(nul(ret)) continue;

                return tpair<str, str>(str(owner), str(ret));
            }

            return tpair<str, str>();
        }

        wbool pushLocal(ncontainer* con) { return pushLocal(*con); }
        wbool pushLocal(ncontainer& con) { return pushLocal(*nchain::wrap(con)); }
        wbool pushLocal(nchain* new1) { return _local.push(*new1); }
        wbool pushLocal(nchain& new1) {
            wbool ret = _local.push(new1);
            if(ret && _local.chainLen() == 1)
                new1.link(*_obj);
            return ret;
        }

        tstr<nchain> popLocal() { return _local.pop(); }

        void setObj(ncontainer& con) { setObj(*nchain::wrap(con)); }
        void setObj(nchain& new1) {
            _obj.bind(new1);
            nchain& bottom = *_local.getBottom();
            if(!nul(bottom))
                bottom.link(new1);
        }
        void clearObj() {
            setObj(nulOf<nchain>());
        }

        // node:
        using node::subs;
        ncontainer& subs() override {
            nchain& top = *_local.getTop();
            return nul(top) ? *_obj : top;
        }

        using super::canRun;
        wbool canRun(const wtypes& types) const override { return false; }

        str run(const containable& args) override { return str(); }
        void rel() override {
            _rel();
            super::rel();
        }

    private:
        void _rel() {
            _obj.rel();
            _local.rel();
        }

        node& _getOwnerFrom(containable& con) {
            // TODO: use hashmap. save ptr into hashmap when all of pushXXX() funcs called.
            return nulOf<node>(); // TODO: remove this line
        }

    private:
        tstr<nchain> _obj;
        scopeStack _local;
    };
}
