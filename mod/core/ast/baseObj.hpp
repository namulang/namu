#pragma once

#include "src.hpp"
#include "../frame/frameInteractable.hpp"

namespace namu {

    class func;
    typedef tnarr<func> funcs;

    /// baseObj handles frame injection event of all objects.
    class _wout baseObj : public node {
        WRD(ADT(baseObj, node),
            FRIEND_VERIFY(baseObj, subNodes))
        friend class obj;
        friend class defaultMakeCtor;
        friend class loweventer;

    protected:
        /// if you don't give any subs when construct an baseObj, _subs will be assigned to dummy array.
        /// instance on ctor of derived class.
        explicit baseObj();

    public:
        using super::run;
        str run(const ucontainable& args) override;

        wbool canRun(const ucontainable& args) const override;

        virtual const baseObj& getOrigin() const = 0;

    protected:
        void _inFrame(const bicontainable& args) override;
        void _outFrame() override;
        str _onRunSub(node& sub, const ucontainable& args) override;

    public:
         inline static const string CTOR_NAME = "@ctor";
         inline static const string PRECTOR_NAME = "@preCtor";
    };
}
