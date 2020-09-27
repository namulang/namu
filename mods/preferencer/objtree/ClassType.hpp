#pragma once

#include "MemberType.hpp"

namespace wrd
{
	namespace pref
	{
		class ClassType : public Type
		{	WRD_INHERIT(ClassType, Type)
		public:
			friend class Preferencer;

		public:
			ClassType();
			ClassType(const std::string& key);

		public:
			wbool push(const MemberType& member);
			const MemberType& operator[](const std::string& key) const;
			const MemberType& getMember(const std::string& key) const;
			virtual wbool release();
			virtual Object& clone() const;

		private:
			typedef std::map<std::string, MemberType> Members;
			Members _members;
		};
	}
}
