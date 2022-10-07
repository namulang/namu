#pragma once

#include "../../../builtin/primitive.hpp"

namespace namu {

    struct marshalErr {};
    template <typename T> class tcppBridge;
    template <typename T> class tarr;
    class arr;

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

        static mgdType& onAddParam() {
            return *new mgdType();
        }

        static mgdType& onGetRet() {
            return *new mgdType();
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

        static mgdType& onAddParam() {
            return *new mgdType();
        }

        static mgdType& onGetRet() {
            return *new mgdType();
        }

        static yes canMarshal();
    };

    template <typename T, nbool isNode = tifSub<T, node>::is>
    struct tmarshaling : public metaIf {
        static T& toNative(node& it) {
            throw marshalErr();
        }

        template <typename E>
        static str toMgd(E& it) {
            throw marshalErr();
        }

        static T& onAddParam() {
            throw marshalErr();
        }

        static T& onGetRet() {
            throw marshalErr();
        }

        static no canMarshal();
    };
    template <typename T>
    struct tmarshaling<T&, true> : public metaIf {
        typedef T mgdType;

        static T& toNative(node& it) {
            return it.cast<T>();
        }

        template <typename E>
        static str toMgd(E& it) {
            return it;
        }

        static mgdType& onAddParam() {
            return *new mgdType();
        }

        static mgdType& onGetRet() {
            return *new mgdType();
        }

        static yes canMarshal();
    };
    template <typename T>
    struct tmarshaling<T&, false> : public metaIf {
        typedef tcppBridge<T> mgdType;

        static T& toNative(node& it) {
            return it.cast<tcppBridge<T>>().get();
        }

        template <typename E>
        static str toMgd(E& it) {
            return new tcppBridge(&it);
        }

        static mgdType& onAddParam() {
            return *new mgdType();
        }

        static mgdType& onGetRet() {
            return *new mgdType();
        }

        static yes canMarshal();
    };
    template <typename T>
    struct tmarshaling<T*, false> : public metaIf {
        typedef tcppBridge<T> mgdType;

        static T* toNative(node& it) {
            return &it.cast<tcppBridge<T>>().get();
        }

        template <typename E>
        static str toMgd(E* it) {
            return new tcppBridge(it);
        }

        static mgdType& onAddParam() {
            return *new mgdType();
        }

        static mgdType& onGetRet() {
            return *new mgdType();
        }

        static yes canMarshal();
    };
    template <typename T>
    struct tmarshaling<tarr<T>, true> : public metaIf {
        typedef arr mgdType;

        static tarr<T> toNative(node& it);

        template <typename E>
        static str toMgd(E* it);

        static mgdType& onAddParam();

        static mgdType& onGetRet();

        static yes canMarshal();
    };

    template <> struct _nout tmarshaling<nint, false> : public tnormalMarshaling<nint, nInt> {};
    template <> struct _nout tmarshaling<nbool, false> : public tnormalMarshaling<nbool, nBool> {};
    template <> struct _nout tmarshaling<nflt, false> : public tnormalMarshaling<nflt, nFlt> {};
    template <> struct _nout tmarshaling<nchar, false> : public tnormalMarshaling<nchar, nChar> {};
    template <> struct _nout tmarshaling<std::string, false> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<std::string&, false> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<const std::string&, false> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<const std::string, false> : public tnormalMarshaling<const std::string&, nStr> {};
    template <> struct _nout tmarshaling<void, false> : public tnormalMarshaling<void, nVoid> {};
}
