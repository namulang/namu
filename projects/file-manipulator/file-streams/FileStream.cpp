#include "FileStream.hpp"
#include <string.h>

using namespace std;

namespace wrd
{
	namespace fm
	{
		#define THIS FileStream

		THIS::THIS() : _mode(MODE_TYPE_START), _fd(0) {}
		THIS::THIS(const std::string& new_path) : Super(new_path), _mode(MODE_TYPE_START), _fd(0)  {}
		THIS::~THIS() { release(); }

		THIS& THIS::operator+=(wint delta)
		{
			if(isInit())
				setCursor(getCursor() + delta);
			return *this;
		}

		THIS& THIS::operator-=(wint delta)
		{
			if(isInit()) 
				setCursor(getCursor() - delta);
			return *this;
		}

		THIS& THIS::operator=(wint new_position)
		{
			if(isInit()) 
				setCursor(new_position);
			return *this;
		}

		wint THIS::getCursor() const 
		{
			if( ! isInit()) return 0;

			return ftell(_fd);
		}

		wint THIS::getEndOfFile() const
		{
			if( ! isInit()) return 0;

			wint backup = getCursor();
			
			FILE* unconsted = const_cast<FILE*>(_fd);
			if(fseek(unconsted, 0, SEEK_END))
				return 0;

			wint to_return = getCursor();
			fseek(unconsted, backup, SEEK_SET);

			return to_return;
		}
		wbool THIS::setCursor(wint new_position)
		{
			if( ! isInit()) return true;
			
			wint mode = new_position >= 0 ? SEEK_SET : SEEK_END;
			if(fseek(_fd, new_position, mode))
				return true;

			return false;
		}
		wbool THIS::setPath(const std::string& new_path) { return _setPath(new_path); }
		wbool THIS::setPath(const Super& path)
		{ 
			if(path.isNull()) return true; 
			
			return _setPath(path.getPath()); 
		}
		wbool THIS::init()
		{
			if(getMode() != APPENDABLE) return false;

			FILE* tmp = fopen(getPath().c_str(), "r");
			if( ! tmp)
				tmp = fopen(getPath().c_str(), "w");
			fclose(tmp);
			return false;
		}
		wbool THIS::isInit() const { return _fd; }
		wbool THIS::release()
		{
			if(_fd)
				fclose(_fd);
			_fd = WRD_NULL;

			_mode = MODE_TYPE_START;

			return Super::release();            
		}
		wbool THIS::setMode(Mode new_mode)
		{
			if(isInit()) return true;

			_mode = new_mode;
			return false;
		}
		THIS::Mode THIS::getMode() const { return _mode; }    
		THIS::THIS(const Super& object) {}

		std::string THIS::readWhole()
		{
			const wint SIZE = 65535;
			char buffer[SIZE] = {0, };

			setCursor(0);
			std::string contents;
			while( ! isEndOfFile())
			{
				wcnt count = read(buffer, SIZE);
				contents.append(buffer, count);
			}

			return contents;
		}
		
		wbool THIS::isEndOfFile() const
		{
			if( ! _fd) return true;

			return feof(_fd);
		}
	}
}
