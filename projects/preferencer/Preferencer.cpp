#pragma once

#include "parser.hpp"
#include <logger.hpp>
#include <algorithm>
#include <map>

namespace NE
{
    namespace PR
    {
        class Object
        {
        public:
            virtual type_bool release() = 0;
            virtual Object& clone() const = 0 ;
        };
        class Node : public Object
        {
        public:
            Node() {}
            Node(const std::string& key) : _key(key) {}
            const std::string& getKey() const { return _key; }
            virtual type_bool release() { 
                _key.clear(); 
                return true;
            }
            Object& clone() const { return *(new Node(*this)); }

        private:
            std::string _key;
        };
        class MemberNode : public Node
        {
        public:
            MemberNode() : Node() {}
            MemberNode(const std::string& key, const std::string& value) : Node(key), _value(value) {}
            const std::string& getValue() const { return _value; }
            virtual type_int toInt() const { return std::stoi(_value); }
            virtual type_bool toBoolean() const {
                return _toLowercase(_value) == "true" || toInt();
            }
            virtual type_float toFloat() const { return std::stof(_value, 0); }
            virtual type_char toChar() const { return _value[0]; }
            virtual std::string toString() const { return _value; }
            virtual type_bool release() {
                _value.clear();
                return Node::release();
            }
            virtual Object& clone() const { return *(new MemberNode(*this)); }

        private:
            static std::string _toLowercase(const std::string& str) {
                std::string to_return = str;
                std::transform(str.begin(), str.end(), to_return.begin(), ::tolower);
                return to_return;
            }

        private:
            std::string _key;
            std::string _value;
        };

        class ClassNode : public Node
        {
        public:
            ClassNode(const std::string& key) : Node(key) {}

        public:
            type_bool push(const MemberNode& member) { 
                _members[member.getKey()] = member;
                
                return true;
            }
            const MemberNode& operator[](const std::string& key) const { return getMember(key); }
            const MemberNode& getMember(const std::string& key) const { return _members.at(key); }
            virtual type_bool release() {
                _members.clear();
                
                return true;
            }
            virtual Object& clone() const { return *(new ClassNode(*this)); }

        private:
            typedef std::map<std::string, MemberNode> Members;
            Members _members;
        };

        class Preferencer : public Object
        {
        public:
            const ClassNode& operator[](const std::string& key) const { return getClass(key); }
            const ClassNode& getClass(const std::string& key) const { return _classes.at(key); }
            virtual type_bool parse(const std::string& contents) {                
                CharStream stream(contents, 1, 1);
                PreferencerParserTokenManager token_manager(&stream);
                PreferencerParser parser(&token_manager);

                NE_INFO("parser.configure_file()");
                parser.configure_file();
                return true;
            }
            virtual type_bool parse(const File& file) {
                //  pre:
                if(file.isNull())
                {
                    NE_WARN("file is null")
                    return false;
                }

                NE_INFO("parse(%s)", file.getPath().c_str());
                AsciiStream stream(file);
                stream.initialize();
                
                return parse(stream.readWhole());
            }
            type_bool release() {
                _classes.clear();
                return true;
            }
            virtual Object& clone() const { return *(new Preferencer(*this)); }

        private:
            typedef std::map<std::string, ClassNode> Classes;
            Classes _classes;
        };
    }
}