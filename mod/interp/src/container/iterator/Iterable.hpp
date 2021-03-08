#pragma once

#include "../../type/WType.hpp"

namespace wrd {

    class NContainer;
    class Containable;
    class Node;
    class Iterable {
        WRD_DECL_THIS(Iterable)

    public:
        virtual ~Iterable() {}

        virtual wbool isEnd() const = 0;
        /// proceed Iteration obj to point next element by given step.
        /// @param  step    how much it proceeds.
        ///                 positive value only.
        /// @return how many step it proceeded. if it tries to proceed further when it reached to End()
        ///         it won't be counted as returning value.
        ///         it'll return '0' if it already reached to the end.
        virtual wcnt next(wcnt step) = 0;
        virtual Node& get() = 0;
        const Node& get() const WRD_UNCONST_FUNC(get())
        virtual wbool isFrom(const NContainer& it) const = 0;
        virtual NContainer& getContainer() = 0;
        const NContainer& getContainer() const WRD_UNCONST_FUNC(getContainer())
    };
}
