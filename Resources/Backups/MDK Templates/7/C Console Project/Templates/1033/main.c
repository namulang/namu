/**********************************************************************
*       Author   : [!output MAIN_AUTHOR_NAME]
*       Created  : [!output MAIN_CREATION_DATE]
*       Modified : [!output MAIN_CREATION_DATE]
*
*       Description :
*         [!output MAIN_PROJECT_DESCRIPTION]
***********************************************************************/


[!if INCLUDE_STDIO_H]
#include <stdio.h>
[!endif]
[!if INCLUDE_STRING_H]
#include <string.h>
[!endif]
[!if INCLUDE_STDLIB_H]
#include <stdlib.h>
[!endif]
[!if INCLUDE_CONIO_H]
#include <conio.h>
[!endif]
[!if INCLUDE_MATH_H]
#include <math.h>
[!endif]
[!if ADD_BOOL_TYPEDEF]


#define TRUE    1
#define FALSE   0

typedef int BOOL;
[!endif]


[!if ADD_ARGV_ARGC]
int main(int argc, char* argv[])
[!else]
int main(void)
[!endif]
{


[!if INCLUDE_CONIO_H]
	system("PAUSE");
[!endif]

	return (1);
}


