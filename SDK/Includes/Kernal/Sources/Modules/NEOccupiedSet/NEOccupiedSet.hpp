#pragma once

#include "../NEBooleanSet/NEBooleanSet.hpp"

namespace NE
{	
	class NE_DLL NEOccupiedSet : public NEBooleanSet
	{
		typedef NEOccupiedSet ThisClass;
		typedef NEBooleanSet SuperClass;

	public:
		type_result setInBatches(bool is_occupied);
		type_index getNextVacantIndex(type_index initial_index, bool want_to_find_being_occupied) const;
		type_index getPrevVacantIndex(type_index initial_index, bool want_to_find_being_occupied) const;
	};
}