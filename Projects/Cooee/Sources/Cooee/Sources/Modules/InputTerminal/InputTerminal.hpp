#pragma once

#include "../Terminal/Terminal.hpp"

class InputTerminal : public Terminal
{
public:
	InputTerminal(const NEString& new_path, const NEString& new_text, NEType::Type type_to_valid) 
		: Terminal(new_path, type_to_valid, 20, 10, 40, 5, BLACK, LIGHTGRAY),
		textbox(0, 25, 13, 30, 1, WHITE, BLACK), key_pressed(false)
	{
		text = new_text;
		regist(1, &textbox);
	}
	InputTerminal(const InputTerminal& rhs) : Terminal(rhs), textbox(rhs.textbox), key_pressed(false) { regist(1, &textbox); }
	
	virtual void onTextInputed() = 0;

	virtual void onKeyPressed(int inputed) {
		if(inputed == ENTER)
		{
			delete_me = true;
			onTextInputed();
		}
		else if(inputed == BACKSPACE && ! key_pressed)
		{
			textbox.makeToHistory();
			textbox.text = "";
		}
		key_pressed = true;

		Terminal::onKeyPressed(inputed); // 여기에서 InputDialog의 모든 gliph가 동작됨
	}

	TextGliph textbox;
	bool key_pressed;
};