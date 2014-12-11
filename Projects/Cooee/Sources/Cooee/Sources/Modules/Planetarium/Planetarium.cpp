#pragma once

#include "../Planetarium/Planetarium.hpp"
#include "../Filter/Filter.hpp"
#include "../Core/Core.hpp"

void Planetarium::onKeyPressed(char inputed)
{
	Window::onKeyPressed(inputed);
	type_index n = 0;
	switch(inputed)
	{
	case MAP:
		delete_me = true;
		break;

	case UP:
		if( ! focusing->parent) return;
		n = focusing->parent->planets.find(focusing);
		if( n == NE_INDEX_ERROR) return;

		if(n > 0)
			focusing = &focusing->parent->planets[n-1];
		setFocus(*focusing);
		break;

	case DOWN:
		if( ! focusing->parent) return;
		n = focusing->parent->planets.find(focusing);
		if( n == NE_INDEX_ERROR) return;

		if(n < focusing->parent->planets.getLengthLastIndex())
			focusing = &focusing->parent->planets[n+1];
		setFocus(*focusing);
		break;

	case LEFT:
		if( ! focusing->parent) return;

		focusing = focusing->parent;
		setFocus(*focusing);
		break;

	case RIGHT:
		if(	focusing->planets.getLength() > 0	&&
			! focusing->is_closed				)
			focusing = &focusing->planets[0];
		setFocus(*focusing);
		break;

	case LG::CANCEL:
		call(Filter());
		break;

	case LG::SPACE:
		focusing->is_closed = ! focusing->is_closed;
		root.updateLines(0);
		break;

	case CONFIRM:
		if(focusing->real->isSubClassOf(NEType::NEMODULE_CODESET_KEY))
			::Core::openModifierFrom(::Core::createPathBy(*focusing->real));
		else if(focusing->real->isSubClassOf(NEType::NENODE_CODESET_KEY))
			::Core::openModifierFrom(::Core::createPathBy(*focusing->real));
		else if(focusing->real->isSubClassOf(NEType::NEKEY))
			::Core::openModifierFrom((NEKey&) *focusing->real);
		else
			::Core::openModifierFrom(::Core::createPathBy(*focusing->real));
		break;
	}
}

void Planetarium::onUpdateData()
{
	synchroSelectors();

	NEListTemplate<NEObject*> selected;
	getSelectedByFilter(selected);

	root.updateLines(0);
	root.markColor(selected);
}

void Planetarium::onFocused()
{        
	NEObject* real_object = focusing->real;
	root.planets.release();
	NENodeCodeSet& ncs = ::Core::isObservingDebug() ? 
		Kernal::getInstance().getNodeManager().getRootNodes()
		:
	Editor::getInstance().getScriptEditor().getScriptNodes();
	generate(ncs);

	setFocus(*real_object);

	Window::onFocused();
}

void Planetarium::onDraw()
{
	LG::BackBuffer& buf = LG::Core::back_buffer;
	bool is_color_locked = buf.isColorLocked();
	if(is_color_locked)
		buf.setColorLock(false);

	Window::onDraw();

	root.onDraw();

	if(is_color_locked)
		buf.setColorLock(true);
}

void Planetarium::getSelectedByFilter(NEListTemplate<NEObject*>& selected)
{
	//	현재 어떤 Filter가 활성화 되어있는 지를 판단한다:
	if (switches[2])
	{
		NEType::Type backup = getKeyFilter().getManagerType();
		if (::Core::isObservingDebug())
			getKeyFilter().setManager(NEType::NENODE_MANAGER);
		else
			getKeyFilter().setManager(NEType::NESCRIPT_EDITOR);

		while (NEKey* itr = &getKeyFilter().getKey())
			selected.push(itr);
		getKeyFilter().setManager(backup);
	}
	if (switches[1])
	{
		NEType::Type backup = getModuleFilter().getManagerType();
		if (::Core::isObservingDebug())
			getModuleFilter().setManager(NEType::NENODE_MANAGER);
		else
			getModuleFilter().setManager(NEType::NESCRIPT_EDITOR);

		while (NEModule* itr = &getModuleFilter().getModule())
			selected.push(itr);
		getModuleFilter().setManager(backup);
	}
	if (switches[0])
	{
		NEType::Type backup = getNodeFilter().getManagerType();
		if (::Core::isObservingDebug())
			getNodeFilter().setManager(NEType::NENODE_MANAGER);
		else
			getNodeFilter().setManager(NEType::NESCRIPT_EDITOR);

		while (NENode* itr = &getNodeFilter().getNode())
			selected.push(itr);
		getNodeFilter().setManager(backup);
	}
}

