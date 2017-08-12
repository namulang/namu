#pragma once

#include "streams/Stream.hpp"
#include <vector>
#include <string>

namespace NE
{
    class Logger : public Stream
    {
    public:
        virtual const char* getName() const;
        const Stream& operator[](type_index n) const;
        Stream& operator[](type_index n);
        const Stream& operator[](const char* message) const;
        Stream& operator[](const char* message);

        Stream& getStream(type_index n);
        const Stream& getStream(type_index n) const;
        const Stream& getStream(const char* c_message) const;
        Stream& getStream(const char* message);
        type_count getStreamCount() const;
        virtual type_bool dump(const char* message);
        type_bool dumpFormat(const char* format, ...);
        type_bool pushStream(Stream* new_stream);
        virtual type_bool initialize();
        virtual type_bool isInitialized() const;
        static Logger& getInstance();

    private:
        Logger();
        Logger(const Logger& rhs);
        virtual type_bool release();

    private:
        std::vector<Stream*> _streams;
    };
}