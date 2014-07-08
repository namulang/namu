#include "NEOccupiedSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	type_result NEOccupiedSet::setInBatches(bool is_occupied)
	{
		type_result result = RESULT_SUCCESS;
		for(int n=0; n < getLength() ;n++)
			result |= setElement(n, is_occupied);

		return result;
	}

	type_index NEOccupiedSet::getNextVacantIndex(type_index initial_index, bool want_to_find_being_occupied) const
	{
		//	pre:
		if(	initial_index < 0					||
			initial_index > getLengthLastIndex())
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		for(int n=initial_index; n < getLength() ;n++)
			if(getElement(n) == want_to_find_being_occupied)
				return n;

		return NE_INDEX_ERROR;
	}

	type_index NEOccupiedSet::getPrevVacantIndex(type_index initial_index, bool want_to_find_being_occupied) const
	{
		//	pre:
		if(	initial_index < 0					||
			initial_index > getLengthLastIndex())
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		for(int n=initial_index; n > -1 ;n--)
			if(getElement(n) == want_to_find_being_occupied)
				return n;

		return NE_INDEX_ERROR;
	}
}
