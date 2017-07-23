#pragma once

#include "FileStream.hpp"

namespace NE
{
    class BinaryStream : public FileStream
    {
    public:
        BinaryStream();
        BinaryStream(const std::string& new_path);
        virtual ~BinaryStream();

    public:
        using FileStream::operator=;
        
        virtual type_bool initialize();

        using FileStream::write;
        template <typename T>
        type_count write(const T& datum) { return write(&datum, sizeof(T)); }

        type_count write(const char* str);
        type_count write(const string& str);
        virtual type_count write(const void* chunks, type_count bytes);
        virtual type_count read(void* target, type_count bytes);

        using FileStream::read;
        template <typename T>
        T read()
        {
            T to_return;
            read(&to_return, sizeof(T));
            return to_return;
        }

        std::string read(type_count bytes);

    private:
        BinaryStream(const PathedObject& object);

    };
}