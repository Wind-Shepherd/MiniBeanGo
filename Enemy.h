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

class Enemy  // 敌人类
{
public:
	IMAGE im_enemy;  // 敌人图像
    IMAGE im_show;  // 当前时刻要显示的图像
    vector <IMAGE> ims_enemy;
    vector <IMAGE> ims_enemy_Right;
    int animId;  // 用于循环动画播放的id
    int frameDelay; // 帧延迟计数器
	float left_x, right_x, top_y; // 用来刻画一个敌人的左、右、上坐标
	float enemy_width, enemy_height; // 一个敌人图像的宽度、高度
    EnemyType type;
    TCHAR filename[500];
    TCHAR filenameRight[500];
    int n;
    bool turn = 0;

	// 巡逻起点和终点
	float patrol_start, patrol_end;
    int endBlock;

	// 移动方向，1 表示向左右，0 表示向上下
	int direction;
    float v = 3;

	// 带参数的构造函数
	Enemy(float x, float y, int end, EnemyType type)//x，y起始位置;end走几格；type怪物类型（已包含方向逻辑）
        :left_x(x), top_y(y), endBlock(end), type(type) {}


	void initialize() // 初始化
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
            for (int i = 0;i <= n - 1;i++) // 把n张图片对象添加到im_enemy中
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
            for (int i = 0;i <= n - 1;i++) // 把n张图片对象添加到im_enemy中
            {
                _stprintf_s(filename, _T("Dada%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filename);
                ims_enemy.push_back(im);
            }
            for (int i = 0;i <= n - 1;i++) // 把n张图片对象添加到im_enemy中
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
            for (int i = 0;i <= n - 1;i++) // 把n张图片对象添加到im_enemy中
            {
                _stprintf_s(filename, _T("Xiaoxiao%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filename);
                ims_enemy.push_back(im);
            }
            for (int i = 0;i <= n - 1;i++) // 把n张图片对象添加到im_enemy中
            {
                _stprintf_s(filenameRight, _T("XiaoxiaoRight%d.png"), i);
                IMAGE im;
                loadImageEnlarged(&im, filenameRight);
                ims_enemy_Right.push_back(im);
            }
            break;
        }
        
        
		
		enemy_width = im_enemy.getwidth(); // 获得地面图像的宽、高
		enemy_height = im_enemy.getheight();
		right_x = left_x + enemy_width;
        animId = 0; // 动画id开始设为0
	}

	void draw(float px, float py)// 显示相关信息	
	{
        move(direction);
        frameDelay++; 
        if (frameDelay >= 5) {
            animId++; // 动画图片开始切换
            frameDelay = 0;
        }
        if (animId >= ims_enemy.size()) // 循环切换
            animId = 0;
        if (!turn && ims_enemy_Right.size() > animId)
            im_show = ims_enemy_Right[animId];
        else if (ims_enemy.size() > animId)
            im_show = ims_enemy[animId]; // 设置要显示的对应图片
		putimagePng(left_x - px, top_y - py, &im_show); // 角色不动，绘制敌人有一个偏移量
	}

    // 新增：移动函数，传入速度和方向（水平或垂直）
    void move(bool direction)
    {
        if (direction) // 如果 direction 为 true，表示水平移动（左右）
        {
            left_x += v; // 水平移动
            right_x = left_x + enemy_width;

            // 检查水平边界
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
        else // 如果 direction 为 false，表示垂直移动（上下）
        {
            top_y += v; // 垂直移动
            
            // 检查垂直边界
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

