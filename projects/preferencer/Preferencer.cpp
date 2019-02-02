#include "Preferencer.hpp"
#include "parser.hpp"

namespace wrd
{
	namespace pref
	{
		#define THIS Preferencer
		const ClassType& THIS::operator[](const std::string& key) const { return getClass(key); }
		const ClassType& THIS::getClass(const std::string& key) const
		{
			Classes::const_iterator e = _classes.find(key);
			if(e == _classes.end())
				return nulr<ClassType>();

			return e->second;
		}

		wbool THIS::parse(const fm::File& file)
		{
			//  pre:
			if(file.isNull())
			{
				WRD_WARN("file is null")
				return false;
			}

			//WRD_INFO("parse(%s)", file.getPath().c_str());
			fm::AsciiStream stream(file);
			stream.init();
			
			return parse(stream.readWhole());
		}
		
		wbool THIS::release()
		{
			_classes.clear();
			return true;
		}
		
		Object& THIS::clone() const { return *(new Preferencer(*this)); }

		wbool THIS::parse(const std::string& contents)
		{
			CharStream stream(contents, 1, 1);
			PRParserTokenManager token_manager(&stream);
			PRParser parser(&token_manager);

			//WRD_INFO("parser.configure_file()");
			parser.setPreferencer(this);
			parser.setErrorHandler(new PRParserHandler());
			parser.configure_file();
			return true;
		}
		wbool THIS::onAddClass(const std::string& name)
		{
			if( ! getClass(name).isNull())
			{
				WRD_ERROR("%s is duplicated.", name.c_str());
				return false;
			}

			_classes[name] = ClassType(name);
			return true;
		}
		wbool THIS::onAddMember(const std::string& class_name, const std::string& key, const std::string& value)
		{
			if(getClass(class_name).isNull())
			{
				WRD_ERROR("class %s is not defined.", class_name.c_str());
				return false;
			}
		   
			ClassType& klass = _classes[class_name];           
			if( ! klass.getMember(key).isNull())
			{
				WRD_ERROR("memberdata %s is duplicated.", key.c_str());
				return false;
			}
		   
			klass._members[key] = MemberType(key, value);
			return true;
		}
	}
}
