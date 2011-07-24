#include "light.hpp"

Light::Light() {}

virtual void Light::run() {
	LOG(INFO) << "Light was run!";
}
