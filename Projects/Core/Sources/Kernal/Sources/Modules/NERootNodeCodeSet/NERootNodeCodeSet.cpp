#include "NERootNodeCodeSet.hpp"
#include "../Kernal/Kernal.hpp"
#include "../NEIndexedNodeSet/NEIndexedNodeSet.hpp"

namespace NE
{
	NERootNodeCodeSet::NERootNodeCodeSet(NEEnlistableManager& manager)
		: SuperClass()
	{
		_manager = &manager;
		//	enlist:
		//		왜 enlist를 true로 하는가:
		//			생성자에서 manager로부터 주소를 넘겨받은 것이 RootNodeCodeSet
		//			에서 다룰 수 있는 유일한 경우의 enlist 이기 때문이다.
		//			만약 NERootNodeCodeSet을 NodeCodeSet으로써 차후에 enlist 한다고
		//			한다면, 그것은 NENodeCodeSet으로써 enlist를 처리하게 될것이다.
		_is_enlisted = true;
	}
	NERootNodeCodeSet::NERootNodeCodeSet(type_index size)
		: SuperClass(size)
	{
		
	}
	NERootNodeCodeSet::NERootNodeCodeSet(const NERootNodeCodeSet& source)
		: SuperClass(source)
	{
		
	}
	NERootNodeCodeSet::~NERootNodeCodeSet()
	{
		
	}

	const NERootNodeCodeSet& NERootNodeCodeSet::operator+=(const NERootNodeCodeSet& source)
	{
		if(this == &source)
		{
			NERootNodeCodeSet copyied(*this);
			resize(_length + copyied._length);
			push(copyied);
		}
		else 
		{
			resize(_length + source._length);
			push(source);
		}

		return *this;
	} 

	NERootNodeCodeSet NERootNodeCodeSet::operator+(const NERootNodeCodeSet& source) const
	{
		ThisClass buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}
	NEObject& NERootNodeCodeSet::clone() const
	{
		return *(new ThisClass(*this));
	}
	NEType::Type NERootNodeCodeSet::getType() const
	{
		return NEType::NEROOT_NODE_CODESET;
	}

	type_result NERootNodeCodeSet::_onEnlisted(NENode& node)
	{
		if( ! &getManager()) return RESULT_TYPE_ERROR;
		if( ! &node) return RESULT_TYPE_ERROR;

		node._is_rootnode = true;
		return SuperClass::_onEnlisted(node);
	}
}