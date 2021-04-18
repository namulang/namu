#pragma once

#include "iterator/iterator.hpp"

namespace wrd {

    class narr;
    template <typename T> class tnarr;

    /// @remark containable has API treating iterator ref and element as its parameter.
    class containable {
        WRD_DECL_ME(containable)

    public:
        virtual ~containable() {}

        virtual wcnt getLen() const = 0;

        virtual narr get(std::function<wbool(const node&)> l) const = 0;

        virtual wbool set(const iterator& at, const node& new1) = 0;
        wbool set(const iterator& at, const node* new1) {
            return set(at, *new1);
        }

        virtual iterator head() const { return iter(0); }
        virtual iterator tail() const { return iter(getLen()); }
        virtual iterator last() const { return iter(getLen()-1); }

        /// @param step step from the head of this container.
        virtual iterator iter(wcnt step) const = 0;

        virtual wbool add(const node& new1) = 0;
        wbool add(std::initializer_list<node*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = add(elem);
            return ret;
        }

        wbool add(const node* new1) {
            return add(*new1);
        }
        virtual wbool add(const iterator& at, const node& new1) = 0;
        wbool add(const iterator& at, const node* new1) {
            return add(at, *new1);
        }
        virtual wcnt add(const iterator& from, const iterator& to) = 0;
        virtual wcnt add(const containable& rhs) = 0;

        virtual wbool del() = 0;
        virtual wbool del(const node& it) = 0;
        wbool del(const node* it) {
            return del(*it);
        }
        virtual wbool del(const iterator& it) = 0;
        virtual wcnt del(const iterator& from, const iterator& to) = 0;
        virtual wcnt del(const containable& rhs) = 0;

        virtual void empty() = 0;
    };

}
