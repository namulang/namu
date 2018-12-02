#pragma once

#include "objtree.hpp"

namespace wrd
{
	namespace pref
	{
		class Preferencer : public Object
		{
		public:
			const ClassType& operator[](const std::string& key) const;
			const ClassType& getClass(const std::string& key) const;
			virtual wbool parse(const std::string& contents);
			virtual wbool parse(const fm::File& file);
			wbool release();
			virtual wbool onAddClass(const std::string& name);
			virtual wbool onAddMember(const std::string& class_name, const std::string& key, const std::string& value);
			virtual Object& clone() const;

		private:
			typedef std::map<std::string, ClassType> Classes;
			Classes _classes;
		};
	}
}
