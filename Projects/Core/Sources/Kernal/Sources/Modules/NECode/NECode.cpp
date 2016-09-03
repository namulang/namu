#include "NECode.hpp"
#include "../Kernal/Kernal.hpp"
#undef max
#include <limits>
using namespace std;

namespace NE
{
	typedef NECode This;

	NECode::NECode()
		: Super()
	{
		_release();
	}

	NECode::NECode(const NEIdentifier& identifier)
		: Super(NECodeType::MODULE_SCRIPT, true)
	{
		setCode(identifier);
	}

	NECode::NECode(const This& source)
		: Super(source)
	{
		_assign(source);
	}

	NECode::NECode(type_code new_code, const NECodeType& codetype /*= NECodeType()*/)
		: Super(codetype)
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

	type_bool NECode::operator==(const type_code source) const
	{
		return getCode() == source;
	}

	type_bool NECode::operator!=(const type_code source) const
	{
		return ! operator==(source);
	}

	This::~This()
	{

	}
	This& This::operator=(const This& source)
	{
		if(this == &source) return *this;
		if( ! isAcceptableType(source))
			return *this;	//	N / A 케이스

		Super::operator=(source);

		return _assign(source);
	}
	This& This::_assign(const This& source)
	{
		setCode(source.getCode());

		return *this;
	}
	type_bool This::operator==(const This& source) const
	{
		return	Super::operator==(source) && _code == source._code;
	}
	type_bool This::operator!=(const This& source) const
	{
		return ! operator==(source);
	}
	type_bool This::operator<(const This& source) const
	{
		return _code < source._code;
	}
	type_bool This::operator<=(const This& source) const
	{
		return _code <= source._code;
	}
	type_bool This::operator>(const This& source) const
	{
		return _code > source._code;
	}
	type_bool This::operator>=(const This& source) const
	{
		return _code >= source._code;
	}	
	This This::_createCode(const This& source, type_code new_code) const
	{
		NECodeType type;
		if (getCodeType() == source.getCodeType())
			type = *this;

		return This(new_code, NECodeType(type.getCodeType(), type.isTypeFixed()));
	}

	This This::operator+(const This& source) const
	{
		return _createCode(source, getCode() + source.getCode());
	}
	This This::operator-(const This& source) const
	{
		return _createCode(source, getCode() - source.getCode());
	}
	This This::operator*(const This& source) const
	{
		return _createCode(source, getCode() * source.getCode());
	}
	This This::operator/(const This& source) const
	{
		return _createCode(source, getCode() / source.getCode());
	}
	This This::operator%(const This& source) const
	{
		return _createCode(source, getCode() % source.getCode());
	}
	This& This::operator+=(const This& source)
	{
		_code += source._code;

		return *this;
	}
	This& This::operator-=(const This& source)
	{
		_code -= source._code;

		return *this;
	}
	This& This::operator*=(const This& source)
	{
		_code *= source._code;

		return *this;
	}
	This& This::operator/=(const This& source)
	{
		_code /= source._code;

		return *this;
	}
	This& This::operator%=(const This& source)
	{
		_code %= source._code;

		return *this;
	}
	type_code This::getCode() const
	{
		return _code;
	}
	type_result This::setCode(type_code new_code)
	{		
		_code = new_code;

		return RESULT_SUCCESS;
	}

	type_result This::setCode(const NEIdentifier& identifier)
	{
		const NEModule& fetched = Kernal::getInstance().getModuleManager().getClasses().match(identifier);
		if (!&fetched)
		{
			KERNAL_ERROR("주어진 Identifier로 모듈을 가져오지 못했습니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}

		return setCode(fetched.getScriptCode());
	}

	void This::release()
	{
		Super::release();

		_code = NE_INDEX_ERROR;		
	}

	NEBinaryFileSaver& This::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		if(getCodeType() == NECodeType::MODULE_SCRIPT)
			return _serializeAsScript(saver);

		return saver << _code;
	}

	NEBinaryFileSaver& This::_serializeAsScript(NEBinaryFileSaver& saver) const
	{
		const NEPackageManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModule& m = moduler.getModuleSet()[_code];
		if( ! &m)
			return saver << false;

		saver << true;
		return m.getHeader().NEIdentifier::serialize(saver);
	}

	NEBinaryFileLoader& This::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		if(getCodeType() == NECodeType::MODULE_SCRIPT)
			return _serializeAsScript(loader);

		return loader >> _code;
	}
	NEBinaryFileLoader& This::_serializeAsScript(NEBinaryFileLoader& loader)
	{
		type_bool is_module_info_saved = false;
		loader >> is_module_info_saved;
		if( ! is_module_info_saved)
			return loader;


		//	main:
		const NEPackageManager& moduler = Kernal::getInstance().getModuleManager();
		NEIdentifier identifier;
		loader >> identifier;
		const NEModule& module = moduler.getClasses().match(identifier);
		_code = &module ? module.getScriptCode() : -1;

		return loader;
	}

	type_result This::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;
		if(_code < 0) return RESULT_TYPE_WARNING;		

		return RESULT_SUCCESS;
	}

	void This::_release()
	{
		_code = NE_DEFAULT;
	}
}