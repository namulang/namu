#pragma once

#include "TConcreteClass.inl"
#include "ObjectClass.hpp"

namespace wrd
{
	class MgdObject;
    class MgdClass : public TConcreteClass<MgdObject, ObjectClass>
    {	WRD_CLASS(MgdClass, TConcreteClass<MgdObject, ObjectClass>)
    public:
        virtual const Origin& getOrigin() const;
        virtual TStrong<Instance> instance() const;

    private:
        TStrong<Origin> _org;
    };
}
