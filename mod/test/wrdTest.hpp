#pragma once

#include "common/dep.hpp"
#include <iostream>

struct wrdTest : public ::testing::Test {
    void SetUp() {
        _assertVault();
    }

    void TearDown() {
        _assertVault();
    }

protected:
    wrd::instance::vault& _getVault() {
        return wrd::instance::_vault;
    }

private:
    void _assertVault() {
        auto& v = _getVault();
        WRD_DI("vault[%x].len()=%d", &v, v.len());
        ASSERT_EQ(v.len(), 0);
    }
};
