#pragma once

#include "node.hpp"

namespace wrd {

    class expr : public node {
        WRD_INTERFACE(expr, node)

    public:
        expr(std::initializer_list<const node*> newTerms): _terms(newTerms) {}

    public:
        ncontainer& subs() override {
            return _terms;
        }

        wbool canRun(const wtypes& args) const override {
            return args.size() == 0;
        }

        wbool isValid() const override {
            for(node& term : _terms)
                if(term.isValid())
                    return false;

            return true;
        }

    private:
        narr _terms;
    };
}
