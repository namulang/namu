#include "NEArgumentBase.hpp"
#include "../Kernal/Kernal.hpp"

namespace 
{
	using namespace NE;
	template <typename T>
	void saveEnumeration(NEBinaryFileSaver& saver, T enumeration)
	{
		int buffer = static_cast<int>(enumeration);
		saver << buffer;
	}
	template <typename T>
	void loadEnumeration(NEBinaryFileLoader& loader, T& enumeration)
	{
		int buffer;
		loader >> buffer;
		enumeration = T(buffer);
	}
}

namespace NE
{
	type_bool NEArgumentBase::operator==(const NEArgumentBase& source) const
	{
		return	Super::operator==(source)				&&
			//_type_validation == source._type_validation	&&
			_limitation == source._limitation			&&
			_purpose == source._purpose					;				
	}
	type_bool NEArgumentBase::operator!=(const NEArgumentBase& source) const
	{
		return ! operator==(source);
	}
	type_result NEArgumentBase::isValid() const
	{
		return RESULT_SUCCESS;
	}
	type_bool NEArgumentBase::isNeedingBinding() const
	{
		return	getKeyName().getLength() > 0	&&
			getKeyName()[0] != 0;
	}
	void NEArgumentBase::release() 
	{
		Super::release();

		_release();
	}

	type_result NEArgumentBase::_onPrepareExecute()
	{
		return RESULT_SUCCESS;
	}
	type_result NEArgumentBase::_onPostExecute()
	{
		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver& NEArgumentBase::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		//saveEnumeration<NEType::Type>(saver, _type_validation);
		saveEnumeration<Purpose>(saver, _purpose);
		saveEnumeration<Purpose>(saver, _limitation);

		return saver;
	}
	NEBinaryFileLoader& NEArgumentBase::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		//NEType::Type validator = NEType::UNDEFINED;
		//loader >> validator;
		loadEnumeration<Purpose>(loader, _purpose);
		loadEnumeration<Purpose>(loader, _limitation);

		return loader;
	}

	NEArgumentBase::NEArgumentBase(/*NEType::Type type, */Purpose limitation)
		: /*_type_validation(type), */_limitation(limitation)
	{
		setPurpose(READ_OR_WRITTEN);
	}

	NEArgumentBase::NEArgumentBase(const This& rhs)
		: Super(rhs)
	{
		_assign(rhs);
	}

// 	NEType::Type NEArgumentBase::getTypeToBeBinded() const
// 	{
// 		return _type_validation;
// 	}

	NEArgumentBase& NEArgumentBase::_assign(const This& source)
	{
		//_type_validation = source._type_validation;
		_purpose = source._purpose;
		_limitation = source._limitation;

		return *this;
	}

	void NEArgumentBase::_release()
	{
		//_type_validation = NEType::UNDEFINED;
		_purpose = _limitation = READ_OR_WRITTEN;		
	}

	NEArgumentBase::~NEArgumentBase()
	{

	}

	type_result NEArgumentBase::bind()
	{
		if( ! isNeedingBinding()	||
			isBinded()				)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return Super::bind();
	}

	type_bool NEArgumentBase::isValidToBind(const NEObject& to_be_bind) const
	{
		if( ! & to_be_bind) return false;

// 		return NEType::isValidHierachy(
// 			getTypeToBeBinded(), to_be_bind.getType()
// 			);
		return false;
	}

	const NEKey& NEArgumentBase::getValueKey() const
	{
		return getBinded();
	}

	NEKey& NEArgumentBase::getValueKey()
	{
		return getBinded();
	}

	NEKey& NEArgumentBase::getKey() 
	{
		NEKey& binded = getBinded();

		return &binded ? binded : getDefaultKey();
	}

	const NEKey& NEArgumentBase::getKey() const
	{
		const NEKey& binded = getBinded();

		return &binded ? binded : getDefaultKey();
	}
}