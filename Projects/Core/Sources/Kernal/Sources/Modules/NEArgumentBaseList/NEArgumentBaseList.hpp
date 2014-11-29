#pragma once

#include "../../Commons/Units/NEArgumentBase/NEArgumentBase.hpp"
#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"
#include "../../Commons/Interfaces/NEUpdatable/NEUpdatable.hpp"

namespace NE
{
	template 
	class NE_DLL NEListTemplate<NEArgumentBase*>;
	class NE_DLL NEArgumentBaseList : public NEListTemplate<NEArgumentBase*>, public NEUpdatable
	{
	public:
		typedef NEArgumentBaseList ThisClass;
		typedef NEListTemplate<NEArgumentBase*> SuperClass;
		typedef NEArgumentBase T;

	public:
		virtual type_result insert(type_index index, const T* const source);
		virtual type_index remove(type_index index);
		virtual type_result update();
	};
}