#include "AsciiStream.hpp"
#include "../structure.hpp"

namespace wrd { namespace indep {

    WRD_DEF_THIS(AsciiStream)

    using namespace std;

    This::AsciiStream() : Super() {}
    This::AsciiStream(const string& new_path) : Super(new_path) {}

    This::AsciiStream(const File& file) : Super() {
        if( ! file.isNull())
            setPath(file.getPath());
    }

    This::~AsciiStream() { release(); }

    wbool This::init() {
        if(Super::init()) return true;

        const char* mode = 0;
        switch(getMode()) {
            case READ_ONLY:         mode = "r"; break;
            case OVERWRITE_ONLY:    mode = "w+";break;
            case APPENDABLE:        mode = "r+";break;
            default:
                return true;
        }

        _fd = fopen(getPath().c_str(), mode);
        if(getMode() == APPENDABLE)
            setCursor(getEndOfFile());

        return ! isInit();
    }

    wcnt This::write(const string& datum) { return write(datum.c_str(), sizeof(char) * datum.size()); }

    wcnt This::write(const void* chunks, wcnt bytes) {
        if( ! isInit()) return 0;

        return fwrite(chunks, 1, bytes, _fd);
    }

    wcnt This::read(void* target, wcnt bytes) {
        string buffer = _peelOffBuffer(bytes);

        wcnt count = 0;
        wcnt max = buffer.length() > bytes ? bytes : buffer.length();
        char* t = (char*) target;
        for(; count < max ;count++)
            t[count] = buffer[count];

        return max;
    }

    string This::readToken(const string& delimeter) {
        wbool matched_once = false;
        wcnt last = 0;
        wcnt to_be_cut = 0;

        while(1) {
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

    string This::readLine() { return readToken("\n"); }

    wbool This::release() {
        _buffer.clear();
        return Super::release();
    }

    This::AsciiStream(const PathedObject& object) {}

    string This::_peelOffBuffer(wcnt bytes/*except for null*/) {
        if(_buffer.length() < bytes)
            _readToBuffer();

        wcnt max_size = _buffer.length() > bytes ? bytes : _buffer.length();
        string to_return(_buffer.c_str(), max_size);
        _buffer.erase(0, max_size);
        return to_return;
    }

    wcnt This::_readToBuffer(wcnt bytes) {
        if( ! isInit()) return 0;

        char* buffer = new char[bytes];

        wcnt n = fread(buffer, 1, bytes, _fd);
        _buffer += string(buffer, n);

        delete [] buffer;
        return n;
    }
} }
