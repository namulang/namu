#include "ClassType.hpp"

namespace wrd
{
	namespace pref
	{
#define THIS ClassType
		THIS::ClassType() {}
		THIS::ClassType(const std::string& key) : Super(key) {}

		wbool THIS::push(const MemberType& member)
		{
			_members[member.getKey()] = member;
			
			return true;
		}

		const MemberType& THIS::operator[](const std::string& key) const { return getMember(key); }

		const MemberType& THIS::getMember(const std::string& key) const
		{
			if(isNull())
				return nulr<MemberType>();
			Members::const_iterator e = _members.find(key);
			if(e == _members.end())
				return nulr<MemberType>();

			return e->second;
		}

		wbool THIS::release()
		{
			_members.clear();
			
			return true;
		}

		Object& THIS::clone() const { return *(new This(*this)); }
	}
}
