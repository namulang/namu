#pragma once

#include "../commons.hpp"

namespace NE
{
    class Stream
    {
    public:
        Stream();
        virtual ~Stream();

        /// @return true means an error.
        virtual type_bool dump(const char* message);
        type_bool isNull() const;
        type_bool isEnable() const;
        void setEnable(type_bool is_enable);
        virtual const char* getName() const = 0;
        virtual type_bool initialize();
        virtual type_bool isInitialized() const;
        virtual type_bool release();

    private:
        type_bool _is_enable;
    };
}
