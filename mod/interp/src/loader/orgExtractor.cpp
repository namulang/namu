#include "orgExtractor.hpp"
#include "../ast/obj.hpp"

namespace wrd {

    WRD_DEF_ME(orgExtractor)

    const me::orgExtractions& me::_getExtractions() const {
        static orgExtractions* inner = nullptr;
        if(!inner) {
            inner = new orgExtractions();

            struct cppExtraction : public orgExtraction {
                tnarr<obj> extract(const std::string& filePath) const override {
                    // TODO:
                    return tnarr<obj>();
                }

                const std::string& getName() const override {
                    static std::string inner = "cpp";
                    return inner;
                }
            };

            inner->push_back(new cppExtraction());
        }

        return *inner;
    }
}
