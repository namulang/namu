#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import stat
import sys
import shutil
import platform
import subprocess
import re
from operator import eq
from tempfile import gettempdir

frame = "======================================================="

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def rmtree(top):
    for root, dirs, files in os.walk(top, topdown=False):
        for name in files:
            filename = os.path.join(root, name)
            os.chmod(filename, stat.S_IWUSR)
            os.remove(filename)
        for name in dirs:
            os.rmdir(os.path.join(root, name))
    os.rmdir(top)

def printErr(msg):
    print(bcolors.WARNING + " × " + bcolors.ENDC + msg)

def printInfo(msg):
    print(bcolors.OKCYAN + msg + bcolors.ENDC)

def printInfoEnd(msg):
    print(bcolors.OKCYAN + msg + bcolors.ENDC, end=" ")

def printOk(msg):
    print(bcolors.OKGREEN + " v " + bcolors.ENDC + msg)

def printOkEnd(msg):
    print(bcolors.OKGREEN + " v " + bcolors.ENDC + msg, end=' ')

def cmdstr(cmd):
    try:
        ret = str(subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True))
        if platform.system() == "Windows":
            ret = ret[2:-5]
        else:
            ret = ret[2:-3]
    except subprocess.CalledProcessError as ex:
        try:
            return f"error: {ex.output.decode('euc-kr').encode('utf-8')}"
        except:
            return "error: "

    return ret

python3 = ""
def branch(command):
    if command == "ver":
        return showRawVersion()

    version()

    if command == "help":
        return help()
    elif command == "prerequisites":
        return prerequisites()
    elif command == "mv":
        arg = None if len(sys.argv) < 3 else sys.argv[2]
        return mv(arg)
    elif command == "history":
        return history()
    elif command == "clean":
        return clean()
    elif command == "commit":
        return commit()
    elif command == "rebuild":
        return rebuild()
    elif command == "rel":
        return relBuild()
    elif command == "reldbg":
        return relDbgBuild()
    elif command == "dbg":
        return dbgBuild()
    elif command == "format":
        return formatCodes(True)
    elif command == "wasm":
        arg3 = None if len(sys.argv) < 3 else sys.argv[2]
        return wasmBuild(arg3)
    elif command == "test":
        arg1 = "" if len(sys.argv) < 3 else sys.argv[2]
        return test(arg1);
    elif command == "run":
        return run()
    elif command == "cov":
        return covBuild()
    elif command == "doc":
        return doc()
    elif command == "pubdoc":
        return _publishDoc()
    elif command == "make":
        return build(False)
    elif command == "pub":
        arg2 = None if len(sys.argv) < 3 else sys.argv[2]
        return pub(arg2);

    printErr(command + " is unknown command.")
    return -1

def mv(directory):
    print("directory= " + directory)
    for path, dirs, files in os.walk(directory):
        for file in files:
            ext = os.path.splitext(file)[1]
            if  ext != ".in" and ext != ".cc" and ext != ".cpp" and ext != ".hpp" and ext != ".inl":
                continue

            prevPath = os.path.join(path, file)
            nextPath = os.path.join(path, file[:1].lower() + file[1:])
            if prevPath == nextPath: continue
            answer = input(prevPath + " -> " + nextPath + " -> [y/n] ")
            if answer == "": answer = "y"
            if answer == "y":
                os.system("git mv " + prevPath + " " + nextPath)

def _cleanParser():
    global namuDir

    pathDir= namuDir
    if isWindow():
        pathDir += "\\mod\\core\\worker\\bison\\"
        leafPathDir = cwd + "\\..\\mod\\leaf\\parser\\bison\\"
    else:
        pathDir += "/mod/core/worker/bison/"
        leafPathDir = cwd + "/../mod/leaf/parser/bison/"

    printInfoEnd("removing generated parser...")
    os.system("rm " + pathDir + "lowscanner.cpp")
    os.system("rm " + pathDir + "lowscanner.hpp")
    os.system("rm " + pathDir + "lowparser.cpp")
    os.system("rm " + pathDir + "lowparser.hpp")
    os.system("rm " + leafPathDir + "leafLowparser.cpp")
    os.system("rm " + leafPathDir + "leafLowparser.hpp")
    os.system("rm " + leafPathDir + "leafLowscanner.hpp")
    os.system("rm " + leafPathDir + "leafLowscanner.cpp")

