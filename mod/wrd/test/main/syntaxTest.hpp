#pragma once

#include "common/dep.hpp"

struct syntaxTest : public ::testing::Test {
    void SetUp() {}
    void TearDown() {}

    wrd::str parse(const wrd::wchar* src) {
        wrd::parser p;
        wrd::str ret = p.parse(src);
        EXPECT_TRUE(ret.isBind()) << "test code: " << src << "\n";
        return ret;
    }

    void parseFail(const wrd::wchar* src) {
        wrd::parser p;
        wrd::str ret = p.parse(src);
        EXPECT_FALSE(ret.isBind()) << "test code: " << src << "\n";
    }

    wrd::wbool assertSame(wrd::str unit, const wrd::wchar* expect) {
        // TODO: run unit and gather output and compare it to expect
        return true;
    }
};
