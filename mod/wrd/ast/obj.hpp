#pragma once

#include "src.hpp"
#include "../builtin/container/native/tnchain.hpp"

namespace wrd {

    class func;
    typedef tnarr<func> funcs;

    /// obj handles frame injection event of all objects.
    class obj : public node {
        WRD(INTERFACE(obj, node))
        friend class mgdObj;

    public:
        explicit obj(const string& name, const nchain& subs);

    protected:
        /// if you don't give any subs when construct an obj you should assign _subs to new nchain instance on ctor of derived class.
        explicit obj();
        explicit obj(const string& name);

    public:
        using super::subs;
        ncontainer& subs() override { return *_subs; }

        using super::run;
        str run(const containable& args) override;

        using super::canRun;
        wbool canRun(const wtypes& types) const override;

        virtual funcs& getCtors() = 0;
        const funcs& getCtors() const WRD_UNCONST_FUNC(getCtors())
        virtual const obj& getOrigin() const = 0;

        const std::string& getName() const override { return _name; }
        wbool setName(const std::string& new1) override {
            _name = new1;
            return true;
        }

    protected:
        std::string _name;
        tstr<nchain> _subs;
    };
}
