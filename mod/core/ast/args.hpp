#pragma once

#include "../builtin/container/native/tnarr.hpp"
#include "obj.hpp"

namespace namu {

    class _nout args : public narr {
        NAMU(CLASS(args, narr))

    public:
        args() {}
        args(const baseObj& me): _me(me) {}
        args(const narr& rhs): super(rhs) {}
        args(const baseObj& me, const narr& rhs): super(rhs), _me(me) {}

    public:
        const me& setMe(const node& me) const {
            if(nul(me))
                _me.rel();
            else
                _me = me.as<node>();
            return *this;
        }

        node& getMe() const { return *_me; }

        clonable* deepClone() const override {
            me* ret = new me();
            for(auto e=this->begin(); e ;e++)
                ret->add((node*) e->clone());

            ret->_me = _me;
            return ret;
        }

    private:
        mutable str _me;
    };
}
