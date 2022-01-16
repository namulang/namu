#pragma once

namespace wrd {

    struct marshalErr {};

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
    struct tnormalMarshaling<void, wVoid> : public metaIf {
        typedef wVoid mgdType;
        typedef void nativeType;

        static str toMgd() {
            return str(new wVoid());
        }

        static yes canMarshal();
    };

    template <typename T>
    struct tmarshaling : public metaIf {
        typedef void mgdType;

        static T toNative(node& it) {
            throw marshalErr();
        }

        template <typename E>
        static str toMgd(E it) {
           return str();
        }

        static no canMarshal();
    };

    template <>
    struct tmarshaling<wint> : public tnormalMarshaling<wint, wInt> {};

    template <>
    struct tmarshaling<std::string> : public tnormalMarshaling<const std::string&, wStr> {};

    template <>
    struct tmarshaling<const std::string> : public tnormalMarshaling<const std::string&, wStr> {};

    template <>
    struct tmarshaling<void> : public tnormalMarshaling<void, wVoid> {};

    // TODO: add more.
}
