#pragma once

#include <graphics.h>  
#include <conio.h>

using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

class Ladder  // 梯子类
{
public:
	IMAGE im_ladder;  // 梯子图像
	float left_x, right_x, top_y; // 用来刻画一个梯子的左、右、上坐标
	float ladder_width, ladder_height; // 一个梯子图像的宽度、高度
	LPCTSTR imagePath; // 新增：存储图像路径

	// 新增：带参数的构造函数
	Ladder(LPCTSTR path, float x, float y) : imagePath(path), left_x(x), top_y(y) {}


	void initialize() // 初始化
	{
		loadImageEnlarged(&im_ladder, imagePath); // 导入图片
		ladder_width = im_ladder.getwidth(); // 获得地面图像的宽、高
		ladder_height = im_ladder.getheight();
		right_x = left_x + ladder_width;
	}

	void draw(float px, float py)// 显示相关信息	
	{
		putimagePng(left_x - px, top_y - py, &im_ladder); // 角色不动，绘制梯子有一个偏移量
	}
};

