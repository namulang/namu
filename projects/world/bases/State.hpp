#pragma once

#include "Instance.hpp"

namespace wrd
{
    class State : public Instance
    {	WRD_CLASS_DECLARE(State, Instance)
    public:
        virtual wbool isInit();
        virtual Result& init();
        virtual Result& release();

    protected:
        Result& _setInit(wbool new1);
	
	private:
		wbool _is_init;
    };
}
