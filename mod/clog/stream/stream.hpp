#pragma once

#include "../common.hpp"

namespace namu {

    class _nout stream {
        NAMU_DECL_ME(stream)

    public:
        stream(nbool isEnable = true);
        virtual ~stream();

        /// @return true means an error.
        virtual nbool dump(const nchar* message);
        nbool isNull() const;
        virtual nbool isEnable() const;
        virtual void setEnable(nbool isEnable);
        virtual const nchar* getName() const = 0;
        virtual nbool init();
        virtual nbool isInit() const;
        virtual nbool rel();

    private:
        nbool _isEnable;
    };
}
