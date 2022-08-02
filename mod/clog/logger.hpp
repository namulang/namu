#pragma once

#include "stream/stream.hpp"

namespace namu {

    class _wout logger : public stream {
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

        wbool isEnable() const override;

        /// modify that all of streams are set to enable or not.
        void setEnable(wbool enable) override;
        void saveStreamEnable() override;
        void loadStreamEnable() override;
        wcnt getStreamCount() const;
        wbool dumpFormat(const wchar* fmt, ...);
        wbool dumpFormatLog(const wchar* level, const wchar* tag, const wchar* filename, const wchar* func, int line, const wchar* fmt, ...);
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
