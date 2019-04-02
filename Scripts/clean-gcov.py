#clean-gcov
import os
import sys

from os.path import join

totalFiles=0

def removeFile(aFileName):
    global totalFiles
    print("Removing:",aFileName)
    try:
        os.remove(aFileName)
        totalFiles=totalFiles+1
    except Exception:
        pass

def removeFiles(root,files):
    # print(root,files)
    for f in files:
        removeFile(join(root,f))

def processFiles(root,files,extensions):
    for ext in extensions:
        removeFiles(root,[f for f in files if f.endswith(ext)])

def walkDir(dir,extensions):
    for root, dirs, files in os.walk(dir, topdown=True):
        # print(root)
        [dirs.remove(d) for d in dirs if d.startswith('.') ]
        [dirs.remove(d) for d in dirs if d=='Debug' ]
        processFiles(root,files,extensions)


def main(args):
    if args==[]:
        args=['.gcda','.gcno','.gcov']
    walkDir('.',args)
    print(totalFiles,"removed")
    print(args)

if __name__ == "__main__":
    main(sys.argv[1:])

