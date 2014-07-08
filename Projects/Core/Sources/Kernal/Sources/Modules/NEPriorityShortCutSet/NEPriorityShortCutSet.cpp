#include "NEPriorityShortCutSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NEPriorityShortCutSet::NEPriorityShortCutSet()
		: SuperClass()
	{

	}
	NEPriorityShortCutSet::NEPriorityShortCutSet(type_index size)
		: SuperClass(size)
	{

	}
	NEPriorityShortCutSet::NEPriorityShortCutSet(const ThisClass& source)
		: SuperClass(source)
	{

	}

	const NEPriorityShortCutSet& NEPriorityShortCutSet::operator+=(const ThisClass& source)
	{
		SuperClass::operator+=(source);

		return *this;
	}
	NEPriorityShortCutSet NEPriorityShortCutSet::operator+(const ThisClass& source) const
	{
		ThisClass buffer(getLength() + source.getLength());
		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_result NEPriorityShortCutSet::_enlist(NENode& node, type_index node_real_index)
	{
		if( ! node.isRootNode())
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		type_code priority = node.getPriority();
		if(	priority <= NE_HAS_NO_SCRIPTCODE	||
			priority > getLengthLastIndex()	)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		if(node_real_index < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		NEShortCut& shortcut = getElement(priority);
		type_index index = shortcut.find(node_real_index);
		if(index != NE_INDEX_ERROR)
		{
			KERNAL_INFORMATION(" : ");
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		}	



		//	main:		
		return shortcut.push(node_real_index);
	}
	type_result NEPriorityShortCutSet::_unlist(NENode& node, type_index node_real_index)
	{
		if( ! node.isRootNode())
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		type_code priority = node.getPriority();
		if(	priority <= NE_HAS_NO_SCRIPTCODE	||
			priority > getLengthLastIndex()	)
		{

			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		NEShortCut& shortcut = getElement(priority);
		type_index index = shortcut.find(node_real_index);
		if(index <= NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}



		return shortcut.remove(index);
	}
}