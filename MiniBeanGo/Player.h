#pragma once

#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include <windows.h>
#include "Land.h"
#include "Scene.h"

using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

enum PlayerStatus // 枚举类型，游戏角色所有的可能状态
{
	standright, jumpright, standleft, jumpleft, die
};

class Player  // 玩家控制的游戏角色类
{
public:
	IMAGE im_show;  // 当前时刻要显示的图像
	IMAGE im_standright; // 向右站立图像
	IMAGE im_standleft; // 向左站立图像

	// 新增：用于裁剪动画的单张图片
	IMAGE im_runright_sprite; // 向右奔跑的精灵图（包含多帧）
	IMAGE im_runleft_sprite;  // 向左奔跑的精灵图（包含多帧）
	IMAGE im_jumpright_sprite; // 向右跳跃的精灵图（包含多帧）
	IMAGE im_jumpleft_sprite;  // 向左跳跃的精灵图（包含多帧）


	vector <IMAGE> ims_runright; // 向右奔跑的图像序列（保留原有功能）
	vector <IMAGE> ims_runleft; // 向左奔跑的图像序列（保留原有功能）

	int animId;  // 用于循环动画播放的id
	PlayerStatus playerStatus; // 当前的状态
	float x_left, y_bottom; // 这两个坐标，因为只要用这两个和地面碰撞就行了
	float vx, vy; // 速度
	float gravity; // 重力加速度
	float width, height; // 图片的宽度、高度

	// 用于跑步动画的变量
	int frameWidth, frameHeight; // 单帧的宽度和高度
	int totalFrames; // 总帧数
	int frameDelay; // 帧延迟计数器
	int currentFrame; // 当前帧索引
	bool useSpriteCut; // 是否使用精灵图裁剪模式

	// 跳跃动画相关变量
	int jumpFrameWidth, jumpFrameHeight; // 跳跃动画单帧的宽度和高度
	int jumpTotalFrames; // 跳跃动画总帧数
	int jumpFrameDelay; // 跳跃动画帧延迟计数器
	int jumpCurrentFrame; // 跳跃动画当前帧索引


	void draw(int sceneOffsetX)// 显示相关信息	
	{
		if (useSpriteCut)
		{
			// 使用裁剪渲染
			drawClippedFrame(sceneOffsetX);
		}
		else
		{
			// 使用原有的渲染方式
			putimagePng(x_left - sceneOffsetX, y_bottom - height, &im_show);
		}
	}

	// 绘制裁剪帧的函数
	void drawClippedFrame(int sceneOffsetX)
	{
		IMAGE* spriteImage = nullptr;
		int srcX = 0, srcY = 0;
		int frameW = width, frameH = height;

		if (playerStatus == standright)
		{
			spriteImage = &im_runright_sprite;
			srcX = currentFrame * frameW;
			srcY = 0;
		}
		else if (playerStatus == standleft)
		{
			spriteImage = &im_runleft_sprite;
			srcX = currentFrame * frameW;
			srcY = 0;
		}
		else if (playerStatus == jumpright)
		{
			spriteImage = &im_jumpright_sprite;
			srcX = jumpCurrentFrame * frameW;
			srcY = 0;
		}
		else if (playerStatus == jumpleft)
		{
			spriteImage = &im_jumpleft_sprite;
			srcX = jumpCurrentFrame * frameW;
			srcY = 0;
		}


		if (spriteImage != nullptr)
		{
			// 创建临时图像存储裁剪结果
			IMAGE tempImg;
			tempImg.Resize(frameW, frameH);
			
			// 将裁剪区域复制到临时图像
			SetWorkingImage(&tempImg);
			putimage(0, 0, frameW, frameH, spriteImage, srcX, srcY);
			SetWorkingImage(); // 恢复到默认工作图像
			
			// 渲染到屏幕
			putimagePng(x_left - sceneOffsetX, y_bottom - height, &tempImg);
		}
	}

