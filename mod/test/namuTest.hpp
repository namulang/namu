#pragma once

#include "common/dep.hpp"
#include <iostream>

struct namuTest : public ::testing::Test {
    void SetUp();

    void TearDown();

    namuTest& negative();

protected:
    namu::instance::vault& _getVault();

private:
    void _assertVault();

private:
    namu::nbool _prevShowCallstack;
};
