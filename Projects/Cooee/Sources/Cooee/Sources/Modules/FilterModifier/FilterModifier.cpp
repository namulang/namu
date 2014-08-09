#include "FilterModifier.hpp"

Planetarium& FilterModifier::getPlanetarium()
{ 
	return (Planetarium&) owner->getCaller();
}