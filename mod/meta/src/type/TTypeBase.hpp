#pragma once

#include "Type.hpp"
#include "../rtti.hpp"

namespace wrd {

    /// @remark TTypeBase returns TTypeBase<Type> as its meta class.
    ///         however, this makes impossible to get specific TTypeBase instance
    ///         at a binder.
    ///
    ///         if user typedefs SuperType at their type T, then TTypeBase
    ///         inherits from given SuperType.
    ///         this eventually make user add API to want to TTypeBase class.
    template <typename T, typename S = typename TSuperTypeDef<T>::is>
    class TTypeBase : public S {
        typedef TTypeBase<T, S> _T;
        WRD_DECL_THIS(_T, S)

    public:
        TTypeBase();

        wbool isTemplate() const override;
        wbool isAbstract() const override;
        const std::string& getName() const override;
        void* make() const override;
        wcnt getSize() const override;
        //TODO: virtual wbool isImmutable() const;
        const Type& getSuper() const override;
        const wbool& isInit() const override;
        static const This& get();

    protected:
        Types& _getSupers() override;
        Types& _getSubs() override;
        Type& _getStatic() const override;

    private:
        TTypeBase(wbool); // for skipping recursive static variable init.
    };
}
