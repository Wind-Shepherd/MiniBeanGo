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

class Ladder  // ������
{
public:
	IMAGE im_ladder;  // ����ͼ��
	float left_x, right_x, top_y; // �����̻�һ�����ӵ����ҡ�������
	float ladder_width, ladder_height; // һ������ͼ��Ŀ�ȡ��߶�
	LPCTSTR imagePath; // �������洢ͼ��·��

	// �������������Ĺ��캯��
	Ladder(LPCTSTR path, float x, float y) : imagePath(path), left_x(x), top_y(y) {}


	void initialize() // ��ʼ��
	{
		loadImageEnlarged(&im_ladder, imagePath); // ����ͼƬ
		ladder_width = im_ladder.getwidth(); // ��õ���ͼ��Ŀ���
		ladder_height = im_ladder.getheight();
		right_x = left_x + ladder_width;
	}

	void draw(float px, float py)// ��ʾ�����Ϣ	
	{
		putimagePng(left_x - px, top_y - py, &im_ladder); // ��ɫ����������������һ��ƫ����
	}
};

