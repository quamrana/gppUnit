path=['C:\DJGPP\BIN','C:\Python27\Scripts']
DJGPP='C:\DJGPP\DJGPP.ENV'

compiler=ARGUMENTS.get('compiler','djgpp')
cov=ARGUMENTS.get('cov','-')

def getGccflags():
	cppflags=['-Wall','-Wextra'] #,'-Weffc++']
	if cov!='-':
		cppflags+=['-fprofile-arcs','-ftest-coverage','-fno-elide-constructors']
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

def Env(key):
	try:
		return env[key]
	except:
		return '???'

if compiler=='msvc':
	env=microsoft()
elif compiler=='gcc':
	env=gcc()
else:
	env=djgpp()

print "compiler is:", compiler
print "cov is:", cov
print "CXX is:", Env('CXX')
print "CPP is:", Env('CPP')
print "CC is:", Env('CC')
print "LINK is:", env['LINK']
print "LIB is:", env['AR']
#print "CCFLAGS is:", env['CCFLAGS']
#print "CPPPATH is:", env['CPPPATH']
#print "LIBPATH is:", env['LIBPATH']
#print "BUILDERS: ", env['BUILDERS']
#print env.Dump()

env.SConscript(['src/SConscript','test/SConscript','Matchers/SConscript','TableFormatting/SConscript'])
