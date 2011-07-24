#include "light.hpp"

Light::Light() {
	this->name =  "Light";
}

void Light::run() {
	LOG(ERROR) << "Light was run!";
}
