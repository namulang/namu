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
        param(const std::string& newName, const wtype& orgType): _name(newName), _type(&orgType) {}

    public:
        const std::string& getName() const { return _name; }
        void setName(const std::string& new1) { _name = new1; }
        const node& getOrigin() const { return *_org; }
        node& getOrigin() { return *_org; }
        const wtype& getOriginType() const { return *_type; }
        void setOrigin(const node& new1);
        void setOriginType(const wtype& new1) {
            _type = &new1;
        }

    public:
        std::string _name;
        const wtype* _type;
        str _org;
    };
}
