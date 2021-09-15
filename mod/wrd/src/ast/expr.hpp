#pragma once

#include "node.hpp"

namespace wrd {

    class expr : public node {
        WRD(INTERFACE(expr, node))

    public:
        expr(const src& s, wcnt lineNum, std::initializer_list<const node*> newTerms)
            : _terms(newTerms), _src(s), _lineNum(lineNum) {}

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

        const src& getSrc() const {
            return *_src;
        }

        wcnt getLineNum() const {
            return _lineNum;
        }

    private:
        narr _terms;
        tstr<src> _src;
        wcnt _lineNum;
    };
}
