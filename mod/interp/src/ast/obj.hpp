#pragma once

#include "node.hpp"
#include "../frame/frameInteractable.hpp"
#include "../builtin/container/native/tnarr.inl"
#include "func.hpp"

namespace wrd {

    class obj : public node, public frameInteractable {
        WRD_INTERFACE(obj, node)
        friend class func;

    public:
        explicit obj(std::string name = "")
            : _owns(new narr()), _subs(new nchain(*_owns)), _name(name) {}
        explicit obj(const me& rhs) {
            _assign(rhs);
        }

        me& operator=(const me& rhs) {
            super::operator=(rhs);

            return _assign(rhs);
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

    protected:
        // frameInteractable:
        wbool _onInFrame(frame& sf, const ncontainer& args) override;
        wbool _onOutFrame(frame& sf, const ncontainer& args) override;

    private:
        me& _assign(const me& rhs);

    private:
        tstr<nchain> _shares;
        tstr<narr> _owns;
        tstr<nchain> _subs;
        std::string _name;
    };
}
