#pragma once

#include "NContainer.hpp"
#include "../../ast/Node.hpp"

namespace wrd {

    class NChain : public NContainer {
        WRD_CLASS(NChain, NContainer)

        friend class NChainIteration;
        class NChainIteration : public Iteration {
            WRD_CLASS(NChainIteration, Iteration)
            friend class NChain;

        public:
            NChainIteration(const NChain& own, const NChain& iteratingChain, const Iter& conIter)
                : _own(const_cast<NChain&>(own)), _ownIter(iteratingChain), _iter(conIter) {}

            wbool operator==(const Iteration& rhs) const override {
                if(Super::operator!=(rhs)) return false;

                const NChainIteration& cast = rhs.cast<NChainIteration>();
                if(nul(cast)) return false;

                return _iter == cast._iter;
            }

            wbool isEnd() const override {
                if(_iter) return false;
                if(!_ownIter) return false;

                return _ownIter->_next;
            }

            wbool next() override {
                ++_iter;
                if(_iter) return true;

                _ownIter = _ownIter->_next;
                if(!_ownIter) return false;
                return _iter = _ownIter->_arr->head();
            }

            Node& get() override {
                return *_iter;
            }

            Containable& getContainer() override { return _own; }
            Iter& getContainerIter() { return _iter; }

        private:
            NChain& _own;
            TStr<NChain> _ownIter;
            Iter _iter;
        };

    public:
        NChain();
        NChain(const NContainer& con): _arr(con) {}

        wcnt getLen() const override;

        wbool set(const Iter& at, const Node& new1) override;
        wbool add(const Iter& at, const Node& new1) override;
        wbool del(const Iter& at) override;

        wbool link(const NContainer& new1);
        wbool link(const NChain& new1);
        wbool unlink();

        Iter head() const override;
        Iter tail() const override;

        void empty() override;

        NContainer& getContainer() { return *_arr; }
        const NContainer& getContainer() const { return *_arr; }
        NChain& getNext() { return *_next; }
        const NChain& getNext() const { return *_next; }

        using Super::each;
        template <typename T>
        void each(std::function<wbool(NChain&, T&)> l) {
            for(NChain* e=this; e ;e=&(*_next)) {
                auto& arr = e->_arr->cast<T>();
                if(nul(arr)) continue;

                if(!l(e, arr)) break;
            }
        }
        template <typename T>
        void each(std::function<wbool(const NChain&, const T&)> l) const {
            for(const NChain* e=this; e ;e=&(*_next)) {
                auto& arr = e->_arr->cast<T>();
                if(nul(arr)) continue;

                if(!l(*e, arr)) break;
            }
        }

    private:
        Iter& _getContainerIterFromChainIter(const Iter& wrap) {
            if(nul(wrap)) return nulOf<Iter>();
            if(!wrap.isFrom(*this)) return nulOf<Iter>();
            NChainIteration& cast = (NChainIteration&) *wrap._step;
            if(nul(cast)) return nulOf<Iter>();

            return cast.getContainerIter();
        }

        TStr<NContainer> _arr;
        TStr<NChain> _next;
    };
}
