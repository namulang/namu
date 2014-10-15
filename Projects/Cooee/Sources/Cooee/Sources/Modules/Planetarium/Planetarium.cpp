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