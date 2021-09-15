#pragma once

#include "native/iter/titer.hpp"

namespace wrd {


    class node;
    template <typename T> class tnarr;
    typedef tnarr<node> narr;

    /// @remark containable has API treating iter ref and element as its parameter.
    class containable {
        WRD_DECL_ME(containable)

    public:
        virtual ~containable() {}

        // len:
        virtual wcnt len() const = 0;

        // get:
        template <typename T>
        T& get(std::function<wbool(const T&)> l) const;
        node& get(std::function<wbool(const node&)> l) const;
        template <typename T>
        tnarr<T> getAll(std::function<wbool(const T&)> l) const;
        narr getAll(std::function<wbool(const node&)> l) const;

        // iter:
        wrd::iter begin() const { return iter<node>(0); }
        virtual wrd::iter end() const { return iter<node>(len()); }
        virtual wrd::iter last() const { return iter<node>(len()-1); }
        template <typename T> titer<T> begin() const { return iter<T>(0); }
        template <typename T> titer<T> end() const { return iter<T>(len()); }
        template <typename T> titer<T> last() const { return iter<T>(len()-1); }
        template <typename T> titer<T> iter(wcnt step) const { return titer<T>(_onMakeIteration(step)); }
        wrd::iter iter(wcnt step) const { return iter<node>(step); }
        wrd::iter iter(const node& elem) const {
            return iter<node>(elem);
        }
        template <typename T>
        titer<T> iter(const T& it) const {
            for(titer<T> e=begin<T>(); e ; ++e)
                if(&e.get() == &it)
                    return titer<T>(e);

            return titer<T>();
        }

        // set:
        virtual wbool set(const wrd::iter& at, const node& new1) = 0;
        wbool set(const wrd::iter& at, const node* new1) { return set(at, *new1); }

        // add:
        virtual wbool add(const wrd::iter& at, const node& new1) = 0;
        wbool add(std::initializer_list<const node*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = add(elem);
            return ret;
        }
        wbool add(const node* new1) { return add(*new1); }
        wbool add(const node& new1) {
            return add(end(), new1);
        }
        wcnt add(const wrd::iter& from, const wrd::iter& to) {
            int ret = 0;
            for(wrd::iter e=from; e != to ;++e)
                if(add(*e))
                    ret++;
            return ret;
        }
        wcnt add(const containable& rhs) {
            return add(rhs.begin(), rhs.end());
        }
        wbool add(const wrd::iter& at, const node* new1) { return add(at, *new1); }

        // del:
        /// delete last element if exists.
        wbool del() { return del(iter(len() - 1)); }
        wbool del(const node* it) { return del(*it); }
        wbool del(const node& it) { return del(iter(it)); }
        virtual wbool del(const wrd::iter& it) = 0;
        virtual wcnt del(const wrd::iter& from, const wrd::iter& end) = 0;
        wcnt del(const containable& rhs) { return del(rhs.begin(), rhs.end()); }

        // etc:
        virtual void rel() = 0;

        virtual tstr<instance> deepClone() const = 0;

    protected:
        virtual iteration* _onMakeIteration(wcnt step) const = 0;
    };

}
