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
#define  WIDTH 800  
#define  HEIGHT 600
//#ifndef IMAGE_UTILS_H
//#define IMAGE_UTILS_H
//
//void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
//#endif

class Scene // 游戏场景类
{
public:
    //二维数组存储所有Land块
	vector<vector<Land>> lands; // 网格化的地面

    //初始化所有Land块
    void initLands() {
        lands.resize(GRID_HEIGHT);
        for(int y=0;y<GRID_HEIGHT; y++) {
            lands[y].resize(GRID_WIDTH);
            for(int x = 0; x < GRID_WIDTH; x++) {
                lands[y][x].gridX = x;
                lands[y][x].gridY = y;
				lands[y][x].initialize(EMPTY);// 初始化为空地 
            }
		}
    }

    IMAGE im_bk;  // 背景图像    

    void draw(float px, float py)// 显示相关信息    
    {
        // 角色不动，绘制背景有一个偏移量
        // 背景偏移量/20，就形成了有深度差的前后景的视觉效果
        putimage(-px / 20, -100 - py / 20, &im_bk);	// 显示背景
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                lands
                    [y][x].draw(px, 0); // 绘制所有地面
            }
        }
    }
    void initialize() {
        loadimage(&im_bk, _T("landscape1.png"), WIDTH, HEIGHT); // 导入背景图片
        initLands();
    }

    // 核心功能：更改指定网格位置的Land类型
    void setLandType(int gridX, int gridY, LandType type) {
        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
            return;
        }
        // 更新地面类型并重新加载图片
        lands[gridY][gridX].initialize(type);
    }
    // 获取指定网格位置的Land类型
    LandType getLandType(int gridX, int gridY) {
        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
            return EMPTY;
        }
        return lands[gridY][gridX].type;
    }
};