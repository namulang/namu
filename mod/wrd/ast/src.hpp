#pragma once

#include "node.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace wrd {

    /// src represents src file of wrdlang source codes.
    class pack;
    class _wout src : public node {
        WRD(CLASS(src, node))

    public:
        src(const std::string& fileName): _fileName(fileName) {}

    public:
        wbool canRun(const ucontainable& args) const override { return false; }

        using super::run;
        str run(const ucontainable& args) override { return str(); }

        nbicontainer& subs() override { return _subs; }

        const std::string& getFileName() const { return _fileName; }

    private:
        std::string _fileName;
        nchain _subs;
    };

    template <typename T, typename WRP> class tnarr;
    typedef tnarr<src> srcs;
}
