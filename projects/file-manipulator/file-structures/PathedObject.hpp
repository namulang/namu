#pragma once

#include <independentor.hpp>
#include <string>

namespace NE
{
    class PathedObject
    {
    public:
        PathedObject();
        PathedObject(const std::string& path);

    public:
        const std::string& getPath() const;
        type_bool isNull() const;
        virtual void release();

    protected:
        type_bool _setPath(const std::string& new_path);

    private:
        /// @remark not allowed.
        PathedObject& operator=(const PathedObject& rhs);
        PathedObject(const PathedObject& rhs);

    private:
        std::string _path;
    };
}