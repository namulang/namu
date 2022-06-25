#pragma once

#include "../common.hpp"
#include "clonable.hpp"
#include "immutableTactic.hpp"
#include "../type/wtype.hpp"

namespace wrd {
    class _wout param : public instance, public clonable {
        WRD(CLASS(param, instance))

    public:
        param(const std::string& newName, const node& origin);

    public:
        const std::string& getName() const;
        void setName(const std::string& new1);
        const str& getOrigin() const;
        void setOrigin(const node& new1);

    public:
        std::string _name;
        str _org;
    };
}
