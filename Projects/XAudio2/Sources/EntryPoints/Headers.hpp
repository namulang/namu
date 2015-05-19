#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/XAudio2WAVEDecoder.hpp"
#include "../Modules/XAudio2Manager.hpp"
#include "../Modules/XAudio2OGGDecoder.hpp"
#include "../Modules/XAudio2WAVEDecoder.hpp"

#ifndef XAudio2_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "XAudio2.dev.dbg.lib")
#			else
#				pragma comment(lib, "XAudio2.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "XAudio2.dev.lib")
#			else
#				pragma comment(lib, "XAudio2.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "XAudio2.lib")
#		else
#			pragma comment(lib, "XAudio2.mbcs.lib")
#		endif
#	endif
#endif
