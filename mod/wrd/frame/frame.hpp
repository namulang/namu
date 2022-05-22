#pragma once

#include "../ast/node.hpp"
#include "scopeStack.hpp"
#include "../builtin/res/tpair.hpp"

struct frameTest;

namespace wrd {

    class _wout frame : public node { // TODO: may be obj, not node.
        WRD(CLASS(frame, node))
        friend struct ::frameTest;

    public:
        ~frame() {
            _rel();
        }

        /*/// @return returns tpair<node, itsOwner>. the owner has the container holding the node
        ///         which can run with given name & argument.
        tpair<str, str> subAndOwner(const std::string& name, const ucontainable& args) {
            scopes& chn = subs().cast<scopes>();
            if(nul(chn)) return tpair<str, str>();

            for(scopes* e=&chn; e ;e=&e->getNext()) {
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
        }*/

        wbool pushLocal(nbicontainer* con) { return pushLocal(*con); }
        wbool pushLocal(nbicontainer& con) { return pushLocal(*scopes::wrap(con)); }
        wbool pushLocal(scopes* new1) { return _local.push(*new1); }
        wbool pushLocal(scopes& new1) {
            wbool ret = _local.push(new1);
            if(ret && _local.chainLen() == 1 && _obj)
                new1.link(_obj->subs());
            return ret;
        }
        wbool pushLocal(const std::string& name, node& n) {
            scopes& top = *_local.getTop();
            if(nul(top))
                return WRD_E("couldn't push new node. the top scope is null"), false;

            return top.add(name, n);
        }
        wbool pushLocal(const std::string& name, node* n) {
            return pushLocal(name, *n);
        }

        scopes& getTop() { return *_local.getTop(); }
        const scopes& getTop() const WRD_UNCONST_FUNC(getTop())

        tstr<scopes> popLocal() { return _local.pop(); }
        // I won't provide API for poping a single node from the scope.

        void setObj(const obj& new1) {
            _obj.bind(new1);
            scopes& bottom = *_local.getBottom();
            if(!nul(bottom)) {
                if(nul(new1))
                    bottom.unlink();
                else
                    bottom.link(new1.subs());
            }
        }

        const obj& getObj() const { return *_obj; }
        obj& getObj() { return *_obj; }

        void setFunc(func& new1) {
            _func.bind(new1);
        }

        func& getFunc() {
            return *_func;
        }

        const func& getFunc() const WRD_UNCONST_FUNC(getFunc())

        void clearObj() {
            setObj(nulOf<obj>());
        }

        // node:
        using node::subs;
        nbicontainer& subs() override {
            scopes& top = *_local.getTop();
            return nul(top) ? _obj->subs() : top;
        }

        wbool canRun(const ucontainable& args) const override { return false; }

        str run(const ucontainable& args) override { return str(); }
        void rel() override {
            _rel();
            super::rel();
        }

        wbool pushReturn(const str& toReturn) { return _ret.bind(*toReturn); }
        wbool isReturned() const { return _ret.isBind(); }
        str popReturn() {
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

    private:
        tstr<obj> _obj;
        tstr<func> _func;
        scopeStack _local;
        str _ret;
    };
}
