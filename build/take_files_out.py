import os
import sys
import shutil

def take_out(directory, place_to):
	print(" * Directory is " + directory)
	files = os.listdir(directory)
	n = 0
	for e in files:
		n = n + 1
		e_path = os.path.join(directory, e)
		ext = os.path.splitext(e_path)[-1]
		if ext == ".c" or ext == ".cpp" or ext == ".inl" or ext == ".hpp" or ext == ".h":
			shutil.move(e_path, os.path.join(place_to, e))
			print("\t [" + str(++n) + "] " + e_path)


print("TakeFilesOut v1.0")
print("=================")
print("take out files in given directory.")
print("Usage : just drag & drop directories onto this file in Windows")
print(" ")
print(" ")

if len(sys.argv) == 1:
	print("needs at least 2 arguments.")

splited = sys.argv[1].split('\\')
splited.pop(len(splited)-1)
place_to = "\\".join(splited)

for n in range(1, len(sys.argv)-1):
	take_out(sys.argv[n], place_to)

print("");
print(" * were placed to " + place_to)
pause = input()