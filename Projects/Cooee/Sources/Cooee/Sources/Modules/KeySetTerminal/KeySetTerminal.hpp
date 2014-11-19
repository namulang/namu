#pragma once

#include "../Terminal/Terminal.hpp"

class KeySetTerminal : public Terminal
{
public:
	KeySetTerminal(const NEString& new_path, type_ushort x=25, type_ushort y=4) 
		: Terminal(new_path, NEType::NEKEY_CODESET, x, y, 31, 17, BLACK, DARKGRAY)
	{
		regist(4, &header, &names, &types, &data);
	}	
	KeySetTerminal(const KeySetTerminal& rhs) : Terminal(rhs), header(rhs.header), names(rhs.names), types(rhs.types), data(rhs.data)
	{
		regist(4, &header, &names, &types, &data);
	}

	class Header : public Gliph
	{
	public:
		Header()
			: Gliph(0, 0, 0, 31, 1, DARKGRAY, LIGHTGRAY, "KeyName   KeyType   KeyData") {}
		Header(const Header& rhs)
			: Gliph(rhs) {}
		FUNC_CLONE(Header)
		FUNC_TO_OWNER(KeySetTerminal)
		virtual void onUpdateData()
		{
			x = toOwner()->x;
			y = toOwner()->y;
		}
	};

	class KeyNameList : public ListGliph
	{
	public:
		KeyNameList() : ListGliph(0, 0, 1, 10, 15, LIGHTCYAN, CYAN, CYAN, LIGHTCYAN) {}
		FUNC_TO_OWNER(KeySetTerminal)
		FUNC_CLONE(KeyNameList)
		virtual void onUpdateData()
		{
			ListGliph::onUpdateData();

			x = toOwner()->x;
			y = toOwner()->y + 1;

			const NEKeyCodeSet& ks = toOwner()->castObject();
			if( ! &ks) return;
			
			items.create(ks.getLength());
			for(int n=0; n < ks.getLength() ;n++)
				items.push(ks[n].getName());

			//ListGliph::onUpdateData();
		}
		virtual void onKeyPressed(char inputed);
	};
	class KeyTypeList : public ListGliph
	{
	public:
		KeyTypeList() : ListGliph(0, 10, 2, 10, 15, BLACK, WHITE, CYAN, LIGHTCYAN) {}
		FUNC_TO_OWNER(KeySetTerminal)
		FUNC_CLONE(KeyTypeList)
		virtual void onUpdateData()
		{
			ListGliph::onUpdateData();

			x = toOwner()->x + 10;
			y = toOwner()->y + 1;

			const NEKeyCodeSet& ks = toOwner()->castObject();
			if( ! &ks) return;

			items.create(ks.getLength());
			for(int n=0; n < ks.getLength() ;n++)
				items.push(ks[n].getTypeName());

			//ListGliph::onUpdateData();
		}
	};
	class KeyDataList : public ListGliph
	{
	public:
		KeyDataList() : ListGliph(0, 20, 2, 11, 15, BLACK, WHITE, CYAN, LIGHTCYAN) {}
		FUNC_TO_OWNER(KeySetTerminal)
		FUNC_CLONE(KeyDataList)
		virtual void onUpdateData()
		{
			ListGliph::onUpdateData();

			x = toOwner()->x + 20;
			y = toOwner()->y + 1;

			const NEKeyCodeSet& ks = toOwner()->castObject();
			if( ! &ks) return;

			items.create(ks.getLength());
			for(int n=0; n < ks.getLength() ;n++)
				items.push(NEStringKey(ks[n]).getValue());

			//ListGliph::onUpdateData();
		}
	};

	FUNC_CLONE(KeySetTerminal)

	NEKeyCodeSet& castObject()
	{
		return (NEKeyCodeSet&) *instance;
	}

	Header header;
	KeyNameList names;
	KeyTypeList types;
	KeyDataList data;
};