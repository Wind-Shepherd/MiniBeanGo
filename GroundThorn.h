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

class GroundThorn // 地刺类
{
public:
	IMAGE im_groundthorn; // 地刺图像
	float left_x, right_x, top_y; // 地刺的左下角坐标
	float groundthorn_width, groundthorn_height; // 地刺的宽度和高度
	LPCTSTR imagePath;

	//带参数的构造函数
	GroundThorn(LPCTSTR path, float x, float y) :imagePath(path), left_x(x), top_y(y) {}

	void initialize() // 初始化
	{
		loadImageEnlarged(&im_groundthorn, imagePath); // 使用存储的路径加载图像
		groundthorn_width = im_groundthorn.getwidth(); // 获得地面图像的宽、高
		groundthorn_height = im_groundthorn.getheight();
		right_x = left_x + groundthorn_width;
	}

	void draw(float px, float py) // 绘制地刺
	{
		putimagePng(left_x - px, top_y - py, &im_groundthorn); // 绘制地刺，考虑偏移量
	}
}
;