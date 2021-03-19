#include "Instance.hpp"
#include "Instancer.hpp"

namespace wrd {

    WRD_DEF_THIS(Instance)
    This::Vault Instance::_vault;

    This::Instance() { _id.chkN = _vault.get(this); }
    This::Instance(Id id): _id(id) {} // no binding required.
    This::Instance(const This& rhs) {
        _id.chkN = _vault.get(this); // _id is only belonged to the instance. not able to be copied.
    }
    This::~Instance() { _getMgr().unbind(*this); }

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

    const BindTag& This::getBindTag() const { return BindTag::getBindTag(getId()); }

    // rel() have not to reset Id. it's regarding to instance info.
    // as long as instance keep alive, that info need to be stuck to instance.

    wbool This::_setId(Id new1) {
        _id = new1;
        return true;
    }

    Instancer& This::_getMgr() { return Instancer::get(); }

    wbool This::Vault::set(void* rcver, widx chkN) {
        if(nul(rcver)) return false;

        _vaults[rcver] = chkN;
        return true;
    }

    widx This::Vault::get(void* rcver) {
        auto e = _vaults.find(rcver);
        widx ret = e == _vaults.end() ? WRD_INDEX_ERROR : _vaults[rcver];
        if(ret > WRD_INDEX_ERROR)
            _vaults.erase(rcver);

        return ret;
    }

    wbool This::Vault::rel() { return set(NULL, WRD_INDEX_ERROR); }
}
