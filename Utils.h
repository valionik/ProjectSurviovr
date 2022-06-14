#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "Entity.h"

namespace utils
{
	inline float hireTimeInSeconds() {
		float t = SDL_GetTicks();
		t *= 0.001f;
		return t;
	}
}