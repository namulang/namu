#include "NENameShortCutSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NENameShortCutSet::NENameShortCutSet()
		: SuperClass()
	{

	}
	NENameShortCutSet::NENameShortCutSet(type_index size)
		: SuperClass(size)
	{

	}
	NENameShortCutSet::NENameShortCutSet(const ThisClass& source)
		: SuperClass(source)
	{

	}

	const NENameShortCutSet& NENameShortCutSet::operator+=(const ThisClass& source)
	{
		SuperClass::operator+=(source);

		return *this;
	}
	NENameShortCutSet NENameShortCutSet::operator+(const ThisClass& source) const
	{
		ThisClass buffer(getLength() + source.getLength());
		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_result NENameShortCutSet::_enlist(NENode& node, type_index node_real_index)
	{
		type_code namecode = node.getNameCode();
		if(	namecode <= NE_HAS_NO_SCRIPTCODE	||
			namecode > getLengthLastIndex()	)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		if(node_real_index < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		NEShortCut& shortcut = getElement(namecode);
		type_index index = shortcut.find(node_real_index);
		if(index != NE_INDEX_ERROR)
		{
			KERNAL_INFORMATION(" : ");
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		}	



		//	main:		
		return shortcut.push(node_real_index);
	}
	type_result NENameShortCutSet::_unlist(NENode& node, type_index node_real_index)
	{
		type_code namecode = node.getNameCode();
		if(	namecode <= NE_HAS_NO_SCRIPTCODE	||
			namecode > getLengthLastIndex()	)
		{

			KERNAL_ERROR(" : unlist하려는 네임코드가 범위를 벗어났습니다.\n\t변경하려던 네임코드 : %d", namecode);
			return RESULT_TYPE_ERROR;
		}
		NEShortCut& shortcut = getElement(namecode);
		type_index index = shortcut.find(node_real_index);
		if(index <= NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : 삭제하려는 네임코드가 존재하지 않습니다.\n\t삭제하려던 네임코드: %d", namecode);
			return RESULT_TYPE_ERROR;
		}



		return shortcut.remove(index);
	}
}