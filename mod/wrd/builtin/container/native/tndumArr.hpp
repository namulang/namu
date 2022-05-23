#pragma once

#include "tnarr.inl"

namespace wrd {

    template <typename T, typename WRAPPER = str>
    class tndumArr: public tnarr<T, WRAPPER> {
        typedef tnarr<T, WRAPPER> _super_;
        WRD(CLASS(tndumArr, _super_))

    public:
        tndumArr() {}

        // add:
        using super::add;
        wbool add(const typename super::iter& e, const node& new1) override { return false; }
        wbool add(widx n, const node& new1) override { return false; }

    public:
        static me singletone;
    };

    typedef tndumArr<node, str> ndumArr;
}
