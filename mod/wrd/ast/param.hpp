#pragma once

#include "../common.hpp"
#include "clonable.hpp"
#include "immutableTactic.hpp"
#include "../type/wtype.hpp"

namespace wrd {
    class param : public instance, public clonable {
        WRD(CLASS(param, instance))

    public:
        param(const std::string& newName, const node& origin): _name(newName) { setOrigin(origin); }
        param(const std::string& newName, const type& origin): _name(newName) { setOrigin(origin); }

    public:
        const std::string& getName() const { return _name; }
        void setName(const std::string& new1) { _name = new1; }
        const node& getOrigin() const { return *_org; }
        node& getOrigin() { return *_org; }
        void setOrigin(const node& new1);
        void setOrigin(const type& new1) {
            _org = str(new1);
        }

    public:
        std::string _name;
        str _org;
    };
}
