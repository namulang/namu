#pragma once

#include "../../ast/param.hpp"

namespace wrd {

    class node;
    template <typename T>
    class tnucontainer;
    template <typename T, typename TACTIC> class tnarr;
    typedef tnarr<node, strTactic> narr;

    /// @remark tucontainable has API treating iter ref and element as its parameter.
    template <typename T>
    class tucontainable {
        WRD_DECL_ME(tucontainable)

    public:
        #include "iter/uiter.hpp"

    public:
        virtual ~tucontainable() {}

        // len:
        virtual wcnt len() const = 0;

        // get:
        template <typename E>
        E& get(std::function<wbool(const E&)> l) const;
        T& get(std::function<wbool(const T&)> l) const;
        template <typename E>
        tnarr<E, strTactic> getAll(std::function<wbool(const E&)> l) const;
        narr getAll(std::function<wbool(const T&)> l) const;

        // iter:
        iter begin() const { return iterate(0); }
        virtual iter end() const { return iterate(len()); }
        virtual iter last() const { return iterate(len()-1); }
        iter iterate(wcnt step) const { return iter(_onMakeIteration(step)); }
        iter iterate(const T& it) const {
            for(iter e = begin(); e ; ++e)
                if(&e.get() == &it)
                    return iter(e);

            return iter();
        }

        // set:
        virtual wbool set(const iter& at, const T& new1) = 0;
        wbool set(const iter& at, const T* new1) { return set(at, *new1); }

        // add:
        virtual wbool add(const iter& at, const T& new1) = 0;
        wbool add(const iter& at, const T* new1) { return add(at, *new1); }
        wbool add(std::initializer_list<const T*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = add(elem);
            return ret;
        }
        wbool add(const T* new1) { return add(*new1); }
        wbool add(const T& new1) { return add(end(), new1); }
        template <typename E>
        wcnt add(const typename tucontainable<E>::iter& from, const typename tucontainable<E>::iter& to) {
            static_assert(areBaseOfT<T, E>::value, "given type 'E' is not subtype of 'T'");
            int ret = 0;
            for(auto e=from; e != to ;++e)
                if(add(*e))
                    ret++;
            return ret;
        }
        wcnt add(const iter& from, const iter& to) { return add<T>(from, to); }
        template <typename E>
        wcnt add(const tucontainable<E>& rhs) { return add(rhs.begin(), rhs.end()); }
        wcnt add(const me& rhs) { return add<T>(rhs); }

        // del:
        /// delete last element if exists.
        wbool del() { return del(iterate(len() - 1)); }
        wbool del(const T* it) { return del(*it); }
        wbool del(const T& it) { return del(iterate(it)); }
        virtual wbool del(const iter& it) = 0;
        virtual wcnt del(const iter& from, const iter& end) = 0;
        wcnt del(const tucontainable& rhs) { return del(rhs.begin(), rhs.end()); }

        // etc:
        virtual void rel() = 0;

        virtual tstr<instance> deepClone() const = 0;

    protected:
        virtual iteration* _onMakeIteration(wcnt step) const = 0;
    };

    typedef tucontainable<node> ucontainable;
}
