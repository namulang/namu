#pragma once

#include "node.hpp"

namespace wrd {

    class subpack : public node {
        WRD(CLASS(subpack, node))

    public:
        subpack() {}
        subpack(const std::string& name): super(), _name(name) {}

    public:
        using super::subs;
        ncontainer& subs() override { return _subs; }

        using super::run;
        str run(const containable& args) override {
            return str();
        }

        wbool canRun(const containable& args) const override {
            return false;
        }

        const std::string& getName() const override {
            if(_name.empty()) return super::getName();
            return _name;
        }

    private:
        std::string _name;
        narr _subs;
    };
}
