#pragma once

#include "../builtin/container/native/tnarr.inl"
#include "../builtin/container/native/tnchain.inl"
#include "../ast/obj.hpp"
#include "packMakable.hpp"

namespace wrd {

    class pack;
    struct manifest;
    template<typename T> class tnchain;
    typedef tnchain<pack> packChain;

    class packLoading : public instance, public packMakable, public clonable {
        WRD(INTERFACE(packLoading, instance))

        typedef wbool (me::*packEvent)(const packChain&);

    public:
        void addPath(const std::string& filePath) {
            _paths.push_back(filePath);
        }
        void addPath(const std::vector<std::string> paths) {
            if(&_paths == &paths) return;

            _paths.insert(_paths.end(), paths.begin(), paths.end());
        }

        tpair<origins&, srcs&> make() override {
            _origins.rel();
            return tpair<origins&, srcs&>();
        }

        virtual void rel() {
            _paths.clear();
            _origins.rel();
        }

        virtual const std::string& getName() const = 0;

        const origins& getOrigins() const {
            return _origins;
        }

    protected:
        const std::vector<std::string>& _getPaths() const {
            return _paths;
        }
        origins& _getOrigins() {
            return _origins;
        }

    private:
        std::vector<std::string> _paths;
        origins _origins;
    };

    typedef std::vector<packLoading*> packLoadings;
}
