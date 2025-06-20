#include "test/namuTest.hpp"

typedef namuTest me;

void me::SetUp() {
    _assertVault();

    thr.bind(new nm::thread());
    nm::thread::set(*thr);
}

void me::TearDown() {
    _assertVault();

    nm::thread::set(nullptr);
    thr.rel();
}

nm::instance::vault& me::_getVault() { return nm::instance::_vault; }

void me::_assertVault() {
    auto& v = _getVault();
    NM_DI("vault[%s].len()=%d", &v, v.len());
    ASSERT_EQ(v.len(), 0);
}
