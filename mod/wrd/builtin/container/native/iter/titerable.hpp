#pragma once

#include "../../../../common.hpp"

namespace wrd {

    class ncontainer;
    class containable;
    class node;

    template <typename T>
    class titerable {
        WRD_DECL_ME(titerable)

    public:
        virtual ~titerable() {}

        virtual wbool isEnd() const = 0;
        /// proceed iteration obj to point next element by given step.
        /// @param  step    how much it proceeds.
        ///                 positive value only.
        /// @return how many step it proceeded. if it tries to proceed further when it reached to End()
        ///         it won't be counted as returning value.
        ///         it'll return '0' if it already reached to the end.
        virtual wcnt next(wcnt step) = 0;
        virtual T& get() = 0;
        const T& get() const WRD_UNCONST_FUNC(get())
        virtual wbool isFrom(const ncontainer& it) const = 0;
        virtual ncontainer& getContainer() = 0;
        const ncontainer& getContainer() const WRD_UNCONST_FUNC(getContainer())
    };
}
