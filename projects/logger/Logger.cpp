#include "Logger.hpp"
#include <iostream>
#include <stdarg.h>
#include "streams.hpp"

namespace WRD
{
    namespace
    {
        template <typename T>
        T& nullreference() {
            T* nulled = 0;
            return *nulled;
        }
    }

    #define THIS Logger
    typedef std::string string;
  
    const char* THIS::getName() const { return "Logger"; }
    const Stream& THIS::operator[](type_index n) const { return getStream(n); }
    Stream& THIS::operator[](type_index n) { return getStream(n); }
    const Stream& THIS::operator[](const char* message) const { return getStream(message); }
    Stream& THIS::operator[](const char* message) { return getStream(message); }

    Stream& THIS::getStream(type_index n)
    { 
        if(n < 0 || n >= getStreamCount())
            return nullreference<Stream>();

        return *_streams[n]; 
    }

    const Stream& THIS::getStream(type_index n) const
    {
        THIS* unconsted = const_cast<THIS*>(this);

        return unconsted->getStream(n);
    }

    const Stream& THIS::getStream(const char* c_message) const
    { 
        string message = c_message;
        for(auto e : _streams)
            if(string(e->getName()) == message)
                return *e;

        return nullreference<Stream>();
    }

    Stream& THIS::getStream(const char* message)
    {
        const THIS* consted = this;

        return const_cast<Stream&>(consted->getStream(message));
    }

    type_count THIS::getStreamCount() const { return _streams.size(); }
    
    type_bool THIS::dump(const char* message)
    {
        type_bool result = false;
        for(auto e : _streams)
            result |= e->dump(message);
        
        return result;
    }

    type_bool THIS::dumpFormat(const char* format, ...)
    {
        va_list va;
        va_start(va, format);
        
        char buffer[1024];
        vsnprintf(buffer, 1024, format, va);
        va_end(va);

        return dump(buffer);
    }

    type_bool THIS::pushStream(Stream* new_stream)
    {
        if( ! new_stream) return true;

        _streams.push_back(new_stream);
        if(isInitialized())
            return new_stream->initialize();
        return false;
    }

    type_bool THIS::initialize()
    {
        static Stream* streams[] = {new ConsoleStream(), new FileLogStream("./logs"), 0};
        Stream* e = 0;
        for(int n=0; (e = streams[n]) ;n++)
            pushStream(e);

        return false;
    }

    type_bool THIS::isInitialized() const
    {
        for(auto e : _streams)
            if( ! e->isInitialized())
                return false;

        return true;
    }
    
    type_bool THIS::release()
    {
        for(auto e : _streams)
        {
            e->release();
            delete e;
        }
        _streams.clear();
        return THIS::Stream::release();
    }

    THIS& THIS::getInstance()
    {
        static THIS* inner = 0;
        if(inner->isNull())
        {
            inner = new THIS();
            inner->initialize();
        }

        return *inner;
    }

    THIS::THIS() : Stream() {}
    THIS::THIS(const THIS& rhs) : Stream(rhs) {}
}
