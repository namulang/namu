#pragma once

#include "wrdTest.hpp"
#include <iostream>

struct wrdSyntaxTest : public wrdTest {
    void TearDown() {
        wrdTest::TearDown();
        _rel();
    }

    wrd::node& getSubPack() { return *_subpack; }
    wrd::pack& getPack() { return *_pack; }
    wrd::errReport& getReport() { return _rpt; }

    wrdSyntaxTest& make() {
        return make(wrd::manifest());
    }

    wrdSyntaxTest& make(const wrd::manifest& mani) {
        _rel();
        _pack.bind(new wrd::pack(mani, wrd::packLoadings()));
        return *this;
    }

    wrdSyntaxTest& parse(const wrd::wchar* src) {
        WRD_I("====================================");
        WRD_I("parsing src:");
        WRD_I("%s", src);
        WRD_I("====================================");
        wrd::parser p;
        _subpack = p.setPack(*_pack).setReport(_rpt).parse(_src = src);
        _isParsed = _subpack && _pack && !_rpt;
        if(!_isParsed) return *this;

        wrd::packs* paks = new wrd::packs();
        paks->add(_pack->getManifest().name, *_pack);
        wrd::packChain verifying(paks);
        verifying.link(wrd::thread::get().getSystemPacks());

        wrd::verifier v;
        v.setReport(_rpt).setPacks(verifying).verify(*_subpack);
        return *this;
    }

    wrd::wbool shouldParsed(wrd::wbool well) const {
        EXPECT_EQ(_isParsed, well);
        wrd::wbool ret = _isParsed == well;
        if(!ret)
            _log(well);
        return ret;
    }
    wrd::wbool shouldVerified(wrd::wbool well) const {
        wrd::wbool verified = _isParsed && !_rpt;
        EXPECT_EQ(verified, well);

        wrd::wbool ret = verified == well;
        if(!ret)
            _log(well);
        return ret;
    }

private:
    void _log(wrd::wbool expected) const {
        std::cout   << "  code: " << _src << "\n"
                    << "  errReport:\n";
        _rpt.log();
    }

    void _rel() {
        _src = "";
        _subpack.rel();
        _pack.rel();
        _rpt.rel();
        _isParsed = false;
    }

private:
    const wrd::wchar* _src;
    wrd::str _subpack;
    wrd::tstr<wrd::pack> _pack;
    wrd::errReport _rpt;
    wrd::wbool _isParsed;
};
