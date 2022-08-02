#include "instance.hpp"
#include "instancer.hpp"

namespace namu {

    NAMU_DEF_ME(instance)
    me::vault instance::_vault;

    me::instance() { _id.chkN = _vault.get(this); }
    me::instance(id newId): _id(newId) {} // no binding required.
    me::instance(const me& rhs) {
        _id.chkN = _vault.get(this); // _id is only belonged to the instance. not able to be copied.
    }
    me::~instance() { _getMgr().rel(*this); }

    ncnt me::vault::len() const { return _vaults.size(); }

    std::map<void*, int>& me::vault::getVaults() {
        return _vaults;
    }

    void* me::operator new(size_t sz) { return _getMgr()._new1(sz); }
    void me::operator delete(void* pt, size_t sz) { _getMgr()._del(pt, sz); }

    id me::getId() const {
        if(_id.tagN == NAMU_INDEX_ERROR)
            _getMgr().bind((me&)*this);
        return _id;
    }

    nbool me::isHeap() const {
        return _id.isHeap();
    }

    const bindTag& me::getBindTag() const { return bindTag::getBindTag(getId()); }

    // rel() have not to reset Id. it's regarding to instance info.
    // as long as instance keep alive, that info need to be stuck to instance.

    nbool me::_setId(id new1) {
        _id = new1;
        return true;
    }

    instancer& me::_getMgr() { return instancer::get(); }

    nbool me::vault::set(void* rcver, nidx chkN) {
        if(nul(rcver)) return false;

        _vaults[rcver] = chkN;
        return true;
    }

    nidx me::vault::get(void* rcver) {
        auto e = _vaults.find(rcver);
        nidx ret = e == _vaults.end() ? NAMU_INDEX_ERROR : _vaults[rcver];
        if(ret > NAMU_INDEX_ERROR)
            _vaults.erase(rcver);

        return ret;
    }

    nbool me::vault::rel() { return set(NULL, NAMU_INDEX_ERROR); }
}
