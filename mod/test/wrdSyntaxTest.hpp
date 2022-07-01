#pragma once

#include "wrdTest.hpp"
#include <iostream>

struct wrdSyntaxTest : public wrdTest {
    void TearDown() {
        wrdTest::TearDown();
        _rel();
    }

    wrd::node& getSubPack() { return _ip.getSubPack(); }
    const wrd::node& getSubPack() const { return _ip.getSubPack(); }
    wrd::slot& getSlot() { return _ip.getSlot(); }
    const wrd::slot& getSlot() const { return _ip.getSlot(); }
    wrd::errReport& getReport() { return _rpt; }

    wrdSyntaxTest& make(const std::string& name) {
        return make(wrd::manifest(name));
    }

    wrdSyntaxTest& make() {
        return make(wrd::manifest());
    }

    wrdSyntaxTest& make(const wrd::manifest& mani) {
        _rel();
        _ip.setSlot(*new wrd::slot(mani));
        return *this;
    }

    wrdSyntaxTest& parse(const wrd::wchar* src) {
        std::vector<std::string> srcs;
        srcs.push_back(src);
        wrd::bufferSrcSupply buf(srcs);

        _ip.setSrcSupply(buf)
           .setLogInterpreter(true)
           .setLogStructure(true)
           .setReport(_rpt)
           .interpret();
        return *this;
    }

    wrd::wbool shouldParsed(wrd::wbool well) {
        wrd::wbool ret = _ip.isParsed();
        EXPECT_EQ(ret, well);
        return ret;
    }
    wrd::wbool shouldVerified(wrd::wbool well) {
        wrd::wbool ret = _ip.isVerified();
        EXPECT_EQ(ret, well);
        return ret;
    }
    wrd::str run() {
        wrd::starter s;
        return s.run(wrd::narr(getSubPack()));
    }

private:
    void _rel() {
        _src = "";
        _rpt.rel();
        _ip.rel();
    }

private:
    const wrd::wchar* _src;
    wrd::errReport _rpt;
    wrd::interpreter _ip;
};
