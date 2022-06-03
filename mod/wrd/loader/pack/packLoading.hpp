#pragma once
#pragma message("packLoading1")
#include "../../builtin/container/native/tnarr.inl"
#pragma message("packLoading2")
#include "../../builtin/container/native/tnchain.inl"
#pragma message("packLoading3")
#include "../../ast/obj.hpp"
#pragma message("packLoading4")
#include "packMakable.hpp"
#pragma message("packLoading5")

namespace wrd {

    class pack;
    struct manifest;
    typedef tnchain<std::string, pack> packChain;

    class _wout packLoading : public instance, public packMakable, public clonable {
        WRD(ADT(packLoading, instance))

        typedef wbool (me::*packEvent)(const packChain&);

    public:
        void addPath(const std::string& filePath);
        void addPath(const std::vector<std::string> paths);

        virtual void rel();

        virtual const std::string& getName() const = 0;

    protected:
        const std::vector<std::string>& _getPaths() const;

    private:
        std::vector<std::string> _paths;
    };

    typedef std::vector<packLoading*> packLoadings;
}
#pragma message("packLoading6")