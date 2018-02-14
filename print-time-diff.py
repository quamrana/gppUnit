#print time
import os

def getSeconds(time):
    #print time
    hours=int(time[0:2])
    mins=int(time[2:4])
    seconds=int(time[4:6])
    millis=float(time[7:9])/100
    return millis+seconds+mins*60+hours*3600
    
start=os.getenv("STARTBATCH")
end=os.getenv("ENDBATCH")

#print(start)
#print(end)
print(str(round(getSeconds(end)-getSeconds(start),3))+" seconds.")