def _cleanIntermediates():
    printInfoEnd("removing intermediate outputs...")
    if isWindow():
        print("del /s /f /q " + cwd + "\\xml")
        os.system("del /s /f /q " + cwd + "\\xml")
        os.system("del /s /f /q " + cwd + "\\*.tmp")
    else:
        os.system("rm -rf " + cwd + "/xml")
        os.system("rm -rf " + cwd + "/*.tmp")
    os.system("git config --unset user.name") # remove local config only
    os.system("git config --unset user.email")
    printOk("done.")
    _cleanCoverageFiles()

def cleanGhPages():
    global cwd, python3, externalDir

    # clean before fetch repo:
    _cleanIntermediates()
    if isWindow():
        os.system("del /s /f /q " + cwd + "\\html\\ref")
    else:
        os.system("rm -rf " + cwd + "/html/ref")

    # standby gh-pages repo:
    printInfoEnd("cloning gh-pages branch...")
    if isWindow():
        res = os.system("git clone -b gh-pages --depth 5 https://github.com/namulang/namu --single-branch " + cwd + "\\html")
    else:
        res = os.system("git clone -b gh-pages --depth 5 https://github.com/namulang/namu --single-branch " + cwd + "/html")
    if res != 0:
        printErr("fail to clone gh-pages repo.")
        _cleanIntermediates()
        return -1
    printOk("done.")

    # clean removed or modified doxygen outputs:
    if isWindow():
        os.system("del /s /f /q " + cwd + "\\html\\ref\\*")
        os.system("del /s /f /q " + cwd + "\\html\\_site\\*")
    else:
        os.system("rm -rf " + cwd + "/html/ref/*")
        os.system("rm -rf " + cwd + "/html/_site/*")

def docDoxygen():
    global cwd, python3, externalDir

    # build doxygen:
    printInfoEnd("generating docs using doxygen...")
    if isWindow():
        res = os.system("doxygen " + cwd + "\\Doxyfile")
    else:
        res = os.system("doxygen " + cwd + "/Doxyfile")
    if res != 0:
        printErr("fail to run doxygen.")
        _cleanIntermediates()
        return -1

def doc():
    if checkDependencies([GitDependency(), CMakeDependency(), DoxygenDependency()]):
        return -1

    cleanGhPages()
    docDoxygen()
    return 0

def formatCodes(showLog):
    if checkDependencies([ClangFormatDependency()]):
        return -1

    global cwd
    root = cwd + "/../"
    if showLog: print("code formatting:")
    for path, dirs, files in os.walk(root):
        if "../mod/" not in path: continue
        if "/worker/bison" in path: continue
        if "/leaf/parser/bison" in path: continue
        for file in files:
            filePath = os.path.join(path, file)
            ext = os.path.splitext(file)[1]
            if  ext != ".cc" and ext != ".cpp" and ext != ".hpp" and ext != ".inl":
                continue
            if showLog: print("\t formatting " + filePath + ", ext=" + ext + " file...")
            os.system("clang-format -i " + filePath)

def prerequisites():
    if checkDependencies([ClangDependency(), MSBuildDependency(), GitDependency(), PythonDependency(), FlexDependency(), CMakeDependency(), BisonDependency(), ClangTidyDependency(), ClangFormatDependency()]):
        return -1
    return 0

