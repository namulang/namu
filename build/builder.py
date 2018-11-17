import os
import sys
import shutil
import platform

frame = "======================================================="

def branch(command):
    if command == "help":
        return help()
    elif command == "history":
        return history()
    elif command == "clean":
        return clean()
    elif command == "commit":
        return commit()
    elif command == "build":
        return build()
    elif command == "run":
        arg = None if len(sys.argv) < 3 else sys.argv[2]
        return run(arg)

    print(command + " is unknown.")    

def run(arg):
    if arg is None:
        print("build Node and run one of next followings...")
        print("\t * unittests")
        return -1

    if arg == "unittests":
        result = build()
        if result:
            return result
        os.system("unittests")

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
    print("")
    generator = "MinGW Makefiles" if isWindow() else "Unix Makefiles"
    print("generating makefiles as " + generator + "...")

    res = os.system("cmake -G \"" + generator + "\"")
    if res != 0:
        return -1

def _make():
    print("")
    make_option = "-j4 -s"  # j4 -> 4 multithread.
                            # s ->  don't print command.
    print("making " + make_option + "...", end=" ")
    if isWindow():
        os.system("mingw32-make -v")
        result = os.system("mingw32-make " + make_option)
        if result != 0:
            print("failed")
            return -1
    else:
        os.system("make -v")
        result = os.system("make " + make_option)
        if result != 0:
            print("failed")
            return -1
    print("ok")

def build():
    #_beautify()
    if _createMakefiles(): 
        return -1
    if _make():
        return -1
    return _ut();

def _ut():
    print("")
    print("let's initiate unit tests...", end=" ")
    res = os.system("unittests.exe")
    if res == 0:
        print("ok")
    return res

def commit():
    return 0

def checkDependencies():
    print("")
    print ("checking dependencies...", end=" ")
    simple_depencies = ["git", "cmake"]

    for e in simple_depencies:
        if not shutil.which(e):
            print("\t > " + e + " is NOT installed!")
            return -1

    if isWindow():
        if not shutil.which("mingw32-make"):
            print("\t > mingw32-make on Windows is NOT installed!")
            return -1
    elif not shutil.which("make"):
        print("\t > make for linux is NOT installed!")
        return -1
    print("ok")

def version():
    print("")
    print("Builder. Support-utility for building World v1.1")
    print("Copyrights (c) kniz, 2009-2018")

def help():
    print("Usage: builder.py <command> <arg1> <arg2> ...")
    print("")
    print("command list:")
    print("\t * help")
    print("\t * history")
    print("\t * clean\tclear all cache files of cmake outputs.")
    print("\t * build")
    print("\t * run\t\tbuild + run one of predefined programs.")

def history():
    print("history:")
    print("\t1.1\t11-17-2017")
    print("\t + runs unittests automatically after build is success.")
    print("\t - it can't build it outside of build folder.")
    print("")
    print("\t1.0\t07-10-2017")
    print("\t + merge 2 seperated utilities and recoded with python.")
    print("")
    print("\t0.3")
    print("\t - Now can choose whether make leave script files or not when build a sdk.")
    print("")
    print("\t0.2.5")
    print("\t + this also package script examples.")
    print("")
    print("\t0.2.4")
    print("\t - resolved that xcopy can't be called cause of environmental variable(= path)")
    print("")
    print("\t0.2.3\t04-15-2015")
    print("\t + build sdk with some sound resources as contents of sounds.")
    print("")
    print("\t0.2.2\t08-14-2013")
    print("\t - path problem has been resolved. now \"\" will be added at the edge of path.")
    print("")
    print("\t0.2.1")
    print("\t - Fix to create sub directory which was named \"Scripts\" in Library Directory")
    print("")
    print("\t0.2")
    print("\t + Manager package will be added to ./Modules directory.")
    print("")
    print("\t0.1")
    print("\t + Now pdb files can be attachable with choose.")
    print("\t + MDK Templates has been seperated from Includes")
    print("\t - Bugs fix.")
    print("")
    print("\t0.0.2\t05-08-2013")
    print("\t + function that package dependencies(what located on './Dependencies/Libraries') has benn added.")
    print("")
    print("\t0.0.1\t??-??-2013")
    print("\t + Created.")

def clean():
    print("Clearing next following files...")
    _clean("..\\")
    print("was removed successfully.")

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
            if dir == "CMakeFiles" or dir == "tmp" or dir == "generated":
                abs_dir = os.path.join(path, dir)
                print("\t * " + abs_dir)
                shutil.rmtree(abs_dir)
def main():
    version()
    print(frame)
    print("")
    
    cwd=os.path.dirname(os.path.realpath(sys.argv[0]))
    os.chdir(cwd)
    print("building directory is " + cwd)

    if checkDependencies():
        print("\n** This program needs following softwares to be fully functional.")
        print("\tgit, cmake, make or mingw32-make")
        print("please install them on your own. **\n")
        return

    if len(sys.argv) == 1:
        help()
    else:
        branch(sys.argv[1])

    print("")

main()
print(" - end -")
