#pragma once

#include "Instance.hpp"

namespace wrd
{
    class State : public Instance
    {	WRD_CLASS_DECL(State, Instance)
	public:
		State();
	
	public:
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);

    public:
        virtual wbool isInit() const;
        virtual Res& init();
        virtual Res& release();

    protected:
        Res& _setInit(wbool new1);
	
	private:
		wbool _is_init;
    };
}
