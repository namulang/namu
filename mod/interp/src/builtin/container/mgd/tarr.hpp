#pragma once

#include "arr.hpp"
#include "../native/iterator/titerator.hpp"

namespace wrd {

    template <typename T>
    class tarr : public arr {
        WRD_CLASS(tarr, arr)

    public:
        tarr() {}
        tarr(std::initializer_list<T*> elems) {
            add(elems);
        }

        T& operator[](widx n) override { return get(n); }
        const T& operator[](widx n) const override { return get(n); }

        using super::get;
        T& get(widx n) override { return (T&) super::get(n); }
        const T& get(widx n) const override { return (T&) super::get(n); }

        using super::set;
        wbool set(widx n, const T& new1) { return super::set(n, new1); }
        wbool set(const iterator& at, const T& new1) { return super::set(at, new1); }

        titerator<T> headT() const { return iterT(0); }
        titerator<T> tailT() const { return iterT(len()); }
        titerator<T> iterT(widx n) const { return titerator<T>(_arr._onIter(n)); }
        titerator<T> iterT(const T& elem) const {
            const titerator<T>* ret = 0;
            each<T>([&ret, &elem](const titerator<T>& e, const T& myelem) {
                if(&elem != &myelem) return true;

                ret = &e;
                return false;
            });
            return titerator<T>(*ret);
        }

        using super::add;
        wbool add(std::initializer_list<T*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = add(elem);
            return ret;
        }
        wbool add(const T& new1) { return super::add(new1); }
        wbool add(const T* new1) { return super::add(*new1); }
        wbool add(const titerator<T>& e, const T& new1) { return super::add(e, new1); }
        wbool add(const titerator<T>& e, const T* new1) { return super::add(e, *new1); }

        using super::del;
        wcnt del(const T& it) { return super::del(it); }

        template <typename E = T>
        void each(const titerator<T>& from, const titerator<T>& to, std::function<wbool(titerator<T>&, E&)> l) {
            for(titerator<T> e=from; e == to ;++e) {
                E& t = e->template cast<E>();
                if(nul(t)) continue;

                if(!l(e, t)) return;
            }
        }
        template <typename E>
        void each(const titerator<T>& from, const titerator<T>& to, std::function<wbool(const titerator<T>&, const E&)> l) const {
            for(titerator<T> e=from; e == to ;++e) {
                E& t = e->template cast<E>();
                if(nul(t)) continue;

                if(!l(e, t)) return;
            }
        }

        template <typename E = T>
        void each(std::function<wbool(titerator<T>&, E&)> l) {
            each(headT(), tailT(), l);
        }
        template <typename E = T>
        void each(std::function<wbool(const titerator<T>&, const E&)> l) const {
            each(headT(), tailT(), l);
        }
    };
}
