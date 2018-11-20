#include "FileStream.hpp"
#include <string.h>

using namespace std;

namespace NE
{
    #define THIS FileStream

    THIS::THIS() : _mode(MODE_TYPE_START), _fd(0) {}
    THIS::THIS(const std::string& new_path) : PathedObject(new_path), _mode(MODE_TYPE_START), _fd(0)  {}
    THIS::~THIS() { release(); }

    type_bool THIS::operator+=(type_int delta)
    {
        if( ! isInitialized()) return 0;

        return setCursor(getCursor() + delta);
    }

    type_bool THIS::operator-=(type_int delta)
    {
        if( ! isInitialized()) return 0;

        return setCursor(getCursor() - delta);
    }

    type_bool THIS::operator=(type_int new_position) { return setCursor(new_position); }

    type_int THIS::getCursor() const 
    {
        if( ! isInitialized()) return 0;

        return ftell(_fd);
    }

    type_int THIS::getEndOfFile() const
    {
        if( ! isInitialized()) return 0;

        type_int backup = getCursor();
        
        FILE* unconsted = const_cast<FILE*>(_fd);
        if(fseek(unconsted, 0, SEEK_END))
            return 0;

        type_int to_return = getCursor();
        fseek(unconsted, backup, SEEK_SET);

        return to_return;
    }
    type_bool THIS::setCursor(type_int new_position)
    {
        if( ! isInitialized()) return true;
        
        type_int mode = new_position >= 0 ? SEEK_SET : SEEK_END;
        if(fseek(_fd, new_position, mode))
            return true;

        return false;
    }
    type_bool THIS::setPath(const std::string& new_path) { return _setPath(new_path); }
    type_bool THIS::setPath(const PathedObject& path)
    { 
        if(path.isNull()) return true; 
        
        return _setPath(path.getPath()); 
    }
    type_bool THIS::initialize()
    {
        if(getMode() != APPENDABLE) return false;

        FILE* tmp = fopen(getPath().c_str(), "r");
        if( ! tmp)
            tmp = fopen(getPath().c_str(), "w");
        fclose(tmp);
        return false;
    }
    type_bool THIS::isInitialized() const { return _fd; }
    type_bool THIS::release()
    {
        if(_fd)
            fclose(_fd);
        _fd = WRD_NULL;

        _mode = MODE_TYPE_START;

        return PathedObject::release();            
    }
    type_bool THIS::setMode(Mode new_mode)
    {
        if(isInitialized()) return true;

        _mode = new_mode;
        return false;
    }
    THIS::Mode THIS::getMode() const { return _mode; }    
    THIS::THIS(const PathedObject& object) {}

    std::string THIS::readWhole()
    {
        const type_int SIZE = 65535;
        char buffer[SIZE] = {0, };

        setCursor(0);
        std::string contents;
        while( ! isEndOfFile())
        {
            type_count count = read(buffer, SIZE);
            contents.append(buffer, count);
        }

        return contents;
    }
    
    type_bool THIS::isEndOfFile() const
    {
        if( ! _fd) return true;

        return feof(_fd);
    }
}
