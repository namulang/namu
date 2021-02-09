#pragma once

#include "stream/Stream.hpp"

namespace wrd {

    class Logger : public Stream {
        WRD_DECL_THIS(Logger, Stream)

    public:
        //  Logger:
        const Stream& operator[](widx n) const;
        Stream& operator[](widx n);
        const Stream& operator[](const wchar* message) const;
        Stream& operator[](const wchar* message);

        Stream& getStream(widx n);
        const Stream& getStream(widx n) const;
        const Stream& getStream(const wchar* c_message) const;
        Stream& getStream(const wchar* message);
        wcnt getStreamCount() const;
        wbool dumpFormat(const wchar* fmt, ...);
        wbool pushStream(Stream* new_stream);
        static Logger& get();
        //  Stream:
        const wchar* getName() const override;
        wbool dump(const wchar* message) override;
        wbool isInit() const override;

    private:
        //  Logger:
        Logger();
        Logger(const Logger& rhs);
        //  Stream:
        wbool init() override;
        wbool rel() override;

    private:
        std::vector<Stream*> _streams;
    };
}
