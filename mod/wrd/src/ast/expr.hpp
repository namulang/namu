#pragma once

#include "src.hpp"

struct exprTest;

namespace wrd {

    class expr : public node {
    public:
        class exprType : public wtype {
            WRD(ME(exprType, wtype))

        public:
            using super::asImpli;
            str asImpli(const node& from, const type& to) const override {
                return str(((node&) from).run());
            }
        };

        WRD(INTERFACE(expr, node, exprType))
        friend class exprMaker;
        friend struct ::exprTest;

    public:
        expr(): _lineNum(0) {}

    public:
        using super::subs;
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
            if(nul(getEvalType())) return false;

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
