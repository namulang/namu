#pragma once

#include "../../Includes/Includes.hpp"
#include "../../Commons/Defines/ClassMacros/ClassMacros.hpp"
#include "../../Commons/Enumerations/CommonEnumerations.hpp"

namespace LG 
{
	using namespace NE;

	class Window; 

	class NE_DLL Gliph : public NEObject
	{
	public:
		Gliph(const Gliph& rhs)
			:	owner(0), x(rhs.x), y(rhs.y), width(rhs.width), height(rhs.height), fore(rhs.fore), back(rhs.back), focused(rhs.focused), 
			text(rhs.text), filled_with(rhs.filled_with) {}
		Gliph(Window* new_owner=0, type_ushort new_x = 0, type_ushort new_y=0, type_ushort new_width=0, type_ushort new_height=0, type_ushort new_fore = LIGHTGRAY, type_ushort new_back = 0, const NEString& new_text = "")
			: owner(new_owner), x(new_x), y(new_y), width(new_width), height(new_height), fore(new_fore), back(new_back), focused(false), text(new_text) {}
		FUNC_CLONE(Gliph)

		bool operator==(const Gliph& rhs) const	{ return this == &rhs; }
		bool operator!=(const Gliph& rhs) const { return ! operator==(rhs); }

		virtual void onKeyPressed(char inputed)	{ }
		virtual void onDraw();
		type_ushort getRealX();
		type_ushort getRealY();
		virtual void onUpdateData();
		virtual void onTerminate() {}
		virtual void release() {}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver; }
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader;}
		virtual type_result isValid() const { return RESULT_SUCCESS; }

		type_ushort x, y, width, height;
		int fore, back;
		Window* owner;
		bool focused;
		NEString text;
		char filled_with;
	};	
}