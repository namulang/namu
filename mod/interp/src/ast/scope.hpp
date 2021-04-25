#pragma once

#include "node.hpp"

namespace wrd {

    class stackFrame;
    class scope : public node {
        WRD_INTERFACE(scope, node)

    public:
        explicit scope(std::string name = ""): _name(name) {}

        const std::string& getName() const override {
            return _name;
        }

    private:
        std::string _name;
    };
}
