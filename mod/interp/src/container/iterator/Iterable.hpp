#pragma once

#include "../../type/WType.hpp"

namespace wrd {

    class Containable;
    class Node;
    class Iterable {
        WRD_DECL_THIS(Iterable)

    public:
        virtual wbool isEnd() const = 0;
        virtual wbool next() = 0;
        virtual Node& get() = 0;
        const Node& get() const WRD_UNCONST_FUNC(get())
        virtual wbool isFrom(const Containable& it) const = 0;
        virtual Containable& getContainer() = 0;
        const Containable& getContainer() const WRD_UNCONST_FUNC(getContainer())
    };
}
