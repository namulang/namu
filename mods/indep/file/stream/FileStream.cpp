#include "FileStream.hpp"

using namespace std;

namespace wrd {
	namespace fm {

        WRD_DEF_THIS(FileStream)

		This::FileStream() : _mode(MODE_TYPE_START), _fd(0) {}
		This::FileStream(const std::string& new_path) : Super(new_path), _mode(MODE_TYPE_START), _fd(0)  {}
		This::~FileStream() { release(); }

		This& This::operator+=(wint delta) {
			if(isInit())
				setCursor(getCursor() + delta);
			return *this;
		}

		This& This::operator-=(wint delta) {
			if(isInit())
				setCursor(getCursor() - delta);
			return *this;
		}

		This& This::operator=(wint new_position) {
			if(isInit())
				setCursor(new_position);
			return *this;
		}

		wint This::getCursor() const {
			if( ! isInit()) return 0;

			return ftell(_fd);
		}

		wint This::getEndOfFile() const {
			if( ! isInit()) return 0;

			wint backup = getCursor();

			FILE* unconsted = const_cast<FILE*>(_fd);
			if(fseek(unconsted, 0, SEEK_END))
				return 0;

			wint to_return = getCursor();
			fseek(unconsted, backup, SEEK_SET);

			return to_return;
		}

		wbool This::setCursor(wint new_position) {
			if( ! isInit()) return true;

			wint mode = new_position >= 0 ? SEEK_SET : SEEK_END;
			if(fseek(_fd, new_position, mode))
				return true;

			return false;
		}

		wbool This::setPath(const std::string& new_path) { return _setPath(new_path); }

		wbool This::setPath(const Super& path) {
			if(path.isNull()) return true;

			return _setPath(path.getPath());
		}

		wbool This::init() {
			if(getMode() != APPENDABLE) return false;

			FILE* tmp = fopen(getPath().c_str(), "r");
			if(!tmp)
				tmp = fopen(getPath().c_str(), "w");
			fclose(tmp);
			return false;
		}

		wbool This::isInit() const { return _fd; }

		wbool This::release() {
			if(_fd)
				fclose(_fd);
			_fd = WRD_NULL;

			_mode = MODE_TYPE_START;

			return Super::release();
		}

		wbool This::setMode(Mode new_mode) {
			if(isInit()) return true;

			_mode = new_mode;
			return false;
		}

		This::Mode This::getMode() const { return _mode; }
		This::FileStream(const Super& object) {}

		std::string This::readWhole() {
			const wint SIZE = 65535;
			char buffer[SIZE] = {0, };

			setCursor(0);
			std::string contents;
			while(!isEndOfFile()) {
				wcnt count = read(buffer, SIZE);
				contents.append(buffer, count);
			}

			return contents;
		}

		wbool This::isEndOfFile() const {
			if(!_fd) return true;

			return feof(_fd);
		}
	}
}
