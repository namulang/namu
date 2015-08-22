
#pragma once

#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <iomanip>
#include <Windows.h>

#include "../../Includes/Includes.hpp"

extern bool opt_show_frame;

class TestCase
{
public:
	enum COLOR
	{		
		BLACK=0, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE, UNKNOWN
	};

	TestCase(const NE::NEString& name)
		: _name(name) {}
	void TestCase::test()
	{
		unsigned int prev = _getTime();
		bool result = onTest();
		_printResult(result, _getTime() - prev);
	}
	virtual bool onTest() = 0;
	const NE::NEString& getName() const
	{
		return _name;
	}
	NE::NEString& getName()
	{
		return _name;
	}

private:
	virtual void _printResult(bool is_success, int process_time) const
	{
		using namespace std;
		using namespace NE;

		if(is_success)
			_setColor(LIGHTGREEN, BLACK);
		else
			_setColor(RED, BLACK);
		NEString result = is_success ? "Success" : "Failure";

		NEDebugManager& dm = Kernal::getInstance().getDebugManager();

		if(opt_show_frame)
		{
			dm.printConsole("[ " + result + " : ");
			cout.width(6); cout.fill(' ');
			dm.printConsole(process_time);
			dm.printConsole("ms ] ");
		}	

		_setColor(LIGHTGRAY, BLACK);
		dm.printConsole(getName() + "\n");

	}
	unsigned int _getTime()
	{
		bool _is_once = false;
		if( ! _is_once)
			timeBeginPeriod(1);

		return timeGetTime();
	}
	void _setColor(int tcolor, int bcolor) const
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bcolor << 4 | tcolor);
	}

private:
	NE::NEString _name;
};