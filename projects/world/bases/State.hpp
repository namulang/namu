#pragma once

#include "Instance.hpp"

namespace wrd
{
    class State : public Instance
    {	WRD_CLASS(State, Instance)
    public:
        virtual wbool isInit() { return _is_init; }
        virtual Result& init()
        {
            WRD_ASSERT(isInit(), Abort)
            return _setInit(true);
        }
        virtual Result& release()
        {
            _setInit(false);
            return Super::release();
        }

    protected:
        Result& _setInit(wbool new1)
        {
            _is_init = new1;
            return Success;
        }
    };
}
