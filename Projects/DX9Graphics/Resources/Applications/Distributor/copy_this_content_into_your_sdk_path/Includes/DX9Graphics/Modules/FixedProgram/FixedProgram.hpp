#pragma once

#include "../ShaderProgram/ShaderProgram.hpp"

namespace DX9Graphics
{
	class NE_DLL FixedProgram : public ShaderProgram
	{
	public:
		typedef ShaderProgram SuperClass;
		typedef FixedProgram ThisClass;

	public:
		bool& isInputRenderTarget()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_bool&>(casted->isInputRenderTarget());
		}
		const type_bool& isInputRenderTarget() const
		{
			const NEKey& key = getKeySet()[4];
			if( ! key.isSubClassOf(NEType::NEBOOLEAN_KEY))
			{
				ALERT_ERROR("4번키는 NEBOOLEAN_KEY여야 합니다");
				type_bool* nullpoint = 0;
				return *nullpoint;
			}

			const NEBooleanKey& target = static_cast<const NEBooleanKey&>(key);
			return target.getValue();
		}

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getSize() + 1);
			return keyset.push(NEBooleanKey(false));
		}
		virtual type_result execute() { return RESULT_SUCCESS; }
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual const NEExportable::ModuleHeader& getHeader() const;	

	private:
		virtual type_result _onRender(DX9& dx9, Camera& camera);
		virtual LPCVOID _onRequestShaderCode(OUT type_int& size_of_binary) const { size_of_binary = 0; return 0; }
		virtual type_result _onSetShaderHandles(SuperClass::ShaderHandleSet&) { return RESULT_SUCCESS; }
	};
}