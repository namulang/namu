#pragma once

#include "../../../loader/packMaking.hpp"

namespace wrd {

    class cppPackMaking : public packMaking {
        WRD_DECL_ME(cppPackMaking, packMaking)
        WRD_INIT_META(me)

    public:
        pack* makeWith(const manifest& mani) const override {
            return new cppPack(mani);
        }

        const std::string& getName() const override {
            static std::string inner = "cpp";
            return inner;
        }
    };
}
