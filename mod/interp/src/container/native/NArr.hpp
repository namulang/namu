#pragma once

#include "../ArrContainable.hpp"
#include "../../ast/Node.hpp"

namespace wrd {

    class NArr : public ArrContainable, public Clonable, public TypeProvidable {
        WRD_DECL_THIS(NArr, ArrContainable)
        WRD_INTERFACE_FOOTER(NArr)
        WRD_CLONE(This)

        friend class NArrIteration;
        class NArrIteration : public Iteration {
            WRD_CLASS(NArrIteration, Iteration)
            friend class NArr;

        public:
            NArrIteration(NArr& own, widx n): _n(n), _own(own) {}

            wbool operator==(const Iteration& rhs) const override {
                if(Super::operator!=(rhs)) return false;

                const NArrIteration& cast = rhs.cast<NArrIteration>();
                if(nul(cast)) return false;

                return _n == cast._n;
            }

            wbool isEnd() const override {
                return _isValidN(_n);
            }
            wbool next() override {
                if(!_isValidN(_n + 1)) return false;

                _n++;
                return true;
            }
            wbool prev() override {
                if(!_isValidN(_n - 1)) return false;

                _n--;
                return true;
            }
            Node& get() override {
                if(isEnd()) return nulOf<Node>();
                return _own.get(_n);
            }
            Containable& getContainer() override { return _own; }

        private:
            wbool _isValidN(widx n) const {
                if(nul(_own)) return true;
                return _own._isValidN(n);
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

        Iteration* _onIter(widx n) const override {
            if(!_isValidN(n)) return NULL;

            This* unconst = const_cast<This*>(this);
            return new NArrIteration(*unconst, n);
        }

        void empty() override;

        using Super::add;
        wbool add(const Iter& e, const Node& new1) override;
        using Super::del;
        wbool del(const Iter& it) override;

    private:
        wbool _isValidN(widx n) const {
            // if n == getLen means it's end of buffer.
            return n < 0 || n > getLen();
        }

        std::vector<Str> _vec;
    };
}
