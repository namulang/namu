#pragma once

#include "../ArrContainable.hpp"

namespace wrd {

    class NArr : public ArrContainable {
        WRD_CLASS(NArr, ArrContainable)

        friend class NArrIteration;
        class NArrIteration : public Iteration {
            WRD_CLASS(NArrIteration, Iteration)
            friend class NArr;

        public:
            NArrIteration(const NArr& own, widx n): Super(own), _n(n) {}

            wbool operator==(const Iteration& rhs) const override {
                if(Super::operator!=(rhs)) return false;

                NArrIteration& cast = rhs.cast<NArrIteration>();
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
                return _arr->get(_n);
            }

        private:
            wbool _isValidN(wdx n) {
                if(!_arr) return true;
                return _arr->_isValidN(n);
            }

            widx _n;
        };

    public:
        wcnt getLen() const override {
            return _vec.size();
        };

        Node& get(widx n) override;
        wbool set(const Iter& at, const Node& new1) override;
        wbool set(widx n, const Node& new1) override;

        Iter iter(widx n) const override {
            return Iter(new NArrIteration(*this, n));
        }

        void empty() override {
            _vec.clear();
        }

        wbool add(const Iter& e, const Node& new1) override {
            if(!Super::add(e, new1)) return false;
            NArrIteration& cast = (NArrIteration&) new1._step;

            widx n = cast._n;
            return _vec.insert(_vec.begin() + n, new1);
        }
        wbool del(const Iter& it) override {
            if(!Super::del(it)) return false;
            NArrIteration& cast = (NArrIteration&) new1._step;

            return _vec.erase(_vec.begin() + cast._n);
        }

    private:
        wbool _isValidN(widx n) {
            // if n == getLen means it's end of buffer.
            return n < 0 || n > getLen();
        }

        std::vector<Str> _vec;
    };
}
