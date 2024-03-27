#include "namuSyntaxTest.hpp"

typedef namuSyntaxTest me;

void me::TearDown() {
    namuTest::TearDown();
    _rel();
}

namu::node& me::getSubPack() {
    return _ip.getSubPack();
}

const namu::node& me::getSubPack() const {
    return _ip.getSubPack();
}

namu::slot& me::getSlot() {
    return _ip.getSlot();
}

const namu::slot& me::getSlot() const {
    return _ip.getSlot();
}

namu::errReport& me::getReport() {
    return _rpt;
}

namuSyntaxTest& me::make(const std::string& name) {
    return make(namu::manifest(name));
}

namuSyntaxTest& me::make() {
    return make(namu::manifest());
}

namuSyntaxTest& me::make(const namu::manifest& mani) {
    _rel();
    _ip.setSlot(*new namu::slot(mani));
    return *this;
}

namuSyntaxTest& me::parse(const namu::nchar* src) {
    std::vector<std::string> srcs;
    srcs.push_back(src);
    namu::bufferSrcSupply buf(srcs);
    namu::nbool isVerbose = namu::logger::get().isEnable();

    _ip.setSrcSupply(buf)
       .setLogStructure(isVerbose)
       .setReport(_rpt)
       .interpret();
    _ip.log();
    return *this;
}

namuSyntaxTest& me::negative() {
    namuTest::negative();
    return *this;
}

namu::nbool me::shouldParsed(namu::nbool expect) {
    namu::nbool ret = _ip.isParsed();
    EXPECT_EQ(ret, expect);
    return ret;
}

namu::nbool me::shouldVerified(namu::nbool expect) {
    namu::nbool ret = _ip.isVerified();
    EXPECT_EQ(ret, expect);
    return ret;
}

namu::str me::run() {
    namu::starter s;
    namu::args a;
    a.setMe(getSubPack());

    return s.run(a);
}

void me::_rel() {
    _src = "";
    _rpt.rel();
    _ip.rel();
}
