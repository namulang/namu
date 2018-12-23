#pragma once

#include "TClass.inl"
#include "helpers.hpp"

namespace wrd
{
	#define TEMPL template <typename T>
	#define THIS TClass<T>

	TEMPL THIS::Tclass() { this->init(); }
	TEMPL wbool THIS::isADT() const { return TIfADT<T>::is; }
	TEMPL wbool THIS::isTemplate() const { return TIfTemplate<T>::is; }
	TEMPL const Container& THIS::getNodes() const { return this->getStaticMembers(); }

#define _REDIRECT(return, func)			\
	TEMPL return THIS::get ## func() const	\
	{										\
		WRD_IS_THIS_1(const Str)			\
		return getStatic ## func();			\
	}

	_REDIRECT(const Str&, Name)
	_REDIRECT(const Classes&, Supers)
	_REDIRECT(const Classes&, Subs)
#undef _REDIRECT

	TEMPL static WRD_LAZY_METHOD(const Container, THIS::getStaticMembers, WRD_VOID(), Array)
	TEMPL static WRD_LAZY_METHOD(const Classes, THIS::getStaticSupers)
	TEMPL static WRD_LAZY_METHOD(const Classes, THIS::getStaticSubs)
	TEMPL static WRD_LAZY_METHOD(wboo, THIS::isStaticOccupy, WRD_VOID(), wboo, isSub<Object/*TODO: OccupiableObject*/>())
    TEMPL TStrong<Instance> THIS::instance() const { return TCloner<T>::instance(); }
    TEMPL wbool THIS::isOccupy() const { return isStaticOccupy(); }
    TEMPL const Class& THIS::getSuper() const { return T::Super::getClassStatic(); }

    TEMPL Result& THIS::_setInit(wbool newone)
    {
    	this->_is_initd = newone;
        return Success;
    }

    TEMPL Result& THIS::_initMembers()
    {
        /*TODO: uncomment this if(Super::_initMembers())
                return SuperFail.warn();*/

        return T::_onInitializeMembers(_getNodes()); // getMethods from RealClass T.
    }

    TEMPL static const Str& THIS::getStaticName()
    {
        static Str inner;
        if(inner.getLength() <= 0)
        {
            int status = 0;
            wchar* demangled = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
            inner = demangled;
            free(demangled);
        }

        return inner;
    }

#undef TEMPL
#undef THIS
}
