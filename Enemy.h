#pragma once

#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include "Land.h"
#include <vector>
#include <windows.h>

#define GRID_SIZE 18*2

using namespace std;
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

enum EnemyType {
    Feifei,
    Dada,
    Xiaoxiao,
};

class Enemy  // ������
{
public:
	IMAGE im_enemy;  // ����ͼ��
    IMAGE im_show;  // ��ǰʱ��Ҫ��ʾ��ͼ��
    vector <IMAGE> ims_enemy;
    vector <IMAGE> ims_enemy_Right;
    int animId;  // ����ѭ���������ŵ�id
    int frameDelay; // ֡�ӳټ�����
	float left_x, right_x, top_y; // �����̻�һ�����˵����ҡ�������
	float enemy_width, enemy_height; // һ������ͼ��Ŀ�ȡ��߶�
    EnemyType type;
    TCHAR filename[500];
    TCHAR filenameRight[500];
    int n;
    bool turn = 0;

	// Ѳ�������յ�
	float patrol_start, patrol_end;
    int endBlock;

	// �ƶ�����1 ��ʾ�����ң�0 ��ʾ������
	int direction;
    float v = 3;

	// �������Ĺ��캯��
	Enemy(float x, float y, int end, EnemyType type)//x��y��ʼλ��;end�߼���type�������ͣ��Ѱ��������߼���
        :left_x(x), top_y(y), endBlock(end), type(type) {}


	void initialize() // ��ʼ��
	{
        patrol_end = endBlock * GRID_SIZE;
        switch (type) {
        case Feifei:
            patrol_start = top_y;
            patrol_end += top_y;
            direction = 0;
            n = 3;
            loadImageEnlarged(&im_enemy, _T("Feifei0.png"));
            im_show = im_enemy;
            for (int i = 0;i <= n - 1;i++) // ��n��ͼƬ������ӵ�im_enemy��
            {
                _stprintf_s(filename, _T("Feifei%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filename);
                ims_enemy.push_back(im);
            }
            break;
        case Dada:
            patrol_start = left_x;
            patrol_end += left_x;
            direction = 1;
            n = 2;
            loadImageEnlarged(&im_enemy, _T("Dada0.png"));
            im_show = im_enemy;
            for (int i = 0;i <= n - 1;i++) // ��n��ͼƬ������ӵ�im_enemy��
            {
                _stprintf_s(filename, _T("Dada%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filename);
                ims_enemy.push_back(im);
            }
            for (int i = 0;i <= n - 1;i++) // ��n��ͼƬ������ӵ�im_enemy��
            {
                _stprintf_s(filenameRight, _T("DadaRight%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filenameRight);
                ims_enemy_Right.push_back(im);
            }
            break;
        case Xiaoxiao:
            patrol_start = left_x;
            patrol_end += left_x;
            direction = 1;
            n = 2;
            loadImageEnlarged(&im_enemy, _T("Xiaoxiao0.png"));
            im_show = im_enemy;
            for (int i = 0;i <= n - 1;i++) // ��n��ͼƬ������ӵ�im_enemy��
            {
                _stprintf_s(filename, _T("Xiaoxiao%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filename);
                ims_enemy.push_back(im);
            }
            for (int i = 0;i <= n - 1;i++) // ��n��ͼƬ������ӵ�im_enemy��
            {
                _stprintf_s(filenameRight, _T("XiaoxiaoRight%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filenameRight);
                ims_enemy_Right.push_back(im);
            }
            break;
        }
        
        
		
		enemy_width = im_enemy.getwidth(); // ��õ���ͼ��Ŀ���
		enemy_height = im_enemy.getheight();
		right_x = left_x + enemy_width;
        animId = 0; // ����id��ʼ��Ϊ0
	}

	void draw(float px, float py)// ��ʾ�����Ϣ	
	{
        move(direction);
        frameDelay++; 
        if (frameDelay >= 5) {
            animId++; // ����ͼƬ��ʼ�л�
            frameDelay = 0;
        }
        if (animId >= ims_enemy.size()) // ѭ���л�
            animId = 0;
        if (!turn && ims_enemy_Right.size() > animId)
            im_show = ims_enemy_Right[animId];
        else if (ims_enemy.size() > animId)
            im_show = ims_enemy[animId]; // ����Ҫ��ʾ�Ķ�ӦͼƬ
		putimagePng(left_x - px, top_y - py, &im_show); // ��ɫ���������Ƶ�����һ��ƫ����
	}

    // �������ƶ������������ٶȺͷ���ˮƽ��ֱ��
    void move(bool direction)
    {
        if (direction) // ��� direction Ϊ true����ʾˮƽ�ƶ������ң�
        {
            left_x += v; // ˮƽ�ƶ�
            right_x = left_x + enemy_width;

            // ���ˮƽ�߽�
            if (left_x <= patrol_start)
            {
                v = -v;
                turn = !turn;
            }
            else if (right_x >= patrol_end)
            {
                v = -v;
                turn = !turn;
            }
        }
        else // ��� direction Ϊ false����ʾ��ֱ�ƶ������£�
        {
            top_y += v; // ��ֱ�ƶ�
            
            // ��鴹ֱ�߽�
            if (top_y <= patrol_start)
            {
                //top_y = patrol_start;
                v = -v;
            }
            else if (top_y - enemy_height >= patrol_end)
            {
                //top_y = patrol_end - enemy_height;
                v = -v;
            }
        }
        
    }

};

