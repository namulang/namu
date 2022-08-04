#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout exprMaker : public typeProvidable, public clonable {
        NAMU(CLASS(exprMaker))

    public:
        exprMaker(): _src(nullptr), _pos({0, 0}) {}
        exprMaker(const src& s, ncnt row, ncnt col) {
            setSrc(s);
            setCol(row);
            setCol(col);
        }

    public:
        me& addRow() { return addRow(1); }
        me& addRow(ncnt step) { return setRow(_pos.row + step); }
        me& addCol() { return addCol(1); }
        me& addCol(ncnt step) { return setCol(_pos.col + step); }

        me& setRow(ncnt row) {
            _pos.row = row;
            return *this;
        }

        me& setCol(ncnt col) {
            _pos.col = col;
            return *this;
        }

        me& setSrc(const src& s) {
            _src = &s;
            return *this;
        }

        const point& getPos() const { return _pos; }
        const src& getSrc() const { return *_src; }

        template <typename T, typename... Args>
        T* make(const Args&... args) const {
            T* ret = new T(args...);
            if(_src)
                ret->_setSrc(*_src);
            ret->_setPos(_pos);
            return ret;
        }

    private:
        const src* _src;
        point _pos;
    };
}
