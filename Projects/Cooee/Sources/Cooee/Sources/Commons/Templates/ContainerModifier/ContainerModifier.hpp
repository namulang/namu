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

			items.create(value.getLength() + 1);
			if(toOwner()->real_key)
				items.push(NEString("키 이름: " + toOwner()->real_key->getName()));

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
					class NameInputWindow : public ::LG::InputWindow
					{
					public:
						NameInputWindow(const NEString& default_string) : InputWindow("새로운 키의 이름을 입력해주시기 바랍니다.", BLACK, LIGHTCYAN, default_string) {}

						FUNC_TO_CALLER(ContainerModifier)
						FUNC_CLONE(NameInputWindow)

						virtual void onInputed()
						{
							toCaller().real_key->getName() = input.text;
							delete_me = true;
						}
					};
					NEKey* rk = toOwner()->real_key;
					int index = rk ? choosed-1 : choosed;
					if(index == -1)
						toOwner()->call(NameInputWindow(rk->getName()));
					else
					{
						typename KEY::Trait& key_value = toOwner()->value[index];
						::LG::Core::open(Modifier<KEY>(key_value));	
					}					
				}				
				break;

			case UP: case DOWN:
				onDraw();
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