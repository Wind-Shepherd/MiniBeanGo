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
#define  WIDTH 1000  
#define  HEIGHT 600

//#ifndef IMAGE_UTILS_H
//#define IMAGE_UTILS_H
//
//void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
//#endif

class Scene // ��Ϸ������
{
public:
	IMAGE im_bk;  // ����ͼ��	
	vector<Land> lands; // �������

	void draw(float px,float py)// ��ʾ�����Ϣ	
	{
		// ��ɫ���������Ʊ�����һ��ƫ����
		// ����ƫ����/һ��ֵ�����γ�������Ȳ��ǰ�󾰵��Ӿ�Ч��
		putimage(-px / 3, -py / 15, &im_bk);	// ��ʾ����	
		for (int i = 0;i < lands.size();i++)
		{
			lands[i].draw(px,0);  // �������е���
		}
	}

	void initialize() // ��ʼ��
	{
		loadimage(&im_bk, _T("landscape1.png")); // ���뱳��ͼƬ
		lands.clear();// ����յ�vector
		for (int i = 0;i < 30;i++) // ����һЩ�������
		{
			Land land;
			land.initialize();
			land.left_x = i * land.land_width;
			land.right_x = land.left_x + land.land_width;
			land.top_y = HEIGHT / 2 + rand() % 2 * HEIGHT / 10;
			lands.push_back(land);
		}
	}
};

