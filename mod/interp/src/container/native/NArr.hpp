#pragma once

#include "NArrContainer.hpp"
#include "../../ast/Node.hpp"

namespace wrd {

    class NArr : public NArrContainer {
        WRD_CLASS(NArr, NArrContainer)

        friend class NArrIteration;
        class NArrIteration : public Iteration {
            WRD_CLASS(NArrIteration, Iteration)
            friend class NArr;

        public:
            NArrIteration(NArr& own, widx n): _n(n), _own(own) {}

            wbool isEnd() const override {
                return !_isValidN(_n);
            }
            wbool next() override {
                // if iteration reached to the last element to iterate, it can precede to next,
                // which means to the End of a buffer.
                // however, if it reached to already, it can't.
                if(!_isValidN(_n)) return false;

                _n++;
                return true;
            }
            Node& get() override {
                if(isEnd()) return nulOf<Node>();
                return _own.get(_n);
            }
            NContainer& getContainer() override { return _own; }

        protected:
            wbool _onSame(const TypeProvidable& rhs) const override {
                if(!Super::_onSame(rhs)) return false;

                const This& cast = (const This&) rhs;
                if(nul(cast)) return false;
                return _n == cast._n;
            }

        private:
            wbool _isValidN(widx n) const {
                if(nul(_own)) return true;
                wbool ret = _own._isValidN(n);
                return ret;
            }

            widx _n;
            NArr& _own;
        };

    public:
        wcnt getLen() const override;

        using Super::get;
        Node& get(widx n) override;

        using Super::set;
        wbool set(const Iter& at, const Node& new1) override;
        wbool set(widx n, const Node& new1) override;

        void empty() override;

        using Super::add;
        wbool add(const Iter& e, const Node& new1) override;
        wbool add(widx n, const Node& new1) override;

        using Super::del;
        /// delete last element if exists.
        wbool del() override;
        wcnt del(const Iter& from, const Iter& end) override;
        wbool del(const Iter& it) override;
        wbool del(widx n) override;

    protected:
        Iteration* _onIter(widx n) const override {
            This* unconst = const_cast<This*>(this);
            return new NArrIteration(*unconst, n);
        }

    private:
        NArrIteration& _getIterationFrom(const Iter& it) {
            if(nul(it)) return nulOf<NArrIteration>();
            if(!it.isFrom(*this)) return nulOf<NArrIteration>();
            if(it.isEnd()) return nulOf<NArrIteration>();
            return (NArrIteration&) *it._step;
        }

        wbool _isValidN(widx n) const;

        std::vector<Str> _vec;
    };
}
