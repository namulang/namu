#include "BindTag.hpp"
#include "../interface/Instancer.hpp"
#include "../bind/TBindable.inl"

namespace wrd {

    WRD_DEF_THIS(BindTag, Instance)

    This::BindTag() : Super(), _pt(NULL), _strong(0) {}
    This::BindTag(Id id) : Super(id), _pt(NULL), _strong(0) {}

    Chunk& This::getChunk() {
        if(!_pt)
            return nulOf<Chunk>();

        return Instancer::get().getPool()[*_pt][*_pt];
    }

    wcnt This::getStrongCnt() { return _strong; }

    wbool This::unbind() {
        if(_pt && isHeap())
            delete _pt;
        _pt = WRD_NULL;
        _strong = 0;
        return true;
    }

    wbool This::isBind() { return _pt; }
    Type& This::getBindable() { return TType<Instance>::get(); }
    wbool This::canBind(Type& type) { return type.isSub(getBindable()); }
    Id This::getId() { return _id; }
    wbool This::isHeap() { return _id.s.chkN != WRD_INDEX_ERROR; }
    wbool This::rel() { return unbind(); }

    wbool This::_onStrong(wcnt vote) {
        if(!isHeap()) return false;
        if(!vote) {
            WRD_I("vote is 0");
            return false;
        }

        _strong += vote;
        if(_strong <= 0)
            unbind();
        return true;
    }

    Instance& This::_get() { return *_pt; }

    wbool This::_bind(Instance& it) {
        unbind();

        _pt = (Instance*) &it;
        return _completeId(*_pt);
    }

    wbool This::_completeId(Instance& it) {
        //  complete mine:
        Id mine = getId();
        mine.s.chkN = it._id.s.chkN;
        //  propagate it:
        return _sync(mine);
    }

    wbool This::_sync(Id new1) {
        if(_pt)
            _pt->_setId(new1);
        return _setId(new1);
    }
 }
