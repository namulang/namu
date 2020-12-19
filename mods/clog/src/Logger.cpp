#include "Logger.hpp"
#include <iostream>
#include "stream.hpp"

namespace wrd { namespace clog {

    WRD_DEF_THIS(Logger)
    typedef std::string string;
    typedef wrd::indep::BuildFeature::Config Config;

    const wchar* This::getName() const { return "Logger"; }
    const Stream& This::operator[](widx n) const { return getStream(n); }
    Stream& This::operator[](widx n) { return getStream(n); }
    const Stream& This::operator[](const wchar* message) const { return getStream(message); }
    Stream& This::operator[](const wchar* message) { return getStream(message); }

    Stream& This::getStream(widx n) {
        if(n < 0 || n >= getStreamCount())
            return nulr<Stream>();

        return *_streams[n];
    }

    const Stream& This::getStream(widx n) const {
        WRD_UNCONST()
        return unconst.getStream(n);
    }

    const Stream& This::getStream(const wchar* c_message) const {
        string message = c_message;
        for(auto e : _streams)
            if(string(e->getName()) == message)
                return *e;

        return nulr<Stream>();
    }

    Stream& This::getStream(const wchar* message) {
        const This* consted = this;

        return const_cast<Stream&>(consted->getStream(message));
    }

    wcnt This::getStreamCount() const { return _streams.size(); }

    wbool This::dump(const wchar* message) {
        wbool result = false;
        for(auto e : _streams)
            result |= e->dump(message);

        return result;
    }

    wbool This::dumpFormat(const wchar* fmt, ...) {
        va_list va;
        va_start(va, fmt);
        wchar buf[1024];
        vsnprintf(buf, 1024, fmt, va);
        va_end(va);

        return dump(buf);
    }

    wbool This::pushStream(Stream* new_stream) {
        if( ! new_stream) return true;

        _streams.push_back(new_stream);
        if(isInit())
            return new_stream->init();
        return false;
    }

    wbool This::init() {
        rel();

        static Stream* streams[] = {new ConsoleStream(), new FileLogStream("./logs"), 0};
        Stream* e = 0;
        for(int n=0; (e = streams[n]) ;n++)
            pushStream(e);

        return false;
    }

    wbool This::isInit() const {
        for(auto e : _streams)
            if( ! e->isInit())
                return false;

        return true;
    }

    wbool This::rel() {
        for(auto e : _streams)
        {
            e->rel();
            delete e;
        }
        _streams.clear();
        return Super::rel();
    }

    This& This::get() {
        static This* inner = 0;
        if(inner->isNull())
        {
            inner = new This();
            inner->init();
        }

        return *inner;
    }

    This::Logger() : Super() {}
    This::Logger(const This& rhs) : Super(rhs) {}
} }
