#pragma once

#include "sobj.hpp"

namespace namu {

    class _nout nullSobj : public sobj {
        NAMU(ME(nullSobj, sobj),
            CLONE(me),
            INIT_META(nullSobj))

    public:
        nullSobj();

    public:
        const std::string& asStr() const override;
        nchar asChar() const override;
        nint asInt() const override;
        nbool asBool() const override;
        const type& getType() const override;
        nbool isExist() const override;

    public:
        static me& get();
    };
}
