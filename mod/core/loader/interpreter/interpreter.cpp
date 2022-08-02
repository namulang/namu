#include "../../ast/exprs/blockExpr.hpp"
#include "../../ast/mgd/mgdFunc.hpp"
#include "../../frame/thread.hpp"
#include "interpreter.hpp"

namespace namu {

    NAMU_DEF_ME(interpreter)

    me::interpreter(): _isParsed(false), _isLogStructure(false), _isLogInterpreter(false) {}

    me& me::setReport(errReport& report) {
        _rpt.bind(report);
        return *this;
    }
    me& me::setSlot(slot& tray) {
        _slot.bind(tray);
        return *this;
    }
    me& me::setSrcSupply(const srcSupply& supply) {
        _srcs.bind(supply);
        return *this;
    }
    me& me::setLogStructure(nbool enable) {
        _isLogStructure = enable;
        return *this;
    }
    me& me::setLogInterpreter(nbool enable) {
        _isLogInterpreter = enable;
        return *this;
    }
    nbool me::isParsed() const {
        return _isParsed;
    }

    nbool me::isVerified() const {
        return isParsed() && (_rpt && !_rpt->hasErr());
    }

    node& me::getSubPack() { return _pser.getSubPack(); }

    slot& me::getSlot() { return _pser.getSlot(); }

    const errReport& me::getReport() const {
        return *_rpt;
    }

    slot& me::interpret() {
        if(!_srcs) {
            _rpt->add(err::newErr(NO_SRC));
            return *_slot;
        }

        _parse();
        tstr<frame> info;
        if(*_rpt)
            return *_slot;
        _verify(info);

        NAMU_DI("======================================");
        NAMU_DI("           preEvaluation");
        NAMU_DI("======================================");
        //_preEvaluation(_slot->getPack());

        _logStructure(*info, _srcs->get());

        return *_slot;
    }

    void me::_preEvalObject(node& eval) {
        obj& cast = eval.cast<obj>();
        if(nul(cast)) return;

        NAMU_DI("run %s.@preCtor", cast.getType().getName().c_str());
        cast.run(baseObj::PRECTOR_NAME);
    }

    void me::_preEvaluation(node& eval) {
        std::map<string, int> checker;

        _preEvalObject(eval);
        // double-checking algorithm:
        //  while iterating and run preCtor, new variable can be added into eval object.
        //  to handle properly that scenario, I prepared checker and run evalutation twice.
        _preEvaluation(checker, eval);
        _preEvaluation(checker, eval);
    }

    void me::_preEvaluation(std::map<string, int>& checker, node& eval) {
        for(auto e=eval.subs().begin(); e ;++e) {
            if(checker.find(e.getKey()) != checker.end())
                continue;

            checker.insert({e.getKey(), 1});//actually, this value doesn't matter
            _preEvaluation(*e);
        }
    }

    void me::rel() {
        _isParsed = false;
        _rpt.rel();
        _veri.rel();
        _pser.rel();
        _srcs.rel();
        _slot.rel();
    }

    void me::log() const {
        if(!_rpt && !*_rpt) return;

        logger& l = logger::get();
        l.saveStreamEnable();
        l.setEnable(true);

        _rpt->log();

        l.loadStreamEnable();
    }

    nbool me::_isPackExist() {
        return !nul(_pser.getSubPack()) && _slot;
    }

    void me::_parse() {
        logger& l = logger::get();
        l.saveStreamEnable();
        l.setEnable(_isLogInterpreter);
        while(_srcs->next()) {
            _pser.rel(); // parser can only take 1 src.

            const char* buf = _srcs->get();
            NAMU_DI("======================================");
            NAMU_DI("                parse                 ");
            NAMU_DI("======================================");

            _pser.setReport(*_rpt)
                 .setSlot(*_slot)
                 .parse(buf);

            if(!_slot)
                _slot.bind(_pser.getSlot());
        }

        _isParsed = _isPackExist() && !_rpt->hasErr();
        l.loadStreamEnable();
    }

    void me::_verify(tstr<frame>& info ) {
        logger& l = logger::get();
        l.saveStreamEnable();
        l.setEnable(_isLogInterpreter);

        NAMU_DI("======================================");
        NAMU_DI("                verify                ");
        NAMU_DI("======================================");

        if(!_slot) {
            NAMU_E("_slot is null");
            return;
        }

        // verify:
        _veri.setReport(*_rpt)
             .setFrameInfo(info)
             .verify(_slot->getPack());
        l.loadStreamEnable();

    }

    void me::_logStructure(frame& info, const nchar* buf) {
        if(!_isLogStructure) return;

        logger& l = logger::get();
        l.saveStreamEnable();
        l.setEnable(true);

        std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGREEN) << " - frame:\n";
        _logFrame(info);
        std::cout << "\n";

        if(!nul(_pser.getSubPack()) && _slot) {
            std::cout << " - structure:\n";
            std::vector<const char*> indents;
            indents.push_back("  ");
            _logStructure(indents, _pser.getSubPack(), _slot->getManifest().name, 0, true, true);
            std::cout << "\n";
        }

        l.loadStreamEnable();
        std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGRAY);
    }

    void me::_logStructure(std::vector<const char*>& indents, const node& n, const std::string& name, int idx, bool isLast, bool isParentLast) const {
        if(nul(n)) {
            NAMU_W("_logStructure(n == null)");
            return;
        }

        indents.push_back((isParentLast ? "    " : "┃    "));
        _logIndent(indents, isParentLast);
        std::cout << (isLast ? "┗━[" : "┣━[") << idx << "]: " << n.getType().getName() << " \"" << name << "\"\n";

        int subN = -1;
        const bicontainable& subs = n.subs();
        for(auto e=subs.begin(); e ;++e) {
            subN++;
            _logStructure(indents, e.getVal(), e.getKey(), subN, subN == subs.len()-1, isLast);
        }

        const mgdFunc& f = n.cast<mgdFunc>();
        if(!nul(f)) {
            subN++;
            _logStructure(indents, f.getBlock().getStmts(), subN, subN == subs.len(), isLast);
        }
        indents.pop_back();
    }

    void me::_logStructure(std::vector<const char*>& indents, const narr& blk, int idx, bool isLast, bool isParentLast) const {
        indents.push_back(isParentLast ? "    " : "┃   ");
        _logIndent(indents, isParentLast);
        std::cout << (isLast ? "┗━[" : "┣━[") << idx << "]: block \n";

        int subN = -1;
        for(const auto& stmt: blk) {
            subN++;
            const blockExpr& blkExpr = stmt.cast<blockExpr>();
            if(!nul(blkExpr))
                _logStructure(indents, blkExpr.getStmts(), subN, subN == blk.len()-1, isLast);
            else
                _logStructure(indents, stmt, "", subN, subN == blk.len()-1, isLast);
        }
        indents.pop_back();
    }

    void me::_logIndent(const std::vector<const char*>& indents, bool isParentLast) const {
        for(int n=0; n < indents.size(); n++)
            std::cout << indents[n];
    }

    void me::_logFrame(const frame& info) const {
        if(nul(info)) {
            std::cout << "    null\n";
            return;
        }

        int n=0;
        for(auto e = info.subs().begin(); e ;++e)
            std::cout << "    [" << n++ << "]: '" << e.getKey() << "' " << e.getVal().getType().getName().c_str() << "\n";
    }
}
