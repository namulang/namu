#pragma once

#include "../expr.hpp"

namespace wrd {

    class getExpr : public expr {
        WRD(CLASS(getExpr, expr))

    public:
        getExpr(const src& s, wcnt lineNum, const Ref& it, const wStr& newName, const arr& args)
            : super(s, lineNum, &target, &newName, &args), _it(it), _name(newName), _args(args) {}
        getExpr(const src& s, wcnt lineNum, const Ref& target, const wStr& newName)
            : super(s, lineNum, &target, &newName), _it(it), _name(newName), _args(nulOf<arr>()) {}

    public:
        str run(const ncontainer& args) {
            // believe that this expression was checked to be valid.
            return str(_it->sub(_name, _args));
        }

        wbool isValid() const override {
            if(!_it) return false;

            narr subs = _it->subAll(_name, _args);
            return subs.len() == 1;
        }

    private:
        const Ref& _it;
        const wStr& _name;
        const arr& _args;
    };
}
