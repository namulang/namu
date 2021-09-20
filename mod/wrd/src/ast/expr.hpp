#pragma once

#include "src.hpp"

namespace wrd {

    class expr : public node {
        WRD(INTERFACE(expr, node))
        friend class exprMaker;

    public:
        ncontainer& subs() override;

        wbool canRun(const wtypes& args) const override {
            return args.size() == 0;
        }

        const src& getSrc() const {
            return *_src;
        }

        wcnt getLine() const {
            return _lineNum;
        }

        wbool isValid() const override {
            if(_lineNum < 1) return false;

            return true;
        }

    protected:
        void _setSrc(const src& newSrc) {
            _src.bind(newSrc);
        }

        wcnt getLineNum() const {
            return _lineNum;
        }

    private:
        tstr<src> _src;
        wcnt _lineNum;
    };
}
