#pragma once

#include "../common.hpp"
#include "clonable.hpp"
#include "immutableTactic.hpp"
#include "../type/wtype.hpp"

namespace wrd {
    class param : public instance, public clonable {
        WRD(CLASS(param, instance))

    public:
        param(const std::string& newName, const node& origin);
        param(const std::string& newName, const wtype& orgType): _name(newName), _org(orgType) {}

    public:
        const std::string& getName() const { return _name; }
        void setName(const std::string& new1) { _name = new1; }
        const str& getOrigin() const { return _org; }
        void setOrigin(const node& new1);
        void setOrigin(const wtype& new1);

    public:
        std::string _name;
        str _org;
    };
}
