#pragma once

#include "streams/Stream.hpp"

namespace wrd
{
	namespace log
	{
		class Logger : public Stream
		{	WRD_INHERIT(Logger, Stream)
		public:
			virtual const char* getName() const;
			const Stream& operator[](widx n) const;
			Stream& operator[](widx n);
			const Stream& operator[](const char* message) const;
			Stream& operator[](const char* message);

			Stream& getStream(widx n);
			const Stream& getStream(widx n) const;
			const Stream& getStream(const char* c_message) const;
			Stream& getStream(const char* message);
			wcnt getStreamCount() const;
			virtual wbool dump(const char* message);
			wbool dumpFormat(const char* format, ...);
			wbool pushStream(Stream* new_stream);
			virtual wbool initialize();
			virtual wbool isInitialized() const;
			static Logger& getInstance();

		private:
			Logger();
			Logger(const Logger& rhs);
			virtual wbool release();

		private:
			std::vector<Stream*> _streams;
		};
	}
}
