#pragma once

#include "../flag.hpp"

namespace namu {

    class logInterpreterFlag : public flag {
        WRD(CLASS(logInterpreterFlag, flag))

    public:
        const wchar* getName() const override { return "-li"; }
        const wchar* getDescription() const override {
            return R"DESC(
        prints all logs of the interpreter.  these are mostly about parser and verifier logs.
        it includes all of process to tokenizing, parsing, verification.
        this info will be useful if you can knew how src to be interpreted.)DESC";
        }

    protected:
        const wchar* _getRegExpr() const override { return "^\\-li$"; }
        wbool _onTake(const args& tray, cli& c, interpreter& ip) const override;
    };
}
