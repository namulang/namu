#pragma once

#include "tnarr.inl"

namespace wrd {

    template <typename T, typename WRAPPER = str>
    class tndumArr: public tnarr<T, WRAPPER> {
        typedef tnarr<T, WRAPPER> __super;
        WRD(CLASS(tndumArr, __super))

    public:
        tndumArr() {}

        // add:
        using super::add;
        wbool add(const typename super::iter& e, const node& new1) override { return false; }
        wbool add(widx n, const node& new1) override { return false; }

    public:
        static me singletone;
    };

    typedef tnarr<node, str> ndumArr;
}
