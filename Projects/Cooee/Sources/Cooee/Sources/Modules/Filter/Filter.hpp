#pragma once

#include "../../Includes/Includes.hpp"

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
	void _updateSwitchWhenFilterExisted(NENodeSelector& filter);

	virtual void onKeyPressed(int inputed);
	virtual void onItemChoosed(type_index item_index, const NEString& chosen_content);
	void _switchOn();
};