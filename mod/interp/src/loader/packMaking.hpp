#pragma once

#include "../builtin/container/native/tnarr.inl"

namespace wrd {

    class pack;
    class obj;
    struct manifest;
    class packMaking {
        WRD_DECL_ME(packMaking)
        WRD_INIT_META(me)

    public:
        virtual pack* makeWith(const manifest& mani) const = 0;
        virtual const std::string& getName() const = 0;
    };

    typedef std::vector<packMaking*> packMakings;
}
