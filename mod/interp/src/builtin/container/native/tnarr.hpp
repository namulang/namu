#pragma once

#include "narrContainer.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

    template <typename T>
    class tnarr : public narrContainer {
        WRD(CLASS(tnarr, narrContainer))
        template <typename E> friend class tarr;

    public:
        friend class narrIteration;
        class narrIteration : public iteration {
            WRD(CLASS(narrIteration, iteration))
            template<typename E>
            friend class tnarr;

        public:
            narrIteration(tnarr& own, widx n): _n(n), _own(own) {}

            wbool isEnd() const override {
                return !_own._isValidN(_n);
            }

            /// if iteration reached to the last element to iterate, it can precede to next,
            /// which means to the End of a buffer.
            /// however, this step wasn't regarded to a step even though it proceeds.
            wcnt next(wcnt step) override {
                if(step <= 0) return 0;
                if(isEnd()) return 0;

                int len = _own.len(),
                    lastN = len - 1;
                int toLast = lastN - _n;

                _n += step;
                if(_n > lastN) {
                    _n = len;
                    step = toLast;
                }
                return step;
            }
            instance& get() override {
                if(isEnd()) return nulOf<instance>();
                return _own.get(_n);
            }
            ncontainer& getContainer() override { return _own; }
            const ncontainer& getContainer() const WRD_UNCONST_FUNC(getContainer())

        protected:
            wbool _onSame(const typeProvidable& rhs) const override {
                const me& cast = (const me&) rhs;
                return isFrom(cast.getContainer()) && _n == cast._n;
            }

        private:
            widx _n;
            tnarr& _own;
        };

    public:
        tnarr() {}
        tnarr(std::initializer_list<const node*> elems) { add(elems); }
        template <typename... Es> tnarr(const Es&... elems) {
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
        wbool set(const wrd::iter& at, const node& new1) override;
        wbool set(widx n, const node& new1) override;

        // add:
        using super::add;
        wbool add(const wrd::iter& e, const node& new1) override;
        wbool add(widx n, const node& new1) override;

        // del:
        using super::del;
        wcnt del(const wrd::iter& from, const wrd::iter& end) override;
        wbool del(const wrd::iter& it) override;
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
        narrIteration& _getIterationFrom(const wrd::iter& it) {
            if(nul(it)) return nulOf<narrIteration>();
            if(!it.isFrom(*this)) return nulOf<narrIteration>();
            return (narrIteration&) *it._step;
        }

        wbool _isValidN(widx n) const;

    private:
        std::vector<str> _vec;
    };

    typedef tnarr<node> narr;
}
