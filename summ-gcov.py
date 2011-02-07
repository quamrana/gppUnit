#summarise all gcov files

import os
from os.path import join,abspath

summary = {}

class FileProcessor:
    def __init__(self):
        self.mapCount={ 
            '-':self.nullProcedure,
            '#####':self.zeroProcedure,
            '0':self.callAccrue
            }
        self.reinit()

    def reinit(self):
        self.file=''
        self.accrueLine=self.nullProcedure

    def processCount(self,count,lineNumber):
        procedure=self.callAccrue
        key=count.strip()
        if key in self.mapCount:
            procedure=self.mapCount[key]
        procedure(count,lineNumber)    

    def callAccrue(self,count,lineNumber):
        self.accrueLine(int(count),lineNumber)        

    def nullProcedure(self,count,lineNumber):
        pass

    def zeroProcedure(self,count,lineNumber):
        key=self.file+':'+str(lineNumber)
        current=0
        if key in summary:
            current=summary[key]
        summary[key]=current

    def process(self,count,lineNumber):
        key=self.file+':'+str(lineNumber)
        current=0
        if key in summary:
            current=summary[key]
        summary[key]=current+count
            
    def processLine(self,line):
        elements=line.split(':')
        if len(elements)>=2:
            count=elements[0]
            lineNumber=int(elements[1])
            if len(elements)>=4:
                if lineNumber==0:
                    if elements[2]=='Source':
                        index=line.find(':Source:')
                        self.file=elements[3]
                        self.file=abspath(line[index+8:])
                        self.accrueLine=self.process
            
            self.processCount(count,lineNumber)        
            
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

def main():
    for root, dirs, files in os.walk('.', topdown=True):
        print root
        [dirs.remove(d) for d in dirs if d.startswith('.') ]
        [dirs.remove(d) for d in dirs if d=='Debug' ]
        processFiles(root,files)

def printSummary():
    relevant=abspath('.')
    relevantEntries=0
    print len(summary),'entries'
    file=[]
    for key,value in summary.items():
        if key.startswith(relevant):
            relevantEntries+=1
            if value==0:
                file.append(key)
    file.sort()
    for f in file:
        print f
    unused=len(file)
    perc=(100.0*(relevantEntries-unused))/relevantEntries
    print '%.1f%%' % perc, 'covered'

if __name__ == "__main__":
    main()
    printSummary()
    