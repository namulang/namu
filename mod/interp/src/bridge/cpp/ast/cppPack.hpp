#include "../../../ast/pack.hpp"

typedef wrd::tnarr<wrd::obj> wrd_bridge_cpp_origins;

namespace wrd {

    typedef void* libHandle;
    typedef std::vector<libHandle> libHandles;
    typedef void (*entrypointFunc)(wrd_bridge_cpp_origins*);

    class cppPack : public pack {
        WRD_CLASS(cppPack, pack)

    public:
        cppPack(const manifest& manifest): super(manifest) {}
        ~cppPack() override { me::rel(); }

    public:
        void rel() override {
            // sequence of rel() matters:
            //  before release handles from _rel(),
            //  origin instances should be freed first from super::rel();
            super::rel();
            _rel();
        }

    protected:
        tstr<narr> _loadOrigins(const std::vector<std::string>& filePaths) override;
        void _rel();

    private:
        libHandles _handles;
    };
}
