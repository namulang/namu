#pragma once

#include "../DockableResource/DockableResource.hpp"

namespace DX9Graphics
{
	class NE_DLL FileResource : public DockableResource
	{
	public:
		typedef DockableResource SuperClass;
		typedef FileResource ThisClass;

	public:
		FileResource()
			: SuperClass()
		{

		}
		FileResource(const ThisClass& source)
			: SuperClass(source)
		{

		}

	public:
		NETArgument<NETStringKey>	arg_path;


	protected:
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{	
			tray.push(arg_path);

			return RESULT_SUCCESS;
		}

		virtual type_result _onFetchModule()
		{
			arg_path.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
	};	
}