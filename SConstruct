VariantDir('work', 'src')

files = Split("""
	work/main.cpp
	work/engine/engine.cpp
	work/light/light.cpp
""")

libs = Split("""
	glog
""")

Program('laser', files, LIBS=libs)
