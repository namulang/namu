#include "frame.hpp"
#include "../ast/obj.hpp"
#include "../ast/baseFunc.hpp"
#include "../visitor/visitor.hpp"

namespace namu {

    nbool retState::isEmpty() const {
        return false;
    }

    retState::retState() {}

    blkRetState::blkRetState(nbool isOverwritable): _isOverwritable(isOverwritable) {}
    blkRetState::blkRetState() {}

    nbool blkRetState::isOverwritable(const retState& it) const {
        return _isOverwritable;
    }

    blkEmptyRetState::blkEmptyRetState(): super(true) {}

    nbool blkEmptyRetState::isEmpty() const {
        return true;
    }

    nbool funcRetState::isOverwritable(const retState& it) const {
        return isEmpty() || it.isSub<funcRetState>();
    }

    funcRetState::funcRetState() {}

    nbool funcEmptyRetState::isEmpty() const {
        return true;
    }

    funcEmptyRetState::funcEmptyRetState() {}


    NAMU(DEF_ME(frame), DEF_VISIT())

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
        _obj.bind(obj);

        scopes& bottom = *_local.getBottom();
        if(nul(bottom)) return;
        if(nul(obj))
            bottom.unlink();
        else
            bottom.link(obj.subs());
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

    nbicontainer& me::getTop() {
        if(_local.chainLen() > 0)
            return _local.getTop()->getContainer();
        if(_obj)
            return _obj->subs();

        static dumScope inner;
        return inner;
    }

    tstr<scopes> me::popLocal() {
        if(*_retState == BLK_RET)
            relRet();
        return _local.pop();
    }
    // I won't provide API for poping a single node from the scope.

    void me::pushFunc(baseFunc& new1) {
        _funcs.push_back(tstr<baseFunc>(new1));
    }

    void me::popFunc() {
        _funcs.pop_back();
    }

    baseFunc& me::getFunc() {
        if(_funcs.size() <= 0) return nulOf<baseFunc>();
        return *_funcs.back();
    }

    baseObj& me::getMe() {
        return *_obj;
    }

    // node:
    nbicontainer& me::subs() {
        scopes& top = *_local.getTop();
        if(!nul(top)) return top;
        if(_obj) return _obj->subs();

        static dumScope inner;
        return inner;
    }

    priority me::prioritize(const args& a) const {
        return NO_MATCH;
    }

    str me::run(const args& a) {
        return str();
    }

    void me::rel() {
        _rel();
        super::rel();
    }

    void me::relRet() {
        _retState.bind(BLK_EMPTY);
        _ret.rel();
    }

    nbool me::setRet(const retState& new1) {
        return setRet(new1, nulOf<node>());
    }
    nbool me::setRet(const retState& new1, const node& toRet) {
        if(_retState && !_retState->isOverwritable(new1)) return true;

        _retState.bind(new1);
        return _ret.bind(toRet);
    }

    const retState& me::getRetState() const {
        return *_retState;
    }

    node& me::getRet() const {
        return *_ret;
    }

    void me::_rel() {
        _obj.rel();
        _funcs.clear();
        _local.rel();
        relRet();
    }
}
