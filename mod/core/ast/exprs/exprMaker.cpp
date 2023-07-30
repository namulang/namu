#include "exprMaker.hpp"

namespace namu {

    NAMU(DEF_ME(exprMaker))

    me::exprMaker() {}

    me::exprMaker(const src& s, ncnt row, ncnt col) {
        setSrc(s);
        setCol(row);
        setCol(col);
    }

    me& me::addRow() {
        return addRow(1);
    }

    me& me::addRow(ncnt step) {
        return setRow(_pos.row + step);
    }

    me& me::addCol() {
        return addCol(1);
    }

    me& me::addCol(ncnt step) {
        return setCol(_pos.col + step);
    }

    me& me::setRow(ncnt row) {
        _pos.row = row;
        return *this;
    }

    me& me::setCol(ncnt col) {
        _pos.col = col;
        return *this;
    }

    me& me::setSrc(const src& s) {
        _src.bind(s);
        return *this;
    }

    void me::rel() {
        _src.rel();
        _pos.rel();
    }

    const point& me::getPos() const {
        return _pos;
    }

    const src& me::getSrc() const {
        return *_src;
    }
}
