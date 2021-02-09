#pragma once

#include "../common.hpp"

namespace wrd {

    class Stream {
        WRD_DECL_THIS(Stream)

    public:
        Stream();
        virtual ~Stream();

        /// @return true means an error.
        virtual wbool dump(const wchar* message);
        wbool isNull() const;
        wbool isEnable() const;
        void setEnable(wbool isEnable);
        virtual const wchar* getName() const = 0;
        virtual wbool init();
        virtual wbool isInit() const;
        virtual wbool rel();

    private:
        wbool _isEnable;
    };
}
