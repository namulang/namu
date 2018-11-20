#pragma once

#include "commons.hpp"

namespace NE
{
    namespace
    {
        template <typename T>
        T& nullreference() {
            T* nulled = 0;
            return *nulled;
        }
    }

    class Object
    {
    public:
        virtual type_bool release() = 0;
        virtual Object& clone() const = 0;
        type_bool isNull() const { return ! this; }
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
        friend class Preferencer;

    public:
        ClassNode() {}
        ClassNode(const std::string& key) : Node(key) {}

    public:
        type_bool push(const MemberNode& member) { 
            _members[member.getKey()] = member;
            
            return true;
        }
        const MemberNode& operator[](const std::string& key) const { return getMember(key); }
        const MemberNode& getMember(const std::string& key) const {
            if(isNull())
                return nullreference<MemberNode>();
            Members::const_iterator e = _members.find(key);
            if(e == _members.end())
                return nullreference<MemberNode>();

            return e->second;
        }
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
        const ClassNode& getClass(const std::string& key) const {
            Classes::const_iterator e = _classes.find(key);
            if(e == _classes.end())
                return nullreference<ClassNode>();

            return e->second;
        }
        virtual type_bool parse(const std::string& contents);
        virtual type_bool parse(const File& file) {
            //  pre:
            if(file.isNull())
            {
                WRD_WARN("file is null")
                return false;
            }

            WRD_INFO("parse(%s)", file.getPath().c_str());
            AsciiStream stream(file);
            stream.initialize();
            
            return parse(stream.readWhole());
        }
        type_bool release() {
            _classes.clear();
            return true;
        }
        virtual Object& clone() const { return *(new Preferencer(*this)); }
        virtual type_bool onAddClass(const std::string& name);
        virtual type_bool onAddMember(const std::string& class_name, const std::string& key, const std::string& value);

    private:
        typedef std::map<std::string, ClassNode> Classes;
        Classes _classes;
    };
}
