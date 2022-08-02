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
        T& operator[](nidx n) override { return _arr[n]; }

    public:
        tnarr<T>& getNative() { return _arr; }
        const tnarr<T>& getNative() const { return _arr; }

        //  len:
        ncnt len() const override { return _arr.len(); }

        nbool has(nidx n) const override { return _arr.has(n); }

        //  get:
        using tarrayable<T>::get;
        using tucontainable<T>::get;
        T& get(nidx n) override { return _arr.get(n); }

        //  set:
        using tucontainable<T>::set;
        using tarrayable<T>::set;
        nbool set(const iter& at, const T& new1) override { return _arr.set(at, new1); }
        nbool set(nidx n, const T& new1) override { return _arr.set(n, new1); }

        //  add:
        using tucontainable<T>::add;
        using tarrayable<T>::add;
        nbool add(std::initializer_list<T*> elems) {
            nbool ret = false;
            for(auto* elem : elems)
                ret = _arr.add(elem);
            return ret;
        }
        nbool add(const iter& at, const T& new1) override { return _arr.add(at, new1); }
        nbool add(nidx n, const T& new1) override { return _arr.add(n, new1); }
        void add(const iter& here, const iter& from, const iter& to) override { _arr.add(here, from, to); }

        //  del:
        using tucontainable<T>::del;
        nbool del(nidx n) override { return _arr.del(n); }
        nbool del(const iter& it) override { return _arr.del(it); }
        nbool del(const iter& from, const iter& to) override { return _arr.del(from, to); }

        //  etc:
        tstr<instance> deepClone() const override {
            return _arr.deepClone();
        }
        void rel() override {
            _arr.rel();

           super::rel();
        }

    protected:
        iteration* _onMakeIteration(ncnt step) const override {
            return _arr._onMakeIteration(step);
        }

        tnarr<T> _arr;
    };

    typedef tarr<node> arr;
}
