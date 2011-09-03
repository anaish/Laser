#pragma once

#include "../engine/config.hpp"

typedef std::tr1::shared_ptr<Config> PConfig;

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_


/**
 * An interface to the display
 */
class Display {
public:
	virtual void init(PConfig config) = 0;
	virtual void OnRender() = 0;
	virtual void rotateScene(float angle,float x, float y, float z)=0;
};

#endif
