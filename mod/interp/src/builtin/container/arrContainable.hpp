#pragma once

#include "containable.hpp"

namespace wrd {

    /// @remark arrContainable has API treating index as its parameter.
    class arrContainable {
        WRD_DECL_ME(arrContainable)

    public:
        virtual ~arrContainable() {}

        virtual node& operator[](widx n) = 0;
        virtual const node& operator[](widx n) const = 0;

        virtual node& get(widx n) = 0;
        virtual const node& get(widx n) const = 0;

        virtual wbool set(widx n, const node& new1) = 0;
        wbool set(widx n, const node* new1) {
            return set(n, *new1);
        }

        /// @return how many element has been added from rhs.
        virtual wbool add(widx n, const node& new1) = 0;
        wbool add(widx n, const node* new1) {
            return add(n, *new1);
        }

        /// delete last element if exists.
        /// @return true if element got deleted successfully.
        virtual wbool del(widx n) = 0;
    };
}
