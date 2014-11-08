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
			ListGliph::onUpdateData();

			if( ! toOwner()) return;
			KT& value = toOwner()->value;
			if( ! &value) return;

			items.create(value.getLength() + 1);
			if(toOwner()->real_key)
				items.push(NEString("Å° ÀÌ¸§: " + toOwner()->real_key->getName()));

			for(int n=0; n < value.getLength(); n++)	
				items.push(NEString(value[n]));
		}
		virtual void onKeyPressed(char inputed)
		{
			int index = toOwner()->real_key ? choosed-1 : choosed;

			switch(inputed)
			{
			case CLOSE:
				toOwner()->delete_me = true;
				break;

			case ADD:
				{
					if(index < 0)
						index = 0;

					KEYS::Trait& container = toOwner()->value;
					if(container.getLength() == container.getSize())
						container.resize(container.getLength() + 1);
					KEY::Trait& inputed = container[container.insert(index, KEY::Trait())];
					if(&inputed)
						::LG::Core::open(Modifier<KEY>(inputed));
				}
				break;

			case REMOVE:
				{					
					if(index < 0)
						index = 0;

					KEYS::Trait& container = toOwner()->value;
					container.remove(index);
					if(container.getLength() == container.getSize())
						container.resize(container.getLength() + 1);					
				}
				break;
			}
		}
	};

	ContainerModifier(KEYS& key) 
		: Terminal("", KEYS().getType(), 25, 5, 30, 15, BLACK, WHITE), value(key.getValue()), real_key(&key)
	{
		regist(1, &list);
	}
	ContainerModifier(typename KEYS::Trait& new_value)
		: Terminal("", KEYS().getType(), 25, 5, 30, 15, BLACK, WHITE), value(new_value), real_key(0)
	{
		regist(1, &list);
	}
	ContainerModifier(const ContainerModifier& rhs)
		: Terminal(rhs), list(rhs.list), value(rhs.value), real_key(rhs.real_key)
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
	KEYS* real_key;
};