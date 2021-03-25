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
        explicit Iter(Iteration* newStep): _step(newStep) {}
        Iter(const Iter& rhs) {
            _assign(rhs);
        }

        Iter operator+(wcnt step) {
            next(step);
            return *this;
        }
        Iter& operator++() {
            next(1);
            return *this;
        }
        Iter operator++(int) {
            Iter ret = *this;
            next(1);
            return ret;
        }
        Iter& operator+=(wcnt step) {
            next(step);
            return *this;
        }
        virtual Node& operator*() { return get(); }
        virtual Node* operator->() { return &get(); }
        virtual const Node& operator*() const WRD_UNCONST_FUNC(operator*())
        virtual const Node* operator->() const WRD_UNCONST_FUNC(operator->())
        operator wbool() const { return !isEnd(); }

        wbool isFrom(const NContainer& it) const override {
            if(!_step) return false;
            return _step->isFrom(it);
        }

        wbool isEnd() const override {
            if(!_step) return true;
            return _step->isEnd();
        }

        wcnt next(wcnt step) override {
            if(!_step) return false;
            return _step->next(step);
        }

        using Iterable::get;
        Node& get() override {
            if(!_step) return nulOf<Node>();
            return _step->get();
        }

        NContainer& getContainer() override {
            if(!_step) return nulOf<NContainer>();
            return _step->getContainer();
        }
        const NContainer& getContainer() const WRD_UNCONST_FUNC(getContainer());

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
