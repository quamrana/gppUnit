
compiler=ARGUMENTS.get('compiler','mingw')
cov=ARGUMENTS.get('cov','-')

def getGccflags():
	cppflags=['-Wall','-Wextra','-std=c++17']  #,'-Weffc++','-pedantic','-std=c++0x']
	if cov!='-':
		cppflags+=['--coverage','-fno-elide-constructors','-fno-default-inline']
	return cppflags

def microsoft():
	cppflags=['/EHsc','/wd4250']
	return DefaultEnvironment(
		CPPFLAGS=cppflags
		)

def djgpp():
	path=['C:\DJGPP\BIN','C:\Python27\Scripts','.\Scripts']
	DJGPP='C:\DJGPP\DJGPP.ENV'
	cppflags=getGccflags()
	return DefaultEnvironment(tools = ['c++','gnulink','ar'],
		ENV={'PATH':path,'DJGPP':DJGPP},
		CXX = 'gpprep', AR = 'arrep', LINK = 'linkrep',
		CPPFLAGS=cppflags,
		EXTRA='djgpp',
		COV=cov
		)

def gcc():
	cppflags=getGccflags()
	return DefaultEnvironment(
		CPPFLAGS=cppflags,
		EXTRA='unix',
		COV=cov
		)

def mingw():
	path=['D:\MinGW16_0\\bin','C:\Python27\Scripts','.\Scripts']
	cppflags=getGccflags()
	return DefaultEnvironment(tools = ['g++','gnulink','ar'],
		ENV={'PATH':path, 'TEMP':'C:\Temp'},
		CPPFLAGS=cppflags,
		#EXTRA='unix',
		COV=cov
		)

env = None

def Env(key):
	try:
		return env[key]
	except:
		return '???'

if compiler=='msvc':
	env=microsoft()
elif compiler=='gcc':
	env=gcc()
elif compiler=='mingw':
	env=mingw()
elif compiler=='djgpp':
	env=djgpp()
else:
	env=mingw()

print ("compiler is:", compiler)
print ("cov is:", cov)
print ("CXX is:", Env('CXX'))
#print ("CPP is:", Env('CPP'))
#print ("CC is:", Env('CC'))
print ("LINK is:", Env('LINK'))
print ("LIB is:", Env('AR'))
#print ("CCFLAGS is:", Env('CCFLAGS'))
#print ("CPPPATH is:", Env('CPPPATH'))
#print ("LIBPATH is:", Env('LIBPATH'))
#print ("BUILDERS: ", Env('BUILDERS'))
#print ("TEMP is:", Env('TEMP'))
#print ("TMP is:", Env('TMP'))

#print env.Dump()

env.SConscript(['src/SConscript','test/SConscript','Matchers/SConscript','TableFormatting/SConscript','ApprovalsTest/SConscript'])
