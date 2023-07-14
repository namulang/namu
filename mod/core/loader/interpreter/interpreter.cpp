#include "../../ast/exprs/blockExpr.hpp"
#include "../../ast/mgd/mgdFunc.hpp"
#include "../../frame/thread.hpp"
#include "interpreter.hpp"
#include "../../visitor/graphVisitor.hpp"
#include "../../visitor/preEvaluator.hpp"

namespace namu {

    NAMU_DEF_ME(interpreter)

    me::interpreter(): _isParsed(false), _isLogStructure(false) {}

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
        if(*_rpt)
            return *_slot;
        _preEval();
        _verify();

        _logStructure(_veri.getErrFrame());

        return *_slot;
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

        _rpt->log();
    }

    nbool me::_isPackExist() {
        return !nul(_pser.getSubPack()) && _slot;
    }

    void me::_parse() {
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
    }

    void me::_preEval() {
        NAMU_DI("======================================");
        NAMU_DI("                preEval               ");
        NAMU_DI("======================================");

        if(!_slot) {
            NAMU_E("_slot is null");
            return;
        }

        preEvaluator evaler;
        evaler.setReport(*_rpt)
              .setLog(false)
              .setRoot(_slot->getPack())
              .start();
    }

    void me::_verify() {
        NAMU_DI("======================================");
        NAMU_DI("                verify                ");
        NAMU_DI("======================================");

        if(!_slot) {
            NAMU_E("_slot is null");
            return;
        }

        // verify:
        _veri.setReport(*_rpt)
             .setLog(true)
             .setRoot(_slot->getPack())
             .start();
    }

    void me::_logStructure(frame& info) {
        if(!_isLogStructure) return;

        std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGREEN) << " - frame:\n";
        _logFrame(info);
        std::cout << "\n";

        if(!nul(_pser.getSubPack()) && _slot) {
            std::cout << " - structure:\n";
            graphVisitor().setRoot(_slot->getPack())
                          .start();
        }

        std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGRAY);
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
