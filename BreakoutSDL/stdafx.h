// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#if (DEBUG || _DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // (DEBUG || _DEBUG)

#undef main

#define BoardWidth 12
#define BoardHeight 12
#define BoardBrickWidth 64
#define BoardBrickHeight 24
#define FPSDelay 500

const float g_fkBallSpeed = 550;
