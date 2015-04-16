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
			text(rhs.text), filled_with(rhs.filled_with), _has_frames(rhs._has_frames) {}
		Gliph(Window* new_owner=0, type_ushort new_x = 0, type_ushort new_y=0, type_ushort new_width=0, type_ushort new_height=0, type_ushort new_fore = LIGHTGRAY, type_ushort new_back = 0, const NEString& new_text = "", bool has_frames = false)
			: owner(new_owner), x(new_x), y(new_y), width(new_width), height(new_height), fore(new_fore), back(new_back), focused(false), text(new_text), _has_frames(has_frames) {}
		FUNC_CLONE(Gliph)

		bool operator==(const Gliph& rhs) const	{ return this == &rhs; }
		bool operator!=(const Gliph& rhs) const { return ! operator==(rhs); }

		virtual void onKeyPressed(int inputed)	{ }
		virtual void onDraw();
		type_ushort getRealX();
		type_ushort getRealY();
		bool hasFrames() const;
		void setHavingFrames(bool have_frames);
		virtual void onUpdateData();
		virtual void onTerminate() {}
		virtual void release() {}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver; }
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader;}
		virtual type_result isValid() const { return RESULT_SUCCESS; }

		void _drawFrames() const;

		type_ushort x, y, width, height;
		int fore, back;
		Window* owner;
		bool focused;
		NEString text;
		char filled_with;
		bool _has_frames;
	};	
}