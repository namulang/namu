#pragma once

#include "parser.hpp"
#include "srcSupply.hpp"
#include "verifier.hpp"

namespace wrd {

    class _wout interpreter : public typeProvidable, public clonable {
        WRD(CLASS(interpreter))

    public:
        interpreter();

    public:
        me& setReport(errReport& report);
        me& setSlot(slot& pak);
        me& setSrcSupply(const srcSupply& supply);
        me& setLogStructure(wbool enable);
        me& setLogInterpreter(wbool enable);
        wbool isParsed() const;
        wbool isVerified() const;
        node& getSubPack();
        const node& getSubPack() const WRD_UNCONST_FUNC(getSubPack())
        slot& getPack();
        const slot& getPack() const WRD_UNCONST_FUNC(getPack())
        const errReport& getReport() const;

        slot& interpret();

        void rel();

        void log() const;

    private:
        wbool _isPackExist();

        void _parse();
        void _verify(tstr<frame>& info );

        void _logStructure(frame& info, const wchar* buf);
        void _logStructure(std::vector<const char*>& indents, const node& n, const std::string& name, int idx, bool isLast, bool isParentLast) const;
        void _logStructure(std::vector<const char*>& indents, const narr& blk, int idx, bool isLast, bool isParentLast) const;
        void _logIndent(const std::vector<const char*>& indents, bool isParentLast) const;
        void _logFrame(const frame& info) const;

    private:
        tstr<errReport> _rpt;
        tstr<slot> _pak;
        verifier _veri;
        parser _pser;
        tstr<srcSupply> _srcs;
        wbool _isParsed;
        wbool _isLogStructure;
        wbool _isLogInterpreter;
    };
}