def _publishDoc():
    if checkDependencies([GitDependency()]):
        return -1

    # pushing on gh-pages:
    origin = cmdstr("git rev-parse --verify HEAD")
    print("origin=" + str(origin))
    os.chdir(cwd + "/html")
    os.system("git add .")
    os.system("git config user.name \"autodocbot\"") # put on local config.
    os.system("git config user.email \"knizofficial@gmail.com\"")
    res = os.system("git commit -m \"The our poor little Autobot \\(❍ᴥ❍ʋ)/ generated docs for " + origin + ", clitter-clatter.\"")
    if res != 0:
        printErr("fail to commit on gh-pages.")
        printInfo("but it seems that nothing changed.")
        _cleanIntermediates()
        return 0

    os.chdir(cwd)
    print("now, please push new commit.")
    _cleanIntermediates()
    return 0

config=""

def wasmBuild(arg):
    global config, cwd, binDir

    if checkDependencies([EmmakeDependency(), EmcmakeDependency()]):
        return -1

    config="-DCMAKE_BUILD_TYPE=Release"
    clean()
    os.system("emcmake cmake " + config + " " + cwd)
    os.system("emmake make -j8 -s")

def dbgBuild():
    global config, cwd

    winProp="-t:Rebuild -p:Configuration=Debug"
    config="-DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_CLANG_TIDY=\"clang-tidy\""
    print(config)

    clean()
    return build(True)

def _cleanCoverageFiles():
    if isWindow(): return

    global cwd
    printInfoEnd("removing coverage report files...")
    os.system("rm -rf " + cwd + "/coverage")
    os.system("rm " + cwd + "/*.profraw")
    os.system("rm " + cwd + "/logs")
    os.system("rm " + cwd + "/cov.info")
    printOk("done.")

def covBuild():
    if isWindow():
        printErr("I can collect coverages in linux only.")
        return -1

    global config, cwd, namuDir
    config="-DCMAKE_BUILD_TYPE=Debug -DCOVERAGE_TOOL=gcov"
    print(config)

    clean()
    build(True)
    printInfoEnd("running TC files...")
    res = os.system("cd " + namuDir + "/bin && ./test")
    if res != 0:
        printErr("failed to pass TCs.")
        return -1

    printOk("done.")

    printInfoEnd("collects gcov results...")
    if checkDependencies([LlvmCovDependency(), GcovDependency(), LcovDependency(), GenHtmlDependency()]):
        return -1

    res = os.system("lcov --directory " + cwd + " --base-directory " + cwd + " --gcov-tool " + cwd + "/llvm-gcov.sh --capture -o cov.info")
    if res != 0:
        printErr("fail to collect gcov results")
        return -1

    printOk("done")

    printInfoEnd("generating coverage info in html...")
    res = os.system("genhtml " + cwd + "/cov.info -o coverage")
    if res != 0:
        printErr("fail to generate report html files.")
        return -1

    printOk("done")

def relBuild():
    global config, winProp

    clean()
    winProp="-t:Rebuild -p:Configuration=Release"
    config="-DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_CLANG_TIDY=\"clang-tidy\""
    return build(True)

def relDbgBuild():
    global config, winProp

    clean()
    winProp="-t:Rebuild -p:Configuration=Release"
    config="-DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_CLANG_TIDY=\"clang-tidy\" -DCMAKE_RELEASE_INCLUDE_DBG_INFO=True"
    return build(True)

# currently this application only supports window and linux.
def isWindow():
    return platform.system().find("Windows") >= 0

# def _beautify():
#     print("beautify source codes...")
#     for path, dirs, files in os.walk("..\\"):
#         for file in files:
#             file_path = os.path.join(path, file)
#             ext = os.path.splitext(file_path)[1]
#             if  ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h" or \
#                 ext == ".inl":
#                 # change encoding:
#                 # beautify
#                 print("\t" + file)
#                 os.system("astyle --style=world " + file_path)

def _createMakefiles():
    global generator, config
    print("")

    printInfoEnd("generating makefiles as " + generator + "...")

    res = os.system("cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 . -G \"" + generator + "\" " + config)
    if not isWindow() and res != 0:
        return -1

    printOk("done")

