#pragma once

#include "../msg-usr/Manager.hpp"

namespace wrd
{
	class Classer : public Manager
	{	WRD_CLASS_DECL(Classer)
		friend class Moduler; // for _unbind.
		friend class Class; // for _getPreloads.
	public:
		//	State:
		Res& init();
		//	Thing:
		Res& release();

	private:
		//	TODO:
		//	_unbind only available to some classes.
		//	TODO: Res& _unbind(Class& old);

	private:
		typedef std::vector<Class*> ClassPtrs;
		static WRD_LAZY_METHOD(ClassPtrs, _getPreloads)
		///	@param it	it should be a ptr of heap allocated or global/static variable.
		static Res& _preload(const Class& it);
		static WRD_LAZY_METHOD(wbool&, _isPreloaded, WRD_VOID(), wbool, false)
	};
}
