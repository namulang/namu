#include "PathedObject.hpp"

namespace wrd
{
	namespace fm
	{
		#define THIS PathedObject
		using namespace std;

		THIS::THIS() {}
		THIS::THIS(const string& path) : _path(path) {}
		THIS::THIS(const THIS& rhs) : _path(rhs._path) {}
		const string& THIS::getPath() const { return _path; }
		wbool THIS::isNull() const { return ! this; }
		wbool THIS::release() { _path.clear(); return false; }

		THIS& THIS::operator=(const THIS& rhs) { return *this; }    

		wbool THIS::_setPath(const string& new_path) { _path = new_path; return false; }
	}
}
