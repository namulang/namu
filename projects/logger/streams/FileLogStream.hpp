#pragma once

#include "Stream.hpp"

namespace NE
{
    class FileLogStream : public Stream {
    public:
        FileLogStream();
        FileLogStream(const std::string& new_path);

    public:
        virtual const char* getName() const;
        virtual type_bool initialize();
        type_bool setPath(const std::string& new_path);
        const std::string& getPath() const;
        virtual type_bool dump(const char* message);
        virtual type_bool release();

    private:
        AsciiStream _file;
    };
}
