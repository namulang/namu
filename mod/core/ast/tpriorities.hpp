#pragma once

#include "../builtin/container/native/tnarr.hpp"

namespace namu {
    enum priority {
        EXACT_MATCH = 0,      // lv0: exact match.
        NUMERIC_MATCH = 1,    // lv1: numeric match.
                        //      it's almost same level of lv0. except lv1 allows numeric implicit type cast ('byte to int' or reverse order)
        IMPLICIT_MATCH = 2,   // lv2: implicit cast match.
                        //      it's almost same level of lv1 except it allows all kind of implicit type cast.
        NO_MATCH,       // lv+: no match.
    };

    template <typename T>
    struct _nout tprior: instance {
        NAMU(CLASS(tprior, instance))

    public:
        tprior(const node& newElem, priority newLv);
        tprior(const node& newElem, const node& newOwner, priority newLv);

    public:
        T* operator->();
        T& operator*();
        const T* operator->() const NAMU_UNCONST_FUNC(operator->())
        const T& operator*() const NAMU_UNCONST_FUNC(operator*())

    public:
        T& get();
        const T& get() const NAMU_UNCONST_FUNC(get())

        /// @brief precedence is more detail concept of priority.
        ///        it considers the owner of them are equal above priority.
        nbool isSamePrecedence(const me& rhs) const;

    public:
        tstr<T> elem;
        str owner;
        priority lv; // priority level.
    };

    template <typename T>
    class _nout tpriorities : public tnarr<tprior<T>> {
        NAMU(CLASS(tpriorities, tprior<T>))

    public:
        tpriorities();
        tpriorities(const T& elem);
        tpriorities(const T& elem, const node& owner);

    public:
        /// @return finally matched sub when you want to access.
        ///         if there is any ambigious err, this will return nulOf<T>().
        tnarr<T> getMatches() const;
        T& getMatch();
        const T& getMatch() const NAMU_UNCONST_FUNC(getMatch())
        tpriorities split(priority by) const;
    };

    typedef tpriorities<node> priorities;
}
