#pragma once

#include "sobj.hpp"

namespace wrd {

    class _wout nullSobj : public sobj {
        WRD_DECL_ME(nullSobj, sobj)
        WRD_INIT_META(nullSobj)

    public:
        nullSobj(): super() {}

        const std::string& asStr() const override {
            static std::string inner = "";
            return inner;
        }
        wchar asChar() const override {
            return '\0';
        }
        wint asInt() const override {
            return 0;
        }
        wbool asBool() const override {
            return false;
        }
        const type& getType() const override {
            return ttype<me>::get();
        }
        wbool isExist() const override {
            return false;
        }

        static me& get() {
            static me inner;
            return inner;
        }
    };
}
