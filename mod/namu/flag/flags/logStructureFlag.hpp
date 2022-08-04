#pragma once

#include "../flag.hpp"

namespace namu {

    class logStructureFlag : public flag {
        NAMU(CLASS(logStructureFlag, flag))

    public:
        const nchar* getName() const override { return "-ls"; }
        const nchar* getDescription() const override {
            return R"DESC(
        this flag prints all log about structure of parsed ast.
        by inspecting the structure, you can figure out that those asts are parsed properly.
        it also shows frame info which contains the stackframe when latest error occurs.)DESC";
        }

    protected:
        const nchar* _getRegExpr() const override { return "^\\-ls$"; }
        nbool _onTake(const args& tray, cli& c, interpreter& ip) const override;
    };
}
