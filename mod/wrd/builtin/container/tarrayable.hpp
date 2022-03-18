#pragma once

#include "../../type/wtype.hpp"
#include "../../common.hpp"

namespace wrd {

    /// @remark arrayable has API treating index as its parameter.
    template <typename T>
    class tarrayable {
        WRD_DECL_ME(tarrayable)

    public:
        virtual ~tarrayable() {}

        // operator:
        virtual T& operator[](widx n) = 0;
        virtual const T& operator[](widx n) const = 0;

        // get:
        virtual T& get(widx n) = 0;
        virtual const T& get(widx n) const = 0;

        // set:
        virtual wbool set(widx n, const T& new1) { return set(n, str(new1)); }
        virtual wbool set(widx n, const str& new1) = 0;
        wbool set(widx n, const T* new1) { return set(n, *new1); }

        // add:
        /// @return how many element has been added from rhs.
        virtual wbool add(widx n, const T& new1) { return add(n, str(new1)); }
        virtual wbool add(widx n, const str& new1) = 0;
        wbool add(widx n, const T* new1) { return add(n, str(new1)); }

        // del:
        /// delete last element if exists.
        /// @return true if element got deleted successfully.
        virtual wbool del(widx n) = 0;
    };
}
