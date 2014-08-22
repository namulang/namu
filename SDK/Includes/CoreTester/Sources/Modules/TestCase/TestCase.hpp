#pragma once

#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <iomanip>
#include <Windows.h>

#include "../../Includes/Includes.hpp"



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

		cout	<< "[ " << result.toCharPointer() << " : ";
		cout.width(6); cout.fill(' ');
		cout	<< process_time;
		cout	<< "ms ] ";

		_setColor(LIGHTGRAY, BLACK);
		cout	<< getName().toCharPointer() << endl;

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