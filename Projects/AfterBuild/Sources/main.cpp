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
	cout	<< "AfterBuild. Automatic worldSDK Binary Packager Version 0.0.2a\n"
			<< "Copyrights (c) kniz, 2009-2015\n";

	if(argc != 4)
	{
		cout	<<	"\n"
				<<	"AfterBuild is a program launched after build one of the projects derived WorldSDK. "
				<<	"this program will increase one build count and copy all of those files to \'Binaries\' directory of each projects.\n"
				<<	"\nHistory :\n"
				<<	"\t0.0.2a\t2015-05-08 : function that package Dependencies(what located on './Dependencies/Libraries') has been added.\n"
				<<	"\t0.0.1a\t2013-00-00 : Creation.\n"
				<<	"\nUsage : \n"
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

	{
		TCHAR commandline[512] = { 0, };
		_tcscpy(commandline, _T("xcopy /e /Y /I "));
		_tcscat(commandline, binary_path);
		_tcscat(commandline, _T(" "));
		_tcscat(commandline, destination_path);

		_tsystem(commandline);
	}
	
	{
		TCHAR commandline[512] = { 0, };
		_tcscpy(commandline, _T("xcopy /e /Y /I "));
		_tcscat(commandline, binary_path);
		_tcscat(commandline, _T("\\..\\..\\Dependencies\\Libraries "));
		_tcscat(commandline, destination_path);
		_tcscat(commandline, _T("\\Dependencies"));
	
		_tsystem(commandline);
	}

}