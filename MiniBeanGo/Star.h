#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include "Land.h"
#include <vector>
#include <windows.h>
using namespace std;

class Star
{
public:
	IMAGE im_star;
	float left_x, right_x, top_y;
	float star_width, star_height;
	LPCTSTR imagePath;

	Star(LPCTSTR path, float x, float y) :imagePath(path), left_x(x), top_y(y) {}

	void initialize()
	{
		loadImageEnlarged(&im_star, imagePath);
		star_width = im_star.getwidth();
		star_height = im_star.getheight();
		right_x = left_x + star_width;
	}

	void draw(float px, float py)
	{
		putimagePng(left_x - px, top_y - py, &im_star);
	}
}
;