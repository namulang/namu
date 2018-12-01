#include "FileLogStream.hpp"

namespace wrd
{
    #define THIS FileLogStream
    typedef std::string string;

    THIS::THIS() : Stream() { _file.setMode(FileStream::APPENDABLE); }
    THIS::THIS(const string& new_path) : Stream()
    { 
        _file.setMode(FileStream::APPENDABLE);
        _file.setPath(new_path);
    }

    const char* THIS::getName() const { return "FileLogStream"; }
    
    wbool THIS::initialize()
    {
        if(Stream::initialize()) return true;

        if(_file.initialize())
            return true;

        return _file.setCursor(_file.getEndOfFile());
    }
    
    wbool THIS::setPath(const string& new_path) { return _file.setPath(new_path); }
    const string& THIS::getPath() const { return _file.getPath(); }
    
    wbool THIS::dump(const char* message)
    {
        if(Stream::dump(message)) return true;

        return _file.write(std::string(message) + "\n") <= 0;
    }

    wbool THIS::release()
    {
        _file.release();
        return Stream::release();
    }
}
