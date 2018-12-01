#pragma once

#include "../fm-commons.hpp"

namespace wrd
{
    class PathedObject
    {
    public:
        PathedObject();
        PathedObject(const std::string& path);
        PathedObject(const PathedObject& rhs);

    public:
        virtual wbool initialize() = 0;
        virtual wbool isInitialized() const = 0;
        const std::string& getPath() const;
        wbool isNull() const;
        virtual wbool release();

    protected:
        wbool _setPath(const std::string& new_path);

    private:
        /// @remark not allowed.
        PathedObject& operator=(const PathedObject& rhs);

    private:
        std::string _path;
    };
}
