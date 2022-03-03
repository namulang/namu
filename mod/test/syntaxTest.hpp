#pragma once

#include "common/dep.hpp"
#include <iostream>

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
        WRD_I("====================================");
        WRD_I("parsing src:");
        WRD_I("%s", src);
        WRD_I("====================================");
        wrd::parser p;
        _subpack = p.setPack(*_pack).setReport(_rpt).parse(_src = src);
        return *this;
    }

    wrd::wbool expect(wrd::wbool expected) const {
        wrd::wbool ret = isSuccess() == expected;
        EXPECT_TRUE(ret);
        if(!ret)
            _log(expected);
        return ret;
    }

    wrd::wbool isSuccess() const {
        return _subpack && _pack && !_rpt;
    }

private:
    void _log(wrd::wbool expected) const {
        std::cout   << "test expected to be " << (expected ? "success" : "fail") << " but it wasn't.\n"
                    << "code: " << _src << "\n"
                    << "errReport:\n";
        _rpt.log();
    }

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
