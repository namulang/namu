#pragma once

#include "../../Functions/NEResult/NEResult.hpp"

namespace NE
{	
	class NENode;
	
	class NEEnlistable
	{		
	protected:
		virtual type_result _enlist(NENode& target, type_index index = NE_INDEX_ERROR) = 0;
		virtual type_result _unlist(NENode& target, type_index index = NE_INDEX_ERROR) = 0;
	};
}