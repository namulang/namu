#include "logger.hpp"
#include <iostream>
#include "stream.hpp"

namespace namu {

    WRD_DEF_ME(logger)
    typedef std::string string;

    const wchar* me::getName() const { return "logger"; }
    const stream& me::operator[](widx n) const { return getStream(n); }
    stream& me::operator[](widx n) { return getStream(n); }
    const stream& me::operator[](const wchar* message) const { return getStream(message); }
    stream& me::operator[](const wchar* message) { return getStream(message); }

    stream& me::getStream(widx n) {
        if(n < 0 || n >= getStreamCount())
            return nulOf<stream>();

        return *_streams[n];
    }

    const stream& me::getStream(widx n) const {
        WRD_UNCONST()
        return unconst.getStream(n);
    }

    const stream& me::getStream(const wchar* c_message) const {
        string message = c_message;
        for(auto e : _streams)
            if(string(e->getName()) == message)
                return *e;

        return nulOf<stream>();
    }

    stream& me::getStream(const wchar* message) {
        const me* consted = this;

        return const_cast<stream&>(consted->getStream(message));
    }

    wcnt me::getStreamCount() const { return _streams.size(); }

    wbool me::dump(const wchar* message) {
        if(!isEnable()) return false;

        wbool result = false;
        for(auto e : _streams)
            result |= e->dump(message);

        return result;
    }

    wbool me::dumpFormat(const wchar* fmt, ...) {
        va_list va;
        va_start(va, fmt);
        wchar buf[1024];
        vsnprintf(buf, 1024, fmt, va);
        va_end(va);

        return dump(buf);
    }

    wbool me::pushStream(stream* new_stream) {
        if( ! new_stream) return true;

        _streams.push_back(new_stream);
        if(isInit())
            return new_stream->init();
        return false;
    }

    wbool me::init() {
        rel();
        super::init();

        static stream* streams[] = {new consoleStream(), new fileLogStream("./logs"), 0};
        stream* e = 0;
        for(int n=0; (e = streams[n]) ;n++)
            pushStream(e);

        return false;
    }

    wbool me::isInit() const {
        for(auto e : _streams)
            if( ! e->isInit())
                return false;

        return true;
    }

    wbool me::rel() {
        for(auto e : _streams)
        {
            e->rel();
            delete e;
        }
        _streams.clear();
        return super::rel();
    }

    me& me::get() {
        static me* inner = 0;
        if(inner->isNull())
        {
            inner = new me();
            inner->init();
        }

        return *inner;
    }

    wbool me::dumpFormatLog(const wchar* level, const wchar* tag, const wchar* filename, const wchar* func, int line, const wchar* fmt, ...) {
        std::cout << platformAPI::getConsoleFore(platformAPI::BROWN);
        dumpFormat("%s ", platformAPI::createNowTime("%b %d %Y  %X").c_str());

        platformAPI::consoleColor clrLv = platformAPI::WHITE;
        switch(level[0]) {
            case 'E': clrLv = platformAPI::LIGHTRED; break;
            case 'W': clrLv = platformAPI::YELLOW; break;
            case 'I': clrLv = platformAPI::LIGHTBLUE; break;
        }

        std::cout << platformAPI::getConsoleFore(clrLv);
        dumpFormat("%s %s ", tag, level);

        std::cout << platformAPI::getConsoleFore(platformAPI::GREEN);
        dumpFormat("<%s::%s#%d> ", filename, func, line);

        std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGRAY);
        va_list va;
        va_start(va, fmt);
        wchar buf[1024];
        vsnprintf(buf, 1024, fmt, va);
        va_end(va);
        return dump(buf);
    }

    me::logger() : super() {}
    me::logger(const me& rhs) : super(rhs) {}

    wbool me::isEnable() const {
        for(stream* s : _streams)
            if(s->isEnable()) return true;
        return false;
    }

    void me::setEnable(wbool enable) {
        for(stream* s : _streams)
            s->setEnable(enable);
    }
    void me::saveStreamEnable() {
        for(stream* s : _streams)
            s->saveStreamEnable();
    }
    void me::loadStreamEnable() {
        for(stream* s : _streams)
            s->loadStreamEnable();
    }
}
