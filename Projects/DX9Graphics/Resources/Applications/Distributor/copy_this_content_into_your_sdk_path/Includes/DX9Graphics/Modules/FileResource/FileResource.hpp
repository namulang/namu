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
		NETString& getPath()
		{
			const ThisClass* consted_this = this;

			return const_cast<NETString&>(consted_this->getPath() );
		}
		const NETString& getPath() const
		{
			const NEKey& somekey = getKeySet()[1];
			if( ! somekey.isSubClassOf(NEType::NETSTRING_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 1번키가 NETStringKey여야 합니다.");
				const NETString* nullpoint = 0;
				return *nullpoint;
			}

			const NETStringKey& target = static_cast<const NETStringKey&>(somekey);
			return target.getValue();
		}

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 1);
			keyset.push(NETStringKey());	//	1:	Path

			return RESULT_SUCCESS;
		}
		
	public:
		virtual type_result isValid() const
		{
			type_result result = SuperClass::isValid();
			if(NEResult::hasError(result)) return result;
			if(getKeySet()[1].getType() != NEType::NETSTRING_KEY) return RESULT_TYPE_ERROR;
			const NETStringKey& key = static_cast<const NETStringKey&>(getKeySet()[1]);
			if(key.getValue().getLength() <= 0) return RESULT_TYPE_ERROR;

			return RESULT_SUCCESS;
		}
	};	
}