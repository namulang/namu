#pragma once

#include "node.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace namu {

    /// src represents src file of namulang source codes.
    class _nout src : public node {
        NAMU(CLASS(src, node), VISIT())

    public:
        src(const std::string& fileName);

    public:
        nbool canRun(const args& a) const override;

        using super::run;
        str run(const args& a) override;
        nbicontainer& subs() override;
        const std::string& getFileName() const;

    private:
        std::string _fileName;
        nchain _subs;
    };

    template <typename T, typename WRP> class tnarr;
    typedef tnarr<src> srcs;
}
