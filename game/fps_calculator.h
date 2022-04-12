#pragma once

class FpsCalculator
{
public:
	static float getDelta();
	static void calcDelta();
private:
	static float delta;
	static float lastFrame;
};

