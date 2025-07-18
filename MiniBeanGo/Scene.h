#pragma once
#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include "Land.h"
#include "Ladder.h"
#include <vector>
#include <windows.h>
#include "GroundThorn.h"
#include "Star.h"

using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
#define GRID_SIZE 18*2
#define ACTIVE_RANGE 400 // 角色活动范围宽度
#define ACTIVE_RANGE_Y 200 // 角色活动范围高度

float sceneOffsetX = 0; // 场景横向偏移量
float sceneOffsetY = 0; // 场景纵向偏移量

float getPlayerScreenX();
float getPlayerScreenY();

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

class Scene // 游戏场景类
{
public:
    IMAGE im_bk;  // 背景图像    
    vector<Land> lands; // 多个地面
    vector<Ladder> ladders; // 多个梯子
    vector<GroundThorn> groundthorns; // 地刺
    vector<Star> stars; // 星星

    // 新增：根据坐标和图像路径创建Land块
    void addLand(LPCTSTR imagePath, float x, float y) {
        Land land(imagePath, x, y);
        land.initialize();
        lands.push_back(land);
    }

    void addLadder(LPCTSTR imagePath, float x, float y) {
        Ladder ladder(imagePath, x, y);
        ladder.initialize();
        ladders.push_back(ladder);
    }

    void addGroundThorn(LPCTSTR imagePath, float x, float y)
    {
        GroundThorn groundthorn(imagePath, x, y);
        groundthorn.initialize();
        groundthorns.push_back(groundthorn);
    }

    void addStar(LPCTSTR imagePath, float x, float y) // 添加星星
    {
        Star star(imagePath, x, y);
        star.initialize();
        stars.push_back(star);
    }

    void draw(float px, float py)// 显示相关信息    
    {
        // 角色不动，绘制背景有一个偏移量
        // 背景偏移量/20，就形成了有深度差的前后景的视觉效果
        putimage(-sceneOffsetX / 20, -100 - sceneOffsetY / 20, &im_bk);	// 显示背景
        for (int i = 0;i < lands.size();i++)
        {
            lands[i].draw(sceneOffsetX, sceneOffsetY);  // 传递完整偏移量
        }

        for (int i = 0;i < ladders.size();i++)
        {
            ladders[i].draw(sceneOffsetX, sceneOffsetY);  // 传递完整偏移量
        }
        for (int i = 0;i < groundthorns.size();i++)
        {
            groundthorns[i].draw(sceneOffsetX, sceneOffsetY); // 绘制所有地刺
        }
        for (int i = 0;i < stars.size();i++)
        {
            stars[i].draw(sceneOffsetX, sceneOffsetY); // 绘制所有星星
        }
    }

    void initialize() // 初始化
    {
        loadimage(&im_bk, _T("landscape1.png")); // 导入背景图片
        lands.clear();// 先清空掉vector

        // 使用addLand函数根据坐标固定创建Land块
        addLand(_T("GRASS_BLOCK6.png"), 0, HEIGHT * 3 / 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 2, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 2, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("GRASS_BLOCK5.png"), GRID_SIZE * 2, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 3, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 4, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 5, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 6, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 7, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK7.png"), GRID_SIZE * 8, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 8, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 8, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 8, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 8, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK7.png"), GRID_SIZE * 9, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 9, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK7.png"), GRID_SIZE * 10, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 10, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 11, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 12, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 13, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 14, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 15, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK5.png"), GRID_SIZE * 15, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 16, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 17, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 18, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 19, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 20, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK7.png"), GRID_SIZE * 21, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 21, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 22, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 23, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 24, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 25, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 26, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 26, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK5.png"), GRID_SIZE * 26, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 27, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 28, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 28, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 28, HEIGHT * 3 / 4);
        addLand(_T("GRASS_BLOCK5.png"), GRID_SIZE * 28, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 29, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 30, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 30, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 30, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 30, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 30, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("GRASS_BLOCK5.png"), GRID_SIZE * 30, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 31, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 32, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 33, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("GRASS_BLOCK7.png"), GRID_SIZE * 34, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 34, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 35, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 36, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("GRASS_BLOCK7.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 37, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 40, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 40, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 41, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 41, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 42, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 42, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH5.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SOIL_BLOCK7.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("DIRT_PATH7.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 44, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 44, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 45, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 45, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 46, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 46, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH0.png"), GRID_SIZE * 46, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH5.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK7.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 48, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH4.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 15);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 14);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 13);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SOIL_BLOCK6.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH0.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 50, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 51, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 51, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 52, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 52, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("DIRT_PATH0.png"), GRID_SIZE * 52, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 54, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH0.png"), GRID_SIZE * 54, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 55, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 58, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 59, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 60, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 61, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 61, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 62, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 63, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 64, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 65, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 65, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 66, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 66, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 67, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 67, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 68, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 68, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 69, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 70, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 72, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 72, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 73, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 73, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 73, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 74, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 74, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 75, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 76, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 76, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 76, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 76, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 76, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 77, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 77, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 78, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 78, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 79, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 80, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 81, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 82, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 83, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 84, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 85, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 85, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 88, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 88, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 91, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 92, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 93, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 93, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 94, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 94, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK7.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 96, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 97, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 98, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 99, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 100, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK7.png"), GRID_SIZE * 101, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 101, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 101, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 102, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 103, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 104, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 105, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 105, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 105, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 105, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 105, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 105, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 106, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 106, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 106, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 106, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 107, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 107, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 107, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 108, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 108, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 108, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK7.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 111, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 111, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 111, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 111, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 111, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 111, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 112, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 113, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 114, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 115, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 116, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 116, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK7.png"), GRID_SIZE * 117, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 117, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 117, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 117, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK7.png"), GRID_SIZE * 118, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 118, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 118, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 118, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 118, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 118, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 118, HEIGHT * 3 / 4 + GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 118, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 119, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 119, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 120, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 121, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 121, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 122, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 123, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 124, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 124, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 124, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 125, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 125, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 125, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 125, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 126, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 127, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 127, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 127, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 128, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 128, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 128, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 128, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 129, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 130, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 130, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 131, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 131, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 131, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 132, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 132, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 133, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 133, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 134, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 134, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK7.png"), GRID_SIZE * 135, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SOIL_BLOCK3.png"), GRID_SIZE * 135, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 138, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 139, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 140, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 141, HEIGHT * 3 / 4 + GRID_SIZE * 6);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 141, HEIGHT * 3 / 4 + GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 142, HEIGHT * 3 / 4 + GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 142, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 143, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 143, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 144, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 144, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 145, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 145, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 146, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 146, HEIGHT * 3 / 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 147, HEIGHT * 3 / 4);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 147, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 148, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 149, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 150, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 151, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 152, HEIGHT * 3 / 4 - GRID_SIZE * 1);

        addLadder(_T("Ladder.png"), GRID_SIZE * 15, HEIGHT / 2 + GRID_SIZE * 2);
        addLadder(_T("Ladder.png"), GRID_SIZE * 15, HEIGHT / 2 + GRID_SIZE * 1);
        addLadder(_T("Ladder.png"), GRID_SIZE * 15, HEIGHT / 2 + GRID_SIZE * 0);
        addLadder(_T("LadderTop.png"), GRID_SIZE * 15, HEIGHT / 2 + GRID_SIZE * (-1));


        addGroundThorn(_T("groundthorn.png"), WIDTH / 2, HEIGHT / 2); // 添加地刺
        addStar(_T("star.png"), WIDTH / 2, HEIGHT / 2 + GRID_SIZE * 2); // 添加星星
        // 可以继续添加更多固定位置的地块...
    }
};

