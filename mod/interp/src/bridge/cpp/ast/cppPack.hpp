#include "../../../ast/pack.hpp"

namespace wrd {

    class cppPack : public pack {
        WRD_CLASS(cppPack, pack)

    public:
        cppPack(const manifest& manifest): super(manifest) {}

    protected:
        tstr<nchain> _loadOrigins(const std::vector<std::string>& filePaths) override {
            if(filePaths.size() <= 0)
                return WRD_E("no entrypoints provided."), tstr<nchain>();

            narr tray;
            /* TODO:
            */

            return tstr<nchain>(new nchain(tray));
        }
    };
}
