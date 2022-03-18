#pragma once

#include "../../ast/clonable.hpp"
#include "../../type/wtype.hpp"

namespace wrd {

    class node;
    class tuncontainer;
    template <typename T> class tnarr;
    typedef tnarr<node> narr;

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
        tnarr<E> getAll(std::function<wbool(const E&)> l) const;
        narr getAll(std::function<wbool(const T&)> l) const;

        // iter:
        wrd::iter begin() const { return iter(0); }
        virtual wrd::iter end() const { return iter(len()); }
        virtual wrd::iter last() const { return iter(len()-1); }
        wrd::iter iter(wcnt step) const { return wrd::iter(_onMakeIteration(step)); }
        wrd::iter iter(const T& it) const {
            for(const T& e : this)
                if(&e.get() == &it)
                    return wrd::iter(e);

            return wrd::iter();
        }

        // set:
        virtual wbool set(const wrd::iter& at, const T& new1) { return set(at, str(new1)); }
        virtual wbool set(const wrd::iter& at, const str& new1) = 0;
        wbool set(const wrd::iter& at, const T* new1) { return set(at, str(new1)); }

        // add:
        virtual wbool add(const wrd::iter& at, const T& new1) { return add(at, str(new1)); }
        wbool add(const wrd::iter& at, const T* new1) { return add(at, str(new1)); }
        virtual wbool add(const wrd::iter& at, const str& new1) = 0;
        wbool add(std::initializer_list<const T*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = add(elem);
            return ret;
        }
        wbool add(const T* new1) { return add(str(new1)); }
        wbool add(const T& new1) { return add(end(), str(new1)); }
        wbool add(const str& new1) { return add(end(), new1); }
        wcnt add(const wrd::iter& from, const wrd::iter& to) {
            int ret = 0;
            for(wrd::iter e=from; e != to ;++e)
                if(add(*e))
                    ret++;
            return ret;
        }
        wcnt add(const tucontainable& rhs) { return add(rhs.begin(), rhs.end()); }

        // del:
        /// delete last element if exists.
        wbool del() { return del(iter(len() - 1)); }
        wbool del(const T* it) { return del(*it); }
        wbool del(const T& it) { return del(iter(it)); }
        virtual wbool del(const wrd::iter& it) = 0;
        virtual wcnt del(const wrd::iter& from, const wrd::iter& end) = 0;
        wcnt del(const tucontainable& rhs) { return del(rhs.begin(), rhs.end()); }

        // etc:
        virtual void rel() = 0;

        virtual tstr<instance> deepClone() const = 0;

    protected:
        virtual iteration* _onMakeIteration(wcnt step) const = 0;
    };
}
