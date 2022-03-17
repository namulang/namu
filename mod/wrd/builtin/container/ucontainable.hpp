#pragma once

#include "containable.hpp"

namespace wrd {

    /// @remark ucontainable has API treating index as its parameter.
    class ucontainable {
        WRD_DECL_ME(ucontainable)

    public:
        virtual ~ucontainable() {}

        // operator:
        virtual node& operator[](widx n) = 0;
        virtual const node& operator[](widx n) const = 0;

        // get:
        virtual node& get(widx n) = 0;
        virtual const node& get(widx n) const = 0;

        // set:
        virtual wbool set(widx n, const node& new1) = 0;
        virtual wbool set(widx n, const str& new1) { return set(n, *new1); }
        wbool set(widx n, const node* new1) { return set(n, *new1); }

        // add:
        /// @return how many element has been added from rhs.
        virtual wbool add(widx n, const node& new1) = 0;
        virtual wbool add(widx n, const str& new1) { return add(n, *new1); }
        wbool add(widx n, const node* new1) { return add(n, *new1); }

        // del:
        /// delete last element if exists.
        /// @return true if element got deleted successfully.
        virtual wbool del(widx n) = 0;
    };
}
