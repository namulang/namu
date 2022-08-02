#pragma once

#include "namuTest.hpp"
#include <iostream>

struct namuSyntaxTest : public namuTest {
    void TearDown() {
        namuTest::TearDown();
        _rel();
    }

    namu::node& getSubPack() { return _ip.getSubPack(); }
    const namu::node& getSubPack() const { return _ip.getSubPack(); }
    namu::slot& getSlot() { return _ip.getSlot(); }
    const namu::slot& getSlot() const { return _ip.getSlot(); }
    namu::errReport& getReport() { return _rpt; }

    namuSyntaxTest& make(const std::string& name) {
        return make(namu::manifest(name));
    }

    namuSyntaxTest& make() {
        return make(namu::manifest());
    }

    namuSyntaxTest& make(const namu::manifest& mani) {
        _rel();
        _ip.setSlot(*new namu::slot(mani));
        return *this;
    }

    namuSyntaxTest& parse(const namu::wchar* src) {
        std::vector<std::string> srcs;
        srcs.push_back(src);
        namu::bufferSrcSupply buf(srcs);

        _ip.setSrcSupply(buf)
           .setLogInterpreter(true)
           .setLogStructure(true)
           .setReport(_rpt)
           .interpret();
        return *this;
    }

    namu::wbool shouldParsed(namu::wbool well) {
        namu::wbool ret = _ip.isParsed();
        EXPECT_EQ(ret, well);
        return ret;
    }
    namu::wbool shouldVerified(namu::wbool well) {
        namu::wbool ret = _ip.isVerified();
        EXPECT_EQ(ret, well);
        return ret;
    }
    namu::str run() {
        namu::starter s;
        return s.run(namu::narr(getSubPack()));
    }

private:
    void _rel() {
        _src = "";
        _rpt.rel();
        _ip.rel();
    }

private:
    const namu::wchar* _src;
    namu::errReport _rpt;
    namu::interpreter _ip;
};
