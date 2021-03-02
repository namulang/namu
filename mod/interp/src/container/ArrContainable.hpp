#pragma once

#include "Containable.hpp"

namespace wrd {

    class ArrContainable {
        WRD_DECL_THIS(ArrContainable)

    public:
        virtual Node& operator[](widx n) = 0;
        virtual const Node& operator[](widx n) const = 0;

        virtual Node& get(widx n) = 0;
        virtual const Node& get(widx n) const = 0;

        virtual wbool set(widx n, const Node& new1) = 0;
        wbool set(widx n, const Node* new1) {
            return set(n, *new1);
        }

        virtual Iter iter(widx n) const = 0;

        virtual wbool add(const Node& new1) = 0;
        wbool add(const Node* new1) {
            return add(*new1);
        }
        virtual wcnt add(const Iter& from, const Iter& to) = 0;
        /// @return how many element has been added from rhs.
        virtual wcnt add(const Containable& rhs) = 0;
        virtual wbool add(widx n, const Node& new1) = 0;
        wbool add(widx n, const Node* new1) {
            return add(n, *new1);
        }

        virtual wbool del(const Node& it) = 0;
        wbool del(const Node* it) {
            return del(*it);
        }

        /// delete last element if exists.
        virtual wbool del() = 0;
        virtual wcnt del(const Iter& from, const Iter& to) = 0;
        virtual wcnt del(const Containable& rhs) = 0;
        /// @return true if element got deleted successfully.
        virtual wbool del(widx n) = 0;

    protected:
        virtual Iteration* _onIter(widx n) const = 0;
    };
}
