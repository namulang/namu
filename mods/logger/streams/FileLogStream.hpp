#pragma once

#include "Stream.hpp"

namespace wrd
{
	namespace log
	{
		class FileLogStream : public Stream
		{	WRD_DECL_THIS(FileLogStream, Stream)
		public:
			FileLogStream();
			FileLogStream(const std::string& new_path);

		public:
			virtual const char* getName() const;
			virtual wbool init();
			wbool setPath(const std::string& new_path);
			const std::string& getPath() const;
			virtual wbool dump(const char* message);
			virtual wbool release();

		private:
			fm::AsciiStream _file;
		};
	}
}
