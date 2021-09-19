#pragma once

#include "../expr.hpp"

namespace wrd {

    class exprMaker : public typeProvidable, public clonable {
        WRD(CLASS(exprMaker))

    public:
        exprMaker(): _src(nullptr), _lineNum(0) {}
        exprMaker(const src& s, int lineNum) {
            setSrc(s);
            setLine(lineNum);
        }

    public:
        me& operator++(int) { return addLine(); }
        me& operator--(int) { return addLine(-1); }

    public:
        me& addLine() { return addLine(1); }
        me& addLine(int step) { return setLine(_lineNum + step); }
        me& setLine(int newLineNum) {
            _lineNum = newLineNum;
            return *this;
        }

        me& setSrc(const src& s) {
            _src = &s;
            return *this;
        }

        int getLine() const { return _lineNum; }
        const src& getSrc() const { return *_src; }

        template <typename T, typename... Args>
        T* make(Args... args) const {
            expr* ret = new T(args...);
            if(_src)
                ret->_setSrc(*_src);
            ret->_setLine(_lineNum);
            return ret;
        }

    private:
        src* _src;
        int _lineNum;
    };
}
