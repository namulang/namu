#pragma once

#include "../DX9Binder/DX9Binder.hpp"

namespace DX9Graphics
{
	class NE_DLL BufferClearer : public DX9Binder
	{
		typedef BufferClearer ThisClass;
		typedef DX9Binder SuperClass;

	public:
		virtual NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result initialize();

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const;
	};
}