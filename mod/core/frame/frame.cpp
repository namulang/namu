#include "frame.hpp"
#include "../ast/obj.hpp"
#include "../ast/func.hpp"

namespace namu {

    NAMU_DEF_ME(frame)

    me::frame() {
        _rel();
    }

    me::~frame() {
        _rel();
    }

    nbool me::pushLocal(nbicontainer* con) { return pushLocal(*con); }
    nbool me::pushLocal(nbicontainer& con) { return pushLocal(*scopes::wrap(con)); }
    nbool me::pushLocal(scopes* new1) { return _local.push(*new1); }
    nbool me::pushLocal(scopes& new1) {
        nbool ret = _local.push(new1);
        if(ret && _local.chainLen() == 1 && _obj)
            new1.link(_obj->subs());
        return ret;
    }
    nbool me::pushLocal(const std::string& name, const node& n) {
        scopes& top = *_local.getTop();
        if(nul(top))
            return NAMU_E("couldn't push new node. the top scope is null"), false;

        return top.add(name, n);
    }
    nbool me::pushLocal(const std::string& name, const node* n) {
        return pushLocal(name, *n);
    }

    void me::pushObj(const baseObj& obj) {
        scopes& bottom = *_local.getBottom();
        if(!nul(bottom)) {
            if(nul(obj))
                bottom.unlink();
            else
                bottom.link(obj.subs());
        }
    }

    namespace {
        thread_local static baseObj* inner = nullptr;
    }

    baseObj& me::_setMe(baseObj& new1) {
        baseObj& ret = *inner;
        inner = &new1;
        return ret;
    }
    baseObj& me::_setMe() {
        return _setMe(nulOf<baseObj>());
    }
    baseObj& me::_getMe() { return *inner; }

    scopes& me::getTop() { return *_local.getTop(); }

    tstr<scopes> me::popLocal() {
        popRet();
        return _local.pop();
    }
    // I won't provide API for poping a single node from the scope.

    void me::setFunc(func& new1) {
        _func.bind(new1);
    }

    func& me::getFunc() {
        return *_func;
    }

    // node:
    nbicontainer& me::subs() {
        scopes& top = *_local.getTop();
        return nul(top) ? _obj->subs() : top;
    }

    nbool me::canRun(const args& a) const { return false; }

    str me::run(const args& a) { return str(); }

    void me::rel() {
        _rel();
        super::rel();
    }

    nbool me::pushRet(const str& toRet) {
        if(_retState == RETURN) return true;

        _retState = RET;
        return _ret.bind(*toRet);
    }
    nbool me::pushReturn(const str& toReturn) {
        _retState = RETURN;
        return _ret.bind(*toReturn);
    }

    frame::retState me::getRetState() const { return _retState; }
    str me::popReturn() {
        str ret = _ret;
        _ret.rel();
        _retState = NO_RET;
        return ret;
    }

    str me::popRet() {
        if(_retState == RETURN) return _ret;
        return popReturn();
    }

    void me::_rel() {
        _obj.rel();
        _func.rel();
        _local.rel();
        popReturn();
    }
}
