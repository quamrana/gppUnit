#clean-gcov
import os
from os.path import join

totalFiles=0

def removeFile(aFileName):
    global totalFiles
    #print "Removing:",aFileName
    try:
        os.remove(aFileName)
        totalFiles=totalFiles+1
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
        #print root
        [dirs.remove(d) for d in dirs if d.startswith('.') ]
        [dirs.remove(d) for d in dirs if d=='Debug' ]
        processFiles(root,files)


def main():
    walkDir('.')
    print totalFiles,"removed"

if __name__ == "__main__":
    main()
    
