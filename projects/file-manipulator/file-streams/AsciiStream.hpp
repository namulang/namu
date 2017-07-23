#pragma once

#include "FileStream.hpp"

namespace NE
{
    class AsciiStream : public FileStream
    {
    public:
        AsciiStream();
        AsciiStream(const std::string& new_path);
        virtual ~AsciiStream();

    public:
        using FileStream::operator=;

        virtual type_bool initialize();
        
        using FileStream::write;
        template <typename T>
        type_count write(const T& datum) { return write(to_string(datum)); }

        type_count write(const std::string& datum);
        virtual type_count write(const void* chunks, type_count bytes);
        virtual type_count read(void* target, type_count bytes);
        std::string readToken(const std::string& delimeter = " ");
        std::string readLine();
        virtual type_bool release();

    private:
        AsciiStream(const PathedObject& object);
        std::string _peelOffBuffer(type_count bytes/*except for null*/);
        type_count _readToBuffer(type_count bytes=1024);

    private:
        std::string _buffer;
    };
}