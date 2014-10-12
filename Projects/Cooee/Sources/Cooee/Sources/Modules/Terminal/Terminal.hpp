#pragma once

#include "../../Includes/Includes.hpp"

class Terminal : public LG::Window 
{
public:
	class Status : public LG::Gliph {
	public:
		Status() : Gliph(0, 1, 1, 78, 1, LG::WHITE, LG::LIGHTRED) { 			
		}
		Status(const Status& rhs) : LG::Gliph(rhs) {}
		FUNC_CLONE(Status)
		FUNC_TO_OWNER(Terminal)

		virtual void onUpdateData();
	};

	Terminal(const NEString& path, NEType::Type new_to_chk_valid, int x, int y, int w, int h, int back, int fore);
	Terminal(const Terminal& rhs);

	virtual void onUpdateData();
	virtual void onKeyPressed(char inputed);
	virtual void onFocused();
	void setPath(const NEString& new_path);
	const NEString& getPath() const;

	NEString _path;
	NEObject* instance;
	NEType::Type to_chk_valid;
	Status status;


	class Navigator : public LG::Gliph {
	public:
		Navigator() : LG::Gliph(0, 1, 23, 78, 1, DARKGRAY, LIGHTGRAY) {}
		Navigator(const Navigator& rhs) : Gliph(rhs) {}
		FUNC_CLONE(Navigator)
		FUNC_TO_OWNER(Terminal)

		virtual void onUpdateData();
	};
	Navigator navigator;

protected:
	void _setObject();
};