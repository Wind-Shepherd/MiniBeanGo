#pragma once

#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include <windows.h>

using namespace std;
#define GRID_SIZE 18
//定义网格数量（宽度和高度方向）
#define GRID_WIDTH 25
#define GRID_HEIGHT 13
//计算窗口总大小
#define WIDTH (GRID_SIZE * GRID_WIDTH)
#define HEIGHT (GRID_SIZE * GRID_HEIGHT)

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

enum LandType {
	EMPTY,  // 空地
	GRASS_BLOCK1,  // 草地块1
	GRASS_BLOCK2,  // 草地块2
	GRASS_BLOCK3,  // 草地块3
	SOIL_BLOCK1,  // 土地块1
	SOIL_BLOCK2,  // 土地块2
	DIRT_PATH1,  // 泥土小路1
	DIRT_PATH2,  // 泥土小路2
	SNOW_BLOCK1,  // 雪地块1
	SNOW_BLOCK2,  // 雪地块2
	SNOW_BLOCK3,  // 雪地块3
	//类型数量
};

class Land  // 地面类
{
public:
	IMAGE im_land;  // 地面图像
	LandType type;  // 地面类型

	int gridX, gridY;  // 网格坐标
	int screenX = gridX * GRID_SIZE;
	int screenY = gridY * GRID_SIZE;

	void initialize(LandType t) {
		type = t;
		if (type == EMPTY) {
			return;  // 如果是空地，不加载图像
		}

		LPCTSTR filename;

		switch (t) {
		case GRASS_BLOCK1: filename = _T("GRASS_BLOCK1.png"); break;
		case GRASS_BLOCK2: filename = _T("GRASS_BLOCK2.png"); break;
		case GRASS_BLOCK3: filename = _T("GRASS_BLOCK3.png"); break;
		case SOIL_BLOCK1: filename = _T("SOIL_BLOCK1.png"); break;
		case SOIL_BLOCK2: filename = _T("SOIL_BLOCK2.png"); break;
		case DIRT_PATH1: filename = _T("DIRT_PATH1.png"); break;
		case DIRT_PATH2: filename = _T("DIRT_PATH2.png"); break;
		case SNOW_BLOCK1: filename = _T("SNOW_BLOCK1.png"); break;
		case SNOW_BLOCK2: filename = _T("SNOW_BLOCK2.png"); break;
		case SNOW_BLOCK3: filename = _T("SNOW_BLOCK3.png"); break;
		default: return;  // 未知类型不加载图像
		}

		loadimage(&im_land, filename, GRID_SIZE, GRID_SIZE, true);  // 直接加载为网格大小
	}
	void draw(float px, float py)// 显示相关信息	
	{
		if (type == EMPTY) {
			return;  // 如果是空地，不绘制
		}
		putimage(screenX - px, screenY - py, &im_land); // 角色不动，绘制地面有一个偏移量
	}
};

