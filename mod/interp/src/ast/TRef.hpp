#pragma once

#include "Ref.hpp"

namespace wrd {

    template <typename T>
    class TRef : public Ref {
        WRD_CLASS(TRef, Ref)

    public:
        TRef() {}
        explicit TRef(const Ref& rhs): Super(rhs) {}
        explicit TRef(const T& new1): Super(new1) {}
        explicit TRef(const T* new1): Super(new1) {}

        T* operator->() override {
            return (T*) Super::operator->();
        }
        T& operator*() override {
            return (T&) Super::operator*();
        }
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
        const T& operator*() const WRD_UNCONST_FUNC(operator*())

        using Super::get;
        T& get() override {
            return (T&) Super::get();
        }

        using Super::bind;
        wbool bind(const T& it) {
            return Super::bind(it);
        }
        wbool bind(const T* it) {
            return Super::bind(*it);
        }
    };
}
