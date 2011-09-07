VariantDir('work', 'src')

files = Split("""
	work/main.cpp
	work/engine/engine.cpp
	work/light/light.cpp
	work/light/opengldisplay.cpp
	work/light/v8config.cpp
	work/light/defaultfilesystem.cpp
	work/light/assimpmodelimporter.cpp
	work/light/defaultphysics.cpp
""")

libs = Split("""
	glog
	SDLmain
	SDL
	assimp
	GL
	v8
	ode
""")

env = Environment()
debug = ARGUMENTS.get('debug', 0)
if int(debug):
 env.Append(CCFLAGS = '-g')
 

env.Program('laser', files, LIBS=libs)
