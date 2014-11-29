#include "NEITArgument.hpp"
#include "../../../Modules/NEIntKey/NEIntKey.hpp"
#include "../../../Modules/NEBooleanKey/NEBooleanKey.hpp"
#include "../../../Modules/NECharKey/NECharKey.hpp"
#include "../../../Modules/NEByteKey/NEByteKey.hpp"
#include "../../../Modules/NEUByteKey/NEUByteKey.hpp"
#include "../../../Modules/NEWCharKey/NEWCharKey.hpp"
#include "../../../Modules/NEShortKey/NEShortKey.hpp"
#include "../../../Modules/NEUShortKey/NEUShortKey.hpp"
#include "../../../Modules/NEIntKey/NEIntKey.hpp"
#include "../../../Modules/NEUIntKey/NEUIntKey.hpp"
#include "../../../Modules/NEInt64Key/NEInt64Key.hpp"
#include "../../../Modules/NEFloatKey/NEFloatKey.hpp"
#include "../../../Modules/NEDoubleKey/NEDoubleKey.hpp"
#include "../../../Modules/NEStringKey/NEStringKey.hpp"
#include "../../../Modules/NEWStringKey/NEWStringKey.hpp"
#include "../../../Modules/NEBooleanSetKey/NEBooleanSetKey.hpp"
#include "../../../Modules/NEByteSetKey/NEByteSetKey.hpp"
#include "../../../Modules/NEUByteSetKey/NEUByteSetKey.hpp"
#include "../../../Modules/NEShortSetKey/NEShortSetKey.hpp"
#include "../../../Modules/NEUShortSetKey/NEUShortSetKey.hpp"
#include "../../../Modules/NEIntSetKey/NEIntSetKey.hpp"
#include "../../../Modules/NEUIntSetKey/NEUIntSetKey.hpp"
#include "../../../Modules/NEInt64SetKey/NEInt64SetKey.hpp"
#include "../../../Modules/NEFloatSetKey/NEFloatSetKEy.hpp"
#include "../../../Modules/NEDoubleSetKey/NEDoubleSetKey.hpp"
#include "../../../Modules/NEStringSetKey/NEStringSetKey.hpp"
#include "../../../Modules/NEWStringSetKey/NEWStringSetKey.hpp"
#include "../../../Modules/NENodeSelector/NENodeSelector.hpp"
#include "../../../Modules/NEModuleSelector/NEModuleSelector.hpp"
#include "../../../Modules/NEKeySelector/NEKeySelector.hpp"
#include "../../../Modules/NEModuleCodeSetKey/NEModuleCodeSetKey.hpp"
#include "../../../Modules/NENodeCodeSetKey/NENodeCodeSetKey.hpp"

namespace NE
{
	template
	class NE_DLL NEITArgument<NEBooleanKey>;
	template
	class NE_DLL NEITArgument<NECharKey>;
	template
	class NE_DLL NEITArgument<NEByteKey>;
	template
	class NE_DLL NEITArgument<NEUByteKey>;
	template
	class NE_DLL NEITArgument<NEWCharKey>;
	template
	class NE_DLL NEITArgument<NEShortKey>;
	template
	class NE_DLL NEITArgument<NEUShortKey>;
	template
	class NE_DLL NEITArgument<NEIntKey>;
	template
	class NE_DLL NEITArgument<NEUIntKey>;
	template
	class NE_DLL NEITArgument<NEInt64Key>;
	template
	class NE_DLL NEITArgument<NEFloatKey>;
	template
	class NE_DLL NEITArgument<NEDoubleKey>;
	template
	class NE_DLL NEITArgument<NEStringKey>;
	template
	class NE_DLL NEITArgument<NEWStringKey>;
	template
	class NE_DLL NEITArgument<NEBooleanSetKey>;
	template
	class NE_DLL NEITArgument<NEByteSetKey>;
	template
	class NE_DLL NEITArgument<NEShortSetKey>;
	template
	class NE_DLL NEITArgument<NEUShortSetKey>;
	template
	class NE_DLL NEITArgument<NEIntSetKey>;
	template
	class NE_DLL NEITArgument<NEUIntSetKey>;
	template
	class NE_DLL NEITArgument<NEInt64SetKey>;
	template
	class NE_DLL NEITArgument<NEFloatSetKey>;
	template
	class NE_DLL NEITArgument<NEDoubleSetKey>;
	template
	class NE_DLL NEITArgument<NEStringSetKey>;
	template
	class NE_DLL NEITArgument<NEWStringSetKey>;
	template
	class NE_DLL NEITArgument<NENodeSelector>;
	template
	class NE_DLL NEITArgument<NEModuleSelector>;
	template
	class NE_DLL NEITArgument<NEKeySelector>;
	template
	class NE_DLL NEITArgument<NEModuleCodeSetKey>;
	template
	class NE_DLL NEITArgument<NENodeCodeSetKey>;
}

