#pragma once

#include "ref.hpp"

namespace wrd {

    template <typename T>
    class tref : public ref {
        WRD_CLASS(tref, ref)

    public:
        tref() {}
        explicit tref(const ref& rhs): super(rhs) {}
        explicit tref(const T& new1): super(new1) {}
        explicit tref(const T* new1): super(new1) {}

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
