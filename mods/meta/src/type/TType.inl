#include "TType.hpp"
#include "../rtti/rtti.hpp"
#include "Type.hpp"

namespace wrd
{
#define TEMPL template <typename T>
    WRD_DEF_THIS(TType<T>, Type)

    TEMPL This::TType() { this->init(); }
    TEMPL WRD_SINGLETON_GETTER(wbool This::isTemplate() const, wbool, TIfTemplate<T>::is);
    TEMPL WRD_SINGLETON_GETTER(wbool This::isAbstract() const, wbool, TIfAbstract<T>::is);
    TEMPL WRD_SINGLETON_GETTER(const std::string& This::getName() const, std::string, TNameGetter<T>::getName());
    TEMPL void* This::make() const { return TInstanceMaker<T>::make(); }
    TEMPL wcnt This::getSize() const { return sizeof(T); }
    TEMPL WRD_SINGLETON_GETTER(const Type& This::getSuper() const, Type&, TType<typename TAdaptiveSuper<T>::Super>());
    TEMPL const wbool& This::isInit() const {
        static wbool inner = &getName() == &TClass<Adam>::get().getName();
        return inner;
    }
    TEMPL WRD_SINGLETON_GETTER(Types& _getSupers(), Types);
    TEMPL WRD_SINGLETON_GETTER(Types& _getSubs(), Types);

#undef TEMPL
}

