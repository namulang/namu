#pragma once

#include "../ShaderHandle/ShaderHandle.hpp"

namespace DX9Graphics
{
	template
	class NE_DLL NETArray<ShaderHandle>;

	class ShaderHandleSet : public NETArray<ShaderHandle>
	{
	public:
		typedef ShaderHandleSet ThisClass;
		typedef NETArray<ShaderHandle> SuperClass;

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual type_result isValid() const
		{
			type_result result = SuperClass::isValid();
			if (NEResult::hasError(result)) return result;


			//	main:
			for (int n = 0; n < getSize(); n++)
			{
				type_result result = getElement(n).isValid();
				if (NEResult::hasError(result))
					return result;
			}

			return RESULT_SUCCESS;
		}

	public:
		D3DXHANDLE getHandleBy(const NETString& name)
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<D3DXHANDLE>(casted->getHandleBy(name));
		}
		const D3DXHANDLE getHandleBy(const NETString& name) const
		{
			for (int n = 0; n < getSize(); n++)
			{
				const ShaderHandle& elem = getElement(n);
				if (elem.getName() == name)
					return elem.getHandle();
			}

			return 0;
		}
	};
}