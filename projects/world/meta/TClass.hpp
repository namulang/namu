#pragma once

#include "TClass.inl"
#include "helpers.hpp"
#include "../pretypes/Reses.hpp"
#include "../pretypes/Str.hpp"
#include "../containers/Chain.hpp"
#include "Classes.hpp"

namespace wrd
{
	#define TEMPL template <typename T>
	#define THIS TClass<T>

	TEMPL const Class& THIS::getClass() const { return Super::getClass(); }
	TEMPL TStrong<THIS> THIS::clone() const { return TStrong<This>((This&)*this); }

	TEMPL const Class& THIS::getClassStatic()
	{
		static This inner;
		return inner;
	}

	TEMPL TStrong<Instance> THIS::_clone() const { return TCloner<THIS>::clone(*this); }
	TEMPL THIS::TClass() { this->init(); }

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
	_REDIRECT(const wbool&, isInit)
#undef _REDIRECT

    TEMPL TStrong<Instance> THIS::instance() const { return TCloner<T>::instance(); }
	TEMPL wcnt THIS::getSize() const { return sizeof(T); }

    TEMPL Res& THIS::_initNodes()
    {
        if(Super::_initNodes())
			return wassuperfail.warn();

		return T::onInitNodes(this->_getNodes()); // getMethods from RealClass T.
    }

#define _REDIRECT(retype, func)	TEMPL retype THIS::func() { return T::__wrd_meta_class_bean::func(); }

	_REDIRECT(const Str&, getNameStatic)
	_REDIRECT(const Class&, getSuperStatic)
	_REDIRECT(const Container&, getNodesStatic)
	_REDIRECT(const Classes&, getSupersStatic)
	_REDIRECT(const Classes&, getSubsStatic)
	_REDIRECT(wbool, isOccupyStatic)
	_REDIRECT(wbool, isADTStatic)
	_REDIRECT(wbool, isTemplateStatic)
	_REDIRECT(const wbool&, isInitStatic)

#undef _REDIRECT

#undef TEMPL
#undef THIS
}
