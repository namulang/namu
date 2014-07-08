@echo off
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo * Distributor For Developer
echo * 	version 0.0.1
echo *	copyright 2012 @ haku All rights reserved.
echo *	Tested by Windows 7
echo *
echo *	this batch program will process to make a distributable package for 
echo *	developers.
echo *	Include and library files will be attached to your module package.
echo *	The Items below will be included when finished.
echo *		Header files 
echo *			from '../../../Sources' 
echo *			to './copy_this_content_into_your_sdk_path/Includes/ProjectName'
echo *		Library files 
echo *			from '../../../Binaries' 
echo *			to './copy_this_content_into_your_sdk_path/Libraries/Modules'
echo *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
pause

:QueryingProjectName
echo *
echo *
set /p project_name=* Enter your project name : 
echo *
echo * Header files : ./copy_this_content_into_your_sdk_path/Includes/%project_name%
echo * Library files : ./copy_this_content_into_your_sdk_path/Libraries/Modules
set /p answer=* Is it fine to go next step? (y/n) :
if %answer% == n goto QueryingProjectName


echo *
echo *
echo * Cleaning folders to make a new distributable package.

rd /Q copy_this_content_into_your_sdk_path

echo * worked.
echo *
echo *
pause


:MakingStubDirectories
echo * Making a stub directories.

md copy_this_content_into_your_sdk_path
md copy_this_content_into_your_sdk_path\Includes
md copy_this_content_into_your_sdk_path\Includes\%project_name%
md copy_this_content_into_your_sdk_path\Libraries
md copy_this_content_into_your_sdk_path\Libraries\Modules

echo * worked.
echo *
echo *
pause


:CopyingFiles
echo * Copying Files.
echo * Copying headers from '../../../Sources' to './copy_this_content_into_your_sdk_path/Includes/%project_name%'

xcopy /Y /E ..\..\..\Sources .\copy_this_content_into_your_sdk_path\Includes\%project_name%
xcopy /Y /E ..\..\..\Binaries .\copy_this_content_into_your_sdk_path\Libraries\Modules

echo * worked.
echo *
echo *
pause


:RemovingImplementFiles
echo * Removing implement files in 'Libraries'. (*.cpp, *.c, *.cxx)

del /s .\copy_this_content_into_your_sdk_path\Includes\%project_name%\*.cpp
del /s .\copy_this_content_into_your_sdk_path\Includes\%project_name%\*.c
del /s .\copy_this_content_into_your_sdk_path\Includes\%project_name%\*.cxx

echo * worked.
echo *
echo *
pause


:Finishing
echo * Your project has been converted to distributable package successfully!
echo * Just check out .\copy_this_content_into_your_sdk_path.
pause