# World uses BuildInfo at CHANGELOGS.md
# and builder.py drives to all world libraries and make it sync all build-info including
# doc releasing.
ver_major = 0
ver_minor = 0
ver_fix = 0
ver_name = ""
ver_buildcnt = 0
def _extractBuildInfo(): # from CHANGELOGS.md at root directory.
    global cwd, ver_major, ver_minor, ver_fix, ver_name, ver_buildcnt
    if isWindow():
        path = cwd + "\\..\\CHANGELOGS.md"
    else:
        path = cwd + "/../CHANGELOGS.md"

    fp = open(path, "r", encoding="UTF8")
    while True:
        line = fp.readline()
        if not line: break
        if line[:4] in "## v":
            minor_head_n = line.find('.', 5) + 1
            ver_major = int(line[4:minor_head_n-1])
            ver_minor = int(line[minor_head_n: minor_head_n+1])
            fix_head_n = line.find('.', minor_head_n) + 1
            ver_name_n = line.find(' ', fix_head_n+1) + 1
            ver_fix_str = line[fix_head_n: ver_name_n]
            if ver_fix_str in "" or ver_fix_str in " ":
                ver_fix = 0
            else:
                ver_fix = int(ver_fix_str)
            ver_name = line[ver_name_n: len(line)-8]
            break

    fp.close()
updated = False

def _updateLine(lines, n, trg, basestr):
    global updated
    idx = len(basestr)-1
    value = int(lines[n][idx:len(lines[n])-2])
    if value != trg:
        lines[n] = basestr + str(trg) + ")\n"
        updated = True

def _updateLineString(lines, n, trg, basestr):
    global updated
    idx = len(basestr)-1
    value = lines[n][idx:len(lines[n])-2]
    if not eq(value, trg):
        lines[n] = basestr + "\"" + str(trg) + "\")\n"
        updated = True

def _injectBuildInfo():
    global cwd, ver_major, ver_minor, ver_fix, ver_name, ver_buildcnt
    if isWindow():
        path = cwd + "\\CMakeLists.txt"
    else:
        path = cwd + "/CMakeLists.txt"

    printInfoEnd("updating buildinfo on CMakeLists.txt...")
    global updated
    updated = False;
    fp = open(path, "r")
    lines = fp.readlines()
    for n in range(0, len(lines)):
        line = lines[n]
        if line[:17] in "set(VERSION_MAJOR":
            _updateLine(lines, n, ver_major, "set(VERSION_MAJOR ")
        elif line[:17] in "set(VERSION_MINOR":
            _updateLine(lines, n, ver_minor, "set(VERSION_MINOR ")
        elif line[:15] in "set(VERSION_FIX":
            _updateLine(lines, n, ver_fix, "set(VERSION_FIX ")
        elif line[:16] in "set(VERSION_NAME":
            _updateLineString(lines, n, ver_name, "set(VERSION_NAME ");
    fp.close()

    if updated == False:
        printOk("skip")
        return

    fp = open(path, "w")
    fp.write("".join(lines))
    fp.close()
    printOk("updated!")

def _incBuildCnt():
    global cwd
    if isWindow():
        path = cwd + "\\CMakeLists.txt"
    else:
        path = cwd + "/CMakeLists.txt"
    printInfoEnd("Increase Build count...")
    fp = open(path, "r")
    lines = fp.readlines()
    buildcnt = 0
    for n in range(0, len(lines)):
        line = lines[n]
        if line[:15] in "set(BUILD_COUNT":
            buildcnt = int(line[16:len(line)-2])
            lines[n] = "set(BUILD_COUNT " + str(buildcnt+1) + ")\n"
            break
    fp.close()

    fp = open(path, "w")
    fp.write("".join(lines))
    fp.close()
    printOk("done")

