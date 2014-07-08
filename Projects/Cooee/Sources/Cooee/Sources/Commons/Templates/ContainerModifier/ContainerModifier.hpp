#pragma once

#include "../../../Modules/Terminal/Terminal.hpp"

template <typename KEYS, typename KEY>
class ContainerModifier : public Terminal
{
public:
	typename typedef KEYS::Trait KT;

	class KeyContentList : public ListGliph
	{
	public:
		FUNC_CLONE(KeyContentList)
		FUNC_TO_OWNER(ContainerModifier)

		KeyContentList() 
		: ListGliph(0, 25, 5, 30, 15, BLACK, WHITE, WHITE, LIGHTRED) {}

		virtual void onUpdateData()
		{
			if( ! toOwner()) return;
			KT& value = toOwner()->value;
			if( ! &value) return;

			items.create(value.getLength());
			for(int n=0; n < value.getLength(); n++)	
				items.push(NEString(value[n]));
		}
		virtual void onKeyPressed(char inputed)
		{
			ListGliph::onKeyPressed(inputed);

			switch(inputed)
			{
			case CANCEL:
				toOwner()->delete_me = true;
				break;
			case CONFIRM:
				{
					typename KEY::Trait& key_value = toOwner()->value[choosed];
					::LG::Core::open(Modifier<KEY>(key_value));				
				}				
				break;

			case UP: case DOWN:
				onDraw();
				break;
			}
		}
	};

	ContainerModifier(KEYS& key) 
		: Terminal("", KEYS().getType(), 25, 5, 30, 15, BLACK, WHITE), value(key.getValue())
	{
		regist(1, &list);
	}
	ContainerModifier(typename KEYS::Trait& new_value)
		: Terminal("", KEYS().getType(), 25, 5, 30, 15, BLACK, WHITE), value(new_value)
	{
		regist(1, &list);
	}
	ContainerModifier(const ContainerModifier& rhs)
		: Terminal(rhs), list(rhs.list), value(rhs.value)
	{
		regist(1, &list);
	}

	virtual void onUpdateData()
	{
		Window::onUpdateData();
	}

	FUNC_CLONE(ContainerModifier)

	KeyContentList list;
	typename KEYS::Trait& value;
};