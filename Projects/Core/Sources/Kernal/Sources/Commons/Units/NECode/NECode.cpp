#include "NECode.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"
#undef max
#include <limits>
using namespace std;

namespace NE
{
	typedef NECode ThisClass;

	NECode::NECode()
		: SuperClass()
	{
		_release();
	}

	NECode::NECode(const NEExportable::Identifier& identifier)
		: SuperClass(NECodeType::MODULE_SCRIPT, true)
	{
		setCode(identifier);
	}

	NECode::NECode(const ThisClass& source)
		: SuperClass(source)
	{
		_assign(source);
	}

	NECode::NECode(type_code new_code, const NECodeType& codetype /*= NECodeType()*/)
		: SuperClass(codetype)
	{
		setCode(new_code);
	}

	NECode& NECode::operator++()
	{
		setCode(getCode() + 1);

		return *this;
	}

	NECode NECode::operator++(int)
	{
		NECode to_return(*this);

		setCode(getCode() + 1);

		return to_return;
	}

	NECode NECode::operator--(int)
	{
		NECode to_return(*this);

		setCode(getCode() - 1);

		return to_return;
	}

	NECode& NECode::operator--()
	{
		setCode(getCode() - 1);

		return *this;
	}

	NECode::operator type_code()
	{
		return _code;
	}

	bool NECode::operator==(const type_code source) const
	{
		return getCode() == source;
	}

	bool NECode::operator!=(const type_code source) const
	{
		return ! operator==(source);
	}

	ThisClass::~ThisClass()
	{

	}
	ThisClass& ThisClass::operator=(const ThisClass& source)
	{
		if(this == &source) return *this;
		if( ! isAcceptableType(source))
			return *this;	//	N / A 케이스

		SuperClass::operator=(source);

		return _assign(source);
	}
	ThisClass& ThisClass::_assign(const ThisClass& source)
	{
		setCode(source.getCode());

		return *this;
	}
	bool ThisClass::operator==(const ThisClass& source) const
	{
		return	SuperClass::operator==(source) && _code == source._code;
	}
	bool ThisClass::operator!=(const ThisClass& source) const
	{
		return ! operator==(source);
	}
	bool ThisClass::operator<(const ThisClass& source) const
	{
		return _code < source._code;
	}
	bool ThisClass::operator<=(const ThisClass& source) const
	{
		return _code <= source._code;
	}
	bool ThisClass::operator>(const ThisClass& source) const
	{
		return _code > source._code;
	}
	bool ThisClass::operator>=(const ThisClass& source) const
	{
		return _code >= source._code;
	}	
	ThisClass ThisClass::_createCode(const ThisClass& source, type_code new_code) const
	{
		NECodeType type;
		if (getCodeType() == source.getCodeType())
			type = *this;

		return ThisClass(new_code, NECodeType(type.getCodeType(), type.isTypeFixed()));
	}

	ThisClass ThisClass::operator+(const ThisClass& source) const
	{
		return _createCode(source, getCode() + source.getCode());
	}
	ThisClass ThisClass::operator-(const ThisClass& source) const
	{
		return _createCode(source, getCode() - source.getCode());
	}
	ThisClass ThisClass::operator*(const ThisClass& source) const
	{
		return _createCode(source, getCode() * source.getCode());
	}
	ThisClass ThisClass::operator/(const ThisClass& source) const
	{
		return _createCode(source, getCode() / source.getCode());
	}
	ThisClass ThisClass::operator%(const ThisClass& source) const
	{
		return _createCode(source, getCode() % source.getCode());
	}
	ThisClass& ThisClass::operator+=(const ThisClass& source)
	{
		_code += source._code;

		return *this;
	}
	ThisClass& ThisClass::operator-=(const ThisClass& source)
	{
		_code -= source._code;

		return *this;
	}
	ThisClass& ThisClass::operator*=(const ThisClass& source)
	{
		_code *= source._code;

		return *this;
	}
	ThisClass& ThisClass::operator/=(const ThisClass& source)
	{
		_code /= source._code;

		return *this;
	}
	ThisClass& ThisClass::operator%=(const ThisClass& source)
	{
		_code %= source._code;

		return *this;
	}
	type_code ThisClass::getCode() const
	{
		return _code;
	}
	type_result ThisClass::setCode(type_code new_code)
	{		
		_code = new_code;

		return RESULT_SUCCESS;
	}

	type_result ThisClass::setCode(const NEExportable::Identifier& identifier)
	{
		const NEModule& fetched = Kernal::getInstance().getModuleManager().getModule(identifier);
		if (!&fetched)
		{
			KERNAL_ERROR("주어진 Identifier로 모듈을 가져오지 못했습니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}

		return setCode(fetched.getScriptCode());
	}

	void ThisClass::release()
	{
		SuperClass::release();

		_code = NE_INDEX_ERROR;		
	}

	NEBinaryFileSaver& ThisClass::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		if(getCodeType() == NECodeType::MODULE_SCRIPT)
			return _serializeAsScript(saver);

		return saver << _code;
	}

	NEBinaryFileSaver& ThisClass::_serializeAsScript(NEBinaryFileSaver& saver) const
	{
		const NEPackageManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModule& m = moduler.getModuleSet()[_code];
		if( ! &m)
			return saver << false;

		saver << true;
		return m.getHeader().NEExportable::Identifier::serialize(saver);
	}

	NEBinaryFileLoader& ThisClass::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		if(getCodeType() == NECodeType::MODULE_SCRIPT)
			return _serializeAsScript(loader);

		return loader >> _code;
	}
	NEBinaryFileLoader& ThisClass::_serializeAsScript(NEBinaryFileLoader& loader)
	{
		bool is_module_info_saved = false;
		loader >> is_module_info_saved;
		if( ! is_module_info_saved)
			return loader;


		//	main:
		const NEPackageManager& moduler = Kernal::getInstance().getModuleManager();
		NEExportable::Identifier identifier;
		loader >> identifier;
		const NEModule& module = moduler.getModule(identifier);
		_code = &module ? module.getScriptCode() : -1;

		return loader;
	}

	type_result ThisClass::isValid() const
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result)) return result;
		if(_code < 0) return RESULT_TYPE_WARNING;		

		return RESULT_SUCCESS;
	}

	void ThisClass::_release()
	{
		_code = NE_DEFAULT;
	}
}