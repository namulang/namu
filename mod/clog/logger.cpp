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
        nbool ret = dump(_makeStr(fmt, va).c_str());
        va_end(va);
        return ret;
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
        for(auto e : _streams) {
            e->rel();
            delete e;
        }
        _streams.clear();
        return super::rel();
    }

    me& me::get() {
        static me* inner = 0;
        if(nul(inner)) {
            inner = new me();
            inner->init();
        }

        return *inner;
    }

    nbool me::dumpFormatLog(logLv::level lv, const nchar* tag, const nchar* filename, const nchar* func, int line, const nchar* fmt, ...) {
        std::string toDump;
        toDump += platformAPI::getConsoleFore(platformAPI::BROWN);
        toDump += _makeStr("%s ", platformAPI::createNowTime("%b %d %Y  %X").c_str());

        platformAPI::consoleColor clrLv = platformAPI::WHITE;
        switch(lv) {
            case logLv::ERR: clrLv = platformAPI::LIGHTRED; break;
            case logLv::WARN: clrLv = platformAPI::YELLOW; break;
            case logLv::INFO: clrLv = platformAPI::LIGHTBLUE; break;
        }
        toDump += platformAPI::getConsoleFore(clrLv);
        toDump += _makeStr("%s %s ", tag, logLv::getName(lv).c_str());

        toDump += platformAPI::getConsoleFore(platformAPI::GREEN);
        toDump += _makeStr("<%s::%s#%d> ", filename, func, line);

        toDump += platformAPI::getConsoleFore(platformAPI::LIGHTGRAY);
        va_list va;
        va_start(va, fmt);
        toDump += _makeStr(fmt, va);
        va_end(va);

        if(_filters)
            toDump = _filters->filt(lv, tag, toDump);
        if(!toDump.empty())
            return dump(toDump.c_str());
        return false;
    }

    me::logger() : super(), _showCallstack(true) {}
    me::logger(const me& rhs) : super(rhs) {
        _showCallstack = rhs._showCallstack;
    }

    nbool me::isEnable() const {
        for(stream* s : _streams)
            if(s->isEnable()) return true;
        return false;
    }

    void me::setEnable(nbool enable) {
        for(stream* s : _streams)
            s->setEnable(enable);
    }

    void me::callstack() const {
        if(!_showCallstack) return;
        std::vector<std::string> cs = platformAPI::callstack();
        for(const auto& e : cs)
            NAMU_E("\tat %s", e.c_str());
    }

    void me::setCallstack(nbool show) {
        _showCallstack = show;
    }

    void me::setFilters(const filters& newFilters) {
        _filters = &newFilters;
    }

    void me::setFilters() {
        _filters = nullptr;
    }

    const filters& me::getFilters() const {
        return *_filters;
    }

    std::string me::_makeStr(const nchar* fmt, ...) {
        va_list va;
        va_start(va, fmt);
        std::string ret = _makeStr(fmt, va);
        va_end(va);
        return ret;
    }

    std::string me::_makeStr(const nchar* fmt, va_list va) {
        nchar buf[1024];
        vsnprintf(buf, 1024, fmt, va);
        return std::string(buf);
    }
}
