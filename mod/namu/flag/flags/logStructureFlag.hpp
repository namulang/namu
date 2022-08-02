#pragma once

#include "../flag.hpp"

namespace namu {

    class logStructureFlag : public flag {
        WRD(CLASS(logStructureFlag, flag))

    public:
        const wchar* getName() const override { return "-ls"; }
        const wchar* getDescription() const override {
            return R"DESC(
        this flag prints all log about structure of parsed ast.
        by inspecting the structure, you can figure out that those asts are parsed properly.
        it also shows frame info which contains the stackframe when latest error occurs.)DESC";
        }

    protected:
        const wchar* _getRegExpr() const override { return "^\\-ls$"; }
        wbool _onTake(const args& tray, cli& c, interpreter& ip) const override;
    };
}
