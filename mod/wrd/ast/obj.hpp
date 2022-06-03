#pragma once

#pragma message ("obj1")
#include "src.hpp"
#pragma message ("obj2")

namespace wrd {

    class func;
    typedef tnarr<func> funcs;

    /// obj handles frame injection event of all objects.
    class _wout obj : public node {
        WRD(ADT(obj, node),
            FRIEND_VERIFY(obj, subNodes))
        friend class mgdObj;

    protected:
        /// if you don't give any subs when construct an obj, _subs will be assigned to dummy array.
        /// instance on ctor of derived class.
        explicit obj();

    public:
        using super::run;
        str run(const ucontainable& args) override;

        wbool canRun(const ucontainable& args) const override;

        virtual funcs& getCtors();
        const funcs& getCtors() const WRD_UNCONST_FUNC(getCtors())

        virtual const obj& getOrigin() const = 0;

    protected:
        str _onRunSub(node& sub, const ucontainable& args) override;

    private:
        void _inFrame();
        void _outFrame();
    };
}
#pragma message ("obj3")