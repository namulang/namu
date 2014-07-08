#pragma once

#include "../DX9Binder/DX9Binder.hpp"

namespace DX9Graphics
{
	class NE_DLL Presentor : public DX9Binder
	{
		typedef Presentor ThisClass;
		typedef DX9Binder SuperClass;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const
		{
			return *(new Presentor(*this));
		}		
	};
}