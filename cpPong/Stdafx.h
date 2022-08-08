#pragma once
#include "memdc.h"
#include <string.h>
#include <string>
#include "afx.h"
#include "Point2D.h"
#include <time.h>
#include <chrono>
#include <mmsystem.h>
#include <iostream>     
#include <thread> 


template <class T>		//template func
T Min_C(T a, T b) {
	T result;
	result = (a < b) ? a : b;
	return (result);
}

//Screen Size
#define RESOLUTION_X 800
#define RESOLUTION_Y 600



