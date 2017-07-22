#include "FileStream.hpp"
#include <string.h>

using namespace std;

namespace NE
{
    #define THIS FileStream

    THIS::THIS() : _mode(MODE_TYPE_START), _fd(0) {}
    THIS::THIS(const std::string& new_path) : PathedObject(new_path), _mode(MODE_TYPE_START), _fd(0)  {}
    THIS::~THIS() { release(); }

    type_bool THIS::setPath(const std::string& new_path) { return _setPath(new_path); }
    type_bool THIS::setPath(const PathedObject& path)
    { 
        if(path.isNull()) return true; 
        
        return _setPath(path.getPath()); 
    }
    type_bool THIS::isInitialized() const { return _fd; }
    type_bool THIS::release()
    {
        if(_fd)
            fclose(_fd);
        _fd = NE_NULL;

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
}