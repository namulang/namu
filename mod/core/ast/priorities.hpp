#pragma once

#include "../builtin/container/native/tnarr.hpp"

namespace namu {
    enum priority {
        EXACT = 0,      // lv0: exact match.
        NUMERIC = 1,    // lv1: numeric match.
                        //      it's almost same level of lv0. except lv1 allows numeric implicit type cast ('byte to int' or reverse order)
        IMPLICIT = 2,   // lv2: implicit cast match.
                        //      it's almost same level of lv1 except it allows all kind of implicit type cast.
        NO_MATCH,       // lv+: no match.
    };

    template <typename T>
    struct _nout prior: instance {
        NAMU(CLASS(prior, instance))

    public:
        prior(const node& newElem, priority newLv);

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
        priority lv; // priority level.
    };

    template <typename T>
    class _nout priorities : public tnarr<prior<T>> {
        NAMU(CLASS(priorities, prior<T>))

    public:
        priorities();
        /// @param  elems   instances to derived type of T.
        ///                 should be created on Heap.
        template <typename... Es>
        explicit priorities(const Es&... elems) {
            static_assert(areBaseOfT<T, Es...>::value, "some of type of args are not base of type 'T'");
            add( { (T*) &elems... } );
        }

    public:
        /// @return finally matched sub when you want to access.
        ///         if there is any ambigious err, this will return nulOf<T>().
        T& getMatched();

        /// @return all elements causes current ambigious err.
        ///         but return nothing if there is no err.
        tnarr<prior<T>> getAmbigious() const;

        tnarr<prior<T>> split(priority by) const;

        const T& getMatched() const NAMU_UNCONST_FUNC(getMatched())
    };
}
