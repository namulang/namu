#include "bindTag.hpp"
#include "../interface/instancer.hpp"
#include "../bind/tbindable.inl"

namespace wrd {

    WRD_DEF_ME(bindTag)

    me::bindTag() : _pt(NULL), _strong(0) {}
    me::bindTag(id newId) : _pt(NULL), _strong(0), _id(newId) {}
    me::~bindTag() {
        _id.serial = 0;
    }

    const chunk& me::getChunk() const {
        if(!_pt)
            return nulOf<chunk>();

        return instancer::get().getPool()[*_pt][*_pt];
    }

    wcnt me::getStrongCnt() const { return _strong; }

    wbool me::unbind() {
        if(_pt && _id.isHeap()) {
            WRD_DI("bindTag(chkN=%d) deletes instance(%x)", _id.chkN, _pt);
            delete _pt;
        }

        _pt = nullptr;
        _strong = 0;
        return true;
    }

    wbool me::isBind() const { return _pt; }
    const type& me::getBindable() const { return ttype<instance>::get(); }
    wbool me::canBind(const type& type) const { return type.isSub(getBindable()); }
    id me::getId() const { return _id; }
    wbool me::rel() { return unbind(); }

    wbool me::_onStrong(wcnt vote) {
        if(!_id.isHeap()) return false;
        if(!vote) {
            WRD_I("vote is 0");
            return false;
        }

        _strong += vote;
        if(_strong <= 0)
            unbind();
        return true;
    }

    instance& me::get() { return *_pt; }

    wbool me::bind(const instance& it) {
        unbind();

        _pt = (instance*) &it;
        return _completeId(*_pt);
    }

    wbool me::_completeId(instance& it) {
        //  complete mine:
        id mine = getId();
        mine.chkN = it._id.chkN;
        //  propagate it:
        return _sync(mine);
    }

    wbool me::_sync(id new1) {
        if(_pt)
            _pt->_setId(new1);
        _id = new1;
        return true;
    }

    const bindTag& me::getBindTag(id newId) {
        return const_cast<bindTag&>(WRD_GETS(instancer::get().getWatcher()[newId], blk));
    }
 }
