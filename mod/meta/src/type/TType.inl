#include "TType.hpp"
#include "../rtti/Rtti.hpp"
#include "Type.hpp"

namespace wrd {
#define TEMPL template <typename T>
#define THIS TType<T>
#define SUPER Type

    TEMPL THIS::TType() { this->init(); }
    TEMPL WRD_SINGLETON_GETTER(wbool THIS::isTemplate(), wbool, TIfTemplate<T>::is);
    TEMPL WRD_SINGLETON_GETTER(wbool THIS::isAbstract(), wbool, !std::is_constructible<T>::value);
    TEMPL WRD_SINGLETON_GETTER(const std::string& THIS::getName(), std::string, TNameGetter<T>::getName());
    TEMPL void* THIS::make() { return TInstanceMaker<T>::make(); }
    TEMPL wcnt THIS::getSize() { return sizeof(T); }

    TEMPL WRD_SINGLETON_GETTER(Type& THIS::getSuper(), TType<typename TAdaptiveSuper<T>::Super>);

    TEMPL const wbool& THIS::isInit() {
        static wbool inner = typeid(T) == typeid(Adam);
        return inner;
    }

    TEMPL THIS& THIS::get() {
        static THIS* inner = WRD_NULL;
        if(!inner) {
            inner = new THIS(false);
            inner->init();
        }

        return *inner;
    }

    TEMPL WRD_SINGLETON_GETTER(Types& THIS::getSupers(), Types);
    TEMPL WRD_SINGLETON_GETTER(Types& THIS::getSubs(), Types);
    TEMPL Type& THIS::_getStatic() { return get(); }
    TEMPL THIS::TType(wbool) {}

#undef TEMPL
#undef THIS
#undef SUPER
}
