#pragma once

#include "tnarr.inl"

namespace wrd {

    template <typename T, typename WRAPPER = str>
    class tndumArr: public tnarr<T, WRAPPER> {
        WRD(CLASS(tndumArr, tnarr))

    public:
        tndumArr() {}

        // add:
        using super::add;
        wbool add(const wrd::iter& e, const node& new1) override { return false; }
        wbool add(widx n, const node& new1) override { return false; }

    public:
        static me singletone;
    };

    typedef tnarr<node, str> ndumArr;
}
