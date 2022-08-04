#pragma once

#include "../flag.hpp"

namespace namu {

    class fileFlag : public flag {
        NAMU(CLASS(fileFlag, flag))

    public:
        const nchar* getName() const override {
            return "<filePath>";
        }

        const nchar* getDescription() const override {
            return R"DESC(
        file path of namu language script file.
        extension of file should be end with 'namu'.
        wildcard and the question mark aren't allowed.)DESC";
        }

    protected:
        const nchar* _getRegExpr() const override {
            return "[\\\\\\w\\.\\/:\\-\\(\\)\\d]+\\.namu$";
        }

        nbool _onTake(const args& tray, cli& c, interpreter& ip) const override;
    };
}
