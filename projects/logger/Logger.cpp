#include "Logger.hpp"
#include <iostream>
#include <stdarg.h>
#include "streams.hpp"

namespace wrd
{
	namespace log
	{
		#define THIS Logger
		typedef std::string string;
	  
		const char* THIS::getName() const { return "Logger"; }
		const Stream& THIS::operator[](widx n) const { return getStream(n); }
		Stream& THIS::operator[](widx n) { return getStream(n); }
		const Stream& THIS::operator[](const char* message) const { return getStream(message); }
		Stream& THIS::operator[](const char* message) { return getStream(message); }

		Stream& THIS::getStream(widx n)
		{ 
			if(n < 0 || n >= getStreamCount())
				return nulr<Stream>();

			return *_streams[n]; 
		}

		const Stream& THIS::getStream(widx n) const
		{
			WRD_UNCONST()
			return unconst.getStream(n);
		}

		const Stream& THIS::getStream(const char* c_message) const
		{ 
			string message = c_message;
			for(auto e : _streams)
				if(string(e->getName()) == message)
					return *e;

			return nulr<Stream>();
		}

		Stream& THIS::getStream(const char* message)
		{
			const THIS* consted = this;

			return const_cast<Stream&>(consted->getStream(message));
		}

		wcnt THIS::getStreamCount() const { return _streams.size(); }
		
		wbool THIS::dump(const char* message)
		{
			wbool result = false;
			for(auto e : _streams)
				result |= e->dump(message);
			
			return result;
		}

		wbool THIS::dumpFormat(const char* format, ...)
		{
			va_list va;
			va_start(va, format);
			
			char buffer[1024];
			vsnprintf(buffer, 1024, format, va);
			va_end(va);

			return dump(buffer);
		}

		wbool THIS::pushStream(Stream* new_stream)
		{
			if( ! new_stream) return true;

			_streams.push_back(new_stream);
			if(isInit())
				return new_stream->init();
			return false;
		}

		wbool THIS::init()
		{
			static Stream* streams[] = {new ConsoleStream(), new FileLogStream("./logs"), 0};
			Stream* e = 0;
			for(int n=0; (e = streams[n]) ;n++)
				pushStream(e);

			return false;
		}

		wbool THIS::isInit() const
		{
			for(auto e : _streams)
				if( ! e->isInit())
					return false;

			return true;
		}
		
		wbool THIS::release()
		{
			for(auto e : _streams)
			{
				e->release();
				delete e;
			}
			_streams.clear();
			return Super::release();
		}

		THIS& THIS::getInstance()
		{
			static THIS* inner = 0;
			if(inner->isNull())
			{
				inner = new THIS();
				inner->init();
			}

			return *inner;
		}

		THIS::THIS() : Super() {}
		THIS::THIS(const This& rhs) : Super(rhs) {}
	}
}