namespace NE	
{	
	NEITArgument<NEKey>::NEITArgument(const ThisClass& rhs)	
		: NEArgumentInterfaceBase(rhs), _concrete_class(0x00)	
	{	

	}	

	NEITArgument<NEKey>::NEITArgument()	
		: _concrete_class(0x00)	
	{	
	}	

	NEType::Type NEITArgument<NEKey>::getKeyType() const	
	{	
		return NEType::NEKEY;	
	}	

	bool NEITArgument<NEKey>::isValidToBind(const NEArgumentBase& rhs) const	
	{	
		return NEType::isValidHierachy(NEType::NEKEY, rhs.getTypeToBeBinded());
	}
	
	type_result NE::NEITArgument<NEKey>::_onInsertedInArguments(type_index index, NEArgumentSet& rhs)	
	{	
		if (rhs.getLength() == rhs.getSize())	
			rhs.resize(rhs.getLength() + 1);	
		ConcreteClass& pushed = (ConcreteClass&)rhs[rhs.insert(index, ConcreteClass())];
		if (!&pushed)	
			return RESULT_TYPE_WARNING;	
		return RESULT_SUCCESS;	
	}	

	type_result NE::NEITArgument<NEKey>::_onBindInstance(NEArgumentBase& concreted)	
	{	
		if(	!&concreted	||	
			! isValidToBind(concreted)	)	
			return RESULT_TYPE_WARNING;	
		_concrete_class = static_cast<ConcreteClass*>(&concreted);	
		return RESULT_SUCCESS;	
	}	

	NEITArgument<NEKey>::ConcreteClass& NE::NEITArgument<NEKey>::getConcreteInstance()	
	{	
		return *_concrete_class;	
	}	

	
	const NEITArgument<NEKey>::ConcreteClass& NE::NEITArgument<NEKey>::getConcreteInstance() const	
	{	
		return *_concrete_class;	
	}	

	NEITArgument<NEKey>::T& NE::NEITArgument<NEKey>::getKey()	
	{	
		if (_concrete_class)	
			return _concrete_class->getBinded();	
		T* nullpointer = 0;	
		return *nullpointer;	
	}	

	const NEITArgument<NEKey>::T& NE::NEITArgument<NEKey>::getKey() const	
	{	
		if (_concrete_class)	
			return _concrete_class->getBinded();	
		T* nullpointer = 0;	
		return *nullpointer;	
	}	

	NEITArgument<NEKey>& NE::NEITArgument<NEKey>::operator=(const ThisClass& src)	
	{	
		if (this == &src) return *this;	

		//	정책:	
		//	"	절대로 내부 바인딩의 결과는 공유 및 할당하지 않는다.	
		//	내부 바인딩을 "할 수 있는" 정보만 넘겨줘서, 그 놈이 바인딩 다시 하도록 하라	"	
		//	그래서 바99인딩 결과물인 _concreate_class는 넘겨주지 않는다.	
		//	대신 default_value 같은 것만 할당 시켜준다.	
		//	밑에 처럼 하지 않는다는 거야.	
		//	
		// if(	_concrete_class && src._concrete_class	&&	
		// _concrete_class>getTypeToBeBinded() == src._concrete_class>getTypeToBeBinded()	)	
		// *_concrete_class = *src._concrete_class;	
		return *this;	
	}	

	NEObject& NEITArgument<NEKey>::clone() const
	{
		return *(new ThisClass(*this));
	}

	NEBinaryFileLoader& NEITArgument<NEKey>::serialize(NEBinaryFileLoader& loader)
	{
		return loader;
	}

	NEBinaryFileSaver& NEITArgument<NEKey>::serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}

	void NEITArgument<NEKey>::release()
	{
		if (_concrete_class)
			_concrete_class->release();
	}

	const NEKey& NEITArgument<NEKey>::getDefaultKey() const
	{
		NEKey* nullpointer = 0x00;

		return *nullpointer;
	}

	NEKey& NEITArgument<NEKey>::getDefaultKey()
	{
		NEKey* nullpointer = 0x00;

		return *nullpointer;
	}
}