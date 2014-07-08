//  Global Values:
var Sources;
var Commons;
var Includes;
var EntryPoints;
var Applications;
var Distributor;
var Modules;
var my_module;
var define;
var execute;
var errorcode;
var Resources;
var Documents;
var Binaries;
var Solutions;
var panel;
var string_typer;
var panel_errorcode;
var is_visual_studio_2012;
function replaceSpaceToUnderbar(input_string)
{
	wizard.ReportError("before : " + input_string);
	var output_string = input_string.replace(/\s/g, '_');
	wizard.ReportError("after : " + output_string);

	return output_string;
}

function OnFinish(selProj, selObj)
{
	try
	{
	    var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
	  	var strProjectName = replaceSpaceToUnderbar(wizard.FindSymbol('PROJECT_NAME'));
	  	wizard.AddSymbol('PROJECT_NAME', strProjectName);
	  	var wizard_name = wizard.FindSymbol('WIZARD_NAME');
	  	is_visual_studio_2012 = (wizard_name == 'MDK for VS2012') ? true : false;	  	

	  	selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		var InfFile = CreateCustomInfFile();
		AddFilters(selProj);
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings(selProj);
		InfFile.Delete();
		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		var project_extention = (is_visual_studio_2012) ? 'vcxproj' : 'vcproj';
		strProjTemplate = strProjTemplatePath + '\\default.' + project_extention;
        var Solution = dte.Solution;
		var strSolutionName = "";

		/*
			처음 솔루션을 생성하는 프로젝트인지 판단:
				왜 CLOSE_SOLUTION의 심볼이 처음 솔루션을 생성한다는 의미가 되는지는 아직 모름.
				다만, 테스트를 통해서 알게 되었다.
				차후에 원하는 위치에 솔루션 파일을 생성할 수 있도록 할 것인지를 선택할 수 있도록 하라.

			솔루션을 지정한 경로/Solutions/VisualStudio2008에 생성할 수 없는 문제:
				지정한 경로/Solutions/VisualStudio2008에 솔루션 파일을 넣고 싶으나, 솔루션을
				지정하는 당시에 폴더가 생성되어 있지 않으므로 에러가 발생한다. 
				자바스크립트 / wizard클래스 상에서 폴더를 생성할 수 있는 방법이 있는가?
				wizard.ReportError("strSolutionPath : " + strSolutionPath + ", strSolutionName : " + strSolutionName);
		*/
		if(wizard.FindSymbol("CLOSE_SOLUTION"))
		{	//	처음 솔루션을 생성하는 거라면:
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if(strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.' + project_extention;

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		
		/*
			아직 1번의 경우는 어떠한 경우에 불러오게 되는지 알지 못했다. 
			따라서 차후에 1번으로 수행될 경우에는 코드수정이 필요함.

			처음 프로젝트를 생성/이미 존재하는 솔루션에 프로젝트 추가시:			
		*/
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
		    var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);			
			prj = prjItem.SubProject;
		}
		else
		{
		    prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		var fxtarget = wizard.FindSymbol("TARGET_FRAMEWORK_VERSION");
		if (fxtarget != null && fxtarget != "")
		{
		    fxtarget = fxtarget.split('.', 2);
		    if (fxtarget.length == 2)
				prj.Object.TargetFrameworkVersion = parseInt(fxtarget[0]) * 0x10000 + parseInt(fxtarget[1])
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}


    
function AddFilters(proj)
{
    //  pre:
	//      targetting:
	var project_name = wizard.FindSymbol('PROJECT_NAME');
    var module_name = wizard.FindSymbol('module_name');  
    var is_execute_enabled = wizard.FindSymbol('export_execute_module');
    var is_panel_enabled = wizard.FindSymbol('export_panel');
    
	
	//  main:
	try
	{
	    Sources = proj.object.AddFilter('Sources');
	    Commons = Sources.AddFilter('Commons');
	    Includes = Sources.AddFilter('Includes');
	    EntryPoints = Sources.AddFilter('EntryPoints');
	    Modules = Sources.AddFilter('Modules');
	    my_module = Modules.AddFilter(module_name);
		define = my_module.AddFilter('define');
		Resources = proj.object.AddFilter('Resources');
		Applications = Resources.AddFilter('Applications');
		Distributor = Applications.AddFilter('Distributor');
		Documents = Resources.AddFilter('Documents');
		
	    if(is_execute_enabled)
	    {
		    //  폴더 추가:
		    execute = my_module.AddFilter('Execute');
		    var innerclass = execute.AddFilter('innerclass');
		    errorcode = innerclass.AddFilter('ErrorCode');		
	    }
	    if(is_panel_enabled)
	    {
	    	panel = my_module.AddFilter('Panel');
	        var panel_innerclass = panel.AddFilter('innerclass');
	        panel_errorcode = panel_innerclass.AddFilter('ErrorCode');
	        string_typer = panel_innerclass.AddFilter('StringTyper');
	    }		
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
    //  symbols:
    var module_platform = wizard.FindSymbol('module_platform');
    var is_developer_debug = wizard.FindSymbol('Developer.Debug_configuration');
    var is_developer_release = wizard.FindSymbol('Developer.Release_configuration');
    var is_release = wizard.FindSymbol('Release_configuration');
    var is_panel_enabled = wizard.FindSymbol('export_panel');

	try
	{
	    //  Debug.Developer:
	    //      Configuration:		    
	    //          기존의 설정 삭제:   최소한 1개의 설정이 있어야 하기에, 먼저 추가를 하고 삭제를 해야 한다
	    //              targetting: RemoveConfiguration은 문자열이 아니라 Object로 받는 것에 주의하라
	    var debug_configuration = proj.Object.Configurations('Debug');
	    //              설정 삭제:
	    proj.Object.RemoveConfiguration(debug_configuration);

        if(is_developer_debug)
        {            
	        proj.Object.AddConfiguration('Developer.Debug');        
	        //      General:    	
		    var config = proj.Object.Configurations('Developer.Debug');
		    config.IntermediateDirectory = '$(ConfigurationName)';
		    config.OutputDirectory = '$(ProjectDir)Binaries/$(ProjectName)/';	    
		    config.BuildLogFile = '$(ConfigurationName)/$(MSBuildProjectName).log';
		    config.CharacterSet = charSet.charSetUnicode;
		    config.ConfigurationType = ConfigurationTypes.typeDynamicLibrary;
		    //			TargetExt:
		    /*
		    				VS2010부터 추가된 속성들 중의 일부는 기존의 VSProjectEngine API를 통해서는
		    				접근이 불가능하다.
		    				이러한 것들은 새로운 방법인 Rules XML 파일을 통해서 값을 변경시키는 방법을 사용한다.
						데이터 획득:
							generalRule.GetEvaluatedPropertyValue("TargetExt");
							generalRule.GetUnevaluatedPropertyValue("PlatfromToolset");
						데이터 세팅:
		    				generalRule.SetPropertyValue("TargetExt", ".dll")
		    */
		    //			Platform Settings:
        	if(is_visual_studio_2012)
        	{
        		var generalRule = config.Rules.Item("ConfigurationGeneral");
	            generalRule.SetPropertyValue("TargetName", "$(ProjectName).dev.dbg");
	            //generalRule.SetPropertyValue("PlatformToolset", "Windows7.1SDK");            
	            generalRule.SetPropertyValue("TargetExt", ".dll");
		        var platform = config.Platform;
		        platform.IncludeDirectories += ';Z:/Node/SDK/Includes';
		        platform.LibraryDirectories += ';Z:/Node/SDK/Libraries;Z:/Node/SDK/Libraries/Modules';
	        }	        
	        

            //      C/C++:
            //          General:        
		    var CLTool = config.Tools('VCCLCompilerTool');
		    CLTool.WarningLevel = warningLevelOption.warningLevel_3;
		    CLTool.DebugInformationFormat = debugOption.debugEditAndContinue;
		    //          최적화:
		    CLTool.Optimization = optimizeOption.optimizeDisabled;
		    //          전처리기:
		    var pre_defines = "WIN32; _DEBUG; _WINDOWS; _UNICODE; _USRDLL; DEVELOPER; " + strProjectName + "_EXPORTS;";
		    CLTool.PreprocessorDefinitions = pre_defines;		
		    //          코드 생성:
		    CLTool.MinimalRebuild = true;
		    CLTool.BasicRuntimeChecks = basicRuntimeCheckOption.runtimeBasicCheckAll;
		    try
		    {
		        CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDebugDLL;
		    }
		    catch(ex)
		    {
		        wizard.ReportError("runtime library = rtMultiThreadedDebugDLL에서 에러가 발생합니다.\nVisual C++ 2005 Express 인가요?");
		    }
		    //          미리 컴파일된 헤더:
		    CLTool.UsePrecompiledHeader = pchOption.pchNone;
		    //          고급:
		    CLTool.CallingConvention = callingConventionOption.callConventionCDecl;
		    CLTool.CompileAs = CompileAsOptions.compileAsCPlusPlus;

           
            //      Linker:
		    var LinkTool = config.Tools('VCLinkerTool');
		    //          General:		
            LinkTool.OutputFile = "$(OutDir)$(TargetName)$(TargetExt)";
            LinkTool.LinkIncremental = linkIncrementalYes;
            //          디버깅:
            LinkTool.GenerateDebugInformation = true;
            //          시스템:        
            switch(module_platform)
            {
                default:
                    wizard.ReportError("알수 없는 플랫폼입니다. Windows로 변경합니다.\n에러가 발생한 플랫폼 문자열 : " + module_platform);
                    
                case "Windows":
                    LinkTool.SubSystem = subSystemOption.subSystemWindows;
                    break;            
            }
            
            //          고급:
		    LinkTool.TargetMachine = machineTypeOption.machineX86;

        }	
    	
        if(is_developer_release)
        {	
		    //  Relase.Developer:
	        //      General:
	        proj.Object.AddConfiguration('Developer.Release');
		    var config = proj.Object.Configurations('Developer.Release');
		    config.IntermediateDirectory = '$(ConfigurationName)';
		    
		    config.OutputDirectory = '$(ProjectDir)Binaries/$(ProjectName)/';	    
		    config.BuildLogFile = '$(ConfigurationName)/$(MSBuildProjectName).log';

		    config.CharacterSet = charSet.charSetUnicode;
		    config.ConfigurationType = ConfigurationTypes.typeDynamicLibrary;
	        //			TargetExt:
		    /*
		    				VS2010부터 추가된 속성들 중의 일부는 기존의 VSProjectEngine API를 통해서는
		    				접근이 불가능하다.
		    				이러한 것들은 새로운 방법인 Rules XML 파일을 통해서 값을 변경시키는 방법을 사용한다.
						데이터 획득:
							generalRule.GetEvaluatedPropertyValue("TargetExt");
						데이터 세팅:
		    				generalRule.SetPropertyValue("TargetExt", ".dll")
		    */
		    if(is_visual_studio_2012)
        	{
			    var generalRule = config.Rules.Item("ConfigurationGeneral");
	            generalRule.SetPropertyValue("TargetExt", ".dev.dll")
	            var platform = config.Platform;
		        platform.IncludeDirectories += ';Z:/Node/SDK/Includes';
		        platform.LibraryDirectories += ';Z:/Node/SDK/Libraries;Z:/Node/SDK/Libraries/Modules';
	        }

            //      C/C++:
            //          General:
            var config = proj.Object.Configurations('Developer.Release');
		    var CLTool = config.Tools('VCCLCompilerTool');
		    CLTool.WarningLevel = warningLevelOption.warningLevel_3;
		    CLTool.DebugInformationFormat = debugOption.debugEnabled;
		    //          최적화:
		    CLTool.Optimization = optimizeOption.optimizeMaxSpeed;
		    //          전처리기:
		    var pre_defines = "WIN32; NDEBUG; _WINDOWS; _UNICODE; _USRDLL; DEVELOPER; " + strProjectName + "_EXPORTS;";
		    CLTool.PreprocessorDefinitions = pre_defines;
		    //          코드 생성:
		    CLTool.MinimalRebuild = true;
		    CLTool.BasicRuntimeChecks = basicRuntimeCheckOption.runtimeBasicCheckNone;
		    try
		    {
		        CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDLL;
		    }
		    catch(ex)
		    {
		        wizard.ReportError("runtime library = rtMultiThreadedDLL에서 에러가 발생합니다.\nVisual C++ 2005 Express 인가요?");
		    }
		    CLTool.EnableFunctionLevelLinking = true;
		    //          미리 컴파일된 헤더:
		    CLTool.UsePrecompiledHeader = pchOption.pchNone;
		    //          고급:
		    CLTool.CallingConvention = callingConventionOption.callConventionCDecl;
		    CLTool.CompileAs = CompileAsOptions.compileAsCPlusPlus;


            //      Linker:
		    var LinkTool = config.Tools('VCLinkerTool');
		    //          General:		
            LinkTool.OutputFile = "$(OutDir)$(ProjectName).dev.dll"
            LinkTool.LinkIncremental = linkIncrementalNo;
            //          디버깅:
            LinkTool.GenerateDebugInformation = true;
            //          시스템:        
            switch(module_platform)
            {
                default:
                    wizard.ReportError("알수 없는 플랫폼입니다. Windows로 변경합니다.\n에러가 발생한 플랫폼 문자열 : " + module_platform);
                    
                case "Windows":
                    LinkTool.SubSystem = subSystemOption.subSystemWindows;
                    break;            
            }
            //          최적화:
            LinkTool.OptimizeReferences = optRefType.optReferences;
            LinkTool.EnableCOMDATFolding = optFoldingType.optFolding;
            //          고급:
		    LinkTool.TargetMachine = machineTypeOption.machineX86;
        }
		
		

		if(is_release)
		{
	        //  Relase:
	        //      General:
		    var config = proj.Object.Configurations('Release');
		    config.IntermediateDirectory = '$(ConfigurationName)';
		    
		    config.OutputDirectory = '$(ProjectDir)Binaries/$(ProjectName)/';
		    config.BuildLogFile = '$(ConfigurationName)/$(MSBuildProjectName).log';
		        
		    config.CharacterSet = charSet.charSetUnicode;
		    config.ConfigurationType = ConfigurationTypes.typeDynamicLibrary;
		    //			TargetExt:
		    /*
		    				VS2010부터 추가된 속성들 중의 일부는 기존의 VSProjectEngine API를 통해서는
		    				접근이 불가능하다.
		    				이러한 것들은 새로운 방법인 Rules XML 파일을 통해서 값을 변경시키는 방법을 사용한다.
						데이터 획득:
							generalRule.GetEvaluatedPropertyValue("TargetExt");
						데이터 세팅:
		    				generalRule.SetPropertyValue("TargetExt", ".dll")
		    */
		    if(is_visual_studio_2012)
        	{
			    var generalRule = config.Rules.Item("ConfigurationGeneral");
	            generalRule.SetPropertyValue("TargetExt", ".dll")
	            var platform = config.Platform;
		        platform.IncludeDirectories += ';Z:/Node/SDK/Includes';
		        platform.LibraryDirectories += ';Z:/Node/SDK/Libraries;Z:/Node/SDK/Libraries/Modules';
	        }		    

            //      C/C++:
            //          General:
		    var CLTool = config.Tools('VCCLCompilerTool');
		    CLTool.WarningLevel = warningLevelOption.warningLevel_3;
		    CLTool.DebugInformationFormat = debugOption.debugEnabled;
		    //          최적화:
		    CLTool.Optimization = optimizeOption.optimizeMaxSpeed;
		    //          전처리기:
		    var pre_defines = "WIN32; NDEBUG; _WINDOWS; _UNICODE; _USRDLL; " + strProjectName + "_EXPORTS;";
		    CLTool.PreprocessorDefinitions = pre_defines;
		    //          코드 생성:
		    CLTool.MinimalRebuild = true;
		    CLTool.BasicRuntimeChecks = basicRuntimeCheckOption.runtimeBasicCheckAll;
		    try
		    {
		        CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDLL;
		    }
		    catch(ex)
		    {
		        wizard.ReportError("runtime library = rtMultiThreadedDLL에서 에러가 발생합니다.\nVisual C++ 2005 Express 인가요?");
		    }
		    CLTool.EnableFunctionLevelLinking = true;
		    //          미리 컴파일된 헤더:
		    CLTool.UsePrecompiledHeader = pchOption.pchNone;
		    //          고급:
		    CLTool.CallingConvention = callingConventionOption.callConventionCDecl;
		    CLTool.CompileAs = CompileAsOptions.compileAsCPlusPlus;


            //      Linker:
		    var LinkTool = config.Tools('VCLinkerTool');
		    //          General:		
            LinkTool.OutputFile = "$(OutDir)$(ProjectName).dll"
            LinkTool.LinkIncremental = linkIncrementalNo;
            //          디버깅:
            LinkTool.GenerateDebugInformation = false;
            //          시스템:        
            switch(module_platform)
            {
                default:
                    wizard.ReportError("알수 없는 플랫폼입니다. Windows로 변경합니다.\n에러가 발생한 플랫폼 문자열 : " + module_platform);
                    
                case "Windows":
                    LinkTool.SubSystem = subSystemOption.subSystemWindows;
                    break;            
            }
            //          최적화:
            LinkTool.OptimizeReferences = optRefType.optReferences;
            LinkTool.EnableCOMDATFolding = optFoldingType.optFolding;
            //          고급:
		    LinkTool.TargetMachine = machineTypeOption.machineX86;  
        }
	}
	catch(e)
	{
		throw e;
	}
}

function PchSettings(proj)
{
	// TODO: pch 설정을 지정합니다.
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);
		var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

		var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName, strTemplate, strProjectPath)
{
	try
	{
		// TODO: set the name of the rendered file based on the template filename
		var strTarget = strName;
		var project_name = wizard.FindSymbol('PROJECT_NAME');
		var module_name = wizard.FindSymbol('module_name');
		var panel_name = wizard.FindSymbol('panel_name');
		var is_include_editor = wizard.FindSymbol('include_editor');
		var is_execute_enabled = wizard.FindSymbol('export_execute_module');
        var is_panel_enabled = wizard.FindSymbol('export_panel');
        
        if (strName == 'Sources/Commons/EntryPointName.hpp')
		{
			strTarget = 'Sources/Commons/EntryPointName.hpp';
			var strFile = strProjectPath + '\\' + strTarget;
			wizard.RenderTemplate(strTemplate, strFile, false);
			Commons.AddFile(strFile);
		}
		else if (strName == 'Sources/Includes/Includes.hpp')
		{
			strTarget =  'Sources/Includes/Includes.hpp';
			var strFile = strProjectPath + '\\' + strTarget;	
	        wizard.RenderTemplate(strTemplate, strFile, false);
			Includes.AddFile(strFile);
		}
		else if (strName == 'Sources/EntryPoints/Headers.hpp')
		{
			strTarget =  'Sources/EntryPoints/Headers.hpp';	
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			EntryPoints.AddFile(strFile);
		}
		else if (strName == 'Sources/EntryPoints/EntryPoints.cpp')
		{
			strTarget =  'Sources/EntryPoints/EntryPoints.cpp';	
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			EntryPoints.AddFile(strFile);
		}	
		else if (strName == 'Sources/Modules/Sample/Sample.hpp')
		{
			strTarget =  'Sources/Modules/' + module_name + '/' + module_name + '.hpp';	
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			my_module.AddFile(strFile);
		}				
        else if(is_execute_enabled && strName == 'Sources/Modules/Sample/Execute/SampleModule.cpp')
	    {
		    strTarget =  'Sources/Modules/' + module_name + '/Execute/' + module_name + '.cpp';
		    var strFile = strProjectPath + '\\' + strTarget;
            wizard.RenderTemplate(strTemplate, strFile, false);
		    execute.AddFile(strFile);
	    }		
	    else if (is_execute_enabled && strName == 'Sources/Modules/Sample/Execute/SampleModule.hpp')
	    {
		    strTarget =  'Sources/Modules/' + module_name + '/Execute/' + module_name + '.hpp';
		    var strFile = strProjectPath + '\\' + strTarget;
            wizard.RenderTemplate(strTemplate, strFile, false);
		    execute.AddFile(strFile);
	    }
	    else if (is_execute_enabled && strName == 'Sources/Modules/Sample/Execute/innerclass/ErrorCode/ErrorCode.hpp')
	    {
		    strTarget =  'Sources/Modules/' + module_name + '/Execute/innerclass/ErrorCode/ErrorCode.hpp';
		    var strFile = strProjectPath + '\\' + strTarget;
            wizard.RenderTemplate(strTemplate, strFile, false);
		    errorcode.AddFile(strFile);
	    }
		else if (strName == 'Sources/Modules/Sample/define/define.hpp')
		{
			strTarget =  'Sources/Modules/' + module_name + '/define/define.hpp';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			define.AddFile(strFile);
		}
		else if (is_panel_enabled && strName == 'Sources/Modules/Sample/Panel/SamplePanel.hpp')
		{
		    strTarget =  'Sources/Modules/' + module_name + '/Panel/' + panel_name + '.hpp';
		    var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			panel.AddFile(strFile);
		}
		else if (is_panel_enabled && strName == 'Sources/Modules/Sample/Panel/SamplePanel.cpp')
		{
			strTarget =  'Sources/Modules/' + module_name + '/Panel/' + panel_name + '.cpp';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			panel.AddFile(strFile);
		}
		else if (is_panel_enabled && strName == 'Sources/Modules/Sample/Panel/innerclass/ErrorCode/ErrorCode.hpp')
		{
			strTarget =  'Sources/Modules/' + module_name + '/Panel/innerclass/ErrorCode/ErrorCode.hpp';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			panel_errorcode.AddFile(strFile);
		}
		else if (is_panel_enabled && strName == 'Sources/Modules/Sample/Panel/innerclass/StringTyper/StringTyper.hpp')
		{
			strTarget =  'Sources/Modules/' + module_name + '/Panel/innerclass/StringTyper/StringTyper.hpp';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
		    string_typer.AddFile(strFile);
		}
		else if (is_panel_enabled && strName == 'Sources/Modules/Sample/Panel/innerclass/StringTyper/StringTyper.cpp')
		{
			strTarget =  'Sources/Modules/' + module_name + '/Panel/innerclass/StringTyper/StringTyper.cpp';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			string_typer.AddFile(strFile);
		}
        else if (strName == 'Resources/Documents/ReadMe.txt')
		{
			strTarget =  'Resources/Documents/ReadMe.txt';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			Documents.AddFile(strFile);
		}
		else if (strName == 'Resources/Applications/Distributor/Distributor.bat')
		{
			strTarget =  'Resources/Applications/Distributor/Distributor.bat';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			Distributor.AddFile(strFile);
		}
        else if (strName == 'VersionNo.ini')
		{
		    strTarget =  'VersionNo.ini';
			var strFile = strProjectPath + '\\' + strTarget;
	        wizard.RenderTemplate(strTemplate, strFile, false);
			Solutions.AddFile(strFile);
		}
		
		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems
		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strTpl = '';
		var strName = '';
		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		
		while (!strTextStream.AtEndOfStream)
		{
		    strTpl = strTextStream.ReadLine();
		    
		    if (strTpl != '')
			{
				strName = strTpl;				
				var strTemplate = strTemplatePath + '\\' + strTpl;
				GetTargetName(strName, strProjectName, strTemplate, strProjectPath);
			}			
			
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}


// SIG // Begin signature block
// SIG // MIIj7gYJKoZIhvcNAQcCoIIj3zCCI9sCAQExCzAJBgUr
// SIG // DgMCGgUAMGcGCisGAQQBgjcCAQSgWTBXMDIGCisGAQQB
// SIG // gjcCAR4wJAIBAQQQEODJBs441BGiowAQS9NQkAIBAAIB
// SIG // AAIBAAIBAAIBADAhMAkGBSsOAwIaBQAEFFfTGHAAPWyb
// SIG // rkX7tagnB/JStUjFoIIe4TCCBBIwggL6oAMCAQICDwDB
// SIG // AIs8PIgR0T72Y+zfQDANBgkqhkiG9w0BAQQFADBwMSsw
// SIG // KQYDVQQLEyJDb3B5cmlnaHQgKGMpIDE5OTcgTWljcm9z
// SIG // b2Z0IENvcnAuMR4wHAYDVQQLExVNaWNyb3NvZnQgQ29y
// SIG // cG9yYXRpb24xITAfBgNVBAMTGE1pY3Jvc29mdCBSb290
// SIG // IEF1dGhvcml0eTAeFw05NzAxMTAwNzAwMDBaFw0yMDEy
// SIG // MzEwNzAwMDBaMHAxKzApBgNVBAsTIkNvcHlyaWdodCAo
// SIG // YykgMTk5NyBNaWNyb3NvZnQgQ29ycC4xHjAcBgNVBAsT
// SIG // FU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEhMB8GA1UEAxMY
// SIG // TWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5MIIBIjANBgkq
// SIG // hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqQK9wXDmO/JO
// SIG // Gyifl3heMOqiqY0lX/j+lUyjt/6doiA+fFGim6KPYDJr
// SIG // 0UJkee6sdslU2vLrnIYcj5+EZrPFa3piI9YdPN4PAZLo
// SIG // lsS/LWaammgmmdA6LL8MtVgmwUbnCj44liypKDmo7EmD
// SIG // QuOED7uabFVhrIJ8oWAtd0zpmbRkO5pQHDEIJBSfqeeR
// SIG // KxjmPZhjFGBYBWWfHTdSh/en75QCxhvTv1VFs4mAvzrs
// SIG // VJROrv2nem10Tq8YzJYJKCEAV5BgaTe7SxIHPFb/W/uk
// SIG // ZgoIptKBVlfvtjteFoF3BNr2vq6Alf6wzX/WpxpyXDzK
// SIG // vPAIoyIwswaFybMgdxOF3wIDAQABo4GoMIGlMIGiBgNV
// SIG // HQEEgZowgZeAEFvQcO9pcp4jUX4Usk2O/8uhcjBwMSsw
// SIG // KQYDVQQLEyJDb3B5cmlnaHQgKGMpIDE5OTcgTWljcm9z
// SIG // b2Z0IENvcnAuMR4wHAYDVQQLExVNaWNyb3NvZnQgQ29y
// SIG // cG9yYXRpb24xITAfBgNVBAMTGE1pY3Jvc29mdCBSb290
// SIG // IEF1dGhvcml0eYIPAMEAizw8iBHRPvZj7N9AMA0GCSqG
// SIG // SIb3DQEBBAUAA4IBAQCV6AvAjfOXGDXtuAEk2HcR81xg
// SIG // Mp+eC8s+BZGIj8k65iHy8FeTLLWgR8hi7/zXzDs7Wqk2
// SIG // VGn+JG0/ycyq3gV83TGNPZ8QcGq7/hJPGGnA/NBD4xFa
// SIG // IE/qYnuvqhnIKzclLb5loRKKJQ9jo/dUHPkhydYV81Ks
// SIG // bkMyB/2CF/jlZ2wNUfa98VLHvefEMPwgMQmIHZUpGk3V
// SIG // HQKl8YDgA7Rb9LHdyFfuZUnHUlS2tAMoEv+Q1vAIj364
// SIG // l8WrNyzkeuSod+N2oADQaj/B0jaK4EESqDVqG2rbNeHU
// SIG // HATkqEUEyFozOG5NHA1itwqijNPVVD9GzRxVpnDbEjqH
// SIG // k3Wfp9KgMIIEEjCCAvqgAwIBAgIPAMEAizw8iBHRPvZj
// SIG // 7N9AMA0GCSqGSIb3DQEBBAUAMHAxKzApBgNVBAsTIkNv
// SIG // cHlyaWdodCAoYykgMTk5NyBNaWNyb3NvZnQgQ29ycC4x
// SIG // HjAcBgNVBAsTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEh
// SIG // MB8GA1UEAxMYTWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5
// SIG // MB4XDTk3MDExMDA3MDAwMFoXDTIwMTIzMTA3MDAwMFow
// SIG // cDErMCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1p
// SIG // Y3Jvc29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0
// SIG // IENvcnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQg
// SIG // Um9vdCBBdXRob3JpdHkwggEiMA0GCSqGSIb3DQEBAQUA
// SIG // A4IBDwAwggEKAoIBAQCpAr3BcOY78k4bKJ+XeF4w6qKp
// SIG // jSVf+P6VTKO3/p2iID58UaKboo9gMmvRQmR57qx2yVTa
// SIG // 8uuchhyPn4Rms8VremIj1h083g8BkuiWxL8tZpqaaCaZ
// SIG // 0Dosvwy1WCbBRucKPjiWLKkoOajsSYNC44QPu5psVWGs
// SIG // gnyhYC13TOmZtGQ7mlAcMQgkFJ+p55ErGOY9mGMUYFgF
// SIG // ZZ8dN1KH96fvlALGG9O/VUWziYC/OuxUlE6u/ad6bXRO
// SIG // rxjMlgkoIQBXkGBpN7tLEgc8Vv9b+6RmCgim0oFWV++2
// SIG // O14WgXcE2va+roCV/rDNf9anGnJcPMq88AijIjCzBoXJ
// SIG // syB3E4XfAgMBAAGjgagwgaUwgaIGA1UdAQSBmjCBl4AQ
// SIG // W9Bw72lyniNRfhSyTY7/y6FyMHAxKzApBgNVBAsTIkNv
// SIG // cHlyaWdodCAoYykgMTk5NyBNaWNyb3NvZnQgQ29ycC4x
// SIG // HjAcBgNVBAsTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEh
// SIG // MB8GA1UEAxMYTWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5
// SIG // gg8AwQCLPDyIEdE+9mPs30AwDQYJKoZIhvcNAQEEBQAD
// SIG // ggEBAJXoC8CN85cYNe24ASTYdxHzXGAyn54Lyz4FkYiP
// SIG // yTrmIfLwV5MstaBHyGLv/NfMOztaqTZUaf4kbT/JzKre
// SIG // BXzdMY09nxBwarv+Ek8YacD80EPjEVogT+pie6+qGcgr
// SIG // NyUtvmWhEoolD2Oj91Qc+SHJ1hXzUqxuQzIH/YIX+OVn
// SIG // bA1R9r3xUse958Qw/CAxCYgdlSkaTdUdAqXxgOADtFv0
// SIG // sd3IV+5lScdSVLa0AygS/5DW8AiPfriXxas3LOR65Kh3
// SIG // 43agANBqP8HSNorgQRKoNWobats14dQcBOSoRQTIWjM4
// SIG // bk0cDWK3CqKM09VUP0bNHFWmcNsSOoeTdZ+n0qAwggRg
// SIG // MIIDTKADAgECAgouqxHcUP9cncvAMAkGBSsOAwIdBQAw
// SIG // cDErMCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1p
// SIG // Y3Jvc29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0
// SIG // IENvcnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQg
// SIG // Um9vdCBBdXRob3JpdHkwHhcNMDcwODIyMjIzMTAyWhcN
// SIG // MTIwODI1MDcwMDAwWjB5MQswCQYDVQQGEwJVUzETMBEG
// SIG // A1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMHUmVkbW9u
// SIG // ZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9u
// SIG // MSMwIQYDVQQDExpNaWNyb3NvZnQgQ29kZSBTaWduaW5n
// SIG // IFBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC
// SIG // ggEBALd5fdZds0U5qDSsMdr5JTVJd8D7H57HRXHv0Ubo
// SIG // 1IzDa0xSYvSZAsNN2ElsLyQ+Zb/OI7cLSLd/dd1FvaqP
// SIG // DlDFJSvyoOcNIx/RQST6YpnPGUWlk0ofmc2zLyLDSi18
// SIG // b9kVHjuMORA53b0p9GY7LQEy//4nSKa1bAGHnPu6smN/
// SIG // gvlcoIGEhY6w8riUo884plCFFyeHTt0w9gA99Mb5PYG+
// SIG // hu1sOacuNPa0Lq8KfWKReGacmHMNhq/yxPMguU8SjWPL
// SIG // LNkyRRnuu0qWO1BTGM5mUXmqrYfIVj6fglCIbgWxNcF7
// SIG // JL1SZj2ZTswrfjNuhEcG0Z7QSoYCboYApMCH31MCAwEA
// SIG // AaOB+jCB9zATBgNVHSUEDDAKBggrBgEFBQcDAzCBogYD
// SIG // VR0BBIGaMIGXgBBb0HDvaXKeI1F+FLJNjv/LoXIwcDEr
// SIG // MCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1pY3Jv
// SIG // c29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0IENv
// SIG // cnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQgUm9v
// SIG // dCBBdXRob3JpdHmCDwDBAIs8PIgR0T72Y+zfQDAPBgNV
// SIG // HRMBAf8EBTADAQH/MB0GA1UdDgQWBBTMHc52AHBbr/Ha
// SIG // xE6aUUQuo0Rj8DALBgNVHQ8EBAMCAYYwCQYFKw4DAh0F
// SIG // AAOCAQEAe6uufkom8s68TnSiWCd0KnWzhv2rTJR4AE3p
// SIG // yusY3GnFDqJ88wJDxsqHzPhTzMKfvVZv8GNEqUQA7pbI
// SIG // mtUcuAufGQ2U19oerSl97+2mc6yP3jmOPZhqvDht0oiv
// SIG // I/3f6dZpCZGIvf7hALs08/d8+RASLgXrKZaTQmsocbc4
// SIG // j+AHDcldaM29gEFrZqi7t7uONMryAxB8evXS4ELfe/7h
// SIG // 4az+9t/VDbNw1pLjT7Y4onwt1D3bNAtiNwKfgWojifZc
// SIG // Y4+wWrs512CMVYQaM/U7mKCCDKJfi7Mst6Gly6vaILa/
// SIG // MBmFIBQNKrxS9EHgXjDjkihph8Fw4vOnq86AQnJ2DjCC
// SIG // BGowggNSoAMCAQICCmEPeE0AAAAAAAMwDQYJKoZIhvcN
// SIG // AQEFBQAweTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldh
// SIG // c2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNV
// SIG // BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEjMCEGA1UE
// SIG // AxMaTWljcm9zb2Z0IENvZGUgU2lnbmluZyBQQ0EwHhcN
// SIG // MDcwODIzMDAyMzEzWhcNMDkwMjIzMDAzMzEzWjB0MQsw
// SIG // CQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQ
// SIG // MA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9z
// SIG // b2Z0IENvcnBvcmF0aW9uMR4wHAYDVQQDExVNaWNyb3Nv
// SIG // ZnQgQ29ycG9yYXRpb24wggEiMA0GCSqGSIb3DQEBAQUA
// SIG // A4IBDwAwggEKAoIBAQCi2wqNz8LBSZvNqjo0rSNZa9ts
// SIG // viEit5TI6q6/xtUmwjIRi7zaXSz7NlYeFSuujw3dFKNu
// SIG // KEx/Fj9BrI1AsUaIDdmBlK2XBtBXRHZc6vH8DuJ/dKMz
// SIG // y3Tl7+NhoX4Dt0X/1T4S1bDKXg3Qe/K3Ew38YGoohXWM
// SIG // t628hegXtJC+9Ra2Yl3tEd867iFbi6+Ac8NF45WJd2Cb
// SIG // 5613wTeNMxQvE9tiya4aqU+YZ63UIDkwceCNZ0bixhz0
// SIG // DVB0QS/oBSRqIWtJsJLEsjnHQqVtXBhKq4/XjoM+eApH
// SIG // 2KSyhCPD4vJ7ZrFKdL0mQUucYRRgTjDIgvPQC3B87lVN
// SIG // d9IIVXaBAgMBAAGjgfgwgfUwDgYDVR0PAQH/BAQDAgbA
// SIG // MB0GA1UdDgQWBBTzIUCOfFH4VEuY5RfXaoM0BS4m6DAT
// SIG // BgNVHSUEDDAKBggrBgEFBQcDAzAfBgNVHSMEGDAWgBTM
// SIG // Hc52AHBbr/HaxE6aUUQuo0Rj8DBEBgNVHR8EPTA7MDmg
// SIG // N6A1hjNodHRwOi8vY3JsLm1pY3Jvc29mdC5jb20vcGtp
// SIG // L2NybC9wcm9kdWN0cy9DU1BDQS5jcmwwSAYIKwYBBQUH
// SIG // AQEEPDA6MDgGCCsGAQUFBzAChixodHRwOi8vd3d3Lm1p
// SIG // Y3Jvc29mdC5jb20vcGtpL2NlcnRzL0NTUENBLmNydDAN
// SIG // BgkqhkiG9w0BAQUFAAOCAQEAQFdvU2eeIIM0AQ7mF0s8
// SIG // revYgX/uDXl0d0+XRxjzABVpfttikKL9Z6Gc5Cgp+lXX
// SIG // mf5Qv14Js7mm7YLzmB5vWfr18eEM04sIPhYXINHAtUVH
// SIG // CCZgVwlLlPAIzLpNbvDiSBIoNYshct9ftq9pEiSU7uk0
// SIG // Cdt+bm+SClLKKkxJqjIshuihzF0mvLw84Fuygwu6NRxP
// SIG // hEVH/7uUoVkHqZbdeL1Xf6WnTszyrZyaQeLLXCQ+3H80
// SIG // R072z8h7neu2yZxjFFOvrZrv17/PoKGrlcp6K4cswMfZ
// SIG // /GwD2r84rfHRXBkXD8D3yoCmEAga3ZAj57ChTD7qsBEm
// SIG // eA7BLLmka8ePPDCCBJ0wggOFoAMCAQICCmEULKcAAAAA
// SIG // AAYwDQYJKoZIhvcNAQEFBQAweTELMAkGA1UEBhMCVVMx
// SIG // EzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1Jl
// SIG // ZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3Jh
// SIG // dGlvbjEjMCEGA1UEAxMaTWljcm9zb2Z0IFRpbWVzdGFt
// SIG // cGluZyBQQ0EwHhcNMDcwNjEyMjM1NDUxWhcNMTIwNjEz
// SIG // MDAwNDUxWjCBpjELMAkGA1UEBhMCVVMxEzARBgNVBAgT
// SIG // Cldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAc
// SIG // BgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEnMCUG
// SIG // A1UECxMebkNpcGhlciBEU0UgRVNOOjI3RjQtRDQ0MC01
// SIG // NEYzMScwJQYDVQQDEx5NaWNyb3NvZnQgVGltZXN0YW1w
// SIG // aW5nIFNlcnZpY2UwggEiMA0GCSqGSIb3DQEBAQUAA4IB
// SIG // DwAwggEKAoIBAQCRy6R7FHPT59SGk8ADfdhEpOGztfi4
// SIG // /bwqUwLKr5HdoRmDOjF49JZEDebg7kVms7z2AnTqNDi8
// SIG // 03c8I7Rw/Acyzp7zRUPmdFNMTi9bvFMFPoH84cNWweQm
// SIG // k9t8umPgkWxWcqrroIsWeGWIl07ieyKLzapZns14xzhi
// SIG // i0ONT8bnQ8xBReL72THv2P++aTHK7Ha59CG0kDQX/skQ
// SIG // +biGz16h0VKyRlghuDlXgW8Iil9sdRXAkDZ2rbbYSaRI
// SIG // fXaeCRPswgB944e8lw8OHPWaRtWk7GvDqnNI+O6ThPkl
// SIG // EkqOBIDgdFDiEWng9fti4WZseTMEpidxhDU2YxIrWRMG
// SIG // ecV1AgMBAAGjgfgwgfUwHQYDVR0OBBYEFDdV2ZYJkbWu
// SIG // W9o/9lmh/kr0gZagMB8GA1UdIwQYMBaAFG/oTj+XuTSr
// SIG // S4aPvJzqrDtBQ8bQMEQGA1UdHwQ9MDswOaA3oDWGM2h0
// SIG // dHA6Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3JsL3By
// SIG // b2R1Y3RzL3RzcGNhLmNybDBIBggrBgEFBQcBAQQ8MDow
// SIG // OAYIKwYBBQUHMAKGLGh0dHA6Ly93d3cubWljcm9zb2Z0
// SIG // LmNvbS9wa2kvY2VydHMvdHNwY2EuY3J0MBMGA1UdJQQM
// SIG // MAoGCCsGAQUFBwMIMA4GA1UdDwEB/wQEAwIGwDANBgkq
// SIG // hkiG9w0BAQUFAAOCAQEAJZxvhzktGoixAgM+u/JIbOo8
// SIG // DQ6u7uYHlQ5iukcnj9MNqmgiHyn6z/y+2u2kL6jycpQO
// SIG // dCez9KyMAEXITZxeAQTej1vJ5VYqnuaTPfHdASHHBsHi
// SIG // QVkycf1YFiGz8xrkBqtbAGgZd3z497e7pyLJVCuI0oic
// SIG // zyzQOl86CHwVYfUCKBWfOW3Gai/4MHiuWeTsavi1lFaW
// SIG // NffDOAw8ghlAzoCKKGoCWR9AbAvC77A/NXrrpXlqi9EK
// SIG // IuZg+AsQEqwhYBStvMk117/9mNdaATQFemayjpzxu+Gh
// SIG // yXbw9bIcTE1AGVm4RqtMyKxMlELjJ675Uz+TymN8JZfL
// SIG // l8Q2nvmuoDCCBJ0wggOFoAMCAQICCmEULKcAAAAAAAYw
// SIG // DQYJKoZIhvcNAQEFBQAweTELMAkGA1UEBhMCVVMxEzAR
// SIG // BgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1v
// SIG // bmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlv
// SIG // bjEjMCEGA1UEAxMaTWljcm9zb2Z0IFRpbWVzdGFtcGlu
// SIG // ZyBQQ0EwHhcNMDcwNjEyMjM1NDUxWhcNMTIwNjEzMDAw
// SIG // NDUxWjCBpjELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldh
// SIG // c2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNV
// SIG // BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEnMCUGA1UE
// SIG // CxMebkNpcGhlciBEU0UgRVNOOjI3RjQtRDQ0MC01NEYz
// SIG // MScwJQYDVQQDEx5NaWNyb3NvZnQgVGltZXN0YW1waW5n
// SIG // IFNlcnZpY2UwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAw
// SIG // ggEKAoIBAQCRy6R7FHPT59SGk8ADfdhEpOGztfi4/bwq
// SIG // UwLKr5HdoRmDOjF49JZEDebg7kVms7z2AnTqNDi803c8
// SIG // I7Rw/Acyzp7zRUPmdFNMTi9bvFMFPoH84cNWweQmk9t8
// SIG // umPgkWxWcqrroIsWeGWIl07ieyKLzapZns14xzhii0ON
// SIG // T8bnQ8xBReL72THv2P++aTHK7Ha59CG0kDQX/skQ+biG
// SIG // z16h0VKyRlghuDlXgW8Iil9sdRXAkDZ2rbbYSaRIfXae
// SIG // CRPswgB944e8lw8OHPWaRtWk7GvDqnNI+O6ThPklEkqO
// SIG // BIDgdFDiEWng9fti4WZseTMEpidxhDU2YxIrWRMGecV1
// SIG // AgMBAAGjgfgwgfUwHQYDVR0OBBYEFDdV2ZYJkbWuW9o/
// SIG // 9lmh/kr0gZagMB8GA1UdIwQYMBaAFG/oTj+XuTSrS4aP
// SIG // vJzqrDtBQ8bQMEQGA1UdHwQ9MDswOaA3oDWGM2h0dHA6
// SIG // Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3JsL3Byb2R1
// SIG // Y3RzL3RzcGNhLmNybDBIBggrBgEFBQcBAQQ8MDowOAYI
// SIG // KwYBBQUHMAKGLGh0dHA6Ly93d3cubWljcm9zb2Z0LmNv
// SIG // bS9wa2kvY2VydHMvdHNwY2EuY3J0MBMGA1UdJQQMMAoG
// SIG // CCsGAQUFBwMIMA4GA1UdDwEB/wQEAwIGwDANBgkqhkiG
// SIG // 9w0BAQUFAAOCAQEAJZxvhzktGoixAgM+u/JIbOo8DQ6u
// SIG // 7uYHlQ5iukcnj9MNqmgiHyn6z/y+2u2kL6jycpQOdCez
// SIG // 9KyMAEXITZxeAQTej1vJ5VYqnuaTPfHdASHHBsHiQVky
// SIG // cf1YFiGz8xrkBqtbAGgZd3z497e7pyLJVCuI0oiczyzQ
// SIG // Ol86CHwVYfUCKBWfOW3Gai/4MHiuWeTsavi1lFaWNffD
// SIG // OAw8ghlAzoCKKGoCWR9AbAvC77A/NXrrpXlqi9EKIuZg
// SIG // +AsQEqwhYBStvMk117/9mNdaATQFemayjpzxu+GhyXbw
// SIG // 9bIcTE1AGVm4RqtMyKxMlELjJ675Uz+TymN8JZfLl8Q2
// SIG // nvmuoDCCBJ0wggOFoAMCAQICEGoLmU/AACWrEdtFH1h6
// SIG // Z6IwDQYJKoZIhvcNAQEFBQAwcDErMCkGA1UECxMiQ29w
// SIG // eXJpZ2h0IChjKSAxOTk3IE1pY3Jvc29mdCBDb3JwLjEe
// SIG // MBwGA1UECxMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMSEw
// SIG // HwYDVQQDExhNaWNyb3NvZnQgUm9vdCBBdXRob3JpdHkw
// SIG // HhcNMDYwOTE2MDEwNDQ3WhcNMTkwOTE1MDcwMDAwWjB5
// SIG // MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3Rv
// SIG // bjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWlj
// SIG // cm9zb2Z0IENvcnBvcmF0aW9uMSMwIQYDVQQDExpNaWNy
// SIG // b3NvZnQgVGltZXN0YW1waW5nIFBDQTCCASIwDQYJKoZI
// SIG // hvcNAQEBBQADggEPADCCAQoCggEBANw3bvuvyEJKcRjI
// SIG // zkg+U8D6qxS6LDK7Ek9SyIPtPjPZSTGSKLaRZOAfUIS6
// SIG // wkvRfwX473W+i8eo1a5pcGZ4J2botrfvhbnN7qr9EqQL
// SIG // WSIpL89A2VYEG3a1bWRtSlTb3fHev5+Dx4Dff0wCN5T1
// SIG // wJ4IVh5oR83ZwHZcL322JQS0VltqHGP/gHw87tUEJU05
// SIG // d3QHXcJc2IY3LHXJDuoeOQl8dv6dbG564Ow+j5eecQ5f
// SIG // Kk8YYmAyntKDTisiXGhFi94vhBBQsvm1Go1s7iWbE/jL
// SIG // ENeFDvSCdnM2xpV6osxgBuwFsIYzt/iUW4RBhFiFlG6w
// SIG // HyxIzG+cQ+Bq6H8mjmsCAwEAAaOCASgwggEkMBMGA1Ud
// SIG // JQQMMAoGCCsGAQUFBwMIMIGiBgNVHQEEgZowgZeAEFvQ
// SIG // cO9pcp4jUX4Usk2O/8uhcjBwMSswKQYDVQQLEyJDb3B5
// SIG // cmlnaHQgKGMpIDE5OTcgTWljcm9zb2Z0IENvcnAuMR4w
// SIG // HAYDVQQLExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xITAf
// SIG // BgNVBAMTGE1pY3Jvc29mdCBSb290IEF1dGhvcml0eYIP
// SIG // AMEAizw8iBHRPvZj7N9AMBAGCSsGAQQBgjcVAQQDAgEA
// SIG // MB0GA1UdDgQWBBRv6E4/l7k0q0uGj7yc6qw7QUPG0DAZ
// SIG // BgkrBgEEAYI3FAIEDB4KAFMAdQBiAEMAQTALBgNVHQ8E
// SIG // BAMCAYYwDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0B
// SIG // AQUFAAOCAQEAlE0RMcJ8ULsRjqFhBwEOjHBFje9zVL0/
// SIG // CQUt/7hRU4Uc7TmRt6NWC96Mtjsb0fusp8m3sVEhG28I
// SIG // aX5rA6IiRu1stG18IrhG04TzjQ++B4o2wet+6XBdRZ+S
// SIG // 0szO3Y7A4b8qzXzsya4y1Ye5y2PENtEYIb923juasxtz
// SIG // niGI2LS0ElSM9JzCZUqaKCacYIoPO8cTZXhIu8+tgzpP
// SIG // sGJY3jDp6Tkd44ny2jmB+RMhjGSAYwYElvKaAkMve0aI
// SIG // uv8C2WX5St7aA3STswVuDMyd3ChhfEjxF5wRITgCHIes
// SIG // BsWWMrjlQMZTPb2pid7oZjeN9CKWnMywd1RROtZyRLIj
// SIG // 9jGCBHkwggR1AgEBMIGHMHkxCzAJBgNVBAYTAlVTMRMw
// SIG // EQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRt
// SIG // b25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRp
// SIG // b24xIzAhBgNVBAMTGk1pY3Jvc29mdCBDb2RlIFNpZ25p
// SIG // bmcgUENBAgphD3hNAAAAAAADMAkGBSsOAwIaBQCggaQw
// SIG // GQYJKoZIhvcNAQkDMQwGCisGAQQBgjcCAQQwHAYKKwYB
// SIG // BAGCNwIBCzEOMAwGCisGAQQBgjcCARUwIwYJKoZIhvcN
// SIG // AQkEMRYEFKW3Nb/DVwoopNClqG44njwrTI33MEQGCisG
// SIG // AQQBgjcCAQwxNjA0oBqAGABjAHUAcwB0AG8AbQB3AGkA
// SIG // egAuAGoAc6EWgBRodHRwOi8vbWljcm9zb2Z0LmNvbTAN
// SIG // BgkqhkiG9w0BAQEFAASCAQA6wCpa+zQMtl4YAlGXyoeU
// SIG // n9EbTMo1wuKaKMJdZUg/PWlmEgGz5qN7JJJzfywovxeJ
// SIG // EiNPjxq1MkZExmrjLTZLVjpIW+l1jLMCg3AaKKmYx3bS
// SIG // AuwZxBLwAj9WWZ7N2t7AC7rFrOmPK9oDLPtAhIkt7Sbj
// SIG // 81qf746l+cqUa490n8/trZG5ih5xlkCk9ZzFUSPRnA4/
// SIG // XU8yNJ8ihZVX8KxEGjSywoAzsBB5zfgG+/Zwm4k3TF4V
// SIG // Taw93B8ytpsuYN3D0VYjZljRbYA1+RXHGP1JlKXYcgzR
// SIG // KJBd63thNo+gqU7c2wjyYDz0CRngD3HkWzLFIUI49c4X
// SIG // zeaDc7K9LZ/uoYICHzCCAhsGCSqGSIb3DQEJBjGCAgww
// SIG // ggIIAgEBMIGHMHkxCzAJBgNVBAYTAlVTMRMwEQYDVQQI
// SIG // EwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4w
// SIG // HAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xIzAh
// SIG // BgNVBAMTGk1pY3Jvc29mdCBUaW1lc3RhbXBpbmcgUENB
// SIG // AgphFCynAAAAAAAGMAcGBSsOAwIaoF0wGAYJKoZIhvcN
// SIG // AQkDMQsGCSqGSIb3DQEHATAcBgkqhkiG9w0BCQUxDxcN
// SIG // MDgwMTA4MTcxOTQzWjAjBgkqhkiG9w0BCQQxFgQUFqso
// SIG // 4CAh27Kw8u7dxFFeGEydqYcwDQYJKoZIhvcNAQEFBQAE
// SIG // ggEAYdnJbtaeYMd65sKQvFGZpVloHLxvlscFrJjuil/o
// SIG // Xa9FqGxoLxQxik9nUEd7NaPU/tII/FXUZg1WP1gu8OJX
// SIG // TVsDOjAVLyH4jwTP2/VhUksgNr6I5zm2uLJdoqtsIaV/
// SIG // sf+3Ib/mfUo/10P/rCOeQgBSbOHcKm7sKddwfI/xA2HE
// SIG // mdttAwzXsOqlXkdaXIwK1jDLxij6GVUKI4JpagZpy5QO
// SIG // dn8aLoHIG8PuGyYoNDdgi1UlLst1MHZTkbZNvPBQ3mAz
// SIG // tXy/QVHq2GMLWQvqZhGyRb6iBxbbmQxrI5S+57+s5lzn
// SIG // 3EF40Hc9lXNF73eOg5p0ikNORGffKYGu+SXPJg==
// SIG // End signature block
