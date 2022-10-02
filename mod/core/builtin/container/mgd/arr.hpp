#pragma once

#include "../../../ast.hpp"
#include "../../../bridge/cpp/tcppBridge.hpp"

namespace namu {

    class arr : public tcppBridge<narr>, public tucontainable<node>, tarrayable<node> {
        NAMU(CLASS(arr, obj), VISIT())
        typedef typename tucontainable<node>::iter iter;
        typedef typename tucontainable<node>::iteration iteration;

    public:
        arr(): _arr(new narr()), _type(&ttype<node>::get()) {}
        arr(const type& newType): _arr(new narr()), _type(&newType) {}

    public:
        using tarrayable<node>::operator[];
        node& operator[](nidx n) override { return _arr->operator[](n); }

    public:
        tnarr<node>& getNative() { return *_arr; }
        const tnarr<node>& getNative() const { return *_arr; }

        //  len:
        ncnt len() const override { return _arr->len(); }

        nbool has(nidx n) const override { return _arr->has(n); }

        //  get:
        using tarrayable<node>::get;
        using tucontainable<node>::get;
        node& get(nidx n) override { return _arr->get(n); }

        //  set:
        using tucontainable<node>::set;
        using tarrayable<node>::set;
        nbool set(const iter& at, const node& new1) override {
            if(!new1.isSub(*_type)) return false;
            return _arr->set(at, new1);
        }
        nbool set(nidx n, const node& new1) override {
            if(!new1.isSub(*_type)) return false;
            return _arr->set(n, new1);
        }

        //  add:
        using tucontainable<node>::add;
        using tarrayable<node>::add;
        nbool add(const iter& at, const node& new1) override {
            if(!new1.isSub(*_type)) return false;
            return _arr->add(at, new1);
        }
        nbool add(nidx n, const node& new1) override {
            if(!new1.isSub(*_type)) return false;
            return _arr->add(n, new1);
        }
        void add(const iter& here, const iter& from, const iter& to) override { _arr->add(here, from, to); }

        //  del:
        using tucontainable<node>::del;
        nbool del(nidx n) override { return _arr->del(n); }
        nbool del(const iter& it) override { return _arr->del(it); }
        nbool del(const iter& from, const iter& to) override { return _arr->del(from, to); }

        //  etc:
        me* deepClone() const override {
            me* ret = clone();
            tstr<tnarr<node>> cloned = _arr->deepClone();
            ret->_arr->add(*cloned);
            return ret;
        }
        void rel() override {
            _arr.rel();

           super::rel();
        }

    protected:
        iteration* _onMakeIteration(ncnt step) const override {
            return _arr->_onMakeIteration(step);
        }

        tstr<narr> _arr;
        const type* _type;
    };
}
