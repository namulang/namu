#include "NECode.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"
#undef max
#include <limits>
using namespace std;

namespace NE
{
	typedef NECode ThisClass;

	const NEScriptHeader& _defaultScriptHeaderInterface()
	{
		const NEScriptHeader* nullpointer = 0x00;
		NEScriptManager& sm = Kernal::getInstance().getScriptManager();
		if (!&sm)
			return *nullpointer;

		return sm.getScriptHeader();
	}

	NECode::GET_SCRIPTHEADER_INTERFACE NECode::_interface = _defaultScriptHeaderInterface;

	type_result ThisClass::setIfValid(const ThisClass& source)
	{
		if( ! isAcceptable(source.getCodeType())) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

		return setCode(source.getCode());
	}
	NECode::NECode(type_code new_code)
		: SuperClass(), _codetype(NECodeType::UNDEFINED)
	{
		setCode(new_code);
	}
	NECode::NECode(NECodeType::CodeType new_codetype, type_code new_code)
		: SuperClass(), _codetype(new_codetype)
	{
		setCode(new_code);
	}
	NECode::NECode(const ThisClass& source)
		: SuperClass(source)
	{
		_assign(source);
	}

	NECode NECode::operator++()
	{
		NECode to_return(*this);

		setCode(getCode() + 1);

		return to_return;
	}

	NECode& NECode::operator++(int)
	{
		setCode(getCode() + 1);

		return *this;
	}

	NECode& NECode::operator--(int)
	{
		setCode(getCode() + 1);

		return *this;
	}

	NECode NECode::operator--()
	{
		NECode to_return(*this);

		setCode(getCode() - 1);

		return to_return;
	}

	NECode::operator type_code()
	{
		return _code;
	}

