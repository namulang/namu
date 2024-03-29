#pragma once

#include "parser.hpp"
#include "srcSupply.hpp"
#include "../../visitor/verifier.hpp"

namespace namu {

    class _nout interpreter : public typeProvidable, public clonable {
        NAMU(CLASS(interpreter))

    public:
        interpreter();

    public:
        me& setReport(errReport& report);
        me& setSlot(slot& pak);
        me& setSrcSupply(const srcSupply& supply);
        me& setLogStructure(nbool enable);
        me& setVerbose(nbool isVerbose);
        nbool isParsed() const;
        nbool isVerified() const;
        node& getSubPack();
        const node& getSubPack() const NAMU_UNCONST_FUNC(getSubPack())
        slot& getSlot();
        const slot& getSlot() const NAMU_UNCONST_FUNC(getSlot())
        errReport& getReport();
        const errReport& getReport() const NAMU_UNCONST_FUNC(getReport())

        slot& interpret();

        void rel();

        void log() const;

    private:
        nbool _isPackExist();

        void _parse();
        void _preEval();
        void _verify();
        void _logStructure(frame& info);
        void _logFrame(const frame& info) const;
        void _log() const;

    private:
        tstr<errReport> _rpt;
        tstr<slot> _slot;
        verifier _veri;
        parser _pser;
        tstr<srcSupply> _srcs;
        nbool _isParsed;
        nbool _isLogStructure;
        nbool _isVerbose;
    };
}
