VariantDir('work', 'src')

files = Split("""
	work/main.cpp
	work/engine/engine.cpp
	work/light/light.cpp
	work/light/opengldisplay.cpp
""")

libs = Split("""
	glog
	SDLmain
	SDL
	GL
""")

Program('laser', files, LIBS=libs)
