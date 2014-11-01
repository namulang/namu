#include "WindowList.hpp"

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

		for(int n=stack.getLengthLastIndex(); n >= 0 ;n--)
			stack[n].onDraw();
	}
}