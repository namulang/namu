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

    protected:
        virtual wbool _onInStackFrame(stackFrame& sf, ncontainer& args) = 0;
        virtual wbool _onOutStackFrame(stackFrame& sf, ncontainer& args) = 0;

    private:
        std::string _name;
    };
}
