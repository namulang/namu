#pragma once

#include "TClass.inl"
#include "helpers.hpp"
#include "../pretypes/Str.hpp"
#include "../container/Chain.hpp"
#include "Classes.hpp"

namespace wrd
{
	#define TEMPL template <typename T>
	#define THIS TClass<T>

	TEMPL const Class& THIS::getClass() const { return *this; }
	TEMPL TStrong<Instance> THIS::_clone() const { return TCloner<THIS>::clone(*this); }
	TEMPL THIS::TClass() { this->init(); }

/*		TODO: add this on _REDIRECT. 
 *		WRD_IS_THIS_1(const Str)			\
 */
#define _REDIRECT(retype, func)			\
	TEMPL retype THIS::func() const	\
	{										\
		return this->func ## Static();\
	}

	_REDIRECT(wbool, isADT)
	_REDIRECT(wbool, isTemplate)
	_REDIRECT(const Str&, getName)
	_REDIRECT(const Classes&, getSupers)
	_REDIRECT(const Classes&, getSubs)
	_REDIRECT(const Container&, getNodes)
	_REDIRECT(wbool, isOccupy)
	_REDIRECT(const Class&, getSuper)
#undef _REDIRECT

    TEMPL TStrong<Instance> THIS::instance() const { return TCloner<T>::instance(); }

    TEMPL Res& THIS::_initNodes()
    {
        /*TODO: uncomment this if(Super::_initMembers())
                return SuperFail.warn();*/

        return nulr<Res>();//TODO: uncomment this. T::_onInitNodes(this->_getNodes()); // getMethods from RealClass T.
    }

    TEMPL const Str& THIS::getNameStatic()
    {
        static Str inner;
		/*TODO: uncomment these:
        if(inner.getLength() <= 0)
        {
            int status = 0;
            wchar* demangled = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
            inner = demangled;
            free(demangled);
        }
		*/

        return inner;
    }

	TEMPL WRD_LAZY_METHOD(const Class&, THIS::getSuperStatic, WRD_VOID(), TClass<Super>)
	TEMPL WRD_LAZY_METHOD(const Container&, THIS::getNodesStatic, WRD_VOID(), Array)
	TEMPL WRD_LAZY_METHOD(const Classes&, THIS::getSupersStatic, WRD_VOID(), Classes)
	TEMPL WRD_LAZY_METHOD(const Classes&, THIS::getSubsStatic, WRD_VOID(), Classes)
	TEMPL WRD_LAZY_METHOD_5(wbool, THIS::isOccupyStatic, WRD_VOID(), wbool, TIfSub<T WRD_COMMA() Object/*TODO: OccupiableObject*/>::is)
	TEMPL WRD_LAZY_METHOD(wbool, THIS::isADTStatic, WRD_VOID(), wbool, TIfADT<T>::is)
	TEMPL WRD_LAZY_METHOD(wbool, THIS::isTemplateStatic, WRD_VOID(), wbool, TIfTemplate<T>::is)

#undef TEMPL
#undef THIS
}
