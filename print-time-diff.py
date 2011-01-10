#print time
import os

start=os.getenv("STARTBATCH")
end=os.getenv("ENDBATCH")

print str(round(float(end)-float(start),3))+" seconds."
