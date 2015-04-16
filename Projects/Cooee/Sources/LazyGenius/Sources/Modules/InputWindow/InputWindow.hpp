#pragma once 

#include "../Window/Window.hpp"
#include "../TextGliph/TextGliph.hpp"

namespace LG
{
	class NE_DLL InputWindow : public Window
	{
	public:
		typedef type_ushort u;

		class NE_DLL InputBox : public TextGliph
		{
		public:
			InputBox(u fore, u back) : TextGliph(0, 25, 15, 30, 1, back, fore) {}
			InputBox(const InputBox& rhs) : TextGliph(rhs) {}
			FUNC_CLONE(InputBox)
			FUNC_TO_OWNER(InputWindow)

			virtual void onKeyPressed(int inputed);
		};

		InputWindow(const NEString& new_text, u fore, u back, const NEString& default_input_text = "")
			: Window(20, 12, 40, 5, fore, back, new_text), input(fore, back) 
		{ 
			if(default_input_text != "")
			{
				input.history.push(default_input_text);
				input.history_idx = 1;
				input.text = default_input_text;
			}
			
			regist(1, &input);
		}
		InputWindow(const InputWindow& rhs) : Window(rhs), input(rhs.input) { regist(1, &input); }

		virtual void onInputed() = 0;

		InputBox input;
	};
}