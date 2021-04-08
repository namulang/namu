#pragma once

#include "NArr.hpp"
#include "../iterator/TIter.hpp"

namespace wrd {

    template <typename T>
    class TNArr : public NArr {
        WRD_CLASS(TNArr, NArr)

    public:
        TNArr() {}
        TNArr(std::initializer_list<T*> elems) {
            add(elems);
        }

        T& operator[](widx n) override { return get(n); }
        const T& operator[](widx n) const override { return get(n); }

        using Super::get;
        T& get(widx n) override { return (T&) Super::get(n); }
        const T& get(widx n) const override { return (T&) Super::get(n); }

        using Super::set;
        wbool set(widx n, const T& new1) {
            return Super::set(n, new1);
        }
        wbool set(const Iter& at, const T& new1) {
            return Super::set(at, new1);
        }

        TIter<T> headT() const { return iterT(0); }
        TIter<T> tailT() const { return iterT(getLen()); }
        TIter<T> iterT(widx n) const {
            return TIter<T>(_onIter(n));
        }
        TIter<T> iterT(const T& elem) const {
            const TIter<T>* ret = 0;
            each<T>([&ret, &elem](const TIter<T>& e, const T& myelem) {
                if(&elem != &myelem) return true;

                ret = &e;
                return false;
            });
            return TIter<T>(*ret);
        }

        using Super::add;
        wbool add(std::initializer_list<T*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = add(elem);
            return ret;
        }
        wbool add(const T& new1) {
            return Super::add(new1);
        }
        wbool add(const T* new1) {
            return Super::add(*new1);
        }
        wbool add(const TIter<T>& e, const T& new1) {
            return Super::add(e, new1);
        }
        wbool add(const TIter<T>& e, const T* new1) {
            return Super::add(e, *new1);
        }

        using Super::del;
        wcnt del(const T& it) {
            return Super::del(it);
        }

        template <typename E = T>
        void each(const TIter<T>& from, const TIter<T>& to, std::function<wbool(TIter<T>&, E&)> l);
        template <typename E>
        void each(const TIter<T>& from, const TIter<T>& to, std::function<wbool(const TIter<T>&, const E&)> l) const;

        template <typename E = T>
        void each(std::function<wbool(TIter<T>&, E&)> l);
        template <typename E = T>
        void each(std::function<wbool(const TIter<T>&, const E&)> l) const;
    };
}
