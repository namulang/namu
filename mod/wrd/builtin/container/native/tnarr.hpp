#pragma once

#include "tnucontainer.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

    template <typename T, typename TACTIC = strTactic>
    class tnarr : public tnucontainer<T> {
        WRD(CLASS(tnarr, tnucontainer))
        template <typename E> friend class tarr;
        typedef tstr<T, TACTIC> wrap;

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
        T& operator[](widx n) override { return get(n); }
        const T& operator[](widx n) const override { return get(n); }

        // len:
        wcnt len() const override;

        // get:
        using super::get;
        T& get(widx n) override;
        const T& get(widx n) const override WRD_UNCONST_FUNC(get(n))

        // set:
        using super::set;
        wbool set(const iter& at, const T& new1) override;
        wbool set(widx n, const T& new1) override;

        // add:
        using super::add;
        wbool add(const iter& e, const T& new1) override;
        wbool add(widx n, const T& new1) override;

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

        wbool _isValidN(widx n) const;

    private:
        std::vector<tstr<node, TACTIC> > _vec;
    };

    typedef tnarr<wrap> narr;
}
