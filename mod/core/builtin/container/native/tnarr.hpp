#pragma once

#include "tnucontainer.hpp"
#include "../tarrayable.hpp"

namespace namu {

    template <typename T, typename TACTIC = strTactic>
    class tnarr : public tnucontainer<T>, public tarrayable<T> {
        WRD(CLASS(tnarr, tnucontainer<T>))

    public:
        template <typename E> friend class tarr;
        typedef tstr<T, TACTIC> wrap;
        typedef typename super::iter iter;
        typedef typename super::iteration iteration;
        friend class narrIteration;
#include "../iter/narrIteration.hpp"

    public:
        tnarr() {}
        template <typename... Es>
        tnarr(const Es&... elems) {
            static_assert(areBaseOfT<T, Es...>::value, "some of type of args are not base of type 'T'");
            add( { (T*) &elems... } );
        }

        // operator:
        using tarrayable<T>::operator[];
        T& operator[](widx n) override { return get(n); }

        // len:
        wcnt len() const override;

        // has:
        wbool has(widx n) const override {
            return 0 <= n && n < len();
        }

        // get:
        using super::get;
        using tarrayable<T>::get;
        T& get(widx n) override;

        // set:
        using super::set;
        using tarrayable<T>::set;
        wbool set(const iter& at, const T& new1) override;
        wbool set(widx n, const T& new1) override;

        // add:
        using super::add;
        using tarrayable<T>::add;
        wbool add(const iter& e, const T& new1) override;
        wbool add(widx n, const T& new1) override;
        void add(const iter& here, const iter& from, const iter& to) override;

        // del:
        using super::del;
        using tarrayable<T>::del;
        wbool del(const iter& from, const iter& end) override;
        wbool del(const iter& it) override;
        wbool del(widx n) override;

        // etc:
        void rel() override;

        tstr<instance> deepClone() const override;

    protected:
        iteration* _onMakeIteration(wcnt step) const override {
            me* unconst = const_cast<me*>(this);
            return new narrIteration(*unconst, step);
        }

    private:
        narrIteration& _getIterationFrom(const iter& it) {
            if(nul(it)) return nulOf<narrIteration>();
            if(!it.isFrom(*this)) return nulOf<narrIteration>();
            return (narrIteration&) *it._step;
        }


    private:
        std::vector<wrap> _vec;
    };

    class node;
    typedef tnarr<node> narr;
}
