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
#define  HEIGHT 600\

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
	IMAGE im_jumpright; // 向右方向跳跃图像
	IMAGE im_jumpleft; // 向左方向跳跃图像
	vector <IMAGE> ims_runright; // 向右奔跑的图像序列
	vector <IMAGE> ims_runleft; // 向左奔跑的图像序列
	int animId;  // 用于循环动画播放的id
	PlayerStatus playerStatus; // 当前的状态
	float x_left, y_bottom; // 这两个坐标，因为只要用这两个和地面碰撞就行了
	float vx, vy; // 速度
	float gravity; // 重力加速度
	float width, height; // 图片的宽度、高度

	void draw()// 显示相关信息	
	{
		putimagePng(x_left, y_bottom - height, &im_show);  // 游戏中显示角色
	}

	void initialize() // 初始化
	{
		ims_runleft.clear(); // 先清空掉vector
		ims_runright.clear();
		loadImageEnlarged(&im_standleft, _T("Beanleft0.png")); // 导入站立图片
		loadImageEnlarged(&im_jumpleft, _T("Beanleft1.png")); // 导入跳图片
		loadImageEnlarged(&im_standright, _T("Beanright0.png")); // 导入站立图片
		loadImageEnlarged(&im_jumpright, _T("Beanright1.png")); // 导入跳图片

		playerStatus = standright; // 初始为站立的游戏状态
		im_show = im_standright;  // 初始显示站立的图片
		width = im_standright.getwidth(); // 获得图像的宽、高，所有动画图片大小一样
		height = im_standright.getheight();


		TCHAR filename[80];
		for (int i = 0;i <= 1;i++) // 把向右奔跑的两张图片对象添加到ims_runleft中
		{
			_stprintf_s(filename, _T("Beanleft%d.png"), i);
			IMAGE im;
			loadImageEnlarged(&im, filename);
			ims_runleft.push_back(im);
		}
		for (int i = 0;i <= 1;i++) // 把向左奔跑的两张图片对象添加到ims_runright中
		{
			_stprintf_s(filename, _T("Beanright%d.png"), i);
			IMAGE im;
			loadImageEnlarged(&im, filename);
			ims_runright.push_back(im);
		}
		animId = 0; // 动画id开始设为0

		updateXY(WIDTH / 2, HEIGHT / 2); // 开始将角色放在画面中间
		vx = 4; // 水平方向初速度
		vy = 0;  // 竖直方向速度初始为0
		gravity = 4;  // 设定重力加速度
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
			im_show = im_jumpright;// 切换到向右起跳图片
			playerStatus = jumpright;// 切换到向右起跳状态
			return;
		}

		if (playerStatus == jumpleft || playerStatus == jumpright) // 如果是起跳状态
		{
			im_show = im_jumpright; // 改变造型为向右起跳造型
		}
		else
		{
			if (playerStatus != standright) // 如果之前角色状态不是向右奔跑
			{
				playerStatus = standright; // 切换为向右奔跑状态
				animId = 0; // 动画播放id初始化为0
			}
			else // 表示之前就是向右奔跑状态了
			{
			animId++; // 动画图片开始切换
			if (animId >= ims_runright.size()) // 循环切换
				animId = 0;
			}
			im_show = ims_runright[animId];	 // 设置要显示的对应图片	 
		}
	}

	void runLeft(Scene& scene) // 游戏角色向左奔跑
	{
		x_left -= vx; // 横坐标减少，向左移动		
		if (isNotOnAllLands(scene.lands, vy))  // 移动后不在任何一块地面上了
		{
			im_show = im_jumpleft; // 切换到向左起跳图片
			playerStatus = jumpleft; // 切换到向左起跳状态
			return;
		}

		if (playerStatus == jumpleft || playerStatus == jumpright) // 如果是起跳状态
		{
			im_show = im_jumpleft; // 改变造型为向左起跳造型
		}
		else
		{
			if (playerStatus != standleft) // 如果之前角色状态不是向左奔跑
			{
				playerStatus = standleft; // 切换为向左奔跑状态
				animId = 0; // 动画播放id初始化为0
			}
			else // 之前就是向左奔跑状态了
			{
			animId++; // 动画图片开始切换
			if (animId >= ims_runleft.size()) // 循环切换
				animId = 0;
			}
			im_show = ims_runleft[animId];	 // 设置要显示的对应图片	
		}
	}

	void standStill() // 游戏角色默认为向左或向右静止站立
	{
		if (playerStatus == standleft)
		{
			im_show = im_standleft;
		}
		else if (playerStatus == standright)
		{
			im_show = im_standright;
		}
	}

	void beginJump() // 按下w或向上方向键后，游戏角色跳跃的处理
	{
		if (playerStatus != jumpleft && playerStatus != jumpright) // 已经在空中的话，不要起跳
		{
			if (playerStatus == standleft)  // 起跳前是向左跑或向左站立状态
			{
				im_show = im_jumpleft; // 切换到向左起跳图片
				playerStatus = jumpleft; // 切换到向左起跳状态
			}
			else if (playerStatus == standright)// 起跳前是向右跑或向右站立状态
			{
				im_show = im_jumpright;// 切换到向右起跳图片
				playerStatus = jumpright;// 切换到向右起跳状态
			}
			vy = -40; // 给角色一个向上的初速度
		}
	}

	// 判断游戏角色是否正站在这块地面上，如果是的话返回1，否则返回0
	int isOnLand(Land& land, float ySpeed)
	{
		float x_right = x_left + width;
		// 判断是否站在地面上，还需要考虑player的y方向速度情况，速度过快有可能直接穿透地面
		if (ySpeed <= 0) // y轴方向速度小于0，表示正在向上运动，不需要考虑速度的影响
			ySpeed = 0;
		if (land.left_x - x_left <= width * 0.6 && x_right - land.right_x <= width * 0.6 && abs(y_bottom - land.top_y) <= 3 + ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<Land>& lands, float speed) // 判断玩家是否不在所有的地面上
	{
		for (int i = 0;i < lands.size();i++)
		{
			if (isOnLand(lands[i], speed))
				return 0; // 在任何一块地面上，返回0
		}
		return 1; // 不在所有地面上，返回1
	}

	void updateYcoordinate(Scene& scene) // x坐标是按键盘控制的，而y坐标是每帧自动更新的
	{
		if (playerStatus == jumpleft || playerStatus == jumpright) // 当前是在空中跳跃状态
		{
			if(vy<=8){
				vy += gravity; // y方向速度受重力影响变化
			}
			y_bottom += vy;  // y方向位置受速度影响变化
			for (int i = 0;i < scene.lands.size();i++)   // 对所有地面遍历
			{
				if (isOnLand(scene.lands[i], vy)) // 当火柴人正好站在一个地面上时
				{
					y_bottom = scene.lands[i].top_y; // 保证正好落在地面上
					if (playerStatus == jumpleft) // 向左跳，落地后切换到向左站立方向
						playerStatus = standleft;
					if (playerStatus == jumpright) // 向右跳，落地后切换到向右站立方向
						playerStatus = standright;
					break; // 跳出循环，不需要再对其他地面判断了
				}
			}
		}
	}
};
