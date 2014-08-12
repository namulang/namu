#pragma once

#include "../Modifier/Modifier.hpp"

class Planetarium;

class Filter : public LG::ListWindow
{
public:
	Filter();
	~Filter();
	Filter(const Filter& rhs);

	FUNC_CLONE(Filter)
	FUNC_TO_CALLER(Planetarium)

	NEString createModifierStateString(NENodeSelector& filter, type_bool is_user_choosed);

	virtual void onUpdateData();
	virtual void onDraw();
	void _updateSwitchWhenFilterExisted(NENodeSelector& filter);

	virtual void onKeyPressed(char inputed);
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content);

	Modifier<NENodeSelector> node_modifier;
	Modifier<NEModuleSelector>* module_modifier;
	Modifier<NEKeySelector>* key_modifier;
	int focused_index;
};