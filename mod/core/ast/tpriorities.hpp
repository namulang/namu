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
        T& getMatched();

        /// @return all elements causes current ambigious err.
        ///         but return nothing if there is no err.
        tpriorities getAmbigious() const;

        tpriorities split(priority by) const;

        const T& getMatched() const NAMU_UNCONST_FUNC(getMatched())

        tpriorities<T> sort() const {
            /* TODO:
            tpriorities<T> ret;
            for(int n=0; n < this->len(); n++) {
                for(const T& elem : *this)
                    ret.add(new tprior<T>(elem, priority(n)));
            }*/
            return *this;
        }

    };

    typedef tpriorities<node> priorities;
}
