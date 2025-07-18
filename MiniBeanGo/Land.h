#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include <windows.h>

using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

class Land  // 地面类
{
public:
	IMAGE im_land;  // 地面图像
	float left_x, right_x, top_y; // 用来刻画一块地面的左、右、上坐标
	float land_width, land_height; // 一块地面图像的宽度、高度
	LPCTSTR imagePath; // 新增：存储图像路径

	// 新增：带参数的构造函数
	Land(LPCTSTR path, float x, float y) : imagePath(path), left_x(x), top_y(y) {}

	void initialize() // 初始化
	{
		loadImageEnlarged(&im_land, imagePath); // 使用存储的路径加载图像
		land_width = im_land.getwidth(); // 获得地面图像的宽、高
		land_height = im_land.getheight();
		right_x = left_x + land_width;
	}

	void draw(float px, float py)// 显示相关信息	
	{
		putimage(left_x - px, top_y - py, &im_land); // 角色不动，绘制地面有一个偏移量
	}
};