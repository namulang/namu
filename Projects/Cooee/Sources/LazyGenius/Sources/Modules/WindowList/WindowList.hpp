#pragma once

#include "../Window/Window.hpp"

namespace LG
{
	template
	class NE_DLL NEListTemplate<Window*, true>;

	class NE_DLL WindowList : public NEListTemplate<Window*, true>
	{
	public:
		typedef NEListTemplate<Window*, true> SuperClass;

		virtual type_index insert(type_index index, const Window* const source) {
			type_index n = SuperClass::insert(index, source);

			Window& added = getElement(n);
			added.onUpdateData();
			added.onDraw();
			return n;
		}

		virtual type_index remove(type_index index)
		{
			type_index n = SuperClass::remove(index);
			_updateNewWindow();
			return n;
		}
		void _updateNewWindow() {
			system("cls");
			Window* itr = 0;
			if( itr = &getElement(0) ) {
				itr->onUpdateData();
				itr->onDraw();
			}
		}
		void collectGarbages() {
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
				_updateNewWindow();
		}
	};
}