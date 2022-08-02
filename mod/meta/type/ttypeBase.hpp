#pragma once

#include "type.hpp"
#include "../rtti.hpp"

namespace namu {

    /// @remark TTypeBase returns TTypeBase<Type> as its meta class.
    ///         however, this makes impossible to get specific TTypeBase instance
    ///         at a binder.
    ///
    ///         if user typedefs SuperType at their type T, then TTypeBase
    ///         inherits from given SuperType.
    ///         this eventually make user add API to want to TTypeBase class.
    template <typename T, typename S = typename tmetaTypeDef<T>::is>
    class ttypeBase : public S {
        typedef ttypeBase<T, S> _T;
        WRD_DECL_ME(_T, S)

    public:
        ttypeBase();

        wbool isTemplate() const override;
        wbool isAbstract() const override;
        const std::string& getName() const override;
        void* make() const override;
        wcnt size() const override;
        //TODO: virtual wbool isImmutable() const;
        const type& getSuper() const override;
        const wbool& isInit() const override;
        static const me& get();

    protected:
        types& _getSupers() override;
        types& _getSubs() override;
        type& _getStatic() const override;
        types** _onGetLeafs() const override;
        void _onAddSubClass(const type& subClass) override;

    private:
        ttypeBase(wbool); // for skipping recursive static variable init.
    };


    template <>
    class ttypeBase<void, type> : public type {
        typedef ttypeBase<void, type> _T;
        WRD_DECL_ME(_T, type)

    public:
        ttypeBase();

        wbool isTemplate() const override;
        wbool isAbstract() const override;

        const std::string& getName() const override;

        void* make() const override;
        wcnt size() const override;
        //TODO: virtual wbool isImmutable() const;
        //
        const type& getSuper() const override;

        const wbool& isInit() const override;

        static const me& get();

    protected:
        types& _getSupers() override;
        types& _getSubs() override;
        type& _getStatic() const override;
        types** _onGetLeafs() const override;
        void _onAddSubClass(const type& subClass) override;

    private:
        ttypeBase(wbool);
    };
}