def _make():
    global cwd, config, winProp
    if isWindow():
        printInfoEnd("build the generated solution using visual studio's msbuild tool...")
        os.system("dir " + cwd + "\\mod")
        os.system("dir " + cwd + "\\mod\\namu")
        res = os.system("msbuild " + winProp + " " + cwd + "\\mod\\namu\\namu.vcxproj")
        if res != 0:
            printErr("failed")
            return res

        res = os.system("msbuild " + winProp + " " + cwd + "\\mod\\bundle\\sys\\sys.vcxproj")
        if res != 0:
            printErr("failed")
            return res

        printOkEnd("built.")
        printInfo("please check your bin/{configuration} directory for these output files.")
        return res

    print("")
    make_option = "-j8 -s"  # j4 -> 4 multithread.
                            # s ->  don't print command.
    printInfoEnd("making " + make_option + "...")
    if not isWindow():
        os.system("make -v")
        result = os.system("make " + make_option)
        if result != 0:
            printErr("failed")
            return -1

    printOk("done")

def _checkGTest():
    global externalDir, generator

    dir = os.path.join(externalDir, "googletest")
    printInfoEnd("checking googletest repo at " + externalDir + "...")
    if _hasDir(dir):
        printOk("repo found. skip installing it.")
        return

    _makeDir(dir)
    os.system("git clone https://github.com/google/googletest " + dir)
    originDir = os.getcwd()
    os.chdir(dir)
    os.system("cmake " + os.path.join(dir, "CMakeLists.txt -G \"" + generator + "\""))
    if not isWindow():
        os.system("sudo make install")
    os.chdir(originDir)
    printOk("installed.")
    _cleanIntermediates()

def _makeDir(dir):
    try:
        if not os.path.exists(dir):
            os.makedirs(dir)
    except OSError:
        print("can't create dir at " + dir)

def _hasDir(dir):
    return os.path.exists(dir)

def rebuild():
    clean()
    return build(true)

def build(incVer):
    if checkDependencies([ClangDependency(), MSBuildDependency(), GitDependency(), CMakeDependency(), BisonDependency(), FlexDependency(), ClangTidyDependency()]):
        return -1

    _checkGTest()
    if incVer:
        _injectBuildInfo()
        if _createMakefiles():
            return -1

        _incBuildCnt()
    if _make():
        return -1

    return 0

def pub(arg):
    global cwd, binDir, ver_major, ver_minor, ver_fix

    if arg == None:
        printErr("please input a platfrom after pub command: 'deb', 'mac'")
        return -1

    if arg == "deb":
        printInfoEnd("cleaning previous outputs of publishing...")
        debianDir = cwd + "/debian"
        os.chdir(debianDir)
        os.system("mkdir usr")
        os.system("mkdir usr/bin")
        os.system("mkdir usr/lib")
        os.system("mkdir usr/include")
        os.system("mkdir usr/share")
        os.system("mkdir usr/share/namu")
        printOk("done.")
        os.chdir(cwd)

        if relBuild() != 0:
            printErr("release build failed. quit publishing.")
            return -1

        os.chdir(debianDir)
        target = debianDir + "/usr/"
        printInfoEnd("copy outputs into debian target directory")
        os.system("cp " + binDir + "/namu " + target + "bin")
        os.system("cp " + binDir + "/*.so " + target + "lib")
        os.system("cp -r " + binDir + "/pack " + target + "share/namu")
        printOk("done")

        printInfoEnd("packaging...")
        os.chdir(cwd)
        os.system("dpkg -b debian")
        printOk("done")

        printInfoEnd("move package into bin/...")
        os.system("mv debian.deb " + binDir + "/namu-ubuntu-x64.deb")
        printOk("done")

        printInfoEnd("remove local shared libraries...")
        os.system("rm " + binDir + "/*.so")
        printOk("done")

        printInfoEnd("remove debian intermediate files...")
        os.system("rm -rf " + "debian/usr/")
        return 0

    elif arg == 'mac':
        if relBuild() != 0:
            printErr("release build failed. quit publishing.")
            return -1

        printInfoEnd("cleaning redandunt files to package")
        os.chdir(binDir)
        os.system("rm ./test")
        os.system("rm ./logs")
        os.system("cp ../LICENSE.md .")
        os.system("cp ../README.md .")
        os.system("cp ../CHANGELOGS.md .")

        printOk("done")
        printInfoEnd("make an archive")
        os.chdir(binDir + "/..")
        os.system("tar -zcvf namu-macos-x64.tar.gz bin")
        printOk("done")
        return 0

    elif arg == 'win':
        if relBuild() != 0:
            printErr("release build failed. but keep publishing.")

        printInfoEnd("cleaning redandunt files to package")
        os.chdir(binDir)
        os.system("del /S test\\*")
        os.system("rmdir test")
        os.system("del logs")
        os.system("copy ..\\LICENSE.md .")
        os.system("copy ..\\README.md .")
        os.system("copy ..\\CHANGELOGS.md .")
        os.system("move Release\\sys.pack .\\pack\\sys")
        os.system("copy Release\\* .")
        os.system("del /S /Q Release\\*")
        os.system("rmdir Release")
        os.system("zip -9vr namu-win-x64.zip ..\\bin")

        printOk("done")
        printInfoEnd("please make an archive.")
        return 0

    printErr("unknown platform name: " + arg)
    return -1