	ThisClass::~ThisClass()
	{

	}
	bool ThisClass::isAcceptable(NECodeType::CodeType codetype) const
	{
		if (codetype == NECodeType::UNDEFINED ||
			_codetype == NECodeType::UNDEFINED)
			return true;

		return _codetype == codetype;
	}
	ThisClass& ThisClass::operator=(const ThisClass& source)
	{
		if (this == &source) return *this;

		return _assign(source);
	}
	ThisClass& ThisClass::_assign(const ThisClass& source)
	{
		if (source._codetype != NECodeType::UNDEFINED)
			_codetype = source._codetype;
		_code = source._code;

		return *this;
	}
	bool ThisClass::operator==(const ThisClass& source) const
	{
		return	_codetype == source._codetype	&&
			_code == source._code;
	}
	bool ThisClass::operator!=(const ThisClass& source) const
	{
		return !operator==(source);
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
	ThisClass ThisClass::_operateWhenAcceptableByValue(const ThisClass& source, type_code new_code) const
	{
		if ( ! isAcceptable(source.getCodeType()))
			return *this;

		ThisClass to_return(*this);
		to_return.setCode(new_code);

		return to_return;
	}
	ThisClass& ThisClass::_operateWhenAcceptableByReference(const ThisClass& source, type_code new_code)
	{
		if (!isAcceptable(source.getCodeType()))
			return *this;

		setCode(new_code);
		return *this;
	}

	ThisClass ThisClass::operator+(const ThisClass& source) const
	{
		return _operateWhenAcceptableByValue(source, getCode() + source.getCode());
	}
	ThisClass ThisClass::operator-(const ThisClass& source) const
	{
		return _operateWhenAcceptableByValue(source, getCode() - source.getCode());
	}
	ThisClass ThisClass::operator*(const ThisClass& source) const
	{
		return _operateWhenAcceptableByValue(source, getCode() * source.getCode());
	}
	ThisClass ThisClass::operator/(const ThisClass& source) const
	{
		return _operateWhenAcceptableByValue(source, getCode() / source.getCode());
	}
	ThisClass ThisClass::operator%(const ThisClass& source) const
	{
		return _operateWhenAcceptableByValue(source, getCode() % source.getCode());
	}
	ThisClass& ThisClass::operator+=(const ThisClass& source)
	{
		return _operateWhenAcceptableByReference(source, getCode() + source.getCode());
	}
	ThisClass& ThisClass::operator-=(const ThisClass& source)
	{
		return _operateWhenAcceptableByReference(source, getCode() - source.getCode());
	}
	ThisClass& ThisClass::operator*=(const ThisClass& source)
	{
		return _operateWhenAcceptableByReference(source, getCode() * source.getCode());
	}
	ThisClass& ThisClass::operator/=(const ThisClass& source)
	{
		return _operateWhenAcceptableByReference(source, getCode() / source.getCode());
	}
	ThisClass& ThisClass::operator%=(const ThisClass& source)
	{
		return _operateWhenAcceptableByReference(source, getCode() % source.getCode());
	}
	NECodeType::CodeType ThisClass::getCodeType() const
	{
		return _codetype;
	}
	type_result ThisClass::setCodeType(NECodeType::CodeType new_codetype)
	{
		_codetype = new_codetype;

		return setCode(getCode());
	}
	type_code ThisClass::getCode() const
	{
		return _code;
	}
	type_code ThisClass::_getMaxCode() const
	{
		const NEScriptHeader& sh = _interface();
		if (!&sh)
			return NE_INDEX_ERROR;

		type_code max_code = 0;
		switch (_codetype)
		{
		case NECodeType::SCRIPT:	return sh.getMaxScriptCodeIndex();				break;
		case NECodeType::NAME:		return sh.getMaxNameCodeIndex();				break;
		case NECodeType::GROUP:		return sh.getMaxGroupCodeIndex();				break;
		case NECodeType::PRIORITY:	return sh.getMaxPriorityCodeIndex();			break;
		case NECodeType::UNDEFINED:	return (type_code) numeric_limits<int>::max();	break;
		}

		return NE_INDEX_ERROR;
	}
	type_result ThisClass::setCode(type_code new_code)
	{
		type_code max_code = _getMaxCode();
		if(	max_code >= 0		&&
			new_code > max_code	)
			new_code = NE_INDEX_ERROR;

		_code = new_code;
		return RESULT_SUCCESS;
	}

	void ThisClass::release()
	{
		_code = NE_INDEX_ERROR;
		_codetype = NECodeType::UNDEFINED;
	}

	NEObject& ThisClass::clone() const
	{
		return *(new ThisClass(*this));
	}

	NEBinaryFileSaver& ThisClass::serialize(NEBinaryFileSaver& saver) const
	{
		int converted = _codetype;
		saver << converted;
		
		if(_codetype == NECodeType::SCRIPT)
			return _serializeAsScript(saver);

		return saver << _code;
	}

	NEBinaryFileSaver& ThisClass::_serializeAsScript(NEBinaryFileSaver& saver) const
	{
		const NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		const NEModule& m = moduler.getModuleSet()[_code];
		if( ! &m)
			return saver << false;

		saver << true;
		return m.getHeader().NEExportable::Identifier::serialize(saver);
	}

	NEBinaryFileLoader& ThisClass::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		int to_convert = 0;
		loader >> to_convert;
		_codetype = NECodeType::CodeType(to_convert);
		
		if(_codetype == NECodeType::SCRIPT)
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
		const NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
		NEExportable::Identifier identifier;
		loader >> identifier;
		const NEModule& module = moduler.getModule(identifier);
		_code = &module ? module.getScriptCode() : -1;

		return loader;
	}

	type_result ThisClass::isValid() const
	{
		using namespace NECodeType;

		switch(_codetype)
		{
		case GROUP:	case PRIORITY:	case SCRIPT:	case NAME:	case UNDEFINED:
			{
				type_code max_code = _getMaxCode();
				if(	_code > max_code	||
					_code < 0			)
						return RESULT_TYPE_ERROR;
			}	
			break;

		default:
			if(_code != -1)
				return RESULT_TYPE_ERROR;
		}

		return RESULT_SUCCESS;
	}

	NEType::Type ThisClass::getType() const
	{
		return NEType::NECODE;
	}
}