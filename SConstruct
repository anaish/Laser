VariantDir('work', 'src')

files = Split("""
	work/main.cpp
	work/engine/engine.cpp
	work/light/light.cpp
	work/light/opengldisplay.cpp
	work/light/v8config.cpp
	work/light/defaultfilesystem.cpp
	work/light/assimpmodelimporter.cpp
""")

libs = Split("""
	glog
	SDLmain
	SDL
	assimp
	GL
	v8
""")

Program('laser', files, LIBS=libs)
