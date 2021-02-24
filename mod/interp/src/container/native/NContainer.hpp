#pragma once

#include "../Containable.hpp"

namespace wrd {

    class NContainer : public Instance, public Containable, public Clonable {
        WRD_INTERFACE(NContainer, Instance)

    public:
        using Containable::get;
        template <typename T>
        TNArr<T> get(std::function<wbool(const T&)> l) const;
        NArr get(std::function<wbool(const Node&)> l) const override;

        template <typename T>
        void each(const Iter& from, const Iter& to, std::function<wbool(Iter&, T&)> l);
        template <typename T>
        void each(const Iter& from, const Iter& to, std::function<wbool(const Iter&, const T&)> l) const;

        template <typename T>
        void each(std::function<wbool(Iter&, T&)> l);
        template <typename T>
        void each(std::function<wbool(const Iter&, const T&)> l) const;
    };
}
