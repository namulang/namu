#pragma once

#include "../flag.hpp"

namespace namu {

    class verboseFlag : public flag {
        NAMU(CLASS(verboseFlag, flag))

    public:
        const nchar* getName() const override { return "-lv"; }
        const nchar* getDescription() const override {
            return R"DESC(
        prints all logs in verbose level of the interpreter.
        these are mostly about parser and verifier logs. and it includes all of process
        to tokenizing, parsing, verification.
        this info will be useful if you know how src to be interpreted.)DESC";
        }

    protected:
        const nchar* _getRegExpr() const override { return "^\\-lv$"; }
        nbool _onTake(const flagArgs& tray, cli& c, interpreter& ip) const override;
    };
}
