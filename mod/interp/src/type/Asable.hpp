#pragma once

#include "../common.hpp"

namespace wrd {

    class WType;
    class Ref;
    template <typename T>
    class TRef;

    struct Asable {
        virtual wbool is(const Type& type) const = 0;
        wbool is(const Node& inst) const;

        virtual Ref as(const Node& it) const = 0;
        template <typename T>
        TRef<T> as(const Node& it) const;
    };

    typedef std::vector<Asable*> Ases;
}
