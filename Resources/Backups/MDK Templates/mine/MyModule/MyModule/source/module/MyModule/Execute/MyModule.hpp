#pragma once

#include "../../../include/includeNodeEngine.hpp"

namespace NE
{
	class MyModule : public NEModule
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		class Connector : public NEModule::BaseConnector
		{
		public:
			Connector();

		public:
			type_result connect(NEKeySet& keyset);

		public:
			NEStringKey* helloworld;
		};

	public:
		MyModule();
		MyModule(const MyModule& source);

	public:
		virtual ~MyModule();

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject* clone() const;

	public: 
		Connector connector;
	};
}
