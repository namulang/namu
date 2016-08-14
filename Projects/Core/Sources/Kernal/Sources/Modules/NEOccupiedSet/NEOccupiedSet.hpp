#pragma once

#include "../NEBooleanSet/NEBooleanSet.hpp"

namespace NE
{	
	class NE_DLL NEOccupiedSet : public NEBooleanSet
	{
		NE_DECLARE_CLASS(NEOccupiedSet, NEBooleanSet)

	public:
		type_result setInBatches(type_bool is_occupied);
		type_index getNextVacantIndex(type_index initial_index, type_bool want_to_find_being_occupied) const;
		type_index getPrevVacantIndex(type_index initial_index, type_bool want_to_find_being_occupied) const;
	};
}