#pragma once

#include "orgExtraction.hpp"

namespace wrd {

    class cppOrgExtraction : public orgExtraction {
        WRD_DECL_ME(cppOrgExtraction, orgExtraction)
        WRD_INIT_META(me)

    public:
        narr extract(const std::string& filePath) const override;

        const std::string& getName() const override {
            static std::string inner = "cpp";
            return inner;
        }
    };
}
