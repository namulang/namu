#pragma once

#include "srcFile.hpp"

namespace namu {
    class _nout src : public instance {
        NAMU(CLASS(src, instance))

    public:
        src(const srcFile& file, const point& pos);

        const srcFile& getFile() const;
        const point& getPos() const;

    private:
        tstr<srcFile> _file;
        point _pos;
    };

    template <typename T, typename WRP> class tnarr;
    typedef tnarr<src> srcs;
}
