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
}
