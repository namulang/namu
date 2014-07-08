#pragma once

#include "Property.hpp"

#ifdef DEVELOPER
#	ifdef _DEBUG
#		if PROPERTY_EXPORT_EXECUTE_MODULE == 1
#			define	_EXECUTE_ENTRYPOINT			registerModuleDevDbg()
#		endif
#		if PROPERTY_EXPORT_PANEL == 1
#			define	_PANEL_ENTRYPOINT			registerPanelDevDbg()
#		endif
#	else
#		if PROPERTY_EXPORT_EXECUTE_MODULE == 1
#			define	_EXECUTE_ENTRYPOINT			registerModuleDev()
#		endif
#		if PROPERTY_EXPORT_PANEL == 1
#			define	_PANEL_ENTRYPOINT			registerPanelDev()
#		endif
#	endif
#else
#	if PROPERTY_EXPORT_EXECUTE_MODULE == 1
#		define	_EXECUTE_ENTRYPOINT				registerModule()
#	endif
#	if PROPERTY_EXPORT_PANEL == 1
#		define	_PANEL_ENTRYPOINT				registerPanel()
#	endif
#endif
