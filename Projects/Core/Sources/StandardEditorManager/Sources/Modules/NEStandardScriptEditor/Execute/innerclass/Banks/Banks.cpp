#include "../../NEStandardScriptEditor.hpp"

namespace NE
{
	typedef class NE_DLL NEStandardScriptEditor::Banks ThisScope;

	type_result ThisScope::initialize()
	{
		type_result result = SuperClass::initialize();

		result |= resize(getLength() + 1);
		return push(NEBank(NECodeType::MODULE_NAME));
	}
	NEObject NE_DLL &ThisScope::clone() const 
	{
		return *(new ThisClass(*this));
	}
}