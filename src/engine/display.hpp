#pragma once

#include "../engine/config.hpp"

typedef std::tr1::shared_ptr<Config> PConfig;

/**
 * An interface to the display
 */
class Display {
public:
	virtual void init(PConfig config) = 0;
	virtual void OnRender() = 0;
	virtual ~Display() {}
};
