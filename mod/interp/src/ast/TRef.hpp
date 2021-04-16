#pragma once

#include "Ref.hpp"

namespace wrd {

    template <typename T>
    class TRef : public Ref {
        WRD_CLASS(TRef, Ref)

    public:
        TRef() {}
        explicit TRef(const Ref& rhs): super(rhs) {}
        explicit TRef(const T& new1): super(new1) {}
        explicit TRef(const T* new1): super(new1) {}

        T* operator->() override {
            return (T*) super::operator->();
        }
        T& operator*() override {
            return (T&) super::operator*();
        }
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
        const T& operator*() const WRD_UNCONST_FUNC(operator*())

        using super::get;
        T& get() override {
            return (T&) super::get();
        }

        using super::bind;
        wbool bind(const T& it) {
            return super::bind(it);
        }
        wbool bind(const T* it) {
            return super::bind(*it);
        }
    };
}
