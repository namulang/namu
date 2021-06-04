#pragma once

#include "narrContainer.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

    template <typename T>
    class tnarr : public narrContainer {
        WRD_CLASS(tnarr, narrContainer)
        template <typename E> friend class tarr;

    public:
        friend class narrIteration;
        class narrIteration : public iteration {
            WRD_CLASS(narrIteration, iteration)
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
                //  pre:
                if(step <= 0) return 0;

                widx lastN = _own.len()-1;
                if(_n >= lastN) {
                    _n = lastN + 1;
                    return 0;
                }

                //  post:
                widx newN = _n + step;
                widx availableN = newN > lastN ? lastN : newN;
                wcnt toStep = availableN - _n;

                _n += toStep;
                return toStep;
            }
            node& get() override {
                if(isEnd()) return nulOf<node>();
                return _own.get(_n);
            }
            ncontainer& getContainer() override { return _own; }

        protected:
            wbool _onSame(const typeProvidable& rhs) const override {
                if(!super::_onSame(rhs)) return false;

                const me& cast = (const me&) rhs;
                if(nul(cast)) return false;

                return _n == cast._n;
            }

        private:
            widx _n;
            tnarr& _own;
        };

    public:
        tnarr() {}
        tnarr(std::initializer_list<T*> elems) {
            add(elems);
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
        wbool set(const iterator& at, const node& new1) override;
        wbool set(widx n, const node& new1) override;

        // add:
        using super::add;
        wbool add(const iterator& e, const node& new1) override;
        wbool add(widx n, const node& new1) override;

        // del:
        using super::del;
        wbool del(const node& it) override { return del(iter(it)); }
        wcnt del(const iterator& from, const iterator& end) override;
        wbool del(const iterator& it) override;
        /// delete last element if exists.
        wbool del() override;
        wbool del(widx n) override;

        // etc:
        void empty() override;

        tstr<instance> deepClone() const override;

    protected:
        iteration* _onMakeIteration(wcnt step) const override {
            me* unconst = const_cast<me*>(this);
            return new narrIteration(*unconst, step);
        }

    private:
        narrIteration& _getIterationFrom(const iterator& it) {
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
