#include "TType.hpp"
#include "../rtti/Rtti.hpp"
#include "Type.hpp"

namespace wrd { namespace meta {
#define TEMPL template <typename T>
#define THIS TType<T>

    TEMPL THIS::TType() { this->init(); }
    TEMPL WRD_SINGLETON_GETTER(wbool THIS::isTemplate() const, wbool, TIfTemplate<T>::is);
    TEMPL WRD_SINGLETON_GETTER(wbool THIS::isAbstract() const, wbool, TIfAbstract<T>::is);
    TEMPL WRD_SINGLETON_GETTER(const std::string& THIS::getName() const, std::string, TNameGetter<T>::getName());
    TEMPL void* THIS::make() const { return TInstanceMaker<T>::make(); }
    TEMPL wcnt THIS::getSize() const { return sizeof(T); }

    TEMPL WRD_SINGLETON_GETTER(const Type& THIS::getSuper() const, TType<typename TAdaptiveSuper<T>::Super>);

    TEMPL const wbool& THIS::isInit() const {
        static wbool inner = typeid(T) == typeid(Adam);
        return inner;
    }

    TEMPL WRD_SINGLETON_GETTER(Types& THIS::_getSupers(), Types);
    TEMPL WRD_SINGLETON_GETTER(Types& THIS::_getSubs(), Types);

#undef TEMPL
#undef THIS
}}
