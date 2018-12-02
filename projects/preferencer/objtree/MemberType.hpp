#pragma once

#include "Type.hpp"

namespace wrd
{
	namespace pref
	{
		class MemberType : public Type
		{
		public:
			MemberType();
			MemberType(const std::string& key, const std::string& value);
	
		public:
			const std::string& getValue() const;
			virtual wint toInt() const;
			virtual wbool toBoolean() const;
			virtual wfloat toFloat() const;
			virtual wchar toChar() const;
			virtual std::string toString() const;
			virtual wbool release();
			virtual Object& clone() const;

		private:
			static std::string _toLowercase(const std::string& str);

		private:
			std::string _key;
			std::string _value;
		};
	}
}





























