#pragma once

#include "../obj.hpp"

namespace wrd {

    class mgdObj : public obj {
        WRD_INTERFACE(mgdObj, obj)

    public:
        explicit mgdObj(const std::string& name = ""): super(name) {}
        explicit mgdObj(const me& rhs): super(rhs) {
            _assign(rhs);
        }

        me& operator=(const me& rhs) {
            if (&rhs == this) return *this;

            super::operator=(rhs);

            return _assign(rhs);
        }

    protected:
        wbool _onInFrame(frame& fr, const ncontainer& args) override;
        wbool _onOutFrame(frame& fr, const ncontainer& args) override;

    private:
        me& _assign(const me& rhs);

    private:
        tstr<nchain> _shares;
    };
}
