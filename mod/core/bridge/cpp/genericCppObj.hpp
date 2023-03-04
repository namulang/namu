#pragma once

#include "../../ast/obj.hpp"

namespace namu {

    class _nout genericCppObj : public obj {
        NAMU(CLASS(genericCppObj, obj))

    public:
        genericCppObj(): super() {}
        genericCppObj(mgdType* newType): super(newType) {}

    public:
        /// @return single generalized parameter of this object.
        virtual const node& getElemType() const;
        virtual nbool setElemType(const node& newType);

    private:
        mutable str _type;
    };
}
