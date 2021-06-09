#pragma once

#include "native/iterator/titerator.hpp"

namespace wrd {


    class node;
    template <typename T> class tnarr;
    typedef tnarr<node> narr;

    /// @remark containable has API treating iterator ref and element as its parameter.
    class containable {
        WRD_DECL_ME(containable)

    public:
        virtual ~containable() {}

        // len:
        virtual wcnt len() const = 0;

        // get:
        template <typename T>
        tnarr<T> get(std::function<wbool(const T&)> l) const;
        narr get(std::function<wbool(const node&)> l) const;

        // iter:
        iterator begin() const { return iter<node>(0); }
        iterator end() const { return iter<node>(len()); }
        iterator last() const { return iter<node>(len()-1); }
        template <typename T> titerator<T> begin() const { return iter<T>(0); }
        template <typename T> titerator<T> end() const { return iter<T>(len()); }
        template <typename T> titerator<T> last() const { return iter<T>(len()-1); }
        template <typename T> titerator<T> iter(wcnt step) const { return titerator<T>(_onMakeIteration(step)); }
        iterator iter(wcnt step) const { return iter<node>(step); }
        iterator iter(const node& elem) const {
            return iter<node>(elem);
        }
        template <typename T>
        titerator<T> iter(const T& it) const {
            for(titerator<T> e=begin<T>(); e ; ++e)
                if(&e.get() == &it)
                    return titerator<T>(e);

            return titerator<T>();
        }

        // set:
        virtual wbool set(const iterator& at, const node& new1) = 0;
        wbool set(const iterator& at, const node* new1) { return set(at, *new1); }

        // add:
        virtual wbool add(const iterator& at, const node& new1) = 0;
        wbool add(std::initializer_list<node*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = add(elem);
            return ret;
        }
        wbool add(const node* new1) { return add(*new1); }
        wbool add(const node& new1) {
            return add(end(), new1);
        }
        wcnt add(const iterator& from, const iterator& to) {
            int ret = 0;
            for(iterator e=from; e != to ;++e) {
                if(add(*e)) ret++;
                return true;
            }
            return ret;
        }
        wcnt add(const containable& rhs) {
            return add(rhs.begin(), rhs.end());
        }
        wbool add(const iterator& at, const node* new1) { return add(at, *new1); }

        // del:
        /// delete last element if exists.
        wbool del() { return del(iter(len() - 1)); }
        wbool del(const node* it) { return del(*it); }
        wbool del(const node& it) { return del(iter(it)); }
        virtual wbool del(const iterator& it) = 0;
        virtual wcnt del(const iterator& from, const iterator& end) = 0;
        wcnt del(const containable& rhs) { return del(rhs.begin(), rhs.end()); }

        // etc:
        virtual void empty() = 0;

        virtual tstr<instance> deepClone() const = 0;

    protected:
        virtual iteration* _onMakeIteration(wcnt step) const = 0;
    };

}
