#pragma once

#include "Thing.hpp"
#include "Id.hpp"

namespace wrd
{
    class Trace : public Thing
    {	WRD_INHERIT(Trace, Thing)
    public:
        Trace();
        Trace(Id id, wcnt serial);

    public: //  Trace:
        Id getId() const;
        wcnt getSerial() const;
        const Block& getBlock() const;
        Instance& get();
        const Instance& get() const;

    public: //  Thing:
        virtual Result& release();

    protected:
        Result& _setId(Id new1);
        Result& _setSerial(wcnt new1);
        Block& _getBlock();
        virtual Instance& _get() = 0;

    private:
        Id _id;
        wcnt _serial;
    };
}
