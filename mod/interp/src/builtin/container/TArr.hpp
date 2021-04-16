#pragma once

#include "Arr.hpp"
#include "../../container/iterator/TIter.hpp"

namespace wrd {

    template <typename T>
    class TArr : public Arr {
        WRD_CLASS(TArr, Arr)

    public:
        TArr() {}
        TArr(std::initializer_list<T*> elems) {
            add(elems);
        }

        T& operator[](widx n) override { return get(n); }
        const T& operator[](widx n) const override { return get(n); }

        using super::get;
        T& get(widx n) override { return (T&) super::get(n); }
        const T& get(widx n) const override { return (T&) super::get(n); }

        using super::set;
        wbool set(widx n, const T& new1) { return super::set(n, new1); }
        wbool set(const Iter& at, const T& new1) { return super::set(at, new1); }

        TIter<T> headT() const { return iterT(0); }
        TIter<T> tailT() const { return iterT(getLen()); }
        TIter<T> iterT(widx n) const { return TIter<T>(_arr._onIter(n)); }
        TIter<T> iterT(const T& elem) const {
            const TIter<T>* ret = 0;
            each<T>([&ret, &elem](const TIter<T>& e, const T& myelem) {
                if(&elem != &myelem) return true;

                ret = &e;
                return false;
            });
            return TIter<T>(*ret);
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
        wbool add(const TIter<T>& e, const T& new1) { return super::add(e, new1); }
        wbool add(const TIter<T>& e, const T* new1) { return super::add(e, *new1); }

        using super::del;
        wcnt del(const T& it) { return super::del(it); }

        template <typename E = T>
        void each(const TIter<T>& from, const TIter<T>& to, std::function<wbool(TIter<T>&, E&)> l) {
            for(TIter<T> e=from; e == to ;++e) {
                E& t = e->template cast<E>();
                if(nul(t)) continue;

                if(!l(e, t)) return;
            }
        }
        template <typename E>
        void each(const TIter<T>& from, const TIter<T>& to, std::function<wbool(const TIter<T>&, const E&)> l) const {
            for(TIter<T> e=from; e == to ;++e) {
                E& t = e->template cast<E>();
                if(nul(t)) continue;

                if(!l(e, t)) return;
            }
        }

        template <typename E = T>
        void each(std::function<wbool(TIter<T>&, E&)> l) {
            each(headT(), tailT(), l);
        }
        template <typename E = T>
        void each(std::function<wbool(const TIter<T>&, const E&)> l) const {
            each(headT(), tailT(), l);
        }
    };
}
