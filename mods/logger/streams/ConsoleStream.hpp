#pragma once

#include "Stream.hpp"

namespace wrd
{
	namespace log
	{
		class ConsoleStream : public Stream
		{	WRD_INHERIT(ConsoleStream, Stream)
		public:
			virtual const char* getName() const;
			virtual wbool dump(const char* message);
		};
	}
}
