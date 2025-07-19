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

class Key
{
public:
	IMAGE im_key;
	float left_x, right_x, top_y;
	float key_width, key_height;
	LPCTSTR imagePath;
	bool isVisible;

	Key(LPCTSTR path, float x, float y) :imagePath(path), left_x(x), top_y(y) {}

	void initialize()
	{
		loadImageEnlarged(&im_key, imagePath);
		key_width = im_key.getwidth();
		key_height = im_key.getheight();
		right_x = left_x + key_width;
		isVisible = true; // 默认可见
	}

	void draw(float px, float py)
	{
		if (isVisible) {
			putimagePng(left_x - px, top_y - py, &im_key);
		}
	}

	void setVisibility(bool visible) {
		isVisible = visible; // 设置钥匙的可见性
	}
}
;