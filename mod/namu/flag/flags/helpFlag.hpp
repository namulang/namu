#pragma once

#include "../flag.hpp"

namespace namu {

    class helpFlag : public flag {
        WRD(CLASS(helpFlag, flag))

    public:
        const wchar* getName() const override;
        const wchar* getDescription() const override;

    protected:
        const wchar* _getRegExpr() const override;
        wbool _onTake(const args& tray, cli& c, interpreter& ip) const override;
        void _printUsage() const;
    };
}
