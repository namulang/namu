#include "Preferencer.hpp"
#include "parser.hpp"

namespace NE
{
    namespace PR
    {
        #define THIS Preferencer
        type_bool THIS::parse(const std::string& contents) {
            CharStream stream(contents, 1, 1);
            PreferencerParserTokenManager token_manager(&stream);
            PreferencerParser parser(&token_manager);

            NE_INFO("parser.configure_file()");
            parser.setPreferencer(this);
            parser.setErrorHandler(new PreferencerErrorHandler());
            parser.configure_file();
            return true;
        }
        type_bool THIS::onAddClass(const std::string& name) {
            if( ! getClass(name).isNull())
            {
                NE_ERROR("%s is duplicated.", name.c_str());
                return false;
            }

            _classes[name] = ClassNode(name);
            return true;
        }
        type_bool THIS::onAddMember(const std::string& class_name, const std::string& key, const std::string& value) {
            if(getClass(class_name).isNull())
            {
                NE_ERROR("class %s is not defined.", class_name);
                return false;
            }
            
            ClassNode& klass = _classes[class_name];            
            if( ! klass.getMember(key).isNull())
            {
                NE_ERROR("memberdata %s is duplicated.", key);
                return false;
            }


            
            klass._members[key] = MemberNode(key, value);
            return true;
        }
    }
}