#include "PathedObject.hpp"

namespace wrd
{
	namespace fm
	{
        WRD_DEF_THIS(PathedObject)
		using namespace std;

		This::PathedObject() {}
		This::PathedObject(const string& path) : _path(path) {}
		This::PathedObject(const This& rhs) : _path(rhs._path) {}
		const string& This::getPath() const { return _path; }
		wbool This::isNull() const { return ! this; }
		wbool This::release() { _path.clear(); return false; }

		This& This::operator=(const This& rhs) { return *this; }    

		wbool This::_setPath(const string& new_path) { _path = new_path; return false; }
	}
}
