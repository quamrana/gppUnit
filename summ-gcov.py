#summarise all gcov files

import os
from os.path import join,abspath

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

class SummaryElement:
    def __init__(self,file,count,lineNumber,line):
        self.file=file
        self.count=count
        self.lineNumber=lineNumber
        self.line=line

    def updateCount(self,count):
        self.count+=count
        return self
    def updateSummary(self,count):
        key=self.file+':'+str(self.lineNumber)
        self.count=count
        current=self
        if key in summary:
            current=summary[key]
        summary[key]=current.updateCount(count)
    
    def getKey(self):
        return self.count.strip()
    def getCount(self):
        return int(self.count)
    def __cmp__(self,other):
        if self.file<other.file:
            return -1
        if self.file>other.file:
            return 1
        return cmp(self.lineNumber,other.lineNumber)

class FileProcessor:
    def __init__(self):
        self.mapCount={ 
            '-':self.nullProcedure,
            '$$$$$':self.nullProcedure,
            '#####':self.zeroProcedure,
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
        elements=line.split(':')
        if len(elements)>2:
            count=elements[0]
            lineNumber=int(elements[1])
            if len(elements)>=4:
                if lineNumber==0:
                    if elements[2]=='Source':
                        index=line.find(':Source:')
                        self.file=elements[3]
                        self.file=abspath(line[index+8:])
                        self.accrueLine=self.process
            
            self.processCount(SummaryElement(self.file,count,lineNumber,line))
            
    def processFile(self,file):
        self.reinit()
        #print file
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
        print root
        [dirs.remove(d) for d in dirs if d.startswith('.') ]
        [dirs.remove(d) for d in dirs if d=='Debug' ]
        [dirs.remove(d) for d in dirs if d=='Release' ]
        processFiles(root,files)

#TODO: filter specific lines also
def isAcceptable(file):
    if file in ignoredFiles:
        return False
    for f in ignoredFiles:
        if file.startswith(f):
            return False
    return True
    
def printSummary():
    relevant=abspath('.')
    relevantEntries=0
    print len(summary),'entries - all files'
    file=[]
    for key,value in summary.items():
        if value.file.startswith(relevant):
            if isAcceptable(value.file):
                relevantEntries+=1
                if value.count==0:
                    file.append(value)

    unused=len(file)
    print unused,'unused of',relevantEntries
    file.sort()
    fname=''
    for f in file:
        if f.file!=fname:
            print f.file
            fname=f.file
        print f.line
    perc=(100.0*(relevantEntries-unused))/relevantEntries
    print '%.1f%%' % perc, 'covered'

def main():
    readIgnoredFiles()
    walkDir('.')
    printSummary()

if __name__ == "__main__":
    main()
    