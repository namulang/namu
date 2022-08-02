#pragma once

#include "common/dep.hpp"
#include <iostream>

struct namuTest : public ::testing::Test {
    void SetUp() {
        _assertVault();
    }

    void TearDown() {
        _assertVault();
    }

protected:
    namu::instance::vault& _getVault() {
        return namu::instance::_vault;
    }

private:
    void _assertVault() {
        auto& v = _getVault();
        WRD_DI("vault[%x].len()=%d", &v, v.len());
        ASSERT_EQ(v.len(), 0);
    }
};
