#clean-gcov
import os
from os.path import join

def removeFile(aFileName):
    print "Removing:",aFileName
    try:
        os.remove(aFileName)
    except Exception:
        pass

def removeFiles(root,files):
    for f in files:
        removeFile(join(root,f))
        
def processFiles(root,files):
    removeFiles(root,[f for f in files if f.endswith('.gcda')])
    removeFiles(root,[f for f in files if f.endswith('.gcno')])
    removeFiles(root,[f for f in files if f.endswith('.gcov')])
    
def walkDir(dir):
    for root, dirs, files in os.walk(dir, topdown=True):
        print root
        [dirs.remove(d) for d in dirs if d.startswith('.') ]
        [dirs.remove(d) for d in dirs if d=='Debug' ]
        processFiles(root,files)


def main():
    walkDir('.')

if __name__ == "__main__":
    main()
    
