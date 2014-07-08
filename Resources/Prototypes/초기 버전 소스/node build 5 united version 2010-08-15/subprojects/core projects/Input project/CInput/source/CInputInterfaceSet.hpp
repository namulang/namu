#pragma once

#include "define.hpp"

class CInputInterfaceSet
{
public:
	CInputInterfaceSet() : _lable(NULL), _xbox360pad_player_number(NULL)
	{

	}
	CInputInterfaceSet(WORD lable, BYTE joypad_player_number)
	{
		_lable = lable;
		_xbox360pad_player_number = joypad_player_number;
	}
	~CInputInterfaceSet()
	{}
	void	setLable(WORD label)
	{
		_lable = label;
	}
	WORD	getLabel()
	{
		return _lable;
	}
	BYTE	getJoypadPlayer()
	{
		return _xbox360pad_player_number;
	}
	void	setJoypadPlayer(BYTE player)
	{
		_xbox360pad_player_number = player;
	}
	CInputInterfaceSet&	operator = (CInputInterfaceSet& rhs)
	{
		_lable = rhs.getLabel();
		_xbox360pad_player_number = rhs.getJoypadPlayer();

		return *this;
	}




private:
	WORD	_lable;
	BYTE	_xbox360pad_player_number; // 1p 조이패드인지, 2p 조이패드인지.
};