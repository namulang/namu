#pragma once

#include "../builtin/container/native/tnarr.inl"

namespace wrd {

    class obj;
    class orgExtraction {
        WRD_DECL_ME(orgExtraction)
        WRD_INIT_META(orgExtraction)

    public:
        virtual tnarr<obj> extract(const std::string& filePath) const = 0;
        virtual const std::string& getName() const = 0;
    };
}
