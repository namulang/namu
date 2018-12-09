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
        print("build world and run one of next followings...")
        print("\t * unittests")
        return -1

    if arg == "unittests":
        result = build()
        if result:
            return result
        return _ut()

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

# World uses BuildInfo at RELEASE.md
# and builder.py drives to all world libraries and make it sync all build-info including 
# doc releasing.
ver_major = 0
ver_minor = 0
ver_patch = 0
ver_name = ""
ver_buildcnt = 0
def _extractBuildInfo(): # from RELEASE.md at root directory.
    global cwd, ver_major, ver_minor, ver_patch, ver_name, ver_buildcnt
    path = cwd + "/../RELEASE.md"

    fp = open(path, "r")
    while True:
        line = fp.readline()
        if not line:
            break
        if line[:4] in "## v":
            minor_head_n = line.find('.', 5) + 1
            ver_major = int(line[4:minor_head_n-1])
            ver_minor = line[minor_head_n: minor_head_n+1]
            ver_name_n = line.find(' ', minor_head_n+1)+1
            ver_patch = line[minor_head_n+1: ver_name_n]
            if ver_patch in "":
                ver_patch = 0
            ver_name = line[ver_name_n: len(line)-6-1-1]
            break

    print(ver_name)
    fp.close()

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
    global cwd
    res = os.system(cwd + "/unittests")
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
    global ver_name, ver_major, ver_minor, ver_patch
    print("")
    print("Builder. Support-utility for building World " + ver_name + " v" + str(ver_major) + "." + str(ver_minor) + str(ver_patch))
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

def clean():
    print("Clearing next following files...")
    global cwd
    _clean(cwd)
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
cwd = ""

def _init():
    global cwd
    cwd=os.path.dirname(os.path.realpath(sys.argv[0]))
    _extractBuildInfo()

def main():
    _init()
  
    version()
    print(frame)
    print("")

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
