#include "args.hpp"

namespace namu {

    NAMU(DEF_ME(args))

    me::args() {}
    me::args(const baseObj& me): _me(me) {}
    me::args(const narr& rhs): super(rhs) {}
    me::args(const baseObj& me, const narr& rhs): super(rhs), _me(me) {}

    const me& me::setMe(const node& me) const {
        if(nul(me))
            _me.rel();
        else
            _me = me.as<node>();
        return *this;
    }

    node& me::getMe() const {
        return *_me;
    }

    clonable* me::deepClone() const {
        me* ret = new me();
        for(auto e=this->begin(); e ;e++)
            ret->add((node*) e->clone());

        ret->_me = _me;
        return ret;
    }
}
