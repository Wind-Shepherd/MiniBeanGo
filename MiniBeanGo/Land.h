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

class Land  // ������
{
public:
	IMAGE im_land;  // ����ͼ��
	float left_x, right_x, top_y; // �����̻�һ���������ҡ�������
	float land_width, land_height; // һ�����ͼ��Ŀ�ȡ��߶�

	void initialize() // ��ʼ��
	{
		loadImageEnlarged(&im_land, _T("grass0.png")); // �������ͼƬ
		land_width = im_land.getwidth(); // ��õ���ͼ��Ŀ���
		land_height = im_land.getheight();
		left_x = WIDTH / 2;  // land��ʼ���ڻ������м䣬���þ�����ҽ�ɫ�ŵ���
		right_x = left_x + land_width;
		top_y = HEIGHT / 2;
	}

	void draw()// ��ʾ�����Ϣ	
	{
		putimage(left_x, top_y, &im_land);  // ����һ������
	}
};

