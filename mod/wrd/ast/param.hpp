#pragma once

#include "../common.hpp"
#include "clonable.hpp"

namespace wrd {
    class param : public instance, public clonable {
        WRD(CLASS(param, instance))

    public:
        param(const std::string& newName, const typeProvidable& provider)
            : name(newName), type(provider.getType()) {}
        param(const std::string& newName, const wtype& newType)
            : name(newName), type(newType) {}

    public:
        std::string name;
        wtype& type;
    };
}
