#pragma once

#include "../option.hpp"

namespace wrd {

    class helpOption : public option {
        WRD(CLASS(helpOption, option))

    public:
        const wchar* getName() const override;
        const wchar* getDescription() const override;

    protected:
        const wchar* _getRegExpr() const override;
        wbool _onTake(const args& tray, cli& c, interpreter& ip) const override;
    };
}
