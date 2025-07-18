#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include "Land.h"
#include "Scene.h"
#include "Player.h"
#include <vector>
#include <windows.h>

using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
#define ACTIVE_RANGE 400 // 角色活动范围宽度
float sceneOffsetX = 0; // 场景横向偏移量


// 一些全局变量
Player player;  // 定义玩家控制的游戏角色对象
Scene scene;  // 定义场景全局对象
Timer timer;  // 用于精确延时


float getPlayerScreenX() {
	float leftBound = (WIDTH - ACTIVE_RANGE) / 2;
	float rightBound = (WIDTH + ACTIVE_RANGE) / 2;
	if (player.x_left - sceneOffsetX < leftBound)
		return leftBound;
	else if (player.x_left - sceneOffsetX > rightBound)
		return rightBound;
	else
		return player.x_left - sceneOffsetX;
}

void startup()  // 初始化
{
	sceneOffsetX = 0; // 场景偏移量归零
	scene.initialize();  // 场景初始化
	scene.setLandType(1, 8, GRASS_BLOCK1);
	scene.setLandType(2, 8, GRASS_BLOCK1);
	scene.setLandType(3, 7, GRASS_BLOCK2);
	scene.setLandType(4, 7, GRASS_BLOCK1);
	scene.setLandType(5, 7, GRASS_BLOCK1);
	scene.setLandType(6, 7, GRASS_BLOCK1);
	scene.setLandType(7, 8, SOIL_BLOCK1);
	scene.setLandType(7, 7, GRASS_BLOCK3);
	scene.setLandType(8, 9, GRASS_BLOCK3);
	scene.setLandType(9, 10, GRASS_BLOCK3);
	scene.setLandType(10, 11, GRASS_BLOCK1);
	scene.setLandType(11, 11, GRASS_BLOCK1);
	scene.setLandType(12, 11, GRASS_BLOCK1);
	scene.setLandType(13, 10, GRASS_BLOCK2);
	scene.setLandType(14, 10, GRASS_BLOCK1);
	scene.setLandType(15, 10, DIRT_PATH1);
	scene.setLandType(16, 10, DIRT_PATH2);
	scene.setLandType(17, 11, DIRT_PATH1);
	scene.setLandType(18, 11, DIRT_PATH1);
	scene.setLandType(19, 11, DIRT_PATH1);
	scene.setLandType(20, 10, SNOW_BLOCK1);
	scene.setLandType(21, 9, SOIL_BLOCK1);
	scene.setLandType(21, 8, SNOW_BLOCK1);
	scene.setLandType(22, 7, SNOW_BLOCK1);
	scene.setLandType(22, 8, SOIL_BLOCK1);
	player.initialize(); // 玩家角色初始化
	initgraph(WIDTH, HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 显示
{
	scene.draw(sceneOffsetX, player.y_bottom - HEIGHT / 2);   // 显示场景相关信息
	player.draw(sceneOffsetX); // 显示玩家相关信息
	FlushBatchDraw(); // 批量绘制
	timer.Sleep(50); // 暂停若干毫秒
}

void updateWithoutInput() // 和输入无关的更新
{
	player.updateYcoordinate(scene); // 游戏角色y坐标是每帧自动更新的
}

void updateWithInput() // 和输入有关的更新
{
	player.standStill(); // 游戏角色默认为向左或向右静止站立

	if (_kbhit()) // 当按键时，切换角色显示图片，更改位置
	{
		if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))) // 同时按下A键和D键或左右方向键
		{
			;//角色不动，既不向左也不向右奔跑
		}
		else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))  // 按下D键或右方向键
		{
			float rightBound = (WIDTH + ACTIVE_RANGE) / 2;
            if (player.x_left - sceneOffsetX < rightBound) {
                player.runRight(scene);
            } else {
                sceneOffsetX += player.vx; // 场景左移
                player.runRight(scene); // 只切换动画，不移动角色
            }
		}
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// 按下A键或左方向键
		{
			float leftBound = (WIDTH - ACTIVE_RANGE) / 2;
            if (player.x_left - sceneOffsetX > leftBound) {
                player.runLeft(scene);
            } else {
                sceneOffsetX -= player.vx; // 场景右移
                player.runLeft(scene); // 只切换动画，不移动角色
            }
		}
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))     // 按下W键或上方向键
		{
			player.beginJump();
		}
	}
}

void loadImageEnlarged(IMAGE* img, LPCTSTR filename) {
	IMAGE temp;
	loadimage(&temp, filename);

	int orig_width = temp.getwidth();
	int orig_height = temp.getheight();
	int new_width = orig_width * 3;
	int new_height = orig_height * 3;

	img->Resize(new_width, new_height);

	// 获取设备上下文
	HDC tempDC = GetImageHDC(&temp);
	HDC imgDC = GetImageHDC(img);

	// 使用StretchBlt进行缩放，保持透明色
	StretchBlt(imgDC, 0, 0, new_width, new_height,
		tempDC, 0, 0, orig_width, orig_height, SRCCOPY);
}

int main() // 主函数
{
	startup();  	// 初始化
	while (1)       // 一直循环
	{

		show();  // 显示
		updateWithoutInput(); // 与输入无关的更新
		updateWithInput();    // 与输入有关的更新



		if (_kbhit() && GetAsyncKeyState('P') & 0x8000) // 检测 'p' 键是否按下
		{
			// 重新初始化游戏
			startup();
		}
	}
	return 0;
}