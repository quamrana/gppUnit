#summarise all gcov files

import os
from os.path import join,abspath,basename
import sys

summary = {}
ignoredFiles = []

def readIgnoredFiles():
    file='gcov.ignore'
    try:
        with open(file) as f:
            for line in f:
                ignoredFiles.append(line.strip('\r\n'))
    except:
        pass
def makeInt(value):
    try:
        return int(value)
    except:
        pass
    return 0
    
class SummaryElement:
    def __init__(self,file,count,lineNumber,line,source):
        self.file=file
        self.key = count 
        self.count = makeInt(count)
        self.lineNumber=lineNumber
        self.line=line
        self.source=source.strip()
        self.disallowed=['class','struct']  # uses startswith()
        self.ignored=['}']	# source is exactly one of these
        self.invalid=['catch(...)', 'summ-gcov:ignore']   # if source contains one of these

    def updateCount(self,count):
        self.count+=count
        return self
    def updateSummary(self,count):
        key=self.file+':'+str(self.lineNumber)
        # self.count=count
        current=self
        if key in summary:
            current=summary[key]
        summary[key]=current.updateCount(count)

    def getKey(self):
        return self.key.strip()
    def getCount(self):
        return self.count
    def isUnused(self):
        if self.getCount()>0:
            return False
        ret = (self.isDisallowed() or self.isIgnored() or self.isInvalid())
        return not ret

    def isDisallowed(self):
    	return len([0 for i in self.disallowed if self.source.startswith(i)])>0
    def isIgnored(self):
    	return len([0 for i in self.ignored if (self.source == i)])>0
    def isInvalid(self):
        return len([0 for i in self.invalid if (i in self.source)])>0
    def __cmp__(self,other):
        if self.file<other.file:
            return -1
        if self.file>other.file:
            return 1
        return cmp(self.lineNumber,other.lineNumber)
    def __lt__(self,other):
        return (self.file,self.lineNumber)<(other.file,other.lineNumber)

class FileProcessor:
    def __init__(self):
        self.mapCount={
            '-':self.nullProcedure,
            '$$$$$':self.nullProcedure,
            '#####':self.zeroProcedure,
            '=====':self.zeroProcedure,
            '0':self.callAccrue
            }
        self.reinit()

    def reinit(self):
        self.file=''
        self.accrueLine=self.nullProcedure

    def processCount(self,element):
        procedure=self.callAccrue
        key=element.getKey()
        if key in self.mapCount:
            procedure=self.mapCount[key]
        procedure(element)

    def callAccrue(self,element):
        self.accrueLine(element)

    def nullProcedure(self,element):
        pass

    def zeroProcedure(self,element):
        element.updateSummary(0)

    def process(self,element):
        element.updateSummary(element.getCount())

    def processLine(self,line):
        # print(line)
        elements=line.split(':')
        if len(elements)>2 and len(elements[1]):
            count=elements[0]
            lineNumber=int(elements[1])
            sourceLine = ':'.join(elements[2:])
            source=elements[2]
            if len(elements)>=4:
                if lineNumber==0:
                    if source=='Source':
                        index=line.find(':Source:')
                        self.file=elements[3]
                        self.file=abspath(line[index+8:])
                        self.accrueLine=self.process

            self.processCount(SummaryElement(self.file,count.replace("*", ""),lineNumber,line,sourceLine))

    def processFile(self,file):
        self.reinit()
        # print(file)
        with open(file) as f:
            for line in f:
                self.processLine(line.strip('\r\n'))

def processFiles(root,files):
    p=FileProcessor()
    cov=[f for f in files if f.endswith('.gcov')]
    for f in cov:
        p.processFile(join(root,f))

def walkDir(dir):
    for root, dirs, files in os.walk(dir, topdown=True):
        #print root
        [dirs.remove(d) for d in dirs if d.startswith('.') ]
        [dirs.remove(d) for d in dirs if d=='Debug' ]
        [dirs.remove(d) for d in dirs if d=='Release' ]
        processFiles(root,files)

def isAcceptable(path):
    file=basename(path)
    if file in ignoredFiles:
        return False
    for f in ignoredFiles:
        if file.startswith(f):
            return False
    return True

def writeSummaryToFile(unused,entries):
    with open('gcov.csv','w') as f:
        f.write('Unused Lines,Total Lines,Unusedx10 Lines,Unusedx100 Lines\n')
        f.write(str(unused))
        f.write(',')
        f.write(str(entries))
        f.write(',')
        f.write(str(unused * 10))
        f.write(',')
        f.write(str(unused * 100))
        f.write('\n')


def printSummary(printLines):
    relevant=abspath('.')
    relevantEntries=0
    print(len(summary),'entries - all files')
    file=[]
    for key,value in summary.items():
        if value.file.startswith(relevant):
            if isAcceptable(value.file):
                relevantEntries+=1
                if value.isUnused():
                    file.append(value)

    unused=len(file)
    file.sort()
    fname=''
    for f in file:
        if f.file!=fname:
            print(f.file)
            fname=f.file
        if printLines:
            print(f.line)
    print(unused,'unused of',relevantEntries)
    if relevantEntries == 0:
        return
    perc=(100.0*(relevantEntries-unused))/relevantEntries
    print('%.2f%%' % perc, 'covered')
    writeSummaryToFile(unused,relevantEntries)

def main(args):
    readIgnoredFiles()
    walkDir('.')
    printSummary('p' in args)

if __name__ == "__main__":
    main(sys.argv[1:])
