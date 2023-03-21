#include "instance.hpp"
#include "instancer.hpp"
#include <vector>
#include <iostream>

namespace namu {

    NAMU_DEF_ME(instance)
    me::vault instance::_vault;

    me::instance() { _id.chkN = _vault.get(); }
    me::instance(id newId): _id(newId) {} // no binding required.
    me::instance(const me& rhs) {
        _id.chkN = _vault.get(); // _id is only belonged to the instance. not able to be copied.
    }
    me::~instance() { _getMgr().rel(*this); }

    ncnt me::vault::len() const { return _vaults.size(); }

    std::vector<int>& me::vault::getVaults() {
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

    void me::vault::set(nidx chkN) {
        _vaults.push_back(chkN);
    }

    nidx me::vault::get() {
        if (_vaults.size() <= 0)
            return NAMU_INDEX_ERROR;

        auto res = _vaults.back();
        _vaults.pop_back();
        return res;
    }

    nbool me::vault::rel() {
        _vaults.clear();
        return true;
    }
}
