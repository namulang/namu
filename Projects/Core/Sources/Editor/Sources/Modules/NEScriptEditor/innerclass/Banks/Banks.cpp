#include "../../NEScriptEditor.hpp"

namespace NE
{
	NE_DLL NEScriptEditor::Banks::Banks()
		: SuperClass()
	{

	}

	NE_DLL NEScriptEditor::Banks::Banks(const ThisClass& source)
		: SuperClass(source)
	{
		//	모두 Banks에서 _assign되는 데이터 뿐이므로 추가적으로 멤버변수 할당이 필요없다
	}

	NE_DLL NEScriptEditor::Banks::~Banks()
	{

	}

	const NEScriptEditor::Banks NE_DLL &NEScriptEditor::Banks::operator=(const ThisClass& source)
	{
		//	SuperClass::operator=(source);를 호출하지 않는다. 같은 작업을 virtual
		//	을 사용하지 않고 사용한다.

		return _assign(source);
	}

	bool NE_DLL NEScriptEditor::Banks::operator==(const ThisClass& source) const
	{
		if(this == &source) return true;
		if(_name_bank != source._name_bank) return false;
		if(_script_bank != source._script_bank) return false;
		if(_group_bank != source._group_bank) return false;
		if(_priority_bank != source._priority_bank) return false;

		return true;
	}

	bool NE_DLL NEScriptEditor::Banks::operator!=(const ThisClass& source) const
	{
		return !(operator==(source));
	}

	const NETStringList NE_DLL &NEScriptEditor::Banks::getScriptBank() const
	{
		return _script_bank;
	}

	const NETStringList NE_DLL &NEScriptEditor::Banks::getNameBank() const
	{
		return _name_bank;
	}

	const NETStringList NE_DLL &NEScriptEditor::Banks::getGroupBank() const
	{
		return _group_bank;
	}

	const NETStringList NE_DLL &NEScriptEditor::Banks::getPriorityBank() const
	{
		return _priority_bank;
	}

	NETStringList NE_DLL &NEScriptEditor::Banks::getScriptBank()
	{
		return _script_bank;
	}

	NETStringList NE_DLL &NEScriptEditor::Banks::getNameBank()
	{
		return _name_bank;
	}

	NETStringList NE_DLL &NEScriptEditor::Banks::getGroupBank()
	{
		return _group_bank;
	}

	NETStringList NE_DLL &NEScriptEditor::Banks::getPriorityBank()
	{
		return _priority_bank;
	}

	void NE_DLL NEScriptEditor::Banks::release()
	{
		_script_bank.release();
		_name_bank.release();
		_group_bank.release();
		_priority_bank.release();
	}

	type_result NE_DLL NEScriptEditor::Banks::isValid() const
	{
		type_result result = _script_bank.isValid();
		if(NEResult::hasError(result)) return result;
		result = _name_bank.isValid();
		if(NEResult::hasError(result)) return result;
		result = _group_bank.isValid();
		if(NEResult::hasError(result)) return result;
		result = _priority_bank.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &NEScriptEditor::Banks::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _script_bank << _name_bank << _group_bank << _priority_bank;
	}

	NEBinaryFileLoader NE_DLL &NEScriptEditor::Banks::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _script_bank >> _name_bank >> _group_bank >> _priority_bank;
	}

	NEObject NE_DLL &NEScriptEditor::Banks::clone() const
	{
		return *(new ThisClass(*this));
	}

	const NEScriptEditor::Banks NE_DLL &NEScriptEditor::Banks::_assign(const ThisClass& source)
	{
		if(this == &source) return *this;

		_script_bank = source._script_bank;
		_name_bank = source._name_bank;
		_group_bank = source._group_bank;
		_priority_bank = source._priority_bank;

		return *this;
	}

	NEType::Type NEScriptEditor::Banks::getType() const
	{
		return NEType::NESCRIPTEDITOR_BANKS;
	}
}