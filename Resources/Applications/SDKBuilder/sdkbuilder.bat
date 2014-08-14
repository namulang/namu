
echo	.\
@echo	off
echo	*	Node SDK Builder 
echo	*		ver 0.2.2
echo	*		2013. 08. 14
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
echo	*	0.2.2
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

echo	*	Do you want generate SDK with PDB files?(y/n)
set /p answer="	*	> "

set target_directory=.\..\..\..\SDK
set source_directory=.\..\..\..\Projects\Core
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
md "%target_directory%\Libraries\Modules"
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

echo	*
echo	*
echo	*	Removing useless files. . .
echo	*
echo	*

del /s "%target_directory%\Includes\*.cpp"
if %answer% == n del /s "%target_directory%\Libraries\*.pdb"

rd "%target_directory%\Resources\Applications\SDKBuilder" /s /q
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