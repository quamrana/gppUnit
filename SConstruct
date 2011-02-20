path=['C:\DJGPP\BIN','C:\Python27\Scripts','.\Scripts']
DJGPP='C:\DJGPP\DJGPP.ENV'

compiler=ARGUMENTS.get('compiler','djgpp')
cov=ARGUMENTS.get('cov','-')

def getGccflags():
	cppflags=['-Wall','-Wextra'] #,'-Weffc++']
	if cov!='-':
		cppflags+=['-fprofile-arcs','-ftest-coverage','-fno-elide-constructors','-fno-default-inline']
	return cppflags

def microsoft():
	cppflags=['/EHsc','/wd4250']
	return DefaultEnvironment(
		CPPFLAGS=cppflags
		)

def djgpp():
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
	global path
	path=['C:\MINGW\BIN','C:\Python27\Scripts','.\Scripts']
	cppflags=getGccflags()
	return DefaultEnvironment(tools = ['g++','gnulink','ar'],
		ENV={'PATH':path},
		CPPFLAGS=cppflags,
		EXTRA='unix',
		COV=cov
		)

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
else:
	env=djgpp()

print "compiler is:", compiler
print "cov is:", cov
print "CXX is:", Env('CXX')
print "CPP is:", Env('CPP')
print "CC is:", Env('CC')
print "LINK is:", Env('LINK')
print "LIB is:", Env('AR')
#print "CCFLAGS is:", Env('CCFLAGS')
#print "CPPPATH is:", Env('CPPPATH')
#print "LIBPATH is:", Env('LIBPATH')
#print "BUILDERS: ", Env('BUILDERS')
#print env.Dump()

env.SConscript(['src/SConscript','test/SConscript','Matchers/SConscript','TableFormatting/SConscript'])
