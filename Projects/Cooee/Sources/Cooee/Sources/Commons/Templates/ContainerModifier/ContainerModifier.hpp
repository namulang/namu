#pragma once

#include "../../../Modules/Terminal/Terminal.hpp"
#include "../../../Modules/NameInputWindow/NameInputWindow.hpp"

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
				items.push(NEString("키 이름: " + toOwner()->real_key->getName()));

			for(int n=0; n < value.getLength(); n++)	
				items.push(NEString(value[n]));
		}
		virtual void onKeyPressed(int inputed)
		{
			int index = toOwner()->real_key ? choosed-1 : choosed;

			ListGliph::onKeyPressed(inputed);

			switch(inputed)
			{
			case CONFIRM:
				if (index < 0)
				{
					if (toOwner()->real_key)
						toOwner()->call(NameInputWindow(toOwner()->real_key->getName()));
				}
				else
				{
					typename KEY::Trait& key_value = toOwner()->value[index];
					::LG::Core::open(Modifier<KEY>(key_value));
				}
				break;


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

template <>
class ContainerModifier<NECodeSetKey, NECodeKey> : public Terminal
{
public:
	typedef NECodeSetKey	KEYS;
	typedef NECodeKey		KEY;
	typedef KEYS::Trait		KT;

	class KeyContentList : public ListGliph
	{
	public:
		FUNC_CLONE(KeyContentList)
			FUNC_TO_OWNER(ContainerModifier)

			KeyContentList()
			: ListGliph(0, 25, 5, 30, 15, BLACK, WHITE, WHITE, LIGHTRED) {}

		NEString createCodeTypeString(const NECodeType& type) const
		{
			switch (type.getCodeType())
			{
			case NECodeType::SCRIPT:		return "SCRIPT";
			case NECodeType::NAME:			return "NAME";
			case NECodeType::GROUP:			return "GROUP";
			case NECodeType::PRIORITY:		return "PRIORITY";
			case NECodeType::UNDEFINED:		return "UNDEFINED";
			case NECodeType::MODULE_SCRIPT: return "MODULE_SCRIPT";
			case NECodeType::MODULE_NAME:	return "MODULE_NAME";
			case NECodeType::ME:			return "ME";
			case NECodeType::RECENT:		return "RECENT";
			case NECodeType::ALL:			return "ALL";
			}

			return "";
		}

		virtual void onUpdateData()
		{
			ListGliph::onUpdateData();

			if (!toOwner()) return;
			KT& value = toOwner()->value;
			if (!&value) return;

			items.create(value.getLength() + 2);
			if (toOwner()->real_key)
				items.push(NEString("키 이름: " + toOwner()->real_key->getName()));

			items.push(NEString("<-" + createCodeTypeString(value.getCodeType()) + " ->"));

			for (int n = 0; n < value.getLength(); n++)
				items.push(createCodeTypeString(value[n].getCodeType()) + " : " + value[n].getCode());
		}
		virtual void onKeyPressed(int inputed)
		{
			int index = toOwner()->real_key ? choosed - 2 : choosed;
			NECodeSet& value = toOwner()->value;
			bool is_focused_on_type =  false;
			if (toOwner()->real_key)
				is_focused_on_type = choosed == 1;
			else
				is_focused_on_type = choosed == 0;

			ListGliph::onKeyPressed(inputed);

			switch (inputed)
			{
			case CONFIRM:
				if (index < 0)
				{
					if (toOwner()->real_key)
						toOwner()->call(NameInputWindow(toOwner()->real_key->getName()));
				}
				else
				{
					KEY::Trait& key_value = toOwner()->value[index];
					::LG::Core::open(Modifier<KEY>(key_value));
				}
				break;

			case LEFT:				
				if(is_focused_on_type)
				{
					int n = value.getCodeType().getCodeType();
					if (n > NECodeType::UNDEFINED)
						n--;
					if (n > 0)
						value.getCodeType().setCodeType(NECodeType::CodeType(n));
				}
				break;

			case RIGHT:
				if (is_focused_on_type)
				{
					int n = value.getCodeType().getCodeType();
					if(n < NECodeType::ALL)
						n++;
					value.getCodeType().setCodeType(NECodeType::CodeType(n));
				}
				break;

			case CLOSE:
				toOwner()->delete_me = true;
				break;

			case ADD:
				{
					if (index < 0)
						index = 0;

					KEYS::Trait& container = toOwner()->value;
					if (container.getLength() == container.getSize())
						container.resize(container.getLength() + 1);
					KEY::Trait& inputed = container[container.insert(index, KEY::Trait())];
					if (&inputed)
						::LG::Core::open(Modifier<KEY>(inputed));
				}
				break;

			case REMOVE:
				{
					if (index < 0)
						index = 0;

					KEYS::Trait& container = toOwner()->value;
					container.remove(index);
					if (container.getLength() == container.getSize())
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
	ContainerModifier(KEYS::Trait& new_value)
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
	KEYS::Trait& value;
	KEYS* real_key;
};