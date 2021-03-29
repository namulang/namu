#include "Type.inl"
#include "TTypeBase.hpp"
#include "../rtti/Rtti.hpp"

namespace wrd {

#define TEMPL template <typename T, typename S>
#define THIS TTypeBase<T, S>
#define SUPER S

    TEMPL THIS::TTypeBase() { this->init(); }
    TEMPL wbool THIS::isTemplate() const {
        static wbool inner = TIfTemplate<T>::is;
        return inner;
    }

    TEMPL wbool THIS::isAbstract() const {
        static wbool inner = !std::is_constructible<T>::value;
        return inner;
    }

    TEMPL const std::string& THIS::getName() const {
        static std::string inner = TNameGetter<T>::getName();
        return inner;
    }

    TEMPL void* THIS::make() const { return TInstanceMaker<T>::make(); }
    TEMPL wcnt THIS::getSize() const { return sizeof(T); }

    TEMPL const Type& THIS::getSuper() const {
        return TType<typename TAdaptiveSuper<T>::Super>::get();
    }

    TEMPL const wbool& THIS::isInit() const {
        static wbool inner = typeid(T) == typeid(Adam);
        return inner;
    }

    TEMPL const THIS& THIS::get() {
        static THIS* inner = nullptr;
        if(!inner) {
            inner = new THIS(false);
            inner->init();
        }

        return *inner;
    }

    TEMPL Types& THIS::_getSupers() {
        static Types inner;
        return inner;
    }

    TEMPL Types& THIS::_getSubs() {
        static Types inner;
        return inner;
    }

    TEMPL Type& THIS::_getStatic() const { return const_cast<THIS&>(get()); }
    TEMPL THIS::TTypeBase(wbool) {}

#undef TEMPL
#undef THIS
#undef SUPER
}
