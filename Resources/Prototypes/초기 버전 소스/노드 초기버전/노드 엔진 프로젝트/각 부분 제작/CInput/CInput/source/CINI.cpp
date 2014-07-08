#include "CINI.hpp"
#include "CInputNodeSample.hpp"
CINI	g_ini;

	//	생성자:
CINI::CINI() : _window_activate(true)
{
	// #인풋프리셋#추가#
	_sample	= new CInputNodeSample();
	_sample->intializeToXbox360Pad(); // #작업# 사실은, 여기서 파일로부터 serialize함.

	setAnalogstickDeadzone(DEFAULT_CINPUTCONSOLEXBOX360PAD_ANALOGSTICK_DEADZONE);
	setAnalogstickMaxDeadzone(DEFAULT_CINPUTCONSOLEXBOX360PAD_ANALOGSTICK_MAX_DEADZONE);
	setAnalogstickToButtonDeadzone(DEFAULT_CINPUTCONSOLEXBOX360PAD_ANALOGSTICK_TO_BUTTON_DEADZONE);
	setTriggerDeadzone(DEFAULT_CINPUTCONSOLEXBOX360PAD_TRIGGER_DEADZONE);
	setTriggerToButtonDeadzone(DEFAULT_CINPUTCONSOLEXBOX360PAD_TRIGGER_TO_BUTTON_DEADZONE);
}
	//	소멸자:
CINI::~CINI()
{
	delete _sample;
	_sample = NULL;
}
