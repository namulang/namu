#pragma once

#include "Thing.hpp"
#include "Gettable.hpp"
#include "Id.hpp"

namespace wrd
{
	class Block;

    class Trace : public Thing, public Gettable
    {	WRD_INHERIT(Trace, Thing)
    public:
        Trace();
        Trace(Id id, wcnt serial);

    public: //  Trace:
        Id getId() const;
        wcnt getSerial() const;
        const Block& getBlock() const;

    public: //  Thing:
        virtual Result& release();

    protected:
        Result& _setId(Id new1);
        Result& _setSerial(wcnt new1);
        Block& _getBlock();

    private:
        Id _id;
        wcnt _serial;
    };
}
