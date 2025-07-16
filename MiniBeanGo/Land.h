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

	void initialize() // 初始化
	{
		loadImageEnlarged(&im_land, _T("grass0.png")); // 导入地面图片
		land_width = im_land.getwidth(); // 获得地面图像的宽、高
		land_height = im_land.getheight();
		left_x = WIDTH / 2;  // land初始化在画面正中间，正好就在玩家角色脚底下
		right_x = left_x + land_width;
		top_y = HEIGHT / 2;
	}

	void draw()// 显示相关信息	
	{
		putimage(left_x, top_y, &im_land);  // 绘制一个地面
	}
};

