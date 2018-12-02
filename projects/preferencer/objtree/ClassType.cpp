#include "ClassType.hpp"

namespace wrd
{
	namespace pref
	{
#define THIS ClassType
		THIS::ClassType() {}
		THIS::ClassType(const std::string& key) : Type(key) {}

		wbool THIS::push(const MemberType& member)
		{
			_members[member.getKey()] = member;
			
			return true;
		}

		const MemberType& THIS::operator[](const std::string& key) const { return getMember(key); }

		const MemberType& THIS::getMember(const std::string& key) const
		{
			if(isNull())
				return nullref<MemberType>();
			Members::const_iterator e = _members.find(key);
			if(e == _members.end())
				return nullref<MemberType>();

			return e->second;
		}

		wbool THIS::release()
		{
			_members.clear();
			
			return true;
		}

		Object& THIS::clone() const { return *(new ClassType(*this)); }
	}
}
