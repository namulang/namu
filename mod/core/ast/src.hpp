#pragma once

#include "node.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace namu {

    /// src represents src file of namulang source codes.
    class _wout src : public node {
        WRD(CLASS(src, node))

    public:
        src(const std::string& fileName);

    public:
        wbool canRun(const ucontainable& args) const override;

        using super::run;
        str run(const ucontainable& args) override;
        nbicontainer& subs() override;
        const std::string& getFileName() const;

    private:
        std::string _fileName;
        nchain _subs;
    };

    template <typename T, typename WRP> class tnarr;
    typedef tnarr<src> srcs;
}
