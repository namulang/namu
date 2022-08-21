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

    namuSyntaxTest& parse(const namu::nchar* src) {
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

    namu::nbool shouldParsed(namu::nbool well) {
        namu::nbool ret = _ip.isParsed();
        EXPECT_EQ(ret, well);
        return ret;
    }
    namu::nbool shouldVerified(namu::nbool well) {
        namu::nbool ret = _ip.isVerified();
        EXPECT_EQ(ret, well);
        return ret;
    }
    namu::str run() {
        namu::starter s;
        namu::args a;
        a.setMe(getSubPack());
        return s.run(a);
    }

private:
    void _rel() {
        _src = "";
        _rpt.rel();
        _ip.rel();
    }

private:
    const namu::nchar* _src;
    namu::errReport _rpt;
    namu::interpreter _ip;
};
