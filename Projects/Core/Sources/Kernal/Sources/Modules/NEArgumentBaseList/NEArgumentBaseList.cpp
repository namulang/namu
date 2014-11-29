#include "NEArgumentBaseList.hpp"

namespace NE
{
	type_result NEArgumentBaseList::insert(type_index index, const T* const source)
	{
		if (find(source) != NE_INDEX_ERROR)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return SuperClass::insert(index, source);
	}

	type_index NEArgumentBaseList::remove(type_index index)
	{
		NEArgumentBase& element = getElement(index);
		if( ! &element) return RESULT_TYPE_ERROR;

		element.cancleUpdate();

		return SuperClass::remove(index);
	}

	type_result NEArgumentBaseList::update()
	{
		type_result result = RESULT_SUCCESS;
		for (Iterator* itr = getIterator(0); itr; itr = itr->getNext())
			result |= itr->getValue().update();

		return result;
	}

}