#include "logger.hpp"
#include <iostream>
#include "stream.hpp"

namespace namu {

    NAMU_DEF_ME(logger)
    typedef std::string string;

    const nchar* me::getName() const { return "logger"; }
    const stream& me::operator[](nidx n) const { return getStream(n); }
    stream& me::operator[](nidx n) { return getStream(n); }
    const stream& me::operator[](const nchar* message) const { return getStream(message); }
    stream& me::operator[](const nchar* message) { return getStream(message); }

    stream& me::getStream(nidx n) {
        if(n < 0 || n >= getStreamCount())
            return nulOf<stream>();

        return *_streams[n];
    }

    const stream& me::getStream(nidx n) const {
        NAMU_UNCONST()
        return unconst.getStream(n);
    }

    const stream& me::getStream(const nchar* c_message) const {
        string message = c_message;
        for(auto e : _streams)
            if(string(e->getName()) == message)
                return *e;

        return nulOf<stream>();
    }

    stream& me::getStream(const nchar* message) {
        const me* consted = this;

        return const_cast<stream&>(consted->getStream(message));
    }

    ncnt me::getStreamCount() const { return _streams.size(); }

    nbool me::dump(const nchar* message) {
        if(!isEnable()) return false;

        nbool result = false;
        for(auto e : _streams)
            result |= e->dump(message);

        return result;
    }

    nbool me::dumpFormat(const nchar* fmt, ...) {
        va_list va;
        va_start(va, fmt);
        nchar buf[1024];
        vsnprintf(buf, 1024, fmt, va);
        va_end(va);

        return dump(buf);
    }

    nbool me::pushStream(stream* new_stream) {
        if( ! new_stream) return true;

        _streams.push_back(new_stream);
        if(isInit())
            return new_stream->init();
        return false;
    }

    nbool me::init() {
        rel();
        super::init();

        static stream* streams[] = {new consoleStream(), new fileLogStream("./logs"), 0};
        stream* e = 0;
        for(int n=0; (e = streams[n]) ;n++)
            pushStream(e);

        return false;
    }

    nbool me::isInit() const {
        for(auto e : _streams)
            if( ! e->isInit())
                return false;

        return true;
    }

    nbool me::rel() {
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

    nbool me::dumpFormatLog(const nchar* level, const nchar* tag, const nchar* filename, const nchar* func, int line, const nchar* fmt, ...) {
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
        nchar buf[1024];
        vsnprintf(buf, 1024, fmt, va);
        va_end(va);
        return dump(buf);
    }

    me::logger() : super() {}
    me::logger(const me& rhs) : super(rhs) {}

    nbool me::isEnable() const {
        for(stream* s : _streams)
            if(s->isEnable()) return true;
        return false;
    }

    void me::setEnable(nbool enable) {
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

    void me::callstack() const {
        NAMU_E("error found...");
        std::vector<std::string> cs = platformAPI::callstack();
        for(const auto& e : cs)
            NAMU_E("\tat %s", e.c_str());
    }
}
