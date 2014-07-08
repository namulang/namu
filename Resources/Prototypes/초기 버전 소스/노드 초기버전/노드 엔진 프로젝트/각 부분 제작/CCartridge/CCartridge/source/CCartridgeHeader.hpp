#include <Windows.h>

class CCartridgeHeader
{
public:
	CCartridgeHeader()
	{
		clearHeader();
	}
	~CCartridgeHeader()
	{

	}
	void	clearHeader()
	{
		_version = 0;
		_valid_code = 0;
		_algorithm_number = 0;
		_compressed = false;
		_unit_start_address = 0;
		_unit_count = 0;
	}
	void	saveHeader()
	{

	}



protected:
	int		_version;
	int		_valid_code;
	BYTE	_algorithm_number;
	bool	_compressed; 
	__int64	_unit_start_address;
	int		_unit_count;
};