#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL BinaryALU : public NEModule
	{
	public:
		typedef BinaryALU ThisClass;
		typedef NEModule SuperClass;

	public:
		NETArgument<NEKey> left_operand;
		NETArgument<NEKey> right_operand;
		NETArgument<NEKey> target;
		NETArgument<NEIntKey> method;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("BinaryALU");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = _T("Key 간의 기본적인 2항 산술연산을 수행합니다.\n\
										  덧셈(0), 뻴셈(1), 곱셈(2), 나눗셈(3),	나머지연산(4), n제곱(5) 등을 수행할 수 있습니다.\n\
										  \"+\" 인 경우, Target = LeftOperand + RightOperand으로 적용됩니다.\n\
										  \n제곱 \"^\"인 경우, Target = LeftOperand의 RightOperand제곱으로 적용되므로,\n\
										  LightOperand = 10, RightOperand = 2의 경우 Target은 100이 됩니다.\n\
										  물론, Target과 Operand를 같은 키로 할 수도 있습니다. \n\
										  예) Key1 = Key1 + Key2 \n\
										  다만 Target이 배열인 경우에는 제대로 동작하지므로 주의바랍니다.");
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("2014-11-27");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(0);
				NETStringSet& args = _header.getArgumentsComments();
				args.create(4);
				args.push("LeftOperand\n연산이 될 대상1 입니다.\n");
				args.push("RightOperand\n연산이 될 대상2 입니다.\n");
				args.push("Target\n결과값이 들어갈 Key입니다.");
				args.push("Operator\LeftOperand와 RightOperand간의 어떤 연산을 적용할지 숫자로 정해줍니다. \n(0: 덧셈(+), 1: 뻴셈(-), 2: 곱셈(*), 3: 나눗셈(/), 4: 나머지(%), 5: n제곱(^), 6: <, 7: <=, 8: >, 9: >=, 10: ==, 11: !=");
			}

			return _header;
		}		

	protected:
		virtual type_result _onExecute()
		{
			const type_float _ECLIPSE = 0.000000001f;
			type_float	lvalue = left_operand.getValue(),
				rvalue = right_operand.getValue();

			switch (method.getValue())
			{
			case 0:
			default:	target.getValue() = lvalue + rvalue;  break;

			case 1:		target.getValue() = lvalue - rvalue;  break;
			case 2:		target.getValue() = lvalue * rvalue;  break;
			case 3:		
				if (rvalue.getValue() == 0.0f)
					rvalue = _ECLIPSE;
				target.getValue() = lvalue / rvalue; 
				break;

			case 4:		
				if (rvalue.getValue() == 0.0f)
					rvalue = _ECLIPSE;				
				target.getValue() = lvalue % rvalue; 
				break;

			case 5:
				{
					type_float multipled_lvalue = 1;
					for (int n = 1; n <= rvalue; n++)
						multipled_lvalue *= lvalue;

					target.getValue() = multipled_lvalue;
				}
				break;
			}

		}
		virtual type_result _onFetchArgument(NEArgumentInterfaceList& tray)
		{
			tray.push(left_operand);
			tray.push(right_operand);
			tray.push(target);
			tray.push(method);

			return tray;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new BinaryALU(*this));
		}
	};
}