# arg is "" for dbg or "silent" for rel
def test(arg):
    if build(False) != 0:
        return -1;

    print("")
    printInfoEnd("let's initiate unit tests...")
    global cwd, binDir

    originDir = os.getcwd()
    os.chdir(binDir)
    failedCnt = 0
    ret = 0
    if isWindow():
        res = os.system(".\\test verbose " + arg)
    else:
        res = os.system("./test verbose " + arg)
    if res != 0:
        printErr("test was failed!")
        ret = -1
        failedCnt += 1

    if failedCnt > 0:
        printErr("total " + str(failedCnt) + " TC files has reported that failed.")
    else:
        printOk("all TCs have been passed!");
    os.chdir(originDir)
    return ret

def commit():
    return 0

class ver:
    def __init__(self, major, minor, patch):
        self.major = major
        self.minor = minor
        self.patch = patch
        self.exist = False

    @classmethod
    def fromVerString(self, verString):
        if verString[:3] == "err" or verString == "":
            return ver(0, 0, 0)
        else:
            ret = ver(0, 0, 0)
            res = re.findall(r"[0-9]+\.[0-9]+[\.0-9]+", verString)
            verStr = res[0].split('.') if len(res) > 0 else ""
            if verStr != "":
                ret.major = int(verStr[0])
                ret.minor = int(verStr[1])
                if len(verStr) > 2:
                    ret.patch = int(verStr[2])
                else:
                    ret.patch = 0
            ret.exist = True
            return ret

    def isVerNotSpecified(self):
        return self.major == 0 and self.minor == 0 and self.patch == 0

    def isValid(self, expectVer):
        if expectVer.isVerNotSpecified():
            return self.doesExist()

        return self.major >= expectVer.major and self.minor >= expectVer.minor and self.patch >= expectVer.patch

    def toString(self):
        if self.major == 0 and self.minor == 0 and self.patch == 0:
            return ""
        return f"{self.major}.{self.minor}.{self.patch}"

    def doesExist(self):
        return self.exist

