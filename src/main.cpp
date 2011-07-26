#include <glog/logging.h>
#include "engine/engine.hpp"
#include "light/light.hpp"

int main(int argc, char* argv[]) {
	google::InitGoogleLogging(argv[0]);

	LOG(ERROR) << "Starting Light";

	PRule lightRules(new Light);

	Engine engine(lightRules);
	engine.init();
	engine.run();
	LOG(ERROR) << "Ending Light";
	return 0;
}
