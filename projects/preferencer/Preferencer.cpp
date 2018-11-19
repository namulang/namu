#include "Preferencer.hpp"
#include "parser.hpp"

namespace NE
{
    #define THIS Preferencer
    type_bool THIS::parse(const std::string& contents) {
        CharStream stream(contents, 1, 1);
        PRParserTokenManager token_manager(&stream);
        PRParser parser(&token_manager);

        WRD_INFO("parser.configure_file()");
        parser.setPreferencer(this);
        parser.setErrorHandler(new PRParserHandler());
        parser.configure_file();
        return true;
    }
    type_bool THIS::onAddClass(const std::string& name) {
        if( ! getClass(name).isNull())
        {
            WRD_ERROR("%s is duplicated.", name.c_str());
            return false;
        }

        _classes[name] = ClassNode(name);
        return true;
    }
    type_bool THIS::onAddMember(const std::string& class_name, const std::string& key, const std::string& value) {
        if(getClass(class_name).isNull())
        {
            WRD_ERROR("class %s is not defined.", class_name.c_str());
            return false;
        }
       
        ClassNode& klass = _classes[class_name];           
        if( ! klass.getMember(key).isNull())
        {
            WRD_ERROR("memberdata %s is duplicated.", key.c_str());
            return false;
        }
       
        klass._members[key] = MemberNode(key, value);
        return true;
    }
}
