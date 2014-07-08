#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>
using std::cout;

/*
	AfterBuild.exe	
*/
void _tmain(int argc, TCHAR** argv)
{
	if(argc != 4)
	{
		cout	<<	"AfterBuild is a program launched after build one of the projects derived NodeEngine(Not Certified) SDK.\n"
				<<	"this program will increase one build count and copy all of the files in \'Binaries\' directory of each projects.\n\n"
				<<	"Usage : \n"
				<<	"\tAfterBuild.exe <ini path> <binary path> <the path to be copied>\n";
		return;
	}



	//	main:
	const int MAX_SIZE = 256;
	LPCTSTR	ini_path = argv[1],
			binary_path = argv[2],
			destination_path = argv[3];
	
	TCHAR buffer[256] = {0, };
	GetPrivateProfileString(_T("Version"), _T("BuildNo"), NULL, buffer, 256, ini_path);
	
	int build_count = _tstoi(buffer) + 1;
	_itot(build_count, buffer, 10);

	WritePrivateProfileString(_T("Version"), _T("BuildNo"), buffer, ini_path);
		
	TCHAR commandline[256] = {0, };
	_tcscpy(commandline, _T("xcopy /e /Y /I "));
	_tcscat(commandline, binary_path);
	_tcscat(commandline, _T(" "));
	_tcscat(commandline, destination_path);

	_tsystem(commandline);
}