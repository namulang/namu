
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
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
		strProjTemplate = strProjTemplatePath + '\\default.vcproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
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
	try
	{
		// Add the folders to your project
		var strSrcFilter1 = wizard.FindSymbol('SOURCE_FILTER');
		var strSrcFilter2 = wizard.FindSymbol('HEADER_FILTER');		
		var strSrcFilter3 = wizard.FindSymbol('RESOURCE_FILTER');
		
		var group1 = proj.Object.AddFilter('Source Files');
		var group2 = proj.Object.AddFilter('Header Files');
		var group3 = proj.Object.AddFilter('Resource Files');			
		
		group1.Filter = strSrcFilter1;
		group2.Filter = strSrcFilter2;
		group3.Filter = strSrcFilter3;			
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
		var config = proj.Object.Configurations('Debug');
		config.IntermediateDirectory = 'Debug';
		config.OutputDirectory = 'Debug';
		config.CharacterSet = charSetMBCS;
		config.useOfMfc = useOfMfc.useMfcDynamic;

		var CLTool = config.Tools('VCCLCompilerTool');
		// TODO: Add compiler settings

		CLTool.DebugInformationFormat = debugEnabled; 
		CLTool.DebugInformationFormat = debugOption.debugEditAndContinue;
		CLTool.SuppressStartupBanner = true; 
		CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDebugDLL; 
		CLTool.WarningLevel = warningLevelOption.warningLevel_3; 
		CLTool.Optimization = optimizeOption.optimizeDisabled;
		CLTool.MinimalRebuild = true;
		CLTool.DebugInformationFormat = debugOption.debugEditAndContinue;
		CLTool.PreprocessorDefinitions = "WIN32;_WINDOWS;_DEBUG";
		CLTool.UsePrecompiledHeader = pchOption.pchGenerateAuto;	

		var LinkTool = config.Tools('VCLinkerTool');
		// TODO: Add linker settings

		LinkTool.ProgramDatabaseFile = "$(OutDir)/$(ProjectName).pdb"; 
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalYes; 
		LinkTool.OutputFile = "$(OutDir)/$(ProjectName).exe";
		LinkTool.SuppressStartupBanner=true;  // nologo
		LinkTool.AdditionalDependencies="opengl32.lib glu32.lib glut32.lib";
		LinkTool.SubSystem = subSystemOption.subSystemWindows;



		config = proj.Object.Configurations('Release');
		config.IntermediateDirectory = 'Release';
		config.OutputDirectory = 'Release';
		config.CharacterSet = charSetMBCS;	
		config.useOfMfc = useOfMfc.useMfcDynamic;
		
		var CLTool = config.Tools('VCCLCompilerTool');
		// TODO: Add compiler settings

		CLTool.DebugInformationFormat = debugEnabled; 
		CLTool.DebugInformationFormat = debugOption.debugEnabled;	
		CLTool.SuppressStartupBanner = true; 
		CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDLL; 
		CLTool.WarningLevel = warningLevelOption.warningLevel_3; 
		CLTool.Optimization = optimizeOption.optimizeMaximizeSpeed;
		CLTool.MinimalRebuild = true;
		CLTool.PreprocessorDefinitions = "WIN32;_WINDOWS;NDEBUG";
		CLTool.UsePrecompiledHeader = pchOption.pchGenerateAuto;	

		var LinkTool = config.Tools('VCLinkerTool');
		// TODO: Add linker settings

		LinkTool.ProgramDatabaseFile = "$(OutDir)/$(ProjectName).pdb"; 
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalYes; 
		LinkTool.OutputFile = "$(OutDir)/$(ProjectName).exe";
		LinkTool.SuppressStartupBanner=true;  // nologo
		LinkTool.AdditionalDependencies="opengl32.lib glu32.lib glut32.lib";
		LinkTool.SubSystem = subSystemOption.subSystemWindows;	
	}
	catch(e)
	{
		throw e;
	}
}

function PchSettings(proj)
{
	// TODO: specify pch settings
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

function GetTargetName(strName, strProjectName)
{
	try
	{
		// TODO: set the name of the rendered file based on the template filename
		var strTarget = strName;
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		if (strName == 'readme.txt')
			strTarget = 'ReadMe.txt';

		if (strName == 'sample.txt')
			strTarget = 'Sample.txt';
			
		if (strName == 'stdafx.cpp')
			strTarget =  'stdafx.cpp';
	
		if (strName == 'stdafx.h')
			strTarget =  'stdafx.h';	

		if (strName == 'OpenGL.h')
			strTarget =  strProjectName + '.h';		
			
		if (strName == 'OpenGL.cpp')
			strTarget =  strProjectName + '.cpp';					

		if (strName == 'MainFrm.h')
			strTarget =  'MainFrm.h';		
			
		if (strName == 'MainFrm.cpp')
			strTarget =  'MainFrm.cpp';					

		if (strName == 'OpenGLView.h')
			strTarget =  strProjectName + 'View.h';		
			
		if (strName == 'OpenGLView.cpp')
			strTarget =  strProjectName + 'View.cpp';					

		if (strName == 'OpenGLDoc.h')
			strTarget =  strProjectName + 'Doc.h';		
			
		if (strName == 'OpenGLDoc.cpp')
			strTarget =  strProjectName + 'Doc.cpp';					

		if (strName == 'OpenGL.rc')
			strTarget =  strProjectName + '.rc';

		if (strName == 'resource.h')
			strTarget =  'Resource.h';		
			
		if (strName == 'Res/OpenGL.ico')
			strTarget =  'Res/' + strProjectName + '.ico';					

		if (strName == 'earth.bmp')
			strTarget =  'earth.bmp';					

		if (strName == 'Res/OpenGL.rc2')
			strTarget =  'Res/' + strProjectName + '.rc2';
			
		if (strName == 'Res/OpenGLDoc.ico')
			strTarget =  'Res/' + strProjectName + 'Doc.ico';					
						
		if (strName == 'Res/OpenGL.manifest')
			strTarget =  'Res/' + strProjectName + '.manifest';							
		
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
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}
