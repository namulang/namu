#pragma once

#include "iteration.hpp"

namespace wrd {

    template <typename T>
    class titer : public titerable<T>, public clonable, public typeProvidable {
        WRD(CLASS(titer))
        friend class iteration;
        template <typename E, typename WRAPPER> friend class tnarr;
        template <typename E, typename defaultContainer> friend class tnchain;

    public:
        titer() {
            _nextToMatchParamType();
        }
        explicit titer(iteration* newStep): _step(newStep) {
            _nextToMatchParamType();
        }
        titer(const me& rhs) {
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
        explicit operator wbool() const { return !isEnd(); }

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

            for(int n=0; n < step ; n++) {
                if(_step->next(1) <= 0) return n;
                _nextToMatchParamType();
            }

            return step;
        }

        using titerable<T>::get;
        T& get() override;

        template <typename E>
        E& get() {
            return get().template cast<E>();
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

        /// iterates until points to object of compatible type to given parameterized type T.
        /// titer should be alwyas stable state which points to object of proper type.
        void _nextToMatchParamType() {
            while(!isEnd()) {
                if(!nul(get())) return;

                next(1);
            }
        }

    protected:
        tstr<iteration> _step;
    };

    typedef titer<node> iter;
}
