#pragma once

#include "Type.hpp"

namespace wrd { namespace meta {

	///	@remark	TType returns TType<Type> as its meta class.
	///			however, this makes impossible to get specific TType instance
	///			at a binder.
    template <typename T>
    class TType : public Type {
        WRD_DECL_THIS(TType<T>, Type)

    public:
        TType();

        wbool isTemplate() const;
        wbool isAbstract() const;
        const std::string& getName() const;
        void* make() const;
		wcnt getSize() const;
        //TODO: virtual wbool isImmutable() const;
		const Type& getSuper() const;
		const wbool& isInit() const;
        static WRD_SINGLETON_GETTER(This);

    protected:
        Types& _getSupers();
        Types& _getSubs();
    };
}}
