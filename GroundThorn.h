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

class GroundThorn // �ش���
{
public:
	IMAGE im_groundthorn; // �ش�ͼ��
	float left_x, right_x, top_y; // �ش̵����½�����
	float groundthorn_width, groundthorn_height; // �ش̵Ŀ�Ⱥ͸߶�
	LPCTSTR imagePath;

	//�������Ĺ��캯��
	GroundThorn(LPCTSTR path, float x, float y) :imagePath(path), left_x(x), top_y(y) {}

	void initialize() // ��ʼ��
	{
		loadImageEnlarged(&im_groundthorn, imagePath); // ʹ�ô洢��·������ͼ��
		groundthorn_width = im_groundthorn.getwidth(); // ��õ���ͼ��Ŀ���
		groundthorn_height = im_groundthorn.getheight();
		right_x = left_x + groundthorn_width;
	}

	void draw(float px, float py) // ���Ƶش�
	{
		putimagePng(left_x - px, top_y - py, &im_groundthorn); // ���Ƶش̣�����ƫ����
	}
}
;