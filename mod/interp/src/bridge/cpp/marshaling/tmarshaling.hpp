#pragma once

namespace wrd {

    struct marshalErr {};

    template <typename nativeType, typename tmarshalType>
    struct tnormalMarshaling : public metaIf {
        typedef tmarshalType marshalType;

        static nativeType from(node& it) {
            return ((marshalType&) it).get();
        }

        static yes canMarshal();
    };

    template <typename T>
    struct tmarshaling : public metaIf {
        typedef void marshalType;

        static T from(node& it) {
            throw marshalErr();
        }
        static no canMarshal();
    };

    template <>
    struct tmarshaling<wint> : public tnormalMarshaling<wint, wInt> {};

    template <>
    struct tmarshaling<std::string> : public tnormalMarshaling<const std::string&, wStr> {};

    template <>
    struct tmarshaling<const std::string> : public tnormalMarshaling<const std::string&, wStr> {};

    // TODO: add more.
}
