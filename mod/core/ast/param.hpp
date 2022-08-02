#pragma once

#include "../common.hpp"
#include "clonable.hpp"
#include "immutableTactic.hpp"
#include "../type/wtype.hpp"

namespace namu {
    class _wout param : public instance, public clonable {
        WRD(CLASS(param, instance))

    public:
        param(const std::string& newName, const node& org);
        param(const std::string& newName, const node* org);

    public:
        const std::string& getName() const;
        void setName(const std::string& new1);
        const node& getOrigin() const;
        void setOrigin(const node& newType);

    public:
        std::string _name;
        str _org;
    };
}
