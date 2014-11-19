#include "WindowList.hpp"
#include "../Core/Core.hpp"

namespace LG
{
	void WindowList::collectGarbages()
	{
		NEListTemplate<type_index> indexes;

		int n=0;
		for(Iterator* itr=getIterator(0); itr ;itr=itr->getNext())
		{
			if(itr->getValue().delete_me) {
				indexes.pushFront(n);
				itr->getValue().delete_me = false;	//	혹시라도 이 윈도우가 살아남아야할 때, 계속 delete_me가 되지 않도록 flag를 꺼준다.
			}
			n++;
		}

		for(NEListTemplate<type_index>::Iterator* itr=indexes.getIterator(0); itr ;itr=itr->getNext()) {
			type_index index = itr->getValue();
			getElement(index).onTerminate();
			SuperClass::remove(index);
		}

		if(indexes.getLength() > 0)
			_focusNewWindow();
	}

	void WindowList::draw()
	{
		NEArrayTemplate<Window*, false> stack(getLength());
		for(Iterator* itr=getIterator(0); itr ;itr=itr->getNext())
			stack.push(&(itr->getValue()));

		WORD backup = Core::getColor();
		Core::setColorLock(false);
		Core::back_buffer.setColorLock(false);
		Core::back_buffer.setColor(DARKGRAY, LIGHTGRAY);
		Core::setColor(DARKGRAY, LIGHTGRAY);
		Core::setColorLock(true);
		Core::back_buffer.setColorLock(true);

		for(int n=stack.getLengthLastIndex(); n >= 1 ;n--)
			stack[n].onDraw();

		Core::setColorLock(false);
		Core::back_buffer.setColorLock(false);
		Core::setColor(backup);

		if(stack.getLength() > 0)
			stack[0].onDraw();
	}
}