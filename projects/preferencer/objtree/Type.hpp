#pragma once

#include "Object.hpp"

namespace wrd
{
	namespace pref
	{
		class Type : public Object
		{
		public:
			Type();
			Type(const std::string& key);
			const std::string& getKey() const;
			virtual wbool release(); 
			Object& clone() const;

		private:
			std::string _key;
		};
	}
}
