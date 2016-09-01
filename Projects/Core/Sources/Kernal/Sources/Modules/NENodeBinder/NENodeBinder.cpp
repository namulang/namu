#include "NENodeBinder.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	type_bool NENodeBinder::isBinded() const
	{
		const NEIndexedNodeSet& nodeset = _getNodeSet();
		if( ! &nodeset)	return false;
		const NENode& node = nodeset[getRealIndex()];
		if( ! &node) return false;
		
		return node.getId() == getComparingId();
	}

	NENode& NENodeBinder::getBinded()
	{
		NENode* nullpointer = NE_NULL;
		if( ! isBinded())
			return *nullpointer;

		return _getNodeSet()[getRealIndex()];
	}

	const NENode& NENodeBinder::getBinded() const
	{
		const NENode* nullpointer = NE_NULL;
		if( ! isBinded())
			return *nullpointer;

		return _getNodeSet()[getRealIndex()];
	}

	NEIndexedNodeSet& NENodeBinder::_getNodeSet()
	{
		NEIndexedNodeSet* nullpointer = NE_NULL;
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
			return *nullpointer;
		
		return manager._getNodeSet();
	}

	const NEIndexedNodeSet& NENodeBinder::_getNodeSet() const
	{
		const NEIndexedNodeSet* nullpointer = NE_NULL;
		const NEEnlistableManager& manager = getManager();
		if( ! &manager)
			return *nullpointer;

		return manager.getNodeSet();
	}

	type_result NENodeBinder::bind(const NENode& node/*, NEType::Type manager_type*/)
	{
		//using namespace NEType;
		////	pre:
		//if( ! isValidHierachy(NEENLISTABLE_MANAGER, manager_type))
		//{

		//	KERNAL_ERROR("주어진 Manager가 null 이거나 NEEnlistableManager가 아닙니다.");
		//	goto ON_ERROR;
		//}
		//_manager_type = manager_type;

		NEIndexedNodeSet& cont = _getNodeSet();
		if( ! &cont)
		{
			KERNAL_ERROR("NEIndexedNodeSet을 가져올 수 없었습니다.");
			goto ON_ERROR;
		}
		const NEOccupiedSet& ocp_tbl = cont.getOccupiedSet();
		type_id src_id = node.getId();


		//	main:
		for(int n=0; n < cont.getSize() ;n++)
		{
			NENode& itr = cont[n];
			if( ! ocp_tbl[n]			||	//	소유권이 없거나
				! &itr					||	//	Node가 없거나
				itr.getId() != src_id	)	//	주어진 Id와 일치하지 않으면
				continue;
			
			_real_index = n;
			_comparing_id = src_id;
			return RESULT_SUCCESS;
		}

ON_ERROR:
		KERNAL_ERROR("주어진 Node&, NEEnlistableManager& 로 바인딩 실패했습니다.");
		return RESULT_TYPE_ERROR;
	}

	NENodeBinder::NENodeBinder()
		: Super()
	{
	
	}

	NENodeBinder::NENodeBinder(const NENode& node/*, NEType::Type manager_type*/)
		: Super()
	{
		bind(node/*, manager_type*/);
	}

}