	void initialize() // 初始化
	{
		ims_runleft.clear(); // 先清空掉vector
		ims_runright.clear();
		loadImageEnlarged(&im_standright, _T("Standright.png")); // 导入右站立图片
		loadImageEnlarged(&im_standleft, _T("Standleft.png")); // 导入左站立图片
		loadImageEnlarged(&im_jumpright_sprite, _T("Jumpright.png")); // 导入右跳图片
		loadImageEnlarged(&im_jumpleft_sprite, _T("Jumpleft.png")); // 导入左跳图片
		loadImageEnlarged(&im_runright_sprite, _T("Runright.png")); // 向右奔跑精灵图片
		loadImageEnlarged(&im_runleft_sprite, _T("Runleft.png"));   // 向左奔跑精灵图片

		playerStatus = standright; // 初始为站立的游戏状态
		im_show = im_standright;  // 初始显示站立的图片
		width = im_standright.getwidth(); // 获得图像的宽、高，所有动画图片大小一样
		height = im_standright.getheight();

		totalFrames = 6; // 有6帧动画
		frameDelay = 0;
		currentFrame = 0;

		jumpTotalFrames = 8; // 跳跃动画有8帧
		jumpFrameDelay = 0;
		jumpCurrentFrame = 2;

		updateXY(WIDTH / 2, HEIGHT / 2); // 开始将角色放在画面中间
		vx = 4; // 水平方向初速度
		vy = 0;  // 竖直方向速度初始为0
		gravity = 4;  // 设定重力加速度

		useSpriteCut = true; // 启用精灵图裁剪模式
	}

	void updateXY(float mx, float my) // 根据输入，更新玩家坐标
	{
		x_left = mx;
		y_bottom = my;
	}

	void runRight(Scene& scene) // 游戏角色向右奔跑
	{
		x_left += vx; // 横坐标增加，向右移动
		if (isNotOnAllLands(scene.lands, vy))  // 移动后不在任何一块地面上了
		{
			im_show = im_jumpright_sprite;// 切换到向右起跳图片
			playerStatus = jumpright;// 切换到向右起跳状态
			useSpriteCut = true; // 跳跃时使用精灵图裁剪
			return;
		}

		if (playerStatus == jumpleft || playerStatus == jumpright) // 如果是起跳状态
		{
			im_show = im_jumpright_sprite; // 改变造型为向右起跳造型
			useSpriteCut = true; // 跳跃时使用精灵图裁剪
			frame(&jumpFrameDelay, &jumpCurrentFrame, &jumpTotalFrames);
		}
		else
		{
			playerStatus = standright; // 设置为向右状态
			useSpriteCut = true; // 启用精灵图裁剪
			frame(&frameDelay, &currentFrame, &totalFrames);
		}
	}



	void runLeft(Scene& scene) // 游戏角色向左奔跑
	{
		x_left -= vx; // 横坐标减少，向左移动		
		if (isNotOnAllLands(scene.lands, vy))  // 移动后不在任何一块地面上了
		{
			im_show = im_jumpleft_sprite; // 切换到向左起跳图片
			playerStatus = jumpleft; // 切换到向左起跳状态
			useSpriteCut = true; // 跳跃时使用精灵图裁剪
			return;
		}

		if (playerStatus == jumpleft || playerStatus == jumpright) // 如果是起跳状态
		{
			im_show = im_jumpleft_sprite; // 改变造型为向左起跳造型
			useSpriteCut = true; // 跳跃时使用精灵图裁剪
			frame(&jumpFrameDelay, &jumpCurrentFrame, &jumpTotalFrames);
		}
		else
		{
			playerStatus = standleft; // 设置为向左状态
			useSpriteCut = true; // 启用精灵图裁剪
			frame(&frameDelay, &currentFrame, &totalFrames);
		}
	}

