#pragma once

#include "common/dep.hpp"

struct syntaxTest : public ::testing::Test {
    void SetUp() {}
    void TearDown() { _rel(); }

    wrd::node& getSubPack() { return *_subpack; }
    wrd::pack& getPack() { return *_pack; }
    wrd::errReport& getReport() { return _rpt; }

    syntaxTest& make() {
        return make(wrd::manifest());
    }

    syntaxTest& make(const wrd::manifest& mani) {
        _rel();
        _pack.bind(new wrd::pack(mani, wrd::packLoadings()));
        return *this;
    }

    syntaxTest& parse(const wrd::wchar* src) {
        wrd::parser p;
        _subpack = p.setReport(_rpt).parse(_src = src);
        return *this;
    }

    wrd::wbool isSuccess() const {
        return _subpack && _subpack->subs().len() > 0 && !_rpt;
    }

    void expect(wrd::wbool success) const {
        EXPECT_TRUE(isSuccess() == success) << "test code: " << _src << "\n";
    }

    void should(wrd::wbool success) const {
        ASSERT_TRUE(isSuccess() == success) << "test code: " << _src << "\n";
    }

private:
    void _rel() {
        _src = "";
        _subpack.rel();
        _pack.rel();
        _rpt.rel();
    }

private:
    const wrd::wchar* _src;
    wrd::str _subpack;
    wrd::tstr<wrd::pack> _pack;
    wrd::errReport _rpt;
};
