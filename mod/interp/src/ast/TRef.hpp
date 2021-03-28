#pragma once

#include "Ref.hpp"

namespace wrd {

    template <typename T>
    class TRef : public Ref {
        WRD_CLASS(TRef, Ref)

    public:
        TRef() {}
        explicit TRef(const T& new1): Super(new1) {}
        explicit TRef(const T* new1): Super(new1) {}

        using Super::get;
        T& get() override {
            return (T&) Super::get();
        }

        wbool bind(const T& it) {
            return Super::bind(it);
        }
        wbool bind(const T* it) {
            return Super::bind(*it);
        }
    };
}
