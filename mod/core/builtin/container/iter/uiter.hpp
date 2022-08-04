#include "uiteration.hpp"

// nested class of tucontainable.hpp:
//  this file allows to be refered by 'tucontainable.hpp' file only.
class iter : public iterable, public clonable, public typeProvidable {
    NAMU(CLASS(iter))
    friend class iteration;
    template <typename E, typename TACTIC> friend class tnarr;
    template <typename K, typename V, typename defaultContainer> friend class tnchain;

public:
    iter() { _nextToMatchParamType(); }
    explicit iter(iteration* newStep): _step(newStep) { _nextToMatchParamType(); }
    iter(const me& rhs) { _assign(rhs); }

    me operator+(ncnt step) {
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
    me& operator+=(ncnt step) {
        next(step);
        return *this;
    }

    T& operator*() { return get(); }
    T* operator->() { return &get(); }
    const T& operator*() const NAMU_UNCONST_FUNC(operator*())
    const T* operator->() const NAMU_UNCONST_FUNC(operator->())
    explicit operator nbool() const { return !isEnd(); }

    nbool isFrom(const tucontainable& it) const override {
        if(!_step) return false;
        return _step->isFrom(it);
    }

    nbool isEnd() const override {
        if(!_step) return true;
        return _step->isEnd();
    }

    ncnt next(ncnt step) override {
        if(!_step) return false;

        for(int n=0; n < step ; n++) {
            if(_step->next(1) <= 0) return n;
            _nextToMatchParamType();
        }

        return step;
    }

    using iterable::get;
    T& get() override;

    template <typename E>
    E& get() {
        return get().template cast<E>();
    }

    tnucontainer<T>& getContainer() override {
        if(!_step) return nulOf<tnucontainer<T>>();
        return _step->getContainer();
    }
    const tnucontainer<T>& getContainer() const NAMU_UNCONST_FUNC(getContainer());

private:
    me& _assign(const me& rhs) {
        _step.bind((iteration*) rhs._step->clone());
        return *this;
    }

    nbool _onSame(const typeProvidable& rhs) const override {
        const me& cast = (const me&) rhs;
        return _step == cast._step;
    }

    /// iterates until points to object of compatible type to given parameterized type T.
    /// iter should be alwyas stable state which points to object of proper type.
    void _nextToMatchParamType() {
        while(!isEnd()) {
            if(!nul(get())) return;

            next(1);
        }
    }

protected:
    tstr<iteration> _step;
};
