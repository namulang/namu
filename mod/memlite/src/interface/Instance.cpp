#include "Instance.hpp"
#include "Instancer.hpp"

namespace wrd {

    WRD_DEF_ME(Instance)
    me::Vault Instance::_vault;

    me::Instance() { _id.chkN = _vault.get(this); }
    me::Instance(Id id): _id(id) {} // no binding required.
    me::Instance(const me& rhs) {
        _id.chkN = _vault.get(this); // _id is only belonged to the instance. not able to be copied.
    }
    me::~Instance() { _getMgr().unbind(*this); }

    void* me::operator new(size_t sz) { return _getMgr()._new1(sz); }
    void me::operator delete(void* pt, size_t sz) { _getMgr()._del(pt, sz); }

    Id me::getId() const {
        if(_id.tagN == WRD_INDEX_ERROR)
            _getMgr().bind((me&)*this);
        return _id;
    }

    wbool me::isHeap() const {
        return _id.isHeap();
    }

    const BindTag& me::getBindTag() const { return BindTag::getBindTag(getId()); }

    // rel() have not to reset Id. it's regarding to instance info.
    // as long as instance keep alive, that info need to be stuck to instance.

    wbool me::_setId(Id new1) {
        _id = new1;
        return true;
    }

    Instancer& me::_getMgr() { return Instancer::get(); }

    wbool me::Vault::set(void* rcver, widx chkN) {
        if(nul(rcver)) return false;

        _vaults[rcver] = chkN;
        return true;
    }

    widx me::Vault::get(void* rcver) {
        auto e = _vaults.find(rcver);
        widx ret = e == _vaults.end() ? WRD_INDEX_ERROR : _vaults[rcver];
        if(ret > WRD_INDEX_ERROR)
            _vaults.erase(rcver);

        return ret;
    }

    wbool me::Vault::rel() { return set(NULL, WRD_INDEX_ERROR); }
}
