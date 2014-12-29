#pragma once

#include "../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ALU : public NEModule
	{
	public:
		typedef ALU ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEKey> arg_left_operand;
		NETArgument<NEKey> arg_right_operand;
		NETArgument<NEKey> arg_target;
		NETArgument<NEStringKey> arg_method;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("ALU");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = "Key 간의 기본적인 2항 산술연산을 수행합니다.\n"
					"덧셈, 뻴셈, 곱셈, 나눗셈,	나머지연산, n제곱 등을 수행할 수 있습니다.\n"
					"예를들어, \"+\" 인 경우, Target = LeftOperand + RightOperand으로 적용되며,\n"										  
					"\n제곱 \"^\"인 경우, Target = LeftOperand의 RightOperand제곱으로 적용되므로,\n"
					"LightOperand = 10, RightOperand = 2의 경우 Target은 100이 됩니다.\n"
					"물론, Target과 Operand를 같은 키로 할 수도 있습니다. \n"
					"예) Key1 = Key1 + Key2 \n\n"
					"다만 Target이 배열인 경우에는 오동작하므로 주의바랍니다.\n"
					"참고로 \"%\"은 나머지 연산자로써, 10 % 3 은 10을 3으로 나누고 남은 나머지인 1이 나오게 됩니다.";
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("2014-11-27");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(0);
				NETStringSet& args = _header.getArgumentsComments();
				args.create(4);
				args.push("LeftOperand\n연산이 될 대상1 입니다.\n");
				args.push("RightOperand\n연산이 될 대상2 입니다.\n");
				args.push("Target\n결과값이 들어갈 Key입니다.");
				args.push("Operator\nLeftOperand와 RightOperand간의 어떤 연산을 적용할지 적습니다. \n다음의 연산자를 쓸수 있습니다 : \"+\" \"-\", \"*(곱셈)\", \"/\"(나눗셈), \"%\"(나머지연산), \"^\"n제곱, \"<\", \"<=\", \">\", \">=\", \"==\", \"!=\"");
			}

			return _header;
		}		

	protected:
		virtual type_result _onExecute()
		{
			static	NETStringSet opers(12);
			if (opers.getLength() != opers.getSize())
			{
				opers.push("+");	//	idx 0
				opers.push("-");
				opers.push("*");
				opers.push("/");
				opers.push("%");

				opers.push("^");	//	5
				opers.push("<");
				opers.push("<=");
				opers.push(">");
				opers.push(">=");

				opers.push("==");	//	10
				opers.push("!=");
			}

			NEKey	&lkey	= arg_target.getValueKey(),
					&rkey1	= arg_left_operand.getValueKey(),
					&rkey2	= arg_right_operand.getValueKey();

			const NETString& op = arg_method.getValue();
			type_index oper_idx = opers.find(op);

			type_result result = RESULT_SUCCESS;

			switch(oper_idx)
			{
			case 0:		result = rkey1.add(lkey, rkey2);		break;
			case 1:		result = rkey1.sub(lkey, rkey2);		break;
			case 2:		result = rkey1.multiply(lkey, rkey2);	break;
			case 3:		result = rkey1.divide(lkey, rkey2);	break;
			case 4:						
				break;

			case 5:
				{
					NEIntKey count(rkey2);
					type_float	converted = NEFloatKey(rkey2).getValue();
					NEFloatKey calculated = 1.0f;
					for (int n = 1; n <= count.getValue(); n++)
						calculated.getValue() *= converted;

					result = arg_target.getValueKey().assign(calculated);
				}
				break;

			case 6:		result |= _applyLogicOperation(NEBooleanKey(lkey < rkey2));	break;
			case 7:		result |= _applyLogicOperation(NEBooleanKey(lkey <= rkey2));	break;
			case 8:		result |= _applyLogicOperation(NEBooleanKey(lkey > rkey2));	break;
			case 9:		result |= _applyLogicOperation(NEBooleanKey(lkey >= rkey2));	break;
			case 10:	result |= _applyLogicOperation(NEBooleanKey(lkey == rkey2));	break;
			case 11:	result |= _applyLogicOperation(NEBooleanKey(lkey != rkey2));	break;
			}

			return result;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_left_operand);
			tray.push(arg_right_operand);
			tray.push(arg_target);
			tray.push(arg_method);

			return RESULT_SUCCESS;
		}

	private:
		type_result _applyLogicOperation(const NEBooleanKey& result)
		{
			arg_target.getValueKey() = result;

			return result.getValue() ? RESULT_TRUE : RESULT_FALSE;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ALU(*this));
		}
	};
}