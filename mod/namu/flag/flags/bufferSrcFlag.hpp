#pragma once

#include "../flag.hpp"

namespace namu {

    class bufferSrcFlag : public flag {
        NAMU(CLASS(bufferSrcFlag, flag))

    public:
        const nchar* getName() const override { return "-s"; }
        const nchar* getDescription() const override {
            return R"DESC(
        programming script can passed in as a string with this flag.)DESC";
        }

    protected:
        const nchar* _getRegExpr() const override { return "^\\-s$"; }
        nbool _onTake(const flagArgs& tray, cli& c, interpreter& ip) const override;
        ncnt _onContinuousArgCount() const override { return 1; }
    };
}
