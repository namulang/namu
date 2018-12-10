#include "BinaryStream.hpp"
#include "../file-structures.hpp"
#include <string.h>

namespace wrd
{
	namespace fm
	{
		#define THIS BinaryStream

		THIS::THIS() : Super() {}
		THIS::THIS(const std::string& new_path) : Super(new_path) {}
		THIS::THIS(const File& file) : Super() 
		{
			if( ! file.isNull())
				setPath(file.getPath());
		}
		THIS::~THIS() { release(); }


		wbool THIS::initialize()
		{
			if(Super::initialize()) return true;

			const char* mode = 0;
			switch(getMode())
			{
			case READ_ONLY:         mode = "rb";    break;
			case OVERWRITE_ONLY:    mode = "w+b";   break;
			case APPENDABLE:        mode = "r+b";   break;
			default:
				return true;
			}
			
			_fd = fopen(getPath().c_str(), mode);
			if(getMode() == APPENDABLE)
				setCursor(getEndOfFile());

			return ! isInitialized();
		}

		wcnt THIS::write(const char* str) { return write(str, sizeof(char) * strlen(str)); }
		wcnt THIS::write(const std::string& str) { return write(str.c_str()); }

		wcnt THIS::write(const void* chunks, wcnt bytes)
		{
			if( ! isInitialized()) return 0;

			return fwrite(chunks, 1, bytes, _fd);
		}

		wcnt THIS::read(void* target, wcnt bytes)
		{
			if( ! isInitialized()) return 0;

			return fread(target, 1, bytes, _fd);
		}

		std::string THIS::read(wcnt bytes)
		{
			char* buffer = new char[bytes];

			wcnt n = read(buffer, sizeof(char) * bytes);
			std::string to_return(buffer, n);

			delete [] buffer;

			return to_return;
		}

		THIS::THIS(const PathedObject& object) {}
	}
}
