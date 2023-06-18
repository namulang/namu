#include "biteration.hpp"

// nested class of tbicontainable.hpp:
//  this file allows to be refered by 'tbicontainable.hpp' file only.
class iter : public iterable, public clonable, public typeProvidable {
    NAMU(CLASS(iter))
    friend class iteration;
    template <typename K1, typename V1, typename defaultContainer1> friend class tnchain;
    template <typename K1, typename V1, typename TACTIC> friend class tnmap;

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

    V& operator*() { return getVal(); }
    V* operator->() { return &getVal(); }
    const V& operator*() const NAMU_UNCONST_FUNC(operator*())
    const V* operator->() const NAMU_UNCONST_FUNC(operator->())

    explicit operator nbool() const { return !isEnd(); }

    nbool isFrom(const tbicontainable& it) const override {
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

    const K& getKey() const override;
    template <typename E>
    const E& getKey() const {
        return getKey().template cast<E>();
    }
    using iterable::getVal;
    V& getVal() override;
    template <typename E>
    E& getVal() {
        return getVal().template cast<E>();
    }

    using iterable::setVal;
    void setVal(const V& new1) override;

    tbicontainable<K, V>& getContainer() override {
        if(!_step) return nulOf<tbicontainable<K, V> >();
        return _step->getContainer();
    }
    const tbicontainable<K, V>& getContainer() const NAMU_UNCONST_FUNC(getContainer());

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
            if(!nul(getVal())) return;

            next(1);
        }
    }

protected:
    tstr<iteration> _step;
};
