#pragma once
#pragma warning(push)
#pragma warning(disable: 4482)

#include "../GliphList/GliphList.hpp"

namespace LG
{
	class NE_DLL Window : public Gliph
	{
	public:
		Window(	type_ushort new_x = 0, type_ushort new_y = 0, type_ushort new_width=0, 
			type_ushort new_height = 0, type_ushort new_fore=COLOR::LIGHTGRAY, 
			type_ushort new_back = 0, const NEString& new_text = "");
		Window(const Window& rhs);

		bool operator==(const Window& rhs) const;
		bool operator!=(const Window& rhs) const;

		FUNC_CLONE(Window)
			void regist(int count, ...);
		virtual void onKeyPressed(char inputed);
		virtual void onUpdateData();
		virtual void onTerminate();
		virtual void onDraw();
		virtual void onFocused();
		void draw();
		Window& getCaller();
		const Window& getCaller() const { return *_caller; }
		void call(Window& dialog);
		bool isShowing() const;

		GliphList gliphs;
		int focused_gliph_idx;
		bool delete_me;

	private:
		Window* _caller;
	};
}

#pragma warning(pop)