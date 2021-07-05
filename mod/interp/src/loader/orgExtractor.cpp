#include "orgExtractor.hpp"
#include "../ast/obj.hpp"
#include "extraction.hpp"

namespace wrd {

    WRD_DEF_ME(orgExtractor)

    const me::orgExtractions& me::_getExtractions() const {
        static orgExtractions* inner = nullptr;
        if(!inner) {
            inner = new orgExtractions();
            inner->push_back(new cppOrgExtraction());
        }

        return *inner;
    }
}
