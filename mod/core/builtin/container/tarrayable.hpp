#pragma once

#include "../../type/wtype.hpp"
#include "../../common.hpp"

namespace namu {

    /// @remark arrayable has API treating index as its parameter.
    template <typename T>
    class tarrayable {
        WRD_DECL_ME(tarrayable)

    public:
        virtual ~tarrayable() {}

        // operator:
        virtual T& operator[](widx n) = 0;
        const T& operator[](widx n) const { return get(n); }

        // has:
        virtual wbool has(widx n) const = 0;

        // get:
        virtual T& get(widx n) = 0;
        const T& get(widx n) const WRD_UNCONST_FUNC(get(n))

        // set:
        virtual wbool set(widx n, const T& new1) = 0;
        wbool set(widx n, const T* new1) { return set(n, *new1); }

        // add:
        /// @return how many element has been added from rhs.
        virtual wbool add(widx n, const T& new1) = 0;
        wbool add(widx n, const T* new1) { return add(n, *new1); }

        // del:
        /// delete last element if exists.
        /// @return true if element got deleted successfully.
        virtual wbool del(widx n) = 0;
    };
}
