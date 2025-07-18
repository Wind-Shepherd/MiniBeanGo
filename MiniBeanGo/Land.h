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
//����������������Ⱥ͸߶ȷ���
#define GRID_WIDTH 25
#define GRID_HEIGHT 13
//���㴰���ܴ�С
#define WIDTH (GRID_SIZE * GRID_WIDTH)
#define HEIGHT (GRID_SIZE * GRID_HEIGHT)

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

enum LandType {
	EMPTY,  // �յ�
	GRASS_BLOCK1,  // �ݵؿ�1
	GRASS_BLOCK2,  // �ݵؿ�2
	GRASS_BLOCK3,  // �ݵؿ�3
	SOIL_BLOCK1,  // ���ؿ�1
	SOIL_BLOCK2,  // ���ؿ�2
	DIRT_PATH1,  // ����С·1
	DIRT_PATH2,  // ����С·2
	SNOW_BLOCK1,  // ѩ�ؿ�1
	SNOW_BLOCK2,  // ѩ�ؿ�2
	SNOW_BLOCK3,  // ѩ�ؿ�3
	//��������
};

class Land  // ������
{
public:
	IMAGE im_land;  // ����ͼ��
	LandType type;  // ��������

	int gridX, gridY;  // ��������
	int screenX = gridX * GRID_SIZE;
	int screenY = gridY * GRID_SIZE;

	void initialize(LandType t) {
		type = t;
		if (type == EMPTY) {
			return;  // ����ǿյأ�������ͼ��
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
		default: return;  // δ֪���Ͳ�����ͼ��
		}

		loadimage(&im_land, filename, GRID_SIZE, GRID_SIZE, true);  // ֱ�Ӽ���Ϊ�����С
	}
	void draw(float px, float py)// ��ʾ�����Ϣ	
	{
		if (type == EMPTY) {
			return;  // ����ǿյأ�������
		}
		putimage(screenX - px, screenY - py, &im_land); // ��ɫ���������Ƶ�����һ��ƫ����
	}
};

