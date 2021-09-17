#pragma once

#include "src.hpp"
#include "../frame/frameInteractable.hpp"

namespace wrd {

    class func;
    typedef tnarr<func> funcs;

    /// obj handles frame injection event of all objects.
    class obj : public node, public frameInteractable {
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
        str run(const ncontainer& args) override;

        wbool canRun(const types& types) const override;
        virtual funcs& getCtors() = 0;
        const funcs& getCtors() const WRD_UNCONST_FUNC(getCtors())
        virtual const obj& getOrigin() const = 0;
        const std::string& getName() const override {
            if(_name.empty()) return super::getName();
            return _name;
        }

    protected:
        wbool _onInFrame(frame& fr, const ncontainer& args) override;
        wbool _onOutFrame(frame& fr, const ncontainer& args) override;

    protected:
        std::string _name;
        tstr<nchain> _subs;
    };
}
