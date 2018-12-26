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
		const Block& getBlock() const;

    public: //  Thing:
        virtual Res& release();

	protected://Trace:
        Res& _setSerial(wcnt new1);
		Block& _getBlock();

    private:
        wcnt _serial;
    };
}
