#include "Instance.hpp"
#include "Instancer.hpp"

namespace wrd {

    WRD_DEF_THIS(Instance)
    This::Vault Instance::_vault;

    This::Instance() { _id.chkN = _vault.get(this); }
    This::Instance(Id id) : _id(id) {} // no binding required.
    This::~Instance() { _getMgr().unbind(*this); }

    wbool This::operator==(const This& rhs) const { return _id == rhs._id; }
    wbool This::operator!=(const This& rhs) const { return !operator==(rhs); }
    void* This::operator new(size_t sz) { return _getMgr()._new1(sz); }
    void This::operator delete(void* pt, size_t sz) { _getMgr()._del(pt, sz); }

    Id This::getId() const {
        if(_id.tagN == WRD_INDEX_ERROR)
            _getMgr().bind((This&)*this);
        return _id;
    }

    wbool This::isHeap() const {
        return _id.isHeap();
    }

    const BindTag& This::getBindTag() const { return _getBindTag(getId()); }

    // rel() have not to reset Id. it's regarding to instance info.
    // as long as instance keep alive, that info need to be stuck to instance.

    BindTag& This::_getBindTag(Id id) {
        return const_cast<BindTag&>(WRD_GETS(_getMgr().getWatcher()[id], blk));
    }

    wbool This::_setId(Id new1) {
        _id = new1;
        return true;
    }

    Instancer& This::_getMgr() { return Instancer::get(); }

    wbool This::Vault::set(void* rcver, widx chkN) {
        _rcver = rcver;
        _chkN = chkN;
        return true;
    }

    widx This::Vault::get(void* rcver) {
        //  pre:
        if( ! _rcver) return WRD_INDEX_ERROR;

        //  main:
        widx ret = _chkN;
        if(rcver != _rcver) {
            WRD_W("rcver(%x) != _rcver(%x)", rcver, _rcver);
            ret = WRD_INDEX_ERROR;
        }

        set(NULL, WRD_INDEX_ERROR);
        return ret;
    }

    wbool This::Vault::rel() { return set(NULL, WRD_INDEX_ERROR); }
}
