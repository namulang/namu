#pragma once

#include "../builtin/container/native/tnarr.hpp"
#include "obj.hpp"

namespace namu {

    class args : public narr {
        NAMU(CLASS(args, narr))

    public:
        args() {}
        args(const baseObj& me): _me(me) {}
        args(const narr& rhs): super(rhs) {}
        args(const baseObj& me, const narr& rhs): super(rhs), _me(me) {}

    public:
        me& setObj(const baseObj& me) {
            _me.bind(me);
            return *this;
        }
        baseObj& getObj() const { return *_me; }

    private:
        mutable tstr<baseObj> _me;
    };
}
