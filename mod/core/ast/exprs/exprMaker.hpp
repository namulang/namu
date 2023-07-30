#pragma once

#include "../expr.hpp"

namespace namu {

    class _nout exprMaker : public typeProvidable, public clonable {
        NAMU(CLASS(exprMaker))

    public:
        exprMaker();
        exprMaker(const src& s, ncnt row, ncnt col);

    public:
        me& addRow();
        me& addRow(ncnt step);
        me& addCol();
        me& addCol(ncnt step);

        me& setRow(ncnt row);
        me& setCol(ncnt col);
        me& setSrc(const src& s);

        void rel();

        const point& getPos() const;
        const src& getSrc() const;

        template <typename T, typename... Args>
        T* make(const Args&... args) const {
            T* ret = new T(args...);
            if(_src)
                ret->_setSrc(*_src);
            ret->_setPos(_pos);
            return ret;
        }

    private:
        tstr<src> _src;
        point _pos;
    };
}
