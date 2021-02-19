#pragma once

#include "iterator/Iter.hpp"

namespace wrd {

    class NArr;
    template <typename T> class TNArr;
    class Containable {
        WRD_DECL_THIS(Containable)

    public:
        virtual wcnt getLen() const = 0;

        template <typename T>
        TNArr<T> get(std::function<wbool(const T&)> l) const;
        NArr get(std::function<wbool(const Node&)> l) const;

        virtual wbool set(const Iter& at, const Node& new1) = 0;

        virtual Iter head() const = 0;
        virtual Iter tail() const = 0;

        template <typename T>
        void each(const Iter& from, const Iter& to, std::function<wbool(Iter&, T&)> l);
        template <typename T>
        void each(std::function<wbool(Iter&, T&)> l) {
            each(head(), tail(), l);
        }
        template <typename T>
        void each(const Iter& from, const Iter& to, std::function<wbool(const Iter&, const T&)> l) const;
        template <typename T>
        void each(std::function<wbool(const Iter&, const T&)> l) const {
            each(head(), tail(), l);
        }

        virtual void empty() = 0;
    };

}