class dependency:
    def getExpectVer(self):
        return ver(0, 0, 0)

    def getName(self):
        return ""

    def getFlag(self):
        return "--version"

    def getInstalledVer(self):
        res = self.onGetInstalledVerString()
        if res[:5] != "error": # usual case
            return ver.fromVerString(res)

        # oddly enough, for some binaries, it always returns an error code even if the file
        # exists. so in this case, you can't check the version and you can't use the output
        # msg to determine whether the file exists.
        # In this case, you have to use shutil to determine directly whether the binary exists
        # in the PATH.
        if shutil.which(self.getName()):
            return ver.fromVerString("0.0.0")
        return ver(0, 0, 0)

    def isValid(self):
        if self.isActivated() == False:
            return True
        return self.getInstalledVer().isValid(self.getExpectVer())

    # if `isActivated` returns true, it means that this dependency has to be checked in all
    # circumstances.
    def isActivated(self):
        return True

    def onGetInstalledVerString(self):
        return cmdstr(f"{self.getName()} {self.getFlag()}")

    def showErrMsg(self):
        installedVer = self.getInstalledVer()
        if installedVer.doesExist() == False:
            printErr(f"{self.getName()} is not installed")
        else:
            printErr(f"{self.getName()} version should be {self.getExpectVer().toString()} but yours is {self.getInstalledVer().toString()}")

    def showSuccessMsg(self):
        if self.isActivated():
            printOkEnd(self.getName())

class FlexDependency(dependency):
    def getExpectVer(self):
        return ver(2, 6, 0)

    def getName(self):
        return "flex"

class PythonDependency(dependency):
    def getExpectVer(self):
        return ver(3, 6, 0)

    def getName(self):
        return "python"

class GitDependency(dependency):
    def getName(self):
        return "git"

class CMakeDependency(dependency):
    def getName(self):
        return "cmake"

    def getExpectVer(self):
        return ver(2, 6, 0)

class DoxygenDependency(dependency):
    def getName(self):
        return "doxygen"

class EmmakeDependency(dependency):
    def getName(self):
        return "emmake"

class EmcmakeDependency(dependency):
    def getName(self):
        return "emcmake"

class BisonDependency(dependency):
    def getName(self):
        return "bison"

    def getExpectVer(self):
        return ver(3, 8, 0)

    def onGetInstalledVerString(self):
        return super().onGetInstalledVerString().split('\n')[0]

class ClangTidyDependency(dependency):
    def getName(self):
        return "clang-tidy"

    def getExpectVer(self):
        return ver(14, 0, 0)

    def onGetInstalledVerString(self):
        return super().onGetInstalledVerString().split('\n')[0]

class LlvmCovDependency(dependency):
    def getName(self):
        return "llvm-cov"

    def onGetInstalledVerString(self):
        return super().onGetInstalledVerString().split('\n')[0]

class ClangDependency(dependency):
    def getName(self):
        return "clang++"

    def getExpectVer(self):
        return ver(14, 0, 0)

    def isActivated(self):
        return isWindow() == False

class MSBuildDependency(dependency):
    def getName(self):
        return "msbuild.exe"

    def getFlag(self):
        return "/version"

    def isActivated(self):
        return isWindow()

    def getExpectVer(self):
        return ver(17, 0, 0) # VS2022

class GcovDependency(dependency):
    def getName(self):
        return "gcov"

    def onGetInstalledVerString(self):
        return super().onGetInstalledVerString().split('\n')[0]

class LcovDependency(dependency):
    def getName(self):
        return "lcov"

class GenHtmlDependency(dependency):
    def getName(self):
        return "genhtml"

class ClangFormatDependency(dependency):
    def getName(self):
        return "clang-format"

    def getExpectVer(self):
        return ver(18, 1, 8)

def checkDependencies(deps):
    printInfoEnd("checking dependencies...")

    hasErr = False;
    for d in deps:
        if d.isValid() == False:
            d.showErrMsg()
            hasErr = True
        else:
            d.showSuccessMsg()
    print("")
    return hasErr

def showRawVersion():
    global ver_major, ver_minor, ver_fix
    print(f"{ver_major}.{ver_minor}.{ver_fix}")
    return 0

def version():
    global ver_name, ver_major, ver_minor, ver_fix, cwd, python3
    print("builder is supporting utility for building namu " + ver_name + " v" + str(ver_major) + "." + str(ver_minor) + "." + str(ver_fix))
    print("created by kniz, 2009-2025")
    print("")

