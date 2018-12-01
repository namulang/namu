#pragma once

#include "pref-commons.hpp"

namespace wrd
{
	namespace pref
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
			virtual wbool release() = 0;
			virtual Object& clone() const = 0;
			wbool isNull() const { return ! this; }
		};
		class Type : public Object
		{
		public:
			Type() {}
			Type(const std::string& key) : _key(key) {}
			const std::string& getKey() const { return _key; }
			virtual wbool release() { 
				_key.clear(); 
				return true;
			}
			Object& clone() const { return *(new Type(*this)); }

		private:
			std::string _key;
		};
		class MemberType : public Type
		{
		public:
			MemberType() : Type() {}
			MemberType(const std::string& key, const std::string& value) : Type(key), _value(value) {}
			const std::string& getValue() const { return _value; }
			virtual wint toInt() const { return std::stoi(_value); }
			virtual wbool toBoolean() const {
				return _toLowercase(_value) == "true" || toInt();
			}
			virtual wfloat toFloat() const { return std::stof(_value, 0); }
			virtual wchar toChar() const { return _value[0]; }
			virtual std::string toString() const { return _value; }
			virtual wbool release() {
				_value.clear();
				return Type::release();
			}
			virtual Object& clone() const { return *(new MemberType(*this)); }

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

		class ClassType : public Type
		{
		public:
			friend class Preferencer;

		public:
			ClassType() {}
			ClassType(const std::string& key) : Type(key) {}

		public:
			wbool push(const MemberType& member) { 
				_members[member.getKey()] = member;
				
				return true;
			}
			const MemberType& operator[](const std::string& key) const { return getMember(key); }
			const MemberType& getMember(const std::string& key) const {
				if(isNull())
					return nullreference<MemberType>();
				Members::const_iterator e = _members.find(key);
				if(e == _members.end())
					return nullreference<MemberType>();

				return e->second;
			}
			virtual wbool release() {
				_members.clear();
				
				return true;
			}
			virtual Object& clone() const { return *(new ClassType(*this)); }

		private:
			typedef std::map<std::string, MemberType> Members;
			Members _members;
		};

		class Preferencer : public Object
		{
		public:
			const ClassType& operator[](const std::string& key) const { return getClass(key); }
			const ClassType& getClass(const std::string& key) const {
				Classes::const_iterator e = _classes.find(key);
				if(e == _classes.end())
					return nullreference<ClassType>();

				return e->second;
			}
			virtual wbool parse(const std::string& contents);
			virtual wbool parse(const File& file) {
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
			wbool release() {
				_classes.clear();
				return true;
			}
			virtual Object& clone() const { return *(new Preferencer(*this)); }
			virtual wbool onAddClass(const std::string& name);
			virtual wbool onAddMember(const std::string& class_name, const std::string& key, const std::string& value);

		private:
			typedef std::map<std::string, ClassType> Classes;
			Classes _classes;
		};
	}
}
