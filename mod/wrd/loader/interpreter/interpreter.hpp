#pragma once

#include "parser.hpp"
#include "srcSupply.hpp"
#include "flag.hpp"
#include "verifier.hpp"

namespace wrd {

    class interpreter : public typeProvidable, public clonable {
        WRD(CLASS(interpreter))

    public:
        interpreter(): _isParsed(false) {}

    public:
        me& setReport(errReport& report) {
            _rpt.bind(report);
            return *this;
        }
        me& setPack(pack& pak) {
            _pak.bind(pak);
            return *this;
        }
        me& setSrcSupply(const srcSupply& supply) {
            _srcs.bind(supply);
            return *this;
        }
        me& addFlag(const flag& f) {
            _flags.push_back(tstr<flag>(f));
            return *this;
        }
        me& delFlags() {
            _flags.clear();
            return *this;
        }

        wbool isParsed() const {
            return _isParsed;
        }

        wbool isVerified() const {
            return isParsed() && (_rpt && !_rpt->hasErr());
        }

        node& getSubPack() { return _pser.getSubPack(); }
        const node& getSubPack() const WRD_UNCONST_FUNC(getSubPack())

        pack& getPack() { return _pser.getPack(); }
        const pack& getPack() const WRD_UNCONST_FUNC(getPack())

        pack& interpret() {
            if(!_srcs) return WRD_E("_srcs not exists."), *_pak;

            _processFlags();
            _parse();
            _verify();

            return *_pak;
        }

        void rel() {
            _isParsed = false;
            _rpt.rel();
            _veri.rel();
            _pser.rel();
            _srcs.rel();
            _pak.rel();
            delFlags();
        }

    private:
        wbool _isPackExist() {
            return !nul(_pser.getSubPack()) && _pak;
        }

        void _processFlags() {
            for(auto& f : _flags)
                f->update(*this);
        }

        void _parse() {
            while(_srcs->next()) {
                _pser.rel(); // parser can only take 1 src.

                const char* buf = _srcs->get();
                WRD_DI("======================================");
                WRD_DI("parse: %s", buf);
                WRD_DI("======================================");

                _pser.setReport(*_rpt)
                     .setPack(*_pak)
                     .parse(buf);

                if(!_pak)
                    _pak.bind(_pser.getPack());

                if(_isPackExist())
                    _log(buf);
            }

            _isParsed = _isPackExist() && !_rpt->hasErr();
        }

        void _verify() {
            if(!_pak) {
                WRD_E("_pak is null");
                return;
            }

            // make tray:
            packs* paks = new packs();
            paks->add(_pak->getManifest().name, *_pak);
            packChain tray(paks);
            tray.link(wrd::thread::get().getSystemPacks());

            // verify:
            tstr<frame> frameInfo;
            _veri.setReport(*_rpt)
                 .setPacks(tray)
                 .setFrameInfo(frameInfo)
                 .verify(*_pak);

            std::cout   << " - frame:\n";
            _logFrame(*frameInfo);
            std::cout   << " - errReport:\n";
            if(_rpt)
                _rpt->log();
        }

        void _log(const char* buf) const {
            std::cout << " - code: " << buf << "\n";

            if(!nul(_pser.getSubPack()) && _pak) {
                std::cout << " - structure:\n";
                _logStructure(_pser.getSubPack(), _pak->getManifest().name, 0, 0, true, true);
            }

            std::cout   << " - errReport:\n";
            if(_rpt)
                _rpt->log();
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

        void _logFrame(const wrd::frame& info) const {
            if(nul(info)) {
                std::cout << "    null\n";
                return;
            }

            int n=0;
            for(auto e = info.subs().begin(); e ;++e)
                std::cout << "    [" << n++ << "]: '" << e.getKey() << "' " << e.getVal().getType().getName().c_str() << "\n";
        }


    private:
        tstr<errReport> _rpt;
        tstr<pack> _pak;
        verifier _veri;
        parser _pser;
        tstr<srcSupply> _srcs;
        flags _flags;
        wbool _isParsed;
    };
}
