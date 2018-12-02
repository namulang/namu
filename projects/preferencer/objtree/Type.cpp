#include "Type.hpp"

namespace wrd
{
	namespace pref
	{
#define THIS Type
		THIS::Type() {}
		THIS::Type(const std::string& key) : _key(key) {}
		const std::string& THIS::getKey() const { return _key; }

		wbool THIS::release()
		{
			_key.clear();
			return true;
		}

		Object& THIS::clone() const { return *(new THIS(*this)); }
	}
}
