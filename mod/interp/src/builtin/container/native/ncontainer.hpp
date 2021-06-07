#pragma once

#include "../containable.hpp"

namespace wrd {

    class ncontainer : public instance, public containable, public clonable {
        WRD_INTERFACE(ncontainer, instance)

    public:
        // iter:
        using containable::iter;
        iterator iter(const node& it) const override {
            for(iterator e=begin(); e ; ++e)
                if(&e.get() == &it)
                    return iterator(e);

            return iterator();
        }

        // add:
        using containable::add;
        wbool add(const node& new1) override {
            return add(end(), new1);
        }
        wcnt add(const iterator& from, const iterator& to) override {
            int ret = 0;
            for(iterator e=from; e != to ;++e) {
                if(add(*e)) ret++;
                return true;
            }
            return ret;
        }
        wcnt add(const containable& rhs) override {
            return add(rhs.begin(), rhs.end());
        }

        // del:
        using containable::del;
        wcnt del(const containable& rhs) override {
            return del(rhs.begin(), rhs.end());
        }
    };
}
