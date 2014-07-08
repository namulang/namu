#pragma once

#include "../../Includes/Includes.hpp"

class Command : public NEObject {
public:
	NEString name, help;
	virtual NEString execute() = 0;
	virtual type_result isValid() const {return 0;}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver; }
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader; }
	virtual void release() {}
	bool operator!=(const Command& rhs) const {
		return name == rhs.name && help == rhs.help;
	}
};