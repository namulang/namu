#pragma once

#include "Iteration.hpp"

namespace wrd {

    class Iter : public Iterable, public Clonable, public TypeProvidable {
        WRD_CLASS(Iter)
        friend class Iteration;
        friend class NArr;
        friend class NChain;

    public:
        Iter() {}
        Iter(Iteration* newStep): _step(newStep) {}
        Iter(const Iter& rhs) {
            _assign(rhs);
        }

        /// @return true if there are more data to proceed
        wbool operator++() { return next(); }
        virtual Node& operator*() { return get(); }
        virtual Node* operator->() { return &get(); }
        virtual const Node& operator*() const WRD_UNCONST_FUNC(operator*())
        virtual const Node* operator->() const WRD_UNCONST_FUNC(operator->())
        operator wbool() const { return !isEnd(); }

        wbool isFrom(const Containable& it) const override {
            if(!_step) return false;
            return _step->isFrom(it);
        }

        wbool isEnd() const override {
            if(!_step) return true;
            return _step->isEnd();
        }

        wbool next() override {
            if(!_step) return false;
            return _step->next();
        }

        Node& get() override {
            if(!_step) return nulOf<Node>();
            return _step->get();
        }

        Containable& getContainer() override {
            if(!_step) return nulOf<Containable>();
            return _step->getContainer();
        }


    private:
        This& _assign(const This& rhs) {
            _step.bind((Iteration*) rhs._step->clone());
            return *this;
        }
        wbool _onSame(const TypeProvidable& rhs) const override {
            const This& cast = (const This&) rhs;
            return _step == cast._step;
        }

    protected:
        TStr<Iteration> _step;
    };

}
