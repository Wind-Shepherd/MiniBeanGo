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
class Scene // 游戏场景类
{
public:
    IMAGE im_bk;  // 背景图像    
    vector<Land> lands; // 多个地面
    void draw()// 显示相关信息    
    {
        putimage(-100, -100, &im_bk);    // 显示背景    
        for (int i = 0;i < lands.size();i++)
        {
            lands[i].draw();  // 绘制所有地面
        }
    }
    void initialize() // 初始化
    {
        loadimage(&im_bk, _T("landscape1.png")); // 导入背景图片
        lands.clear();// 先清空掉vector
        for (int i = 0;i < 30;i++) // 产生一些随机地面
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