#pragma once

#include "../common.hpp"

namespace wrd {

    class stream {
        WRD_DECL_ME(stream)

    public:
        stream(wbool isEnable = true);
        virtual ~stream();

        /// @return true means an error.
        virtual wbool dump(const wchar* message);
        wbool isNull() const;
        virtual wbool isEnable() const;
        virtual void setEnable(wbool isEnable);
        virtual void saveStreamEnable() { _save = _isEnable; }
        virtual void loadStreamEnable() { _isEnable = _save; }
        virtual const wchar* getName() const = 0;
        virtual wbool init();
        virtual wbool isInit() const;
        virtual wbool rel();

    private:
        wbool _isEnable;
        wbool _save;
    };
}
