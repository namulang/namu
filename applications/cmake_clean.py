import os
import shutil

def clean(directory):
    for path, dirs, files in os.walk(directory):

        for file in files:
            file_path = os.path.join(path, file)
            ext = os.path.splitext(file_path)[1]
            if  ext == ".sln" or ext == ".vcproj" or ext == ".vcxproj" or ext == ".cmake" or \
                file == "CMakeCache.txt" or ext == ".stamp" or ext == ".depend":
                print("\t * " + file_path)
                os.remove(file_path)

        for dir in dirs:
            if dir == "CMakeFiles":
                abs_dir = os.path.join(path, dir)
                print("\t * " + abs_dir)
                shutil.rmtree(abs_dir)

print("CMakeClean v1.0")
print("=====================")
print("this clear all caches of CMake on entire World project reculsively.")
print(" ")

print("Next following files...")
clean("..\\")
print("was removed successfully.")

pause = input()