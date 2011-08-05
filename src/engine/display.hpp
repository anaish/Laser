#pragma once

/**
 * An interface to the display
 */
class Display {
public:
	virtual void init() = 0;
	virtual void OnRender() = 0;
	virtual ~Display() {}
};
