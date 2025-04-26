#include "indep/helper/dlib.hpp"
#include "indep/helper/nulr.hpp"
#ifndef NM_BUILD_PLATFORM_IS_WINDOWS
#    include <dirent.h> // not compatible to winOs
#    include <dlfcn.h>
#endif

namespace nm {

    NM(DEF_ME(dlib))

    me::dlib(): _handle(nullptr) {}

    me::dlib(const char* path): me(std::string(path)) {}

    me::dlib(const std::string& path): _path(path), _handle(nullptr) {}

    me::dlib(const me& rhs): _path(rhs._path), _handle(rhs._handle) {
        me& cast = (me&) rhs;
        cast._handle = nullptr;
    }

    me::~dlib() { rel(); }

    me& me::operator=(const me& rhs) {
        WHEN(this == &rhs).ret(*this);

        _path = rhs._path;
        me& cast = (me&) rhs;
        _handle = cast._handle;
        cast._handle = nullptr;
        return *this;
    }

    const std::string& me::getPath() const { return _path; }

    void me::setPath(const std::string& path) { _path = path; }

    namespace {

        std::string getErrMsg() {
#ifdef NM_BUILD_PLATFORM_IS_WINDOWS
            static nchar* buffer[256] = {
                0,
            };
            auto err = GetLastError();
            if(FormatMessageA(FORMAT_MESSAGE_FROM_STRING, nullptr, err,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), &buffer, 0, nullptr))
                return buffer;
            else return "failed get error msg from `GetLastError`";
#else
            return dlerror();
#endif
        }

    }

    tmay<std::string> me::load() {
#ifdef NM_BUILD_PLATFORM_IS_WINDOWS
        _handle = LoadLibraryA(_path.c_str());
#else
        _handle = dlopen(_path.c_str(), RTLD_LAZY);
#endif
        WHEN(_handle).ret(tmay<std::string>());

        rel();
        return tmay<std::string>(getErrMsg());
    }

    nbool me::isLoaded() const { return _handle; }

    void me::rel() {
        WHEN_NUL(_handle).ret();
#ifdef NM_BUILD_PLATFORM_IS_WINDOWS
        FreeLibrary(_handle);
#else
        dlclose(_handle);
#endif
        _handle = nullptr;
    }

    tmayFunc<dlibHandle> me::_accessFunc(const nchar* name) {
        WHEN_NUL(_handle).ret(tmayFunc<dlibHandle>(std::string("library not loaded")));

        dlibHandle func = nullptr;
#ifdef NM_BUILD_PLATFORM_IS_WINDOWS
        func = GetProcAddress(newHandle, name);
#else
        func = dlsym(_handle, name);
#endif
        WHEN(func).ret(tmayFunc<dlibHandle>(func));

        // when error occurs:
        rel();
        return tmayFunc<dlibHandle>(getErrMsg());
    }
} // namespace nm
