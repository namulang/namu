#pragma once

#include "../common.hpp"
#include "clonable.hpp"
#include "immutableTactic.hpp"
#include "../type/wtype.hpp"

namespace wrd {
    class _wout param : public instance, public clonable {
        WRD(CLASS(param, instance))

    public:
        param(const std::string& newName, const wtype& orgType);
        param(const std::string& newName, const node& org);

    public:
        const std::string& getName() const;
        void setName(const std::string& new1);
        const wtype& getOrgType() const;
        void setOrgType(const wtype& newType);

    public:
        std::string _name;
        const wtype* _type;
    };
}
