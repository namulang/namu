#include "../../ast/exprs/blockExpr.hpp"
#include "../../ast/func.hpp"
#include "interpreter.hpp"
#include "../../visitor/graphVisitor.hpp"
#include "../../visitor/preEvaluator.hpp"
#include "../../frame/threadUse.hpp"

namespace namu {

    NAMU_DEF_ME(interpreter)

    me::interpreter(): _isParsed(false) {}

    me& me::addSupply(const srcSupply& supply) {
        _pser.addSupply(supply);
        return *this;
    }

    me& me::relSupplies() {
        _pser.relSupplies();
        return *this;
    }

    nbool me::isParsed() const {
        return _isParsed;
    }

    nbool me::isVerified() const {
        return isParsed() && (!nul(getReport()) && !getReport().hasErr());
    }

    node& me::getSubPack() {
        return _pser.getSubPack();
    }

    tstr<slot> me::_onWork() {
        threadUse thr;
        _parse();
        if(getReport())
            return getTask();
        _preEval();
        _verify();

        return getTask();
    }

    void me::_onEndWork() {
        super::_onEndWork();
        if(isFlag(LOG_STRUCTURE))
            _logStructure();
    }

    void me::rel() {
        super::rel();

        _isParsed = false;
        _veri.rel();
        _pser.rel();
        _slot.rel();
    }

    nbool me::_isPackExist() {
        return !nul(_pser.getSubPack()) && _slot;
    }

    void me::_parse() {
        NAMU_DI("======================================");
        NAMU_DI("                parse                 ");
        NAMU_DI("======================================");

        _pser.setReport(getReport())
             .setTask(getTask())
             .work();

        if(!_slot)
            _slot.bind(_pser.getTask());

        _isParsed = _isPackExist() && _pser.isOk();
    }

    void me::_preEval() {
        NAMU_DI("======================================");
        NAMU_DI("                preEval               ");
        NAMU_DI("======================================");

        if(!_slot)
            return NAMU_E("_slot is null"), void();

        preEvaluator evaler;
        evaler.setReport(getReport())
              .setFlag(0)
              .setTask(getTask().getPack())
              .work();
    }

    void me::_verify() {
        NAMU_DI("======================================");
        NAMU_DI("                verify                ");
        NAMU_DI("======================================");

        if(!_slot)
            return NAMU_E("_slot is null"), void();

        // verify:
        _veri.setReport(getReport())
             .setFlag(getFlag())
             .setTask(getTask().getPack())
             .work();
    }

    void me::_logStructure(frame& info) {
        if(!isFlag(LOG_STRUCTURE)) return;

        if(!nul(_pser.getSubPack()) && _slot) {
            std::cout << " - structure:\n";
            graphVisitor().setTask(getTask().getPack())
                          .work();
        }
    }
}
