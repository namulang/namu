#pragma once

#include "parser.hpp"
#include "../../visitor/verifier.hpp"

namespace namu {

    class _nout interpreter : public worker<tstr<slot>, slot> {
        typedef worker<slot, slot> __super7;
        NAMU(CLASS(interpreter, __super7))

    public:
        enum logFlag2 {
            LOG_STRUCTURE = 1 << 7,
            LOG_GRAPH_ON_EX = 1 << 8
        };

    public:
        interpreter();

    public:
        me& addSupply(const srcSupply& supply);
        me& relSupplies();
        me& setLogStructure(nbool enable);
        nbool isParsed() const;
        nbool isVerified() const;
        node& getSubPack();
        const node& getSubPack() const NAMU_UNCONST_FUNC(getSubPack())

        void rel() override;

        void log() const;

    protected:
        tstr<slot> _onWork() override;

    private:
        nbool _isPackExist();

        void _parse();
        void _preEval();
        void _verify();
        void _logStructure(frame& info);
        void _logFrame(const frame& info) const;
        void _log() const;

    private:
        tstr<slot> _slot;
        verifier _veri;
        parser _pser;
        nbool _isParsed;
    };
}
