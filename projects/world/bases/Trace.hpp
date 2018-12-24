#pragma once

#include "Instance.hpp"
#include "TGettable.inl"
#include "../binds/Bindable.hpp"

namespace wrd
{
	class Block;

    class Trace : public TGettable<Instance, Instance>, public Bindable 
    {	WRD_INHERIT_2(Trace, TGettable<Instance WRD_COMMA() Instance>)
    public:
        Trace();
        Trace(Id id, wcnt serial);

    public: //  Trace:
        wcnt getSerial() const;

    public: //  Thing:
        virtual Result& release();

    protected:
        Result& _setSerial(wcnt new1);

    private:
        wcnt _serial;
    };
}
