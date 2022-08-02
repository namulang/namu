#pragma once

#include "../../../ast.hpp"

namespace namu {

    template <typename T>
    class tarr : public obj, public tucontainable<T>, tarrayable<T> {
        WRD(CLASS(tarr, obj))
        typedef typename tucontainable<T>::iter iter;
        typedef typename tucontainable<T>::iteration iteration;

    public:
        tarr() {}
        explicit tarr(std::initializer_list<const T*> elems) { this->add(elems); }
        explicit tarr(const tnarr<T>& nativeArr): _arr(nativeArr) {}

    public:
        using tarrayable<T>::operator[];
        T& operator[](widx n) override { return _arr[n]; }

    public:
        tnarr<T>& getNative() { return _arr; }
        const tnarr<T>& getNative() const { return _arr; }

        //  len:
        wcnt len() const override { return _arr.len(); }

        wbool has(widx n) const override { return _arr.has(n); }

        //  get:
        using tarrayable<T>::get;
        using tucontainable<T>::get;
        T& get(widx n) override { return _arr.get(n); }

        //  set:
        using tucontainable<T>::set;
        using tarrayable<T>::set;
        wbool set(const iter& at, const T& new1) override { return _arr.set(at, new1); }
        wbool set(widx n, const T& new1) override { return _arr.set(n, new1); }

        //  add:
        using tucontainable<T>::add;
        using tarrayable<T>::add;
        wbool add(std::initializer_list<T*> elems) {
            wbool ret = false;
            for(auto* elem : elems)
                ret = _arr.add(elem);
            return ret;
        }
        wbool add(const iter& at, const T& new1) override { return _arr.add(at, new1); }
        wbool add(widx n, const T& new1) override { return _arr.add(n, new1); }
        void add(const iter& here, const iter& from, const iter& to) override { _arr.add(here, from, to); }

        //  del:
        using tucontainable<T>::del;
        wbool del(widx n) override { return _arr.del(n); }
        wbool del(const iter& it) override { return _arr.del(it); }
        wbool del(const iter& from, const iter& to) override { return _arr.del(from, to); }

        //  etc:
        tstr<instance> deepClone() const override {
            return _arr.deepClone();
        }
        void rel() override {
            _arr.rel();

           super::rel();
        }

    protected:
        iteration* _onMakeIteration(wcnt step) const override {
            return _arr._onMakeIteration(step);
        }

        tnarr<T> _arr;
    };

    typedef tarr<node> arr;
}
