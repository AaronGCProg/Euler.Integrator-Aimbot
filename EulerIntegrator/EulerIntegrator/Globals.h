#pragma once
#include <iostream>
#include "p2Log.h"


using namespace std;
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef float float32;
typedef double float64;




#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )

typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum collision_type : uint16
{
	COLL_NONE = 0x0000,
	COLL_FOREGROUND = 0x0001,
	COLL_BACKGROUND = 0x0002,
	COLL_GROUND = 0x0003,

	COLL_ALL
};

// Configuration -----------
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "EULER_INTEGRATOR"