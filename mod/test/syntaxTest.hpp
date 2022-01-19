#pragma once

#include "common/dep.hpp"

struct syntaxTest : public ::testing::Test {
    void SetUp() {}
    void TearDown() {}

    wrd::str parse(const wrd::wchar* src) {
        wrd::errReport rpt;
        return parse(src, rpt);
    }

    wrd::tstr<wrd::narr> parse(const wrd::wchar* src, wrd::errReport& rpt) {
        wrd::parser p;
        auto ret = p.setReport(rpt).parse(src);
        EXPECT_TRUE(!rpt && ret->len() > 0) << "test code: " << src << "\n";
        return ret;
    }

    void parseFail(const wrd::wchar* src) {
        wrd::errReport rpt;
        parseFail(src, rpt);
    }

    void parseFail(const wrd::wchar* src, wrd::errReport& rpt) {
        wrd::parser p;
        auto ret = p.setReport(rpt).parse(src);
        EXPECT_TRUE(rpt || ret->len() <= 0) << "test code: " << src << "\n";
    }

    wrd::wbool assertSame(wrd::str unit, const wrd::wchar* expect) {
        // TODO: run unit and gather output and compare it to expect
        return true;
    }
};
