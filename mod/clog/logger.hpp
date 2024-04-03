#pragma once

#include "stream/stream.hpp"
#include "filter/filters.hpp"

namespace namu {

    class _nout logger : public stream {
        NAMU_ME(logger, stream)

    public:
        //  Logger:
        const stream& operator[](nidx n) const;
        stream& operator[](nidx n);
        const stream& operator[](const nchar* message) const;
        stream& operator[](const nchar* message);

    public:
        stream& getStream(nidx n);
        const stream& getStream(nidx n) const;
        const stream& getStream(const nchar* c_message) const;
        stream& getStream(const nchar* message);

        nbool isEnable() const override;

        /// modify that all of streams are set to enable or not.
        void setEnable(nbool enable) override;
        ncnt getStreamCount() const;
        nbool dumpFormat(const nchar* fmt, ...);
        nbool dumpFormatLog(logLv::level lv, const nchar* tag, const nchar* filename, const nchar* func, int line, const nchar* fmt, ...);
        nbool pushStream(stream* new_stream);
        static logger& get();
        //  stream:
        const nchar* getName() const override;
        nbool dump(const nchar* message) override;
        nbool isInit() const override;
        void callstack() const;
        void setCallstack(nbool show);
        nbool isShowCallstack() const { return _showCallstack; }
        //  filter:
        void setFilters(const filters& newFilters);
        void setFilters();
        const filters& getFilters() const;

    private:
        //  Logger:
        logger();
        logger(const logger& rhs);
        //  stream:
        nbool init() override;
        nbool rel() override;

        std::string _makeStr(const nchar* fmt, ...);
        std::string _makeStr(const nchar* fmt, va_list va);

    private:
        std::vector<stream*> _streams;
        const filters* _filters;
        nbool _showCallstack;
    };
}
