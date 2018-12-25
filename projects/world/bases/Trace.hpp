#pragma once

#include "Instance.hpp"
#include "../binds/TBindable.inl"

namespace wrd
{
	class Block;

    class Trace : public TBindable<Instance>
    {	WRD_CLASS_DECLARE(Trace, TBindable<Instance>)
    public:
        Trace();
        Trace(Id id, wcnt serial);

    public: //  Trace:
        wcnt getSerial() const;

    public: //  Thing:
        virtual Res& release();

    protected:
        Res& _setSerial(wcnt new1);

    private:
        wcnt _serial;
    };
}
