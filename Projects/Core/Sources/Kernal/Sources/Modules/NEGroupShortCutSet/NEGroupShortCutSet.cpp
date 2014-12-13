#include "NEGroupShortCutSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NEGroupShortCutSet::NEGroupShortCutSet()
		: SuperClass()
	{

	}
	NEGroupShortCutSet::NEGroupShortCutSet(type_index size)
		: SuperClass(size)
	{

	}
	NEGroupShortCutSet::NEGroupShortCutSet(const ThisClass& source)
		: SuperClass(source)
	{

	}

	const NEGroupShortCutSet& NEGroupShortCutSet::operator+=(const ThisClass& source)
	{
		SuperClass::operator+=(source);

		return *this;
	}
	NEGroupShortCutSet NEGroupShortCutSet::operator+(const ThisClass& source) const
	{
		ThisClass buffer(getLength() + source.getLength());
		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_result NEGroupShortCutSet::_enlist(NENode& node, type_index node_real_index)
	{
		const NECodeSet& codeset = node.getGroupCode();
		if(node_real_index < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}



		//	main:
		type_result result = RESULT_SUCCESS;
		for(int n=0; n < codeset.getLength() ;n++)
		{
			type_code groupcode = codeset[n].getCode();
			if(	groupcode <= NE_HAS_NO_SCRIPTCODE	||
				groupcode > getLengthLastIndex()	)
			{
				KERNAL_ERROR(" : ");
				return RESULT_TYPE_ERROR;
			}
			NEShortCut& shortcut = getElement(groupcode);			
			type_index index = shortcut.find(node_real_index);
			if(index != NE_INDEX_ERROR)
			{
				KERNAL_INFORMATION(" : ");
				result |= RESULT_SUCCESS | RESULT_ABORT_ACTION;
				continue;
			}
			shortcut.push(node_real_index);
		}

		return result;
	}
	type_result NEGroupShortCutSet::_unlist(NENode& node, type_index node_real_index)
	{
		const NECodeSet& codeset = node.getGroupCode();
		if(node_real_index < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}



		//	main:
		type_result result = RESULT_SUCCESS;

		for(int n=0; n < codeset.getLength() ;n++)
		{
			type_code groupcode = codeset[n].getCode();
			if(	groupcode <= NE_HAS_NO_SCRIPTCODE	||
				groupcode > getLengthLastIndex()	)
			{

				KERNAL_ERROR(" : ");
				return RESULT_TYPE_ERROR;
			}
			NEShortCut& shortcut = getElement(groupcode);
			type_index index = shortcut.find(node_real_index);
			if(index <= NE_INDEX_ERROR)
			{
				KERNAL_ERROR(" : ");
				return RESULT_TYPE_ERROR;
			}

			result |= shortcut.remove(index);
		}

		return result;
	}
}