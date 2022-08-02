#include "ttypeBase.inl"

namespace namu {

#define ME ttypeBase<void, type>
#define SUPER type

    ME::ttypeBase() { this->init(); }
    wbool ME::isTemplate() const { return false; }
    wbool ME::isAbstract() const { return true; }

    const std::string& ME::getName() const {
        static const std::string inner = "void";
        return inner;
    }

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

    types** ME::_onGetLeafs() const {
        static types* inner = nullptr;
        return &inner;
    }

    void ME::_onAddSubClass(const type& subClass) {
        super::_onAddSubClass(subClass);

        types** leafs = _onGetLeafs();
        if(*leafs)
            this->_setLeafs(nullptr);
    }

#undef TEMPL
#undef ME
#undef SUPER
}
