#include "ttypeBase.inl"

namespace wrd {

#define ME ttypeBase<void, type>
#define SUPER type

    ME::ttypeBase() { this->init(); }
    wbool ME::isTemplate() const { return false; }
    wbool ME::isAbstract() const { return true; }
    const std::string& ME::getName() const { return "void"; }
    void* ME::make() const { return nullptr; }
    wcnt ME::size() const { return 0; }

    const type& ME::getSuper() const {
        return ttype<typename tadaptiveSuper<void>::super>::get();
    }

    const wbool& ME::isInit() const {
        static wbool inner = typeid(void) == typeid(adam);
        return inner;
    }

    const ME& ME::get() {
        static ME* inner = nullptr;
        if(!inner) {
            inner = new ME(false);
            inner->init();
        }

        return *inner;
    }

    types& ME::_getSupers() {
        static types inner;
        return inner;
    }

    types& ME::_getSubs() {
        static types inner;
        return inner;
    }

    type& ME::_getStatic() const { return const_cast<ME&>(get()); }

    ME::ttypeBase(wbool) {}

#undef TEMPL
#undef ME
#undef SUPER
}
