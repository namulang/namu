#include "BaseNavigator.hpp"
#include "../Core/Core.hpp"

void BaseNavigator::onUpdateData() {
	text = type + ", on " + ::Core::path;
}