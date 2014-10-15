#pragma warning(push)
#pragma warning(disable: 4482)
#pragma warning(disable: 4355)

#include "Window.hpp"
#include "../Core/Core.hpp"

namespace LG
{
	Window::Window(	type_ushort new_x, type_ushort new_y, type_ushort new_width, type_ushort new_height, 
					type_ushort new_fore, type_ushort new_back, const NEString& new_text)
		: Gliph(0, new_x, new_y, new_width, new_height, new_fore, new_back, new_text), gliphs(this), focused_gliph_idx(0), delete_me(false), _caller(0)
	{

	}
	Window::Window(const Window& rhs)
		: Gliph(rhs), gliphs(this), focused_gliph_idx(0), delete_me(rhs.delete_me), _caller(rhs._caller)
	{

	}

	void Window::regist(int count, ...) 
	{
		va_list args;
		va_start(args, count);

		for(int n=0; n < count ;n++)
			gliphs.push(va_arg(args, Gliph*));
	}

	void Window::onKeyPressed(char inputed)	{

		if(inputed == CLOSE)
			delete_me = true;

		for(GliphList::Iterator* itr=gliphs.getIterator(0); itr ; itr=itr->getNext()) {
			itr->getValue().onKeyPressed(inputed);
		}
	}

	void Window::onUpdateData() {
		for(GliphList::Iterator* itr=gliphs.getIterator(0); itr ;itr=itr->getNext()) {
			itr->getValue().onUpdateData();
		}
	}

	void Window::onTerminate()
	{

	}

	void Window::onDraw() {
		if( ! isShowing()) return;

		draw();
	}			

	bool Window::operator!=(const Window& rhs) const
	{
		return ! operator==(rhs);
	}

	bool Window::operator==(const Window& rhs) const
	{
		return	delete_me == rhs.delete_me					&&
				gliphs == rhs.gliphs						&&
				focused_gliph_idx == rhs.focused_gliph_idx;
	}

	bool Window::isShowing() const
	{
		//	return	Core::windows.getLength() > 0	&& &Core::windows[0] == this;
		return true;
	}

	void Window::call(Window& dialog)
	{
		dialog._caller = this;
		type_index ind = Core::windows.pushFront(dialog);
		if(ind == NE_INDEX_ERROR) return;

		Window& pushed = Core::windows[ind];
	}

	void Window::draw()
	{
		Gliph::onDraw();

		for(GliphList::Iterator* itr=gliphs.getIterator(0); itr ; itr=itr->getNext())
			itr->getValue().onDraw();
	}

	void Window::onFocused()
	{
		onUpdateData();
	}

}
#pragma warning(pop)