#pragma once

#include "iteration.hpp"

namespace wrd {

    class iterator : public iterable, public clonable, public typeProvidable {
        WRD_CLASS(iterator)
        friend class iteration;
        friend class narr;
        friend class nchain;

    public:
        iterator() {}
        explicit iterator(iteration* newStep): _step(newStep) {}
        iterator(const iterator& rhs) {
            _assign(rhs);
        }

        iterator operator+(wcnt step) {
            next(step);
            return *this;
        }
        iterator& operator++() {
            next(1);
            return *this;
        }
        iterator operator++(int) {
            iterator ret = *this;
            next(1);
            return ret;
        }
        iterator& operator+=(wcnt step) {
            next(step);
            return *this;
        }
        virtual node& operator*() { return get(); }
        virtual node* operator->() { return &get(); }
        virtual const node& operator*() const WRD_UNCONST_FUNC(operator*())
        virtual const node* operator->() const WRD_UNCONST_FUNC(operator->())
        operator wbool() const { return !isEnd(); }

        wbool isFrom(const ncontainer& it) const override {
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

        using iterable::get;
        node& get() override {
            if(!_step) return nulOf<node>();
            return _step->get();
        }

        ncontainer& getContainer() override {
            if(!_step) return nulOf<ncontainer>();
            return _step->getContainer();
        }
        const ncontainer& getContainer() const WRD_UNCONST_FUNC(getContainer());

    private:
        me& _assign(const me& rhs) {
            _step.bind((iteration*) rhs._step->clone());
            return *this;
        }
        wbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _step == cast._step;
        }

    protected:
        tstr<iteration> _step;
    };

}
