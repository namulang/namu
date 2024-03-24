// nested class of tucontainable.inl:
//  this file allows to be refered by 'tucontainable.inl' file only.
#pragma once

#include "../../../ast/node.hpp"

namespace namu {

#define TEMPL template <typename T>
#define ME tucontainable<T>::iter

    TEMPL
    typename ME ME::operator+(ncnt step) {
        next(step);
        return *this;
    }

    TEMPL
    typename ME& ME::operator++() {
        next(1);
        return *this;
    }

    TEMPL
    typename ME ME::operator++(int) {
        me ret = *this;
        next(1);
        return ret;
    }

    TEMPL
    typename ME& ME::operator+=(ncnt step) {
        next(step);
        return *this;
    }

    TEMPL
    T& ME::operator*() {
        return get();
    }

    TEMPL
    T* ME::operator->() {
        return &get();
    }

    TEMPL
    ME::operator nbool() const {
        return !isEnd();
    }

    TEMPL
    nbool ME::isFrom(const tucontainable& it) const {
        if(!_step) return false;
        return _step->isFrom(it);
    }

    TEMPL
    nbool ME::isEnd() const {
        if(!_step) return true;
        return _step->isEnd();
    }

    TEMPL
    ncnt ME::next(ncnt step) {
        if(!_step) return false;

        for(int n=0; n < step ; n++) {
            if(_step->next(1) <= 0) return n;
            _nextToMatchParamType();
        }

        return step;
    }

    TEMPL
    T& ME::get() {
        if(!_step) return nulOf<T>();
        return (T&) _step->get();
    }

    TEMPL
    tucontainable<T>& ME::getContainer() {
        if(!_step) return nulOf<tnucontainer<T>>();
        return _step->getContainer();
    }

    TEMPL
    node& ME::getOwner() {
        auto& con = getContainer();
        if(nul(con)) return nulOf<node>();
        return con.getOwner();
    }

    TEMPL
    typename ME& ME::_assign(const me& rhs) {
        _step.bind((iteration*) rhs._step->clone());
        return *this;
    }

    TEMPL
    nbool ME::_onSame(const typeProvidable& rhs) const {
        const me& cast = (const me&) rhs;
        return _step == cast._step;
    }

    TEMPL
    void ME::_nextToMatchParamType() {
        while(!isEnd()) {
            if(!nul(get())) return;

            next(1);
        }
    }

#undef ME
#undef TEMPL
}
