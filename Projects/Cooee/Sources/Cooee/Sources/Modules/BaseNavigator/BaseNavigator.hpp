#pragma once

#include "../../Includes/Includes.hpp"

class BaseNavigator : public Gliph {
public:
	BaseNavigator(const NEString& new_type, int x, int y, int w, int h, int fore, int back) : Gliph(0, x, y, w, h, fore, back), type(new_type) {}
	BaseNavigator(const BaseNavigator& rhs) : Gliph(rhs), type(rhs.type) {}
	virtual void onUpdateData();

	NEString type;
};