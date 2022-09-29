#pragma once

#include "../../../builtin/primitive.hpp"

namespace namu {

    struct marshalErr {};
    template <typename T> class tcppBridge;

    template <typename tnativeType, typename tmarshalType>
    struct tnormalMarshaling : public metaIf {
        typedef tmarshalType mgdType;
        typedef tnativeType nativeType;

        static nativeType toNative(node& it) {
            return ((mgdType&) it).get();
        }

        static str toMgd(nativeType it) {
            return str(new mgdType(it));
        }

        static yes canMarshal();
    };

    template <>
    struct _nout tnormalMarshaling<void, nVoid> : public metaIf {
        typedef nVoid mgdType;
        typedef void nativeType;

        static str toMgd() {
            return str(new nVoid());
        }

        static yes canMarshal();
    };

    template <typename T>
    struct tmarshaling : public metaIf {
        typedef tcppBridge<T> mgdType;

        static T& toNative(node& it) {
            throw marshalErr();
        }

        template <typename E>
        static str toMgd(E& it) {
            throw marshalErr();
        }

        static no canMarshal();
    };
    template <typename T>
    struct tmarshaling<T&> : public metaIf {
        typedef tcppBridge<T> mgdType;

        static T& toNative(node& it) {
            return it.cast<tcppBridge<T>>().get();
        }

        template <typename E>
        static str toMgd(E& it) {
            return new tcppBridge(&it);
        }

        static yes canMarshal();
    };
    template <typename T>
    struct tmarshaling<T*> : public metaIf {
        typedef tcppBridge<T> mgdType;

        static T* toNative(node& it) {
            return &it.cast<tcppBridge<T>>().get();
        }

        template <typename E>
        static str toMgd(E* it) {
            return new tcppBridge(it);
        }

        static yes canMarshal();
    };

    template <> struct _nout tmarshaling<nint> : public tnormalMarshaling<nint, nInt> {};
    template <> struct _nout tmarshaling<std::string> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<std::string&> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<const std::string&> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<const std::string> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<void> : public tnormalMarshaling<void, nVoid> {};
}
