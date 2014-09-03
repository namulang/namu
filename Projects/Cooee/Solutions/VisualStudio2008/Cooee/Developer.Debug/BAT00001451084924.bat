@echo off
z:\Projects\Progressing\Node\Projects\Cooee\Solutions\VisualStudio2008\Cooee\..\..\..\..\..\Resources\Applications\AfterBuild\AfterBuild.exe z:\Projects\Progressing\Node\Projects\Cooee\Solutions\VisualStudio2008\Cooee\VersionNo.ini z:\Projects\Progressing\Node\Projects\Cooee\Binaries\Cooee\..\Cooee z:\Projects\Progressing\Node\Projects\Cooee\Solutions\VisualStudio2008\Cooee\..\..\..\..\..\SDK\Libraries\
if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: 도구에서 오류 코드를 반환했습니다. 위치: "빌드 후 이벤트를 수행하고 있습니다..."
exit 1
:VCEnd