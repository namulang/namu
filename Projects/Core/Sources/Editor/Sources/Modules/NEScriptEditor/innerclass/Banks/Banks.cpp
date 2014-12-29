#include "../../NEScriptEditor.hpp"

namespace NE
{
	const NEBank NE_DLL &NEScriptEditor::Banks::getBank(const NECodeType& type) const
	{
		ThisClass* unconsted = const_cast<ThisClass*>(this);

		return unconsted->getBank(type);
	}

	NEBank NE_DLL &NEScriptEditor::Banks::getBank(const NECodeType& type)
	{
		for (int n = 0; n < getLength(); n++)
			if (getElement(n).getCodeType() == type)
				return getElement(n);

		NEBank* nullpointer = 0x00;
		return *nullpointer;
	}

	NEObject NE_DLL &NEScriptEditor::Banks::clone() const
	{
		return *(new ThisClass(*this));
	}

	NEType::Type NEScriptEditor::Banks::getType() const
	{
		return NEType::NESCRIPTEDITOR_BANKS;
	}

	type_result NEScriptEditor::Banks::initialize()
	{
		type_result result = create(4);

		result |= push(NEBank(NECodeType::SCRIPT));
		result |= push(NEBank(NECodeType::NAME));
		result |= push(NEBank(NECodeType::GROUP));
		return result |= push(NEBank(NECodeType::PRIORITY));
	}
}