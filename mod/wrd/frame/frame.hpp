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
        wbool pushLocal(node& n) {
            nchain& scope = *_local.getTop();
            if(nul(scope))
                return WRD_E("couldn't push new node. the top scope is null"), false;

            containable& con = scope.getContainer();
            return con.add(con.begin(), n);
        }

        tstr<nchain> popLocal() { return _local.pop(); }
        // I won't provide API for poping a single node from the scope.

        void setObj(ncontainer& con) { setObj(*nchain::wrap(con)); }
        void setObj(nchain& new1) {
            _obj.bind(new1);
            nchain& bottom = *_local.getBottom();
            if(!nul(bottom))
                bottom.link(new1);
        }

        void setFunc(func& new1) {
            _func.bind(new1);
        }

        func& getFunc() {
            return *_func;
        }

        const func& getFunc() const WRD_UNCONST_FUNC(getFunc())

        void clearObj() {
            setObj(nulOf<nchain>());
        }

        // node:
        using node::subs;
        ncontainer& subs() override {
            nchain& top = *_local.getTop();
            return nul(top) ? *_obj : top;
        }

        wbool canRun(const containable& args) const override { return false; }

        str run(const containable& args) override { return str(); }
        void rel() override {
            _rel();
            super::rel();
        }

        wbool pushReturn(const str& toReturn) const { return _ret.bind(*toReturn); }
        wbool isReturned() const { return _ret.isBind(); }
        str popReturn() const {
            str ret = _ret;
            _ret.rel();
            return ret;
        }

    private:
        void _rel() {
            _obj.rel();
            _func.rel();
            _local.rel();
        }

        node& _getOwnerFrom(containable& con) {
            // TODO: use hashmap. save ptr into hashmap when all of pushXXX() funcs called.
            return nulOf<node>(); // TODO: remove this line
        }

    private:
        tstr<nchain> _obj;
        tstr<func> _func;
        scopeStack _local;
        mutable str _ret;
    };
}
