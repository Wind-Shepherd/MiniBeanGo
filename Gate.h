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

class Gate // 大门类
{
public:
	IMAGE im_gate; // 大门图像
	float left_x, right_x, top_y; // 大门的左下角坐标
	float gate_width, gate_height; // 大门的宽度和高度
	LPCTSTR imagePath; // 图像路径 
	// 带参数的构造函数
	Gate(LPCTSTR path, float x, float y) : imagePath(path), left_x(x), top_y(y) {}
	void initialize() // 初始化
	{
		loadImageEnlarged(&im_gate, imagePath); // 使用存储的路径加载图像
		gate_width = im_gate.getwidth(); // 获得大门图像的宽、高
		gate_height = im_gate.getheight();
		right_x = left_x + gate_width;
	}
	void draw(float px, float py) // 绘制大门
	{
		putimagePng(left_x - px, top_y - py, &im_gate); // 绘制大门，考虑偏移量
	}
};