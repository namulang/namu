#pragma once

#include "common/dep.hpp"
#include <iostream>

struct namuTest : public ::testing::Test {
    void SetUp() {
        _assertVault();
        _prevShowCallstack = namu::logger::get().isShowCallstack();
    }

    void TearDown() {
        _assertVault();
        namu::logger::get().setCallstack(_prevShowCallstack);
    }

public:
    namuTest& negative() {
        namu::logger::get().setCallstack(false);
        return *this;
    }

protected:
    namu::instance::vault& _getVault() {
        return namu::instance::_vault;
    }

private:
    void _assertVault() {
        auto& v = _getVault();
        NAMU_DI("vault[%x].len()=%d", &v, v.len());
        ASSERT_EQ(v.len(), 0);
    }

private:
    namu::nbool _prevShowCallstack;
};
