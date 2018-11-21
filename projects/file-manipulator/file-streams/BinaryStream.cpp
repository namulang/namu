#include "BinaryStream.hpp"
#include "../file-structures.hpp"
#include <string.h>

namespace WRD
{
    #define THIS BinaryStream

    THIS::THIS() : FileStream() {}
    THIS::THIS(const std::string& new_path) : FileStream(new_path) {}
    THIS::THIS(const File& file) : FileStream() 
    {
        if( ! file.isNull())
            setPath(file.getPath());
    }
    THIS::~THIS() { release(); }


    type_bool THIS::initialize()
    {
        if(FileStream::initialize()) return true;

        const char* mode = 0;
        switch(getMode())
        {
        case READ_ONLY:         mode = "rb";    break;
        case OVERWRITE_ONLY:    mode = "w+b";   break;
        case APPENDABLE:        mode = "r+b";   break;
        default:
            return true;
        }
        
        _fd = fopen(getPath().c_str(), mode);
        if(getMode() == APPENDABLE)
            setCursor(getEndOfFile());

        return ! isInitialized();
    }

    type_count THIS::write(const char* str) { return write(str, sizeof(char) * strlen(str)); }
    type_count THIS::write(const std::string& str) { return write(str.c_str()); }

    type_count THIS::write(const void* chunks, type_count bytes)
    {
        if( ! isInitialized()) return 0;

        return fwrite(chunks, 1, bytes, _fd);
    }

    type_count THIS::read(void* target, type_count bytes)
    {
        if( ! isInitialized()) return 0;

        return fread(target, 1, bytes, _fd);
    }

    std::string THIS::read(type_count bytes)
    {
        char* buffer = new char[bytes];

        type_count n = read(buffer, sizeof(char) * bytes);
        std::string to_return(buffer, n);

        delete [] buffer;

        return to_return;
    }

    THIS::THIS(const PathedObject& object) {}
}
