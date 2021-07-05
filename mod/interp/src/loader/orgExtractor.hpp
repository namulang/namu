#pragma once

#include "extraction/orgExtraction.hpp"

namespace wrd {

    class orgExtractor {
        WRD_DECL_ME(orgExtractor)
        WRD_INIT_META(orgExtractor)
        typedef std::vector<orgExtraction*> orgExtractions;

    public:
        const orgExtraction& getExtraction(const std::string& name) {
            for(const orgExtraction* e : _getExtractions()) {
                if(e->getName() == name) return *e;
            }

            WRD_W("can't find extgractio obj named to %s", name.c_str());
            return nulOf<orgExtraction>();
        }

    private:
        const orgExtractions& _getExtractions() const;
    };
}
