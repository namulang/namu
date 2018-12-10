#include "MemberType.hpp"

namespace wrd
{
	namespace pref
	{
#define THIS MemberType
		THIS::MemberType() : Super() {}
		THIS::MemberType(const std::string& key, const std::string& value) : Type(key), _value(value) {}
		const std::string& THIS::getValue() const { return _value; }
		wint THIS::toInt() const { return std::stoi(_value); }
		wbool THIS::toBoolean() const { return _toLowercase(_value) == "true" || toInt(); }
		wfloat THIS::toFloat() const { return std::stof(_value, 0); }
		wchar THIS::toChar() const { return _value[0]; }
		std::string THIS::toString() const { return _value; }

		wbool THIS::release()
		{
			_value.clear();
			return Super::release();
		}

		Object& THIS::clone() const { return *(new MemberType(*this)); }

		std::string THIS::_toLowercase(const std::string& str)
		{
			std::string to_return = str;
			std::transform(str.begin(), str.end(), to_return.begin(), ::tolower);
			return to_return;
		}
	}
}
