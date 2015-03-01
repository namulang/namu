#pragma once

#include "../Core/Core.hpp"

class KeyEncyclo : public LG::ListWindow
{
public:
	KeyEncyclo(const NEString& new_path_to_added = "")
		: LG::ListWindow(" Key Encyclopedia > ", 40, 10, 15, 10, BLACK, LIGHTGREEN), path_to_added(new_path_to_added)
	{ 
		list.use_matching = true;
	}
	KeyEncyclo(CONST KeyEncyclo & rhs) 
		: LG::ListWindow(rhs), path_to_added(rhs.path_to_added)
	{ 

	}
	NEObject& clone() const { return *(new KeyEncyclo(*this)); }

	virtual void onUpdateData()
	{
		LG::ListWindow::onUpdateData();

		NEKeyManager& km = Kernal::getInstance().getKeyManager();
		const NEKeySet& ks = km.getKeySet();

		list.items.create(ks.getLength());
		for(int n=0; n < ks.getLength() ;n++)
			list.items.push(ks[n].getTypeName());
	}
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content)
	{
		::Core::commander.command(NEString("add -key ") + chosen_content + " " + path_to_added);
		delete_me = true;
	}

	NEString path_to_added;
};