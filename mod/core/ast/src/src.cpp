#include "src.hpp"

namespace namu {
    NAMU(DEF_ME(src))

    me::src(const srcFile& file, const point& pos): _file(file), _pos(pos) {}

    const srcFile& me::getFile() const {
        return *_file;
    }

    const point& me::getPos() const {
        return _pos;
    }

    void me::_setFile(const srcFile& new1) {
        _file.bind(new1);
    }

    void me::_setPos(const point& new1) {
        _pos = new1;
    }
}
