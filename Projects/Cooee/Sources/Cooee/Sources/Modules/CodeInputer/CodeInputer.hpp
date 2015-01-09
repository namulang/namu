#pragma once

#include "../../Includes/Includes.hpp"

class CodeInputer : public LG::InputWindow
{
public:
	virtual NEObject& clone() const { return *(new CodeInputer(*this)); }
	CodeInputer(NECode& target) 
		: LG::InputWindow("새로 추가할 CODE를 입력하세요.", BLACK, WHITE),
		_target(target)
	{

	}

	//	성공시 true 반환
	bool pushHistoryWithBank()
	{
		NEBank& bank = Editor::getInstance().getScriptEditor().getBanks().getBank(_target);
		if (!&bank)
			return false;

		NETString& name = bank[_target.getCode()];
		if (!&name)
		{
			text = "잘못된 뱅크 인덱스입니다. 에러.";
			return true;
		}

		input.history.release();
		for (NETStringList::Iterator* e = bank.getIterator(0); e; e = e->getNext())
			input.history.push(e->getValue());

		input.history_idx = _target.getCode();

		return true;
	}

	bool pushHistoryWithScriptSet()
	{
		if(_target.getCodeType() != NECodeType::MODULE_SCRIPT) return false;
		const NEModuleSet& ms = Kernal::getInstance().getModuleManager().getModuleSet();

		input.history.release();
		for (int n = 0; n < ms.getLength(); n++)
			input.history.push(ms[n].getHeader().getName());		

		return true;
	}

	virtual void onFocused()
	{
		if( ! pushHistoryWithBank())
			if( ! pushHistoryWithScriptSet())
				if (_target == NECodeType::MODULE_NAME)
					text = "MODULE_NAME 의 Code를 입력하세요.";
				else
					text = "알 수 없는 Code값 혹은 Type 입니다.";

		input.history_idx = _target.getCode() > input.history.getLengthLastIndex() ? input.history.getLengthLastIndex() : _target.getCode();
	}
	virtual void onUpdateData()
	{
		NEString& history = input.history[input.history_idx];
		if (&history)
			input.text = history;
	}

	virtual void onInputed()
	{
		int code = input.history_idx;
		if (code == -1)
			code = input.text.toInt();
		_target.setCode(code);

		delete_me = true;
	}

private:
	NECode& _target;
};