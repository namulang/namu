#pragma once

#include "node.hpp"
#include "../frame/frameInteractable.hpp"
#include "../builtin/container/native/tnchain.inl"

namespace wrd {

    class func;
    typedef tnarr<func> funcs;

    /// obj handles frame injection event of all objects.
    class obj : public node, public frameInteractable {
        WRD(INTERFACE(obj, node))
        friend class mgdObj;

    public:
        explicit obj(const std::string& name = "", const narr& subItself = *new narr());
        explicit obj(const me& rhs) {}

        me& operator=(const me& rhs) {
            if (&rhs == this) return *this;
            return *this;
        }

        using super::subs;
        ncontainer& subs() override {
            return *_subs;
        }

        const std::string& getName() const override {
            return _name;
        }

        using super::run;
        str run(const ncontainer& args) override;

        wbool canRun(const wtypes& types) const override;
        virtual funcs& getCtors() = 0;
        const funcs& getCtors() const WRD_UNCONST_FUNC(getCtors())
        virtual const obj& getOrigin() const = 0;

    protected:
        wbool _onInFrame(frame& fr, const ncontainer& args) override;
        wbool _onOutFrame(frame& fr, const ncontainer& args) override;

    protected:
        std::string _name;
        tstr<nchain> _subs;
    };
}
