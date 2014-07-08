#include <Windows.h>
#include <tchar.h>
#include <string.h>
#include "cartridge_define.hpp"
#include <atlstr.h> // CString을 API에서 사용하기위해

class CCartridgeUnit
{
public:
	CCartridgeUnit() :_start_point(0), _filename(_T("")), _file_size(0), _path(_T(""))
	{

	}
	~CCartridgeUnit()
	{
		clear();
	}
	//	연산자:
	CCartridgeUnit&	operator = (CCartridgeUnit& rhs)
	{
		_start_point = rhs._start_point;
		_filename = rhs._filename;
		_file_size = rhs._file_size;
		_path = rhs._path;
	}
	//	접근자:
	void	setStartPoint(__int64 start_point)
	{
		_start_point = start_point;
	}
	//	일반함수:
	void	clear()
	{
		_start_point = 0;
		_filename = _T("");
		_file_size = 0;
	}
	void	loadHeader(CString target)
	{

	}
	void	saveHeader()
	{

	}
	void	save()
	{

	}

public:	
	__int64	_start_point;
	CString	_filename; // 파일이름만
	CString	_path;
	__int64	_file_size;
};