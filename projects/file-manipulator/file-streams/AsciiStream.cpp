#include "AsciiStream.hpp"

namespace NE
{
    #define THIS AsciiStream

    THIS::THIS() : FileStream() {}
    THIS::THIS(const string& new_path) : FileStream(new_path) {}
    THIS::~THIS() { release(); }

    type_bool THIS::initialize() 
    {
        const char* mode = 0;
        switch(getMode())
        {
        case READ_ONLY:         mode = "r"; break;
        case OVERWRITE_ONLY:    mode = "r+";break;
        case WRITABLE:          mode = "a+";break;
        default:
            return true;
        }

        _fd = fopen(getPath().c_str(), mode);
        
        return ! isInitialized();
    }
    
    type_count THIS::write(const string& datum) { return write(datum.c_str(), sizeof(char) * datum.size()); }
    
    type_count THIS::write(const void* chunks, type_count bytes)
    {
        if( ! isInitialized()) return 0;

        return fwrite(chunks, 1, bytes, _fd);
    }

    type_count THIS::read(void* target, type_count bytes)
    {
        string buffer = _peelOffBuffer(bytes);
        
        type_count count = 0;
        type_count max = buffer.length() > bytes ? bytes : buffer.length();
        char* t = (char*) target;
        for(; count < max ;count++)
            t[count] = buffer[count];

        return max;
    }

    string THIS::readToken(const string& delimeter)
    {
        type_bool matched_once = false;
        type_count last = 0;
        type_count to_be_cut = 0;
        while(1)
        {
            //  algorithm:
            //      it finds the index when extracting character, which means "e", is judged as one of delimiter.
            //      But, if the next character of "e" is also one of delimiter, we should forward until it's not.
            if(_buffer.length() <= to_be_cut)
                if(_readToBuffer() <= 0)
                    break;
            char e = _buffer[to_be_cut++];
            if(delimeter.find(e) != string::npos)
                matched_once = true; // okay. we've met one of a delimiter.
            else if(matched_once)
                break;                    
            else
                last = to_be_cut; // our users shouldn't receive a string with a delimiter.
        }
        string to_return(_buffer.c_str(), last);
        _buffer.erase(0, to_be_cut); // last + delimiters.

        return to_return;
    }

    string THIS::readLine() { return readToken("\n"); }

    type_bool THIS::release()
    {
        _buffer.clear();
        return FileStream::release();
    }

    THIS::THIS(const PathedObject& object) {}
    
    string THIS::_peelOffBuffer(type_count bytes/*except for null*/)
    {
        if(_buffer.length() < bytes)
            _readToBuffer();

        type_count max_size = _buffer.length() > bytes ? bytes : _buffer.length();
        string to_return(_buffer, max_size);
        _buffer.erase(0, max_size);
        return to_return;
    }
    
    type_count THIS::_readToBuffer(type_count bytes)
    {
        if( ! isInitialized()) return 0;

        char* buffer = new char[bytes];

        type_count n = fread(buffer, 1, bytes, _fd);
        _buffer += string(buffer, n);
        
        delete [] buffer;
        return n;
    }
}