	void standStill() // 游戏角色默认为向左或向右静止站立
	{
		if (playerStatus == standleft)
		{
			im_show = im_standleft;
			useSpriteCut = false; // 静止时不使用精灵图裁剪
		}
		else if (playerStatus == standright)
		{
			im_show = im_standright;
			useSpriteCut = false; // 静止时不使用精灵图裁剪
		}
	}

	void beginJump() // 按下w或向上方向键后，游戏角色跳跃的处理
	{
		if (playerStatus != jumpleft && playerStatus != jumpright) // 已经在空中的话，不要起跳
		{
			if (playerStatus == standleft)  // 起跳前是向左跑或向左站立状态
			{
				im_show = im_jumpleft_sprite; // 切换到向左起跳图片
				playerStatus = jumpleft; // 切换到向左起跳状态
			}
			else if (playerStatus == standright)// 起跳前是向右跑或向右站立状态
			{
				im_show = im_jumpright_sprite;// 切换到向右起跳图片
				playerStatus = jumpright;// 切换到向右起跳状态
			}
			vy = -40; // 给角色一个向上的初速度w
			useSpriteCut = true; // 跳跃时不使用精灵图裁剪
		}
	}

	// 判断游戏角色是否正站在这块地面上，如果是的话返回1，否则返回0
	int isOnLand(Land& land, float ySpeed)
	{
		float x_right = x_left + width;
		// 判断是否站在地面上，还需要考虑player的y方向速度情况，速度过快有可能直接穿透地面
		if (ySpeed <= 0) // y轴方向速度小于0，表示正在向上运动，不需要考虑速度的影响
			ySpeed = 0;
		if (land.screenX - x_left <= width * 0.6 && x_right - (land.screenX - 1) <= width * 0.6 && abs(y_bottom - land.screenY) <= +ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<vector<Land>>& lands, float speed) // 判断玩家是否不在所有的地面上
	{
		for (int i = 0; i < lands.size(); i++)
		{
			for (int j = 0; j < lands[i].size(); j++)
			{
				// 对每一块地面进行判断
				if (isOnLand(lands[i][j], speed))
					return 0; // 在任何一块地面上，返回0
			}
		}
		return 1; // 不在所有地面上，返回1
	}

	void updateYcoordinate(Scene& scene) // x坐标是按键盘控制的，而y坐标是每帧自动更新的
	{
		if (playerStatus == jumpleft || playerStatus == jumpright) // 当前是在空中跳跃状态
		{
			if (vy <= 8) {
				vy += gravity; // y方向速度受重力影响变化
			}
			y_bottom += vy;  // y方向位置受速度影响变化
			frame(&jumpFrameDelay, &jumpCurrentFrame, &jumpTotalFrames);
			for (int i = 0; i < scene.lands.size(); i++) {
				for (int j = 0; j < scene.lands[i].size(); j++)
				{
					if (isOnLand(scene.lands[i][j], vy)) // 当火柴人正好站在一个地面上时
					{
						y_bottom = scene.lands[i][j].screenY; // 保证正好落在地面上
						jumpCurrentFrame = 0; // 重置跳跃动画帧
						jumpFrameDelay = 0;
						if (playerStatus == jumpleft) // 向左跳，落地后切换到向左站立方向
							playerStatus = standleft;
						if (playerStatus == jumpright) // 向右跳，落地后切换到向右站立方向
							playerStatus = standright;
						break; // 跳出循环，不需要再对其他地面判断了
					}
				}
			}
		}
	}

	void frame(int* frameDelay,int* currentFrame,int* totalFrames) {
		useSpriteCut = true; // 启用精灵图裁剪

		// 更新动画帧
		(*frameDelay) ++;
		if (*frameDelay >= 2) // 控制动画速度，数值越大动画越慢
		{
			*frameDelay = 0;
			(*currentFrame)++;
			if (*currentFrame >= *totalFrames) // 循环播放
			{
				*currentFrame = 0;
			}
		}
	}
};