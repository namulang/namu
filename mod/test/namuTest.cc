#include "namuTest.hpp"

typedef namuTest me;

void me::SetUp() {
    _assertVault();
    _prevShowCallstack = namu::logger::get().isShowCallstack();
}

void me::TearDown() {
    _assertVault();
    namu::logger::get().setCallstack(_prevShowCallstack);
}

namuTest& me::negative() {
    namu::logger::get().setCallstack(false);
    return *this;
}

namu::instance::vault& me::_getVault() {
    return namu::instance::_vault;
}

void me::_assertVault() {
    auto& v = _getVault();
    NAMU_DI("vault[%x].len()=%d", &v, v.len());
    ASSERT_EQ(v.len(), 0);
}
