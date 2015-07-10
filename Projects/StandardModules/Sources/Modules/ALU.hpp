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
		NETArgument<NEFloatKey> arg_left_operand;
		NETArgument<NEFloatKey> arg_right_operand;
		NETArgument<NEFloatKey> arg_target;
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
					"참고로 \"%\"은 나머지 연산자로써, 10 % 3 은 10을 3으로 나누고 남은 나머지인 1이 나오게 됩니다.\n"
					"단항 연산인 =와 = ! 도 사용이 가능합니다.";
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("2014-11-27");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(0);
				NETStringSet& args = _header.getArgumentsComments();
				args.create(4);
				args.push("LeftOperand\n연산이 될 대상1 입니다.\n");
				args.push("RightOperand\n연산이 될 대상2 입니다.\n");
				args.push("Target\n결과값이 들어갈 Key입니다.");
				args.push("Operator(연산자)\n사용가능한 연산자 : \"+\" \"-\", \"*(곱셈)\", \"/\"(나눗셈), \"%\"(나머지연산), \"^\"n제곱, \"<\", \"<=\", \">\", \">=\", \"==\", \"!=\", \"=\", \"= !\"");
			}

			return _header;
		}		

	protected:
		virtual type_result _onExecute()
		{
			static	NETStringSet opers(14);
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
				opers.push("=");
				opers.push("= !");
			}

			type_float	loperand = arg_left_operand.getValue(),
				roperand = arg_right_operand.getValue();

			const NETString& op = arg_method.getValue();
			type_index oper_idx = opers.find(op);

			type_result result = RESULT_SUCCESS;

			switch(oper_idx)
			{
			case 0:		arg_target.setValue(loperand + roperand);		break;
			case 1:		arg_target.setValue(loperand - roperand);		break;
			case 2:		arg_target.setValue(loperand * roperand);		break;
			case 3:		arg_target.setValue(loperand / roperand);		break;
			case 4:		arg_target.setValue((float)((int) loperand % (int) roperand));		break;
			case 5:
				{
					type_float calculator = 1.0f;
					for (int n = 0; n <= roperand ;n++)
						calculator *= loperand;
					arg_target.setValue(calculator);
				}
				break;

			case 6:		arg_target.setValue(loperand < roperand);		break;
			case 7:		arg_target.setValue(loperand <= roperand);	break;
			case 8:		arg_target.setValue(loperand > roperand);		break;
			case 9:		arg_target.setValue(loperand >= roperand);	break;
			case 10:	arg_target.setValue(loperand == roperand);	break;
			case 11:	arg_target.setValue(loperand != roperand);	break;
			case 12:	
				arg_left_operand.getKey() = arg_right_operand.getKey();
				arg_target.getKey() = arg_right_operand.getKey();
				break;

			case 13:
				arg_left_operand.setValue( ! roperand);
				arg_target.setValue( ! roperand);
			}

			if(arg_target.getValue() == 0.0f)
				return RESULT_SUCCESS | RESULT_FALSE;

			return RESULT_SUCCESS | RESULT_TRUE;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_left_operand);
			tray.push(arg_right_operand);
			tray.push(arg_target);
			tray.push(arg_method);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchModule()
		{
			return arg_method.setPurposeLimitation(NEArgumentBase::READ_BY);			
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ALU(*this));
		}
	};
}