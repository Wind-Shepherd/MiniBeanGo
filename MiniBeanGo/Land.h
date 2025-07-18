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
	LPCTSTR imagePath; // �������洢ͼ��·��

	// �������������Ĺ��캯��
	Land(LPCTSTR path, float x, float y) : imagePath(path), left_x(x), top_y(y) {}

	void initialize() // ��ʼ��
	{
		loadImageEnlarged(&im_land, imagePath); // ʹ�ô洢��·������ͼ��
		land_width = im_land.getwidth(); // ��õ���ͼ��Ŀ���
		land_height = im_land.getheight();
		right_x = left_x + land_width;
	}

	void draw(float px, float py)// ��ʾ�����Ϣ	
	{
		putimage(left_x - px, top_y - py, &im_land); // ��ɫ���������Ƶ�����һ��ƫ����
	}
};