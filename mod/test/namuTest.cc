#include "namuTest.hpp"

typedef namuTest me;

void me::SetUp() {
    _assertVault();
}

void me::TearDown() {
    _assertVault();
}

namu::instance::vault& me::_getVault() {
    return namu::instance::_vault;
}

void me::_assertVault() {
    auto& v = _getVault();
    NAMU_DI("vault[%x].len()=%d", &v, v.len());
    ASSERT_EQ(v.len(), 0);
}
