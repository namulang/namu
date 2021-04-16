#include "BindTag.hpp"
#include "../interface/Instancer.hpp"
#include "../bind/TBindable.inl"

namespace wrd {

    WRD_DEF_ME(BindTag)

    me::BindTag() : _pt(NULL), _strong(0) {}
    me::BindTag(Id id) : _pt(NULL), _strong(0), _id(id) {}
    me::~BindTag() {
        _id.serial = 0;
    }

    const Chunk& me::getChunk() const {
        if(!_pt)
            return nulOf<Chunk>();

        return Instancer::get().getPool()[*_pt][*_pt];
    }

    wcnt me::getStrongCnt() const { return _strong; }

    wbool me::unbind() {
        if(_pt && _id.isHeap()) {
            WRD_DI("BindTag(chkN=%d) deletes instance(%x)", _id.chkN, _pt);
            delete _pt;
        }

        _pt = nullptr;
        _strong = 0;
        return true;
    }

    wbool me::isBind() const { return _pt; }
    const Type& me::getBindable() const { return TType<Instance>::get(); }
    wbool me::canBind(const Type& type) const { return type.isSub(getBindable()); }
    Id me::getId() const { return _id; }
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

    Instance& me::get() { return *_pt; }

    wbool me::bind(const Instance& it) {
        unbind();

        _pt = (Instance*) &it;
        return _completeId(*_pt);
    }

    wbool me::_completeId(Instance& it) {
        //  complete mine:
        Id mine = getId();
        mine.chkN = it._id.chkN;
        //  propagate it:
        return _sync(mine);
    }

    wbool me::_sync(Id new1) {
        if(_pt)
            _pt->_setId(new1);
        _id = new1;
        return true;
    }

    const BindTag& me::getBindTag(Id id) {
        return const_cast<BindTag&>(WRD_GETS(Instancer::get().getWatcher()[id], blk));
    }
 }
