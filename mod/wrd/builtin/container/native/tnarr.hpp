#pragma once

#include "tnucontainer.hpp"
#include "../tarrayable.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

    template <typename T, typename TACTIC = strTactic>
    class tnarr : public tnucontainer<T>, public tarrayable<T> {
        WRD(CLASS(tnarr, tnucontainer<T>))
        template <typename E> friend class tarr;
        typedef tstr<T, TACTIC> wrap;
        typedef typename super::iter iter;
        typedef typename super::iteration iteration;

    public:
        friend class narrIteration;
#include "../iter/narrIteration.hpp"

    public:
        tnarr() {}
        tnarr(std::initializer_list<const T*> elems) {
            for(const T* e : elems)
                add(e);
        }
        template <typename... Es>
        tnarr(const Es&... elems) {
            static_assert(areBaseOfT<T, Es...>::value);
            add( { (T*) &elems... } );
        }

        // operator:
        using super::operator[];
        T& operator[](widx n) override { return get(n); }

        // len:
        wcnt len() const override;

        // has:
        wbool has(widx n) const override {
            return 0 <= n && n < len();
        }

        // get:
        using super::get;
        T& get(widx n) override;

        // set:
        using super::set;
        wbool set(const iter& at, const T& new1) override;
        wbool set(const iter& at, const str& new1) override;
        wbool set(widx n, const T& new1) override;
        wbool set(widx n, const str& new1) override;

        // add:
        using super::add;
        wbool add(const iter& e, const T& new1) override;
        wbool add(const iter& e, const str& new1) override;
        wbool add(widx n, const T& new1) override;
        wbool add(widx n, const str& new1) override;

        // del:
        using super::del;
        wcnt del(const iter& from, const iter& end) override;
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

    typedef tnarr<node> narr;
}
