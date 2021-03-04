#pragma once

#include "iterator/Iter.hpp"

namespace wrd {

    class NArr;
    template <typename T> class TNArr;

    /// @remark Containable has API treating iter ref and element as its parameter.
    class Containable {
        WRD_DECL_THIS(Containable)

    public:
        virtual ~Containable() {}

        virtual wcnt getLen() const = 0;

        virtual NArr get(std::function<wbool(const Node&)> l) const = 0;

        virtual wbool set(const Iter& at, const Node& new1) = 0;
        wbool set(const Iter& at, const Node* new1) {
            return set(at, *new1);
        }

        virtual Iter head() const = 0;
        virtual Iter tail() const = 0;

        virtual wbool add(const Node& new1) = 0;
        wbool add(const Node* new1) {
            return add(*new1);
        }
        virtual wbool add(const Iter& at, const Node& new1) = 0;
        wbool add(const Iter& at, const Node* new1) {
            return add(at, *new1);
       }
        virtual wcnt add(const Iter& from, const Iter& to) = 0;
        virtual wcnt add(const Containable& rhs) = 0;

        virtual wbool del() = 0;
        virtual wbool del(const Node& it) = 0;
        wbool del(const Node* it) {
            return del(*it);
        }
       virtual wbool del(const Iter& it) = 0;
        virtual wcnt del(const Iter& from, const Iter& to) = 0;
        virtual wcnt del(const Containable& rhs) = 0;

        virtual void empty() = 0;
    };

}
