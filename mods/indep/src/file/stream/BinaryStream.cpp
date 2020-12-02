#include "BinaryStream.hpp"
#include "../structure.hpp"

namespace wrd { namespace indep {

    WRD_DEF_THIS(BinaryStream)

    This::BinaryStream() : Super() {}
    This::BinaryStream(const std::string& new_path) : Super(new_path) {}

    This::BinaryStream(const File& file) : Super() {
        if( ! file.isNull())
            setPath(file.getPath());
    }
    This::~BinaryStream() { release(); }


    wbool This::init() {
        if(Super::init()) return true;

        const char* mode = 0;
        switch(getMode()) {
            case READ_ONLY:         mode = "rb";    break;
            case OVERWRITE_ONLY:    mode = "w+b";   break;
            case APPENDABLE:        mode = "r+b";   break;
            default:
                return true;
        }

        _fd = fopen(getPath().c_str(), mode);
        if(getMode() == APPENDABLE)
            setCursor(getEndOfFile());

        return ! isInit();
    }

    wcnt This::write(const char* str) { return write(str, sizeof(char) * strlen(str)); }
    wcnt This::write(const std::string& str) { return write(str.c_str()); }

    wcnt This::write(const void* chunks, wcnt bytes) {
        if( ! isInit()) return 0;

        return fwrite(chunks, 1, bytes, _fd);
    }

    wcnt This::read(void* target, wcnt bytes) {
        if( ! isInit()) return 0;

        return fread(target, 1, bytes, _fd);
    }

    std::string This::read(wcnt bytes) {
        char* buffer = new char[bytes];

        wcnt n = read(buffer, sizeof(char) * bytes);
        std::string to_return(buffer, n);

        delete [] buffer;

        return to_return;
    }

    This::BinaryStream(const PathedObject& object) {}
} }
