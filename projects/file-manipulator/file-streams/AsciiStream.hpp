#pragma once

#include "FileStream.hpp"

namespace wrd
{
	namespace fm
	{
		class File;

		class AsciiStream : public FileStream
		{
		public:
			AsciiStream();
			AsciiStream(const std::string& new_path);
			AsciiStream(const File& file);
			virtual ~AsciiStream();

		public:
			using FileStream::operator=;

			virtual wbool initialize();
			
			using FileStream::write;
			template <typename T>
			wcnt write(const T& datum) { return write(to_string(datum)); }

			wcnt write(const std::string& datum);
			virtual wcnt write(const void* chunks, wcnt bytes);
			virtual wcnt read(void* target, wcnt bytes);
			std::string readToken(const std::string& delimeter = " ");
			std::string readLine();
			virtual wbool release();

		private:
			AsciiStream(const PathedObject& object);
			std::string _peelOffBuffer(wcnt bytes/*except for null*/);
			wcnt _readToBuffer(wcnt bytes=1024);

		private:
			std::string _buffer;
		};
	}
}
