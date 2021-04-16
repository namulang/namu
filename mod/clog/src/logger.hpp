#pragma once

#include "stream/stream.hpp"

namespace wrd {

    class logger : public stream {
        WRD_DECL_ME(logger, stream)

    public:
        //  Logger:
        const stream& operator[](widx n) const;
        stream& operator[](widx n);
        const stream& operator[](const wchar* message) const;
        stream& operator[](const wchar* message);

        stream& getStream(widx n);
        const stream& getStream(widx n) const;
        const stream& getStream(const wchar* c_message) const;
        stream& getStream(const wchar* message);
        wcnt getStreamCount() const;
        wbool dumpFormat(const wchar* fmt, ...);
        wbool pushStream(stream* new_stream);
        static logger& get();
        //  stream:
        const wchar* getName() const override;
        wbool dump(const wchar* message) override;
        wbool isInit() const override;

    private:
        //  Logger:
        logger();
        logger(const logger& rhs);
        //  stream:
        wbool init() override;
        wbool rel() override;

    private:
        std::vector<stream*> _streams;
    };
}
