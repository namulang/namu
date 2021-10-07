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

        const point& getPos() const {
            return _pos;
        }

    protected:
        void _setSrc(const src& newSrc) {
            _src.bind(newSrc);
        }

        void _setPos(const point& newPos) {
            _pos = newPos;
        }

    private:
        tstr<src> _src;
        point _pos;
    };
}
