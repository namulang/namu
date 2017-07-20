#pragma once

#include "../file-structures/PathedObject.hpp"

using namespace std;

namespace NE
{
    class FileStream : public PathedObject
    {
    public:
        enum Mode
        {
            MODE_TYPE_START = 0,
            READ_ONLY,
            WRITABLE,

            MODE_TYPE_END,
            OVERWRITABLE = MODE_TYPE_END,
        };

    public:
        type_bool setPath(const std::string& new_path) { return _setPath(new_path); }
        type_bool setPath(const PathedObject& path) { 
            if(path.isNull()) return true; 
            
            return _setPath(path.getPath()); 
        }
        type_bool isOpen() const { return _fd; }
        virtual void release() {
            if(_fd)
                fclose(_fd);
            _fd = NE_NULL;

            _mode = MODE_TYPE_START;

            PathedObject::release();
        }
        virtual void initialize() = 0;
        type_bool setMode(Mode new_mode) {
            if(isOpen()) return true;

            _mode = new_mode;
            return false;
        }
        Mode getMode() const { return _mode; }
        type_count write(const void* chunks, type_count bytes) {
            if( ! isOpen()) return 0;

            return fwrite(chunks, 1, bytes, _fd);
        }

    private:
        Mode _mode;
        FILE* _fd;
    };

    class BinaryStream : public FileStream
    {
    public:        
        template <typename T>
        type_count write(const T& datum) {
            return write(&datum, sizeof(T));
        }
    };

    class AsciiStream : public FileStream
    {
    public:
        template <typename T>
        type_count write(const T& datum) { return write(to_string(datum)); }
        type_count write(const std::string& datum) { return FileStream::write(datum.c_str(), sizeof(char) * datum.size()); }
    };
}