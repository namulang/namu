#pragma once

#include "tnucontainer.hpp"
#include "../tarrayable.hpp"

namespace namu {

    template <typename T, typename TACTIC = strTactic>
    class tnarr : public tnucontainer<T>, public tarrayable<T> {
        NAMU(ADT(tnarr, tnucontainer<T>))

    public:
        friend class arr;
        typedef tstr<T, TACTIC> wrap;
        typedef typename super::iter iter;
        typedef typename super::iteration iteration;
        friend class narrIteration;
#include "../iter/narrIteration.hpp"

    public:
        tnarr() {}
        template <typename... Es>
        explicit tnarr(const Es&... elems) {
            static_assert(areBaseOfT<T, Es...>::value, "some of type of args are not base of type 'T'");
            add( { (T*) &elems... } );
        }

    public:
        using tarrayable<T>::operator[];
        T& operator[](nidx n) override { return get(n); }

    public:
        // len:
        ncnt len() const override;

        // has:
        using super::has;
        nbool has(nidx n) const override {
            return 0 <= n && n < len();
        }

        // get:
        using tarrayable<T>::get;
        T& get(nidx n) override;
        template <typename E>
        E& get(std::function<nbool(const E&)> l) const;
        T& get(std::function<nbool(const T&)> l) const;
        template <typename E>
        tnarr<E, strTactic> getAll(std::function<nbool(const E&)> l) const;
        narr getAll(std::function<nbool(const T&)> l) const;
        // set:
        using super::set;
        using tarrayable<T>::set;
        nbool set(const iter& at, const T& new1) override;
        nbool set(nidx n, const T& new1) override;
        // add:
        using super::add;
        using tarrayable<T>::add;
        nbool add(const iter& e, const T& new1) override;
        nbool add(nidx n, const T& new1) override;
        void add(const iter& here, const iter& from, const iter& to) override;
        // del:
        using super::del;
        using tarrayable<T>::del;
        nbool del(const iter& from, const iter& end) override;
        nbool del(const iter& it) override;
        nbool del(nidx n) override;
        // etc:
        void rel() override;

        clonable* clone() const override {
            return new me(*this);
        }
        clonable* deepClone() const override;

        std::string asStr() const {
            std::string ret;
            nbool first = true;
            for(const auto& e : *this) {
                str eval = e.getEval();
                ret += (first ? "" : ",") + (eval ? e.getEval()->getType().getName() : "{none}");
                first = false;
            }

            return ret;
        }

    protected:
        iteration* _onMakeIteration(ncnt step) const override {
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
