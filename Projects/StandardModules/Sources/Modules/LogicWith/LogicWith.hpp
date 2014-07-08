#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL LogicWith : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/OperatorType/OperatorType.hpp"

	public:
		LogicWith();
		LogicWith(const LogicWith& source);

	public:
		virtual ~LogicWith();

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;
	};
}