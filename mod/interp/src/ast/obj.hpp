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
        explicit obj();
        explicit obj(const string& name);
        explicit obj(const string& name, const nchain& subs);
        explicit obj(const me& rhs) { /*obj doesn't handle assignment. */ }
        ~obj() override {
            _destruct();
        }

    public:
        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;

            _destruct();
            _name = new string(*rhs._name);

            return *this;
        }

        using super::subs;
        ncontainer& subs() override {
            return *_subs;
        }

        using super::run;
        str run(const ncontainer& args) override;

        wbool canRun(const wtypes& types) const override;
        virtual funcs& getCtors() = 0;
        const funcs& getCtors() const WRD_UNCONST_FUNC(getCtors())
        virtual const obj& getOrigin() const = 0;
        const std::string& getName() const override {
            return *_name;
        }

    protected:
        wbool _onInFrame(frame& fr, const ncontainer& args) override;
        wbool _onOutFrame(frame& fr, const ncontainer& args) override;
        void _setSubs(const nchain& newSubs) {
            _subs.bind(newSubs);
        }

    private:
        /// 'destruct' is called when an irreversible state transition occurs.
        /// conversely, 'release' is called when reinitialization is possible.
        void _destruct();

    protected:
        tstr<nchain> _subs;
        const string* _name;
    };
}
