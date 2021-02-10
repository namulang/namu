#pragma once

#include "Type.hpp"
#include "../rtti.hpp"

namespace wrd {

    /// @remark TType returns TType<Type> as its meta class.
    ///         however, this makes impossible to get specific TType instance
    ///         at a binder.
    ///
    ///         if user typedefs SuperType at their type T, then TType
    ///         inherits from given SuperType.
    ///         this eventually make user add API to want to TType class.
    template <typename T>
    class TType : public TSuperTypeDef<T>::is {
        WRD_DECL_THIS(TType<T>, typename TSuperTypeDef<T>::is)

    public:
        TType();

        wbool isTemplate() override;
        wbool isAbstract() override;
        const std::string& getName() override;
        void* make() override;
        wcnt getSize() override;
        //TODO: virtual wbool isImmutable() const;
        Type& getSuper() override;
        const wbool& isInit() override;
        static This& get();
        Types& getSupers() override;
        Types& getSubs() override;

    protected:
        Type& _getStatic() override;

    private:
        TType(wbool); // for skipping recursive static variable init.
    };
}
