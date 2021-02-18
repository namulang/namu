#pragma once

#include "../../ast/Clonable.hpp"
#include "../../type/WType.hpp"

namespace wrd {

    class Containable;
    class Node;
    class Iterable : public Clonable {
        WRD_INTERFACE(Iterable, Clonable)

    public:
        virtual wbool isEnd() const = 0;
        virtual wbool next() = 0;
        virtual wbool prev() = 0;
        virtual Node& get() = 0;
        virtual const Node& get() const = 0;
        virtual wbool isFrom(const Containable& it) const = 0;
    };

}
