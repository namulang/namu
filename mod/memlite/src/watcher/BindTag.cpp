#include "BindTag.hpp"
#include "../interface/Instancer.hpp"
#include "../bind/TBindable.inl"

namespace wrd {

    WRD_DEF_THIS(BindTag)

    This::BindTag() : _pt(NULL), _strong(0) {}
    This::BindTag(Id id) : _pt(NULL), _strong(0), _id(id) {}
    This::~BindTag() {
        _id.serial = 0;
    }

    const Chunk& This::getChunk() const {
        if(!_pt)
            return nulOf<Chunk>();

        return Instancer::get().getPool()[*_pt][*_pt];
    }

    wcnt This::getStrongCnt() const { return _strong; }

    wbool This::unbind() {
        if(_pt && _id.isHeap()) {
            WRD_DI("BindTag(chkN=%d) deletes instance(%x)", _id.chkN, _pt);
            delete _pt;
        }

        _pt = nullptr;
        _strong = 0;
        return true;
    }

    wbool This::isBind() const { return _pt; }
    const Type& This::getBindable() const { return TType<Instance>::get(); }
    wbool This::canBind(const Type& type) const { return type.isSub(getBindable()); }
    Id This::getId() const { return _id; }
    wbool This::rel() { return unbind(); }

    wbool This::_onStrong(wcnt vote) {
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

    Instance& This::get() { return *_pt; }

    wbool This::bind(const Instance& it) {
        unbind();

        _pt = (Instance*) &it;
        return _completeId(*_pt);
    }

    wbool This::_completeId(Instance& it) {
        //  complete mine:
        Id mine = getId();
        mine.chkN = it._id.chkN;
        //  propagate it:
        return _sync(mine);
    }

    wbool This::_sync(Id new1) {
        if(_pt)
            _pt->_setId(new1);
        _id = new1;
        return true;
    }
 }
