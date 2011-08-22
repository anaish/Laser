#include <glog/logging.h>
#include "engine/engine.hpp"
#include "light/light.hpp"
#include "light/opengldisplay.hpp"
#include "light/v8config.hpp"
#include "light/defaultfilesystem.hpp"
#include "light/assimpmodelimporter.hpp"

int main(int argc, char* argv[]) {

	google::InitGoogleLogging(argv[0]);

	LOG(ERROR) << "Starting Light";

	PRule lightRules(new Light);
	PDisplay openGlDisplay(new OpenGlDisplay());
	PConfig v8Config(new V8Config());
	PFileSystem fileSystem(new DefaultFileSystem());

	Engine engine(lightRules);
	engine.setConfig(v8Config);
	engine.setDisplay(openGlDisplay);
	engine.setFileSystem(fileSystem);
	engine.init();
	engine.run();
	LOG(ERROR) << "Ending Light";
	return 0;
}
