#pragma once

#include "../flag.hpp"

namespace wrd {

    class fileFlag : public flag {
        WRD(CLASS(fileFlag, flag))

    public:
        const wchar* getName() const override {
            return "<filePath>";
        }

        const wchar* getDescription() const override {
            return R"DESC(
        file path of wrd language script file.
        extension of file should be end with 'wrd'.
        wildcard and the question mark aren't allowed.)DESC";
        }

    protected:
        const wchar* _getRegExpr() const override {
            return "[\\\\\\w\\.\\/:]+\\.wrd$";
        }

        wbool _onTake(const args& tray, cli& c, interpreter& ip) const override;
    };
}
