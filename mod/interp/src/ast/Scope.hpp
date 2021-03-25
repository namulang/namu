#pragma once

#include "Node.hpp"

namespace wrd {

    class StackFrame;
    class Scope : public Node {
        WRD_INTERFACE(Scope, Node)

    public:
        explicit Scope(std::string name = ""): _name(name) {}

        const std::string& getName() const override {
            return _name;
        }

    protected:
        virtual wbool _onInStackFrame(StackFrame& sf, NContainer& args) = 0;
        virtual wbool _onOutStackFrame(StackFrame& sf, NContainer& args) = 0;

    private:
        std::string _name;
    };
}
