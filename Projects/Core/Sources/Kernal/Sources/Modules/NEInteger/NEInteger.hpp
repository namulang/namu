#pragma once

#include "../NENumericType/NENumericType.hpp"
#include "../NETClass/define/ClassMacro.hpp"

namespace NE
{
	//	Must not to use DECLARE_CLASS macro:
	//		This class will be included in while including TClass.
	//		So, if we use DECLARE_CLASS macro, Because of its using TClass as 
	//		inline, we may fall into reculsively infinite INCLUDE loop.
	//		Have to declare manually to use the forward declaration.
	template <typename T>
	class NETClass;

	class NE_DLL NEInteger : public NENumericType
	{
		NE_NATIVE_DECLARE_CLASS_TYPEDEFS(NEInteger, NENumericType, NETClass)
	public:
		virtual const NEClassBase& getClass() const;

	public:
		virtual type_result isValid() const;
		virtual NEObject& clone() const;

	public:
		static const ThisClass& getClassStatically();
	};
}