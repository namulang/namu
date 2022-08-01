#pragma once

#include "sobj.hpp"

namespace wrd {

    class _wout nullSobj : public sobj {
        WRD_DECL_ME(nullSobj, sobj)
        WRD_INIT_META(nullSobj)

    public:
        nullSobj();

    public:
        const std::string& asStr() const override;
        wchar asChar() const override;
        wint asInt() const override;
        wbool asBool() const override;
        const type& getType() const override;
        wbool isExist() const override;

    public:
        static me& get();
    };
}