def help():
    print("Usage: builder.py <command> <arg1> <arg2> ...")
    print("")
    print("command list:")
    print("\t * help")
    print("\t * prerequisites check all dependent app and their version")
    print("\t * clean         clear all cache files of cmake outputs.")
    print("\t * dbg           build new binary with debug configuration.")
    print("\t * rel           build new binary with release configuration. binary optimized, debug logs will be hidden.")
    print("\t * reldbg        same as rel. but this includes dbg info.")
    print("\t * test          runs unit tests but skip build if they are built already.")
    print("\t * doc           generate documents only.")
    print("\t * cov           generate coverage file and visualize data with html")
    print("\t * format        apply our code convention rules to current repository.")

def clean():
    printInfo("Clearing next following files...")
    global cwd, binDir, externalDir
    _clean(cwd)
    _cleanIntermediates()
    _cleanDir(binDir)
    _cleanParser()
    if isWindow():
        os.system("del /f /s /q " + cwd + "\\html")
    else:
        os.system("rm -rf " + cwd + "/html")
    printOk("was removed successfully.")

def _clean(directory):
    for path, dirs, files in os.walk(directory):

        for file in files:
            file_path = os.path.join(path, file)
            ext = os.path.splitext(file_path)[1]
            if  ext == ".sln" or ext == ".vcproj" or ext == ".vcxproj" or ext == ".cmake" or \
                file == "CMakeCache.txt" or ext == ".stamp" or ext == ".depend" or file == "Makefile" or \
                ext == ".exe" or ext == ".dll" or ext == ".log" or ext == ".a" or ext == ".so":
                print("\t * " + file_path)
                os.remove(file_path)

        for dir in dirs:
            if dir == "CMakeFiles" or dir == "tmp" or dir == "generated" or dir == "cmake-build-debug" or dir == "Testing":
                abs_dir = os.path.join(path, dir)
                print("\t * " + abs_dir)
                _cleanDir(abs_dir)

def _cleanDir(dir):
    if os.path.isdir(dir) == False: return
    rmtree(dir)


def _where(name):
    cmd = ""
    prefix = ""
    if platform.system() == "Linux" or platform.system() == "Darwin":
        cmd = "which"
    elif platform.system() == "Windows":
        cmd = "where"
        prefix = "\""
    else:
        printErr(platform.system() + " unsupported.")
        return ""

    res = cmdstr(cmd + " " + name)
    ret = ""
    if res:
        ret = prefix + res + prefix
    return ret

def _extractEnv():
    global python3
    if "PYTHON" in os.environ:
        python3 = os.environ["PYTHON"]
    else:
        python3 = _where("python3")
        if not python3:
            python3 = _where("python")
        return python3 == ""
cwd = ""
namuDir = ""
resDir = ""
binDir = ""
externalDir = ""
generator = "Visual Studio 17 2022" if isWindow() else "Unix Makefiles"
winProp = ""

def _init():
    global cwd, namuDir, binDir, externalDir, resDir
    cwd = os.path.dirname(os.path.realpath(sys.argv[0]))
    if isWindow():
        namuDir = cwd + "\\.."
        binDir = namuDir + "\\bin"
        resDir = namuDir + "\\res"
        externalDir = namuDir + "\\external"
        # in order to color output text in windows terminal, I need this.
        os.system('color')
    else:
        namuDir = cwd + "/.."
        binDir = namuDir + "/bin"
        resDir = namuDir + "/res"
        externalDir = namuDir + "/external"

    _extractBuildInfo()
    return _extractEnv()

def main():
    if _init():
        return -1

    os.chdir(cwd)
    if len(sys.argv) == 1:
        help()
    else:
        return branch(sys.argv[1])

    print("")
    return 0

ret = main()
if ret != 0:
    printErr("ends with " + str(ret) + " exit code.")
sys.exit(ret)
