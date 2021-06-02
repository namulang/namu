#pragma once

#include "iteration.hpp"

namespace wrd {

    template <typename T>
    class titerator : public titerable<T>, public clonable, public typeProvidable {
        WRD_CLASS(titerator)
        friend class iteration;
        template <typename E>
        friend class tnarr;
        friend class nchain;

    public:
        titerator() {}
        explicit titerator(iteration* newStep): _step(newStep) {}
        titerator(const me& rhs) {
            _assign(rhs);
        }

        me operator+(wcnt step) {
            next(step);
            return *this;
        }
        me& operator++() {
            next(1);
            return *this;
        }
        me operator++(int) {
            me ret = *this;
            next(1);
            return ret;
        }
        me& operator+=(wcnt step) {
            next(step);
            return *this;
        }

        T& operator*() { return get(); }
        T* operator->() { return &get(); }
        const T& operator*() const WRD_UNCONST_FUNC(operator*())
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
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

        using titerable<T>::get;
        T& get() override;
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

    typedef titerator<node> iterator;
}
