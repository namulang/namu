#pragma once

#include "Containable.hpp"

namespace wrd {

    /// @remark ArrContainable has API treating index as its parameter.
    class ArrContainable {
        WRD_DECL_THIS(ArrContainable)

    public:
        virtual ~ArrContainable() {}

        virtual Node& operator[](widx n) = 0;
        virtual const Node& operator[](widx n) const = 0;

        virtual Node& get(widx n) = 0;
        virtual const Node& get(widx n) const = 0;

        virtual wbool set(widx n, const Node& new1) = 0;
        wbool set(widx n, const Node* new1) {
            return set(n, *new1);
        }

        virtual Iter iter(widx n) const = 0;

        /// @return how many element has been added from rhs.
        virtual wbool add(widx n, const Node& new1) = 0;
        wbool add(widx n, const Node* new1) {
            return add(n, *new1);
        }

        /// delete last element if exists.
        /// @return true if element got deleted successfully.
        virtual wbool del(widx n) = 0;

    protected:
        virtual Iteration* _onIter(widx n) const = 0;
    };
}
