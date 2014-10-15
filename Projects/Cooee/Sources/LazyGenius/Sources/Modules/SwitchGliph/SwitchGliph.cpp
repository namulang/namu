#include "SwitchGliph.hpp"
#include "../Window/Window.hpp"

void LG::SwitchGliph::setValue(bool new_value, bool drawing /*= false*/)
{
	_value = new_value;

	onUpdateData();
}