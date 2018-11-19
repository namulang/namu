#pragma once

#include "../Includes.hpp"

namespace NE
{
    class PathedObject
    {
    public:
        PathedObject();
        PathedObject(const std::string& path);
        PathedObject(const PathedObject& rhs);

    public:
        virtual type_bool initialize() = 0;
        virtual type_bool isInitialized() const = 0;
        const std::string& getPath() const;
        type_bool isNull() const;
        virtual type_bool release();

    protected:
        type_bool _setPath(const std::string& new_path);

    private:
        /// @remark not allowed.
        PathedObject& operator=(const PathedObject& rhs);

    private:
        std::string _path;
    };
}
