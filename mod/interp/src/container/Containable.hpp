#pragma once

#include "iterator/Iter.hpp"

namespace wrd {

    class NArr;
    template <typename T> class TNArr;
    class Containable {
        WRD_DECL_THIS(Containable)

    public:
        virtual wcnt getLen() const = 0;

        virtual NArr get(std::function<wbool(const Node&)> l) const = 0;

        virtual wbool set(const Iter& at, const Node& new1) = 0;

        virtual Iter head() const = 0;
        virtual Iter tail() const = 0;

        virtual wbool add(const Iter& e, const Node& new1) = 0;
        virtual wbool del(const Iter& it) = 0;

        virtual void empty() = 0;
    };

}
