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

class Gate // ������
{
public:
	IMAGE im_gate; // ����ͼ��
	float left_x, right_x, top_y; // ���ŵ����½�����
	float gate_width, gate_height; // ���ŵĿ�Ⱥ͸߶�
	LPCTSTR imagePath; // ͼ��·�� 
	// �������Ĺ��캯��
	Gate(LPCTSTR path, float x, float y) : imagePath(path), left_x(x), top_y(y) {}
	void initialize() // ��ʼ��
	{
		loadImageEnlarged(&im_gate, imagePath); // ʹ�ô洢��·������ͼ��
		gate_width = im_gate.getwidth(); // ��ô���ͼ��Ŀ���
		gate_height = im_gate.getheight();
		right_x = left_x + gate_width;
	}
	void draw(float px, float py) // ���ƴ���
	{
		putimagePng(left_x - px, top_y - py, &im_gate); // ���ƴ��ţ�����ƫ����
	}
};