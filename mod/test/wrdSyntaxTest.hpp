#pragma once

#include "wrdTest.hpp"
#include <iostream>

struct wrdSyntaxTest : public wrdTest {
    void TearDown() {
        wrdTest::TearDown();
        _rel();
    }

    wrd::node& getSubPack() { return _pser.getSubPack(); }
    const wrd::node& getSubPack() const { return _pser.getSubPack(); }
    wrd::pack& getPack() { return _pser.getPack(); }
    const wrd::pack& getPack() const { return _pser.getPack(); }
    wrd::errReport& getReport() { return _rpt; }

    wrdSyntaxTest& make(const std::string& name) {
        return make(wrd::manifest(name));
    }

	wrdSyntaxTest& make() {
		return make(wrd::manifest());
	}

    wrdSyntaxTest& make(const wrd::manifest& mani) {
        _rel();
        _pser.setPack(*new wrd::pack(mani, wrd::packLoadings()));
        return *this;
    }

    wrdSyntaxTest& parse(const wrd::wchar* src) {
        WRD_I("====================================");
        WRD_I("parsing src:");
        WRD_I("%s", src);
        WRD_I("====================================");
        _pser.setReport(_rpt).parse(_src = src);

		wrd::pack& pak = _pser.getPack();
		wrd::node& subpack = _pser.getSubPack();
		WRD_DI("subpack=%x, pack=%x, _rpt=%d", &subpack, &pak, _rpt.hasErr());
        _isParsed = !nul(subpack) && !nul(pak) && !_rpt;
        if(!_isParsed) return *this;

        wrd::packs* paks = new wrd::packs();
        paks->add(pak.getManifest().name, pak);
        wrd::packChain verifying(paks);
        verifying.link(wrd::thread::get().getSystemPacks());

        wrd::verifier v;
        v.setReport(_rpt).setPacks(verifying).verify(subpack);
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
                    << "  structure:\n";
        _logStructure(getSubPack(), getPack().getManifest().name, 0, 0, true, true);
        std::cout   << "  errReport:\n";
        _rpt.log();
    }

    void _logStructure(const wrd::node& n, const std::string& name, int idx, int level, bool isLast, bool isParentLast) const {
		if(nul(n)) {
			WRD_W("_logStructure(n == null)");
			return;
		}

        _logIndent(level, isParentLast);
        std::cout << (isLast ? "┗━[" : "┣━[") << idx << "]: " << n.getType().getName() << " \"" << name << "\"\n";

        int subN = -1;
        const wrd::bicontainable& subs = n.subs();
        for(auto e=subs.begin(); e ;++e) {
            subN++;
            _logStructure(e.getVal(), e.getKey(), subN, level + 2, subN == subs.len()-1, isLast);
        }

        const wrd::mgdFunc& f = n.cast<wrd::mgdFunc>();
        if(!nul(f)) {
            subN++;
            _logStructure(f.getBlock().getStmts(), subN, level+2, subN == subs.len(), isLast);
        }
    }

    void _logStructure(const wrd::narr& blk, int idx, int level, bool isLast, bool isParentLast) const {
        _logIndent(level, isParentLast);
        std::cout << (isLast ? "┗━[" : "┣━[") << idx << "]: block \n";

        int subN = -1;
        for(const auto& stmt: blk) {
            subN++;
            const wrd::blockExpr& blkExpr = stmt.cast<wrd::blockExpr>();
            if(!nul(blkExpr))
                _logStructure(blkExpr.getStmts(), subN, level+2, subN == blk.len()-1, isLast);
            else
                _logStructure(stmt, "", subN, level + 2, subN == blk.len()-1, isLast);
        }
    }

    void _logIndent(int level, bool isParentLast) const {
        std::cout << "  ";
        for(int n=0; n < level-1; n++)
            std::cout << (isParentLast ? "  " : "┃ ");
    }

    void _rel() {
        _src = "";
        _rpt.rel();
		_pser.rel();
        _isParsed = false;
    }

private:
    const wrd::wchar* _src;
    wrd::errReport _rpt;
    wrd::wbool _isParsed;
	wrd::parser _pser;
};
