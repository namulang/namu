#pragma once

#include "../../../ast/node.hpp"
#include "../../../builtin/err/errCode.hpp"
#include "tnarr.hpp"
#include "tnucontainer.inl"

namespace nm {

    class thread;
    class baseErr;

#define TEMPL template <typename T, typename TACTIC>
#define ME tnarr<T, TACTIC>

    TEMPL
    ME::tnarr() {}

    TEMPL
    ME::tnarr(const std::initializer_list<const T*> args) {
        for(const T* arg : args)
            add(arg);
    }

    TEMPL
    T& ME::get(nidx n) {
        WHEN(!in(n)).exErr(OUT_OF_RANGE, n, len()).template retNul<T>();

        binder& ret = _vec[n];
        return (T&) *ret;
    }

    TEMPL
    nbool ME::set(const iter& at, const T& new1) {
        narrIteration& cast = _getIterationFrom(at);
        WHEN_NUL(cast).exErr(ITERATOR_IS_NUL).ret(false);
        WHEN(cast.isEnd()).ret(false);

        return set(cast._n, new1);
    }

    TEMPL
    nbool ME::set(nidx n, const T& new1) {
        WHEN(!in(n)).exErr(OUT_OF_RANGE, n, len()).ret(false);

        return _vec[n].bind(new1);
    }

    TEMPL
    nbool ME::add(const iter& e, const T& new1) {
        WHEN_NUL(e).exErr(ITERATOR_IS_NUL).ret(false);
        WHEN_NUL(new1).ret(false);
        WHEN(!e.isFrom(*this)).exErr(ITERATOR_NOT_BELONG_TO_CONTAINER).ret(false);
        narrIteration& cast = (narrIteration&) *e._iteration;
        WHEN_NUL(cast).exErr(CAST_NOT_AVAILABLE, "this iterator", "arr iterator").ret(false);

        return add(cast._n, new1);
    }

    TEMPL
    nbool ME::add(nidx n, const T& new1) {
        WHEN(n < 0 || n > len()).exErr(OUT_OF_RANGE, n, len()).ret(false);
        WHEN_NUL(new1).ret(false);

        _vec.insert(_vec.begin() + n, wrap(new1));
        return true;
    }

    TEMPL
    void ME::add(const iter& here, const iter& from, const iter& to) {
        WHEN(!from.isFrom(to.getContainer())).exErr(ITERATOR_NOT_BELONG_TO_CONTAINER).ret();
        const narrIteration& hereCast = _getIterationFrom(here);
        const narrIteration& fromCast = (narrIteration&) *from._iteration;
        const narrIteration& toCast = (narrIteration&) *to._iteration;
        WHEN_NUL(hereCast, fromCast, toCast)
            .exErr(CAST_NOT_AVAILABLE, "one of these iterator", "arr iterator")
            .ret();

        WHEN(hereCast._n < 0 || hereCast._n > len()).ret(); // if n equals to len(), it means that will be added at end of container.

        auto fromBegin = ((me&) from.getContainer())._vec.begin();
        _vec.insert(_vec.begin() + hereCast._n, fromBegin + fromCast._n, fromBegin + toCast._n);
    }

    TEMPL
    nbool ME::del(const iter& at) {
        narrIteration& cast = _getIterationFrom(at);
        WHEN_NUL(cast).exErr(CAST_NOT_AVAILABLE, "'at' iterator", "arr iterator").ret(false);
        WHEN(cast.isEnd()).ret(false);

        return del(cast._n);
    }

    TEMPL
    nbool ME::del(nidx n) {
        WHEN(!in(n)).exErr(OUT_OF_RANGE, n, len()).ret(false);

        _vec.erase(_vec.begin() + n);
        return true;
    }

    TEMPL
    nbool ME::del(const iter& from, const iter& end) {
        narrIteration &endIter = _getIterationFrom(end), &fromIter = _getIterationFrom(from);
        WHEN_NUL(endIter, fromIter).exErr(ITERATOR_IS_NUL).ret(false);

        nidx fromN = fromIter.isEnd() ? len() - 1 : fromIter._n;
        ncnt cnt = endIter._n - fromN;
        WHEN(cnt <= 0).ret(false);

        for(int n = 0; n < cnt; n++)
            _vec.erase(_vec.begin() + fromN);
        return true;
    }

    TEMPL
    ncnt ME::len() const { return _vec.size(); };

    TEMPL
    void ME::rel() { _vec.clear(); }

    TEMPL
    void ME::onCloneDeep(const clonable& from) {
        const me& rhs = (const me&) from;
        rel();
        for(const auto& e: rhs)
            add((T*) e.cloneDeep());
    }

    TEMPL
    std::string ME::asStr() const {
        std::string ret;
        nbool first = true;
        for(const auto& e: *this) {
            ret += (first ? "" : ",") + e.getType().getName();
            first = false;
        }

        return ret;
    }

    TEMPL
    typename ME::iteration* ME::_onMakeIteration(ncnt step, nbool isReversed) const {
        me* unconst = const_cast<me*>(this);
        return new narrIteration(*unconst, step, isReversed);
    }

    TEMPL
    typename ME::narrIteration& ME::_getIterationFrom(const iter& it) {
        WHEN_NUL(it).retNul<narrIteration>();
        WHEN(!it.isFrom(*this)).retNul<narrIteration>();
        return (narrIteration&) *it._iteration;
    }

#undef TEMPL
#undef ME
} // namespace nm
