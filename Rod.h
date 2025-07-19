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

// ��������״̬ö��
enum RodStatus {
    ROD_CLOSED,
    ROD_OPEN
};

class Rod
{
public:
    IMAGE im_rod_closed;  // ���˹ر�״̬ͼƬ
    IMAGE im_rod_open;    // ���˴�״̬ͼƬ
    float left_x, right_x, top_y; // ���˵����Ͻ�����
    float rod_width, rod_height;  // ����ͼƬ�Ŀ�Ⱥ͸߶�
    LPCTSTR imagePath_closed;     // ���˹ر�״̬ͼƬ·��
    LPCTSTR imagePath_open;       // ���˴�״̬ͼƬ·��
    RodStatus status;             // ���˵�ǰ״̬

    Rod(LPCTSTR path_closed, LPCTSTR path_open, float x, float y) : imagePath_closed(path_closed), imagePath_open(path_open), left_x(x), top_y(y), status(ROD_CLOSED) {}

    void initialize() // ��ʼ��
    {
        loadImageEnlarged(&im_rod_closed, imagePath_closed); // ���عر�״̬ͼƬ
        loadImageEnlarged(&im_rod_open, imagePath_open);     // ���ش�״̬ͼƬ
        rod_width = im_rod_closed.getwidth(); // ��ȡͼƬ���
        rod_height = im_rod_closed.getheight();
        right_x = left_x + rod_width;
		status = ROD_CLOSED; // Ĭ��״̬Ϊ�ر�
    }

    void draw(float px, float py) // ��������
    {
        if (status == ROD_CLOSED) {
            putimagePng(left_x - px, top_y - py, &im_rod_closed); // ���ƹر�״̬ͼƬ
        }
        else {
            putimagePng(left_x - px, top_y - py, &im_rod_open);   // ���ƴ�״̬ͼƬ
        }
    }

    void changeStatus() // ��������״̬
    {
        if (status == ROD_CLOSED) {
            status = ROD_OPEN;
        }
        else {
            status = ROD_CLOSED;
        }
    }
};