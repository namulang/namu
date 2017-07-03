echo	.\
@echo	off
echo	*	Node SDK Builder 
echo	*		ver 0.3.0
echo	*		2015. 09. 28
echo	*		Only windows 7, 8 tested.
echo	*
echo	*		by kniz. 
echo	*
echo	*
echo	*	!IMPORTANT!	:	DO NOT EXECUTE THIS PROGRAM AS ADMINISTER
echo	*
echo	*
echo	*	building sdk by using 'Core' Projects.
echo	*	You must run this after new version of Core solution has been builded.
echo	*	this task takes some minutes till be finished.
echo	*
echo 	*	Updates :
echo	*	0.3.0
echo	*		- Now can choose whether make leave script files or not when build 
echo	*		a sdk.
echo	*
echo	*	0.2.5
echo	*		- will also package script examples.
echo	*	0.2.4
echo	*		- solved that xcopy can't be called causeof environmental variable(path).
echo	*	0.2.3	2015-04-15
echo	*		- build sdk with some sound resources as contents of sounds.
echo	*	0.2.2	2013-08-14
echo	*		- path problem issue has been solved. (now "" will be added at 
echo	*		  the edge of path)
echo	*	0.2.1
echo	*		- fix to create sub directory which was named "Scripts" in 
echo	*		  Library Directory.
echo	*	0.2.0
echo	*		- Manager packages will be added to ./Modules directory.
echo	*	0.1.0
echo	*		- now pdb files can be attachable with choose.
echo	*		- MDK Templates has been seperated from Includes
echo	*		- some bug was fixed.
echo	*	-----------------------------------------------------
pause

rem add envrionmental variables for xcopy issue.
set Path=%Path%;%SystemRoot%\System32

rem create a temporary folder
set TEMP=.\tmp
rd "%TEMP%" /s /q
md tmp

set target_directory=.\..\..\..\SDK
set source_directory=.\..\..\..\Projects\Core

echo	*	Do you want generate SDK with PDB files?(y/n)
set /p answer="	*	> "
echo	* 	Want not to remove resources("Scripts", "Images" folder) ?(y/n)
set /p isWantingNotToRemoveResources=" *	> "

if %isWantingNotToRemoveResources% == y (
	md %TEMP%\Scripts
	md %TEMP%\Images
	xcopy /s /Q "%target_directory%\Libraries\Scripts\*.script" "%TEMP%\Scripts"
	xcopy /s /Q "%target_directory%\Libraries\Images\*.*" "%TEMP%\Images"
)


echo	*
echo	*
echo	*	Cleaning previous data. . .
echo	*
echo	*

rd "%target_directory%" /s /q
echo	*
echo	*
echo	*	Completed.
echo	*
echo	*
pause

echo	*	Making stub directories.

md "%target_directory%"
md "%target_directory%\Libraries"
md "%target_directory%\Libraries\Sounds"
md "%target_directory%\Libraries\Modules"
md "%target_directory%\Libraries\Modules\Dependencies"
md "%target_directory%\Libraries\Scripts"
md "%target_directory%\Includes"
md "%target_directory%\Templates"
echo	*
echo	*
echo	*	Completed.
echo	*
echo	*
pause

echo	*
echo	*
echo	*	Copying files. . .
echo	*
echo	*

copy /Y "%target_directory%\..\DeveloperGuide.docx" "%target_directory%"
xcopy /e /h /Y /I "%source_directory%\Sources\*.*" "%target_directory%\Includes"
xcopy /e /h /Y /I "%source_directory%\..\..\Resources\SDK base files\*.*" "%target_directory%\Libraries\"
xcopy /e /h /Y /I ".\..\..\..\Projects\MDK\Sources\*.*" "%target_directory%\Templates"
xcopy /h /Y /I "%source_directory%\Binaries\Core\*.*" "%target_directory%\Libraries"
xcopy /h /Y /I "%source_directory%\Binaries\StandardEditorManager" "%target_directory%\Libraries\Modules"
xcopy /h /Y /I "%source_directory%\Binaries\StandardKernalManager" "%target_directory%\Libraries\Modules"

echo	*
echo	*
echo	*	Completed.
echo	*
echo	*
pause

if %isWantingNotToRemoveResources% == y (
echo	*
echo	*
echo	*	Preventing not to remove old resource files. . .
echo	*
echo	*

xcopy /s /Q /Y "%TEMP%\Scripts\*.script" "%target_directory%\Libraries\Scripts\" 
xcopy /s /Q /Y "%TEMP%\Images\*.*" "%target_directory%\Libraries\Images\" 

echo	*
echo	*
echo	*	Completed.
echo	*
echo	*
pause
)


echo	*
echo	*
echo	*	Removing useless files. . .
echo	*
echo	*

del /s "%target_directory%\Includes\*.cpp"
if %answer% == n del /s "%target_directory%\Libraries\*.pdb"

rd "%target_directory%\Resources\Applications\SDKBuilder" /s /q

rd "%TEMP%" /s /q

echo	*
echo	*
echo	*	Completed.
echo	*
echo	*
pause

echo	*
echo	*
echo	*	Completed Building SDK.
echo	*
echo	*
pause