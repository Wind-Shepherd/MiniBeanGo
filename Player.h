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
#include "Key.h"
#include "Rod.h"
#include "Gate.h"

using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
#define GRAVITY 4.5
#define ACTIVE_RANGE_Y 300 // 角色活动范围高度

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

enum PlayerStatus // 枚举类型，游戏角色所有的可能状态
{
	standright, jumpright, standleft, jumpleft, climb, hurtright, hurtleft, dieright, dieleft
};

enum PlayerHealthStatus {
	no_health,
	half_health,
	full_health,
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
	IMAGE im_climb_sprite;// 向爬的精灵图（包含多帧）
	IMAGE im_hurtright_sprite; // 向右受伤的精灵图（包含多帧）
	IMAGE im_hurtleft_sprite;  // 向左受伤的精灵图（包含多帧）
	IMAGE im_dieright_sprite; // 向右死亡的精灵图（包含多帧）
	IMAGE im_dieleft_sprite;  // 向左跳跃的精灵图（包含多帧）

	// 新增：血量状态对应的图片
	IMAGE im_full_health;
	IMAGE im_half_health;
	IMAGE im_no_health;

	bool isInvincible; // 是否处于无敌状态
	clock_t invincibleStartTime; // 无敌开始时间
	int invincibleDuration; // 无敌持续时间（毫秒）

	int death = 0;
	int key = 0;
	int win = 0;
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

	// 爬动画相关变量
	int climbFrameWidth, climbFrameHeight; // 爬动画单帧的宽度和高度
	int climbTotalFrames; // 爬动画总帧数
	int climbFrameDelay; // 爬动画帧延迟计数器
	int climbCurrentFrame; // 爬动画当前帧索引

	// 受伤动画相关变量
	int hurtFrameWidth, hurtFrameHeight; // 受伤动画单帧的宽度和高度
	int hurtTotalFrames; // 受伤动画总帧数
	int hurtFrameDelay; // 受伤动画帧延迟计数器
	int hurtCurrentFrame; // 受伤动画当前帧索引

	// 死亡动画相关变量
	int dieFrameWidth, dieFrameHeight; // 死亡动画单帧的宽度和高度
	int dieTotalFrames; // 死亡动画总帧数
	int dieFrameDelay; // 死亡动画帧延迟计数器
	int dieCurrentFrame; // 死亡动画当前帧索引

	float getXRight() const { return x_left + width; }  // 角色右边界
	float getYTop() const { return y_bottom - height; } // 角色上边界
	float getYBottom() const { return y_bottom; }       // 角色下边界

	PlayerHealthStatus healthStatus = full_health;

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
			putimagePng(x_left - sceneOffsetX, y_bottom - height - sceneOffsetY, &im_show);
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
		else if (playerStatus == climb)
		{
			spriteImage = &im_climb_sprite;
			srcX = climbCurrentFrame * frameW;
			srcY = 0;
		}
		else if (playerStatus == hurtright)
		{
			spriteImage = &im_hurtright_sprite;
			srcX = hurtCurrentFrame * frameW;
			srcY = 0;
		}
		else if (playerStatus == hurtleft)
		{
			spriteImage = &im_hurtleft_sprite;
			srcX = hurtCurrentFrame * frameW;
			srcY = 0;
		}
		else if (playerStatus == dieright)
		{
			spriteImage = &im_dieright_sprite;
			srcX = dieCurrentFrame * frameW;
			srcY = 0;
		}
		else if (playerStatus == dieleft)
		{
			spriteImage = &im_dieleft_sprite;
			srcX = dieCurrentFrame * frameW;
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
			putimagePng(x_left - sceneOffsetX, y_bottom - height - sceneOffsetY, &tempImg);
		}
	}

	//void drawHealthStatus() {
	//	IMAGE* healthImg = nullptr;
	//	switch (healthStatus) {
	//	case full_health:
	//		healthImg = &im_full_health;
	//		break;
	//	case half_health:
	//		healthImg = &im_half_health;
	//		break;
	//	case no_health:
	//		healthImg = &im_no_health;
	//		break;
	//	}
	//	if (healthImg != nullptr) {
	//		putimagePng(100, 100, healthImg); // 绘制在屏幕左上角
	//	}
	//}

	void initialize() // 初始化
	{

		loadImageEnlarged(&im_standright, _T("Standright.png")); // 导入右站立图片
		loadImageEnlarged(&im_standleft, _T("Standleft.png")); // 导入左站立图片
		loadImageEnlarged(&im_jumpright_sprite, _T("Jumpright.png")); // 导入右跳图片
		loadImageEnlarged(&im_jumpleft_sprite, _T("Jumpleft.png")); // 导入左跳图片
		loadImageEnlarged(&im_runright_sprite, _T("Runright.png")); // 向右奔跑精灵图片
		loadImageEnlarged(&im_runleft_sprite, _T("Runleft.png"));   // 向左奔跑精灵图片
		loadImageEnlarged(&im_climb_sprite, _T("Climb.png"));   // 爬图片
		loadImageEnlarged(&im_hurtright_sprite, _T("Hurtright.png")); // 导入右跳图片
		loadImageEnlarged(&im_hurtleft_sprite, _T("Hurtleft.png")); // 导入左跳图片
		loadImageEnlarged(&im_dieright_sprite, _T("Dieright.png")); // 导入右跳图片
		loadImageEnlarged(&im_dieleft_sprite, _T("Dieleft.png")); // 导入左跳图片

		key = 0;
		win = 0;
		death = 0;
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

		climbTotalFrames = 4; // 爬动画有4帧
		climbFrameDelay = 0;
		climbCurrentFrame = 0;

		hurtTotalFrames = 4; // 受伤动画有4帧
		hurtFrameDelay = 0;
		hurtCurrentFrame = 0;

		dieTotalFrames = 8; // 死亡动画有4帧
		dieFrameDelay = 0;
		dieCurrentFrame = 0;

		updateXY(WIDTH / 2, HEIGHT / 2); // 开始将角色放在画面中间
		vx = 10; // 水平方向初速度
		vy = 0;  // 竖直方向速度初始为0
		gravity = GRAVITY;  // 设定重力加速度

		isInvincible = false;
		invincibleStartTime = 0;
		invincibleDuration = 2000; // 例如，无敌时间设置为 2 秒

		useSpriteCut = true; // 启用精灵图裁剪模式
	}

	void updateXY(float mx, float my) // 根据输入，更新玩家坐标
	{
		x_left = mx;
		y_bottom = my;

	}

	void runRight(Scene& scene) // 游戏角色向右奔跑
	{
		float correctedX = x_left;

		if (checkHorizontalCollision(vx, scene, true)) {
			x_left = correctedX; // 使用修正后的x坐标
			// 保持当前动画状态
			if (playerStatus == standright || playerStatus == jumpright) {
				frame(&frameDelay, &currentFrame, &totalFrames);
			}
			return;
		}
		if (playerStatus != dieright && playerStatus != dieright) {
			x_left += vx; // 横坐标增加，向右移动
		}
		
		if (playerStatus != hurtleft && playerStatus != hurtright && playerStatus != dieright && playerStatus != dieright) // 已经受伤的话，不要播放其他动画
		{
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
		else if (playerStatus == hurtleft) {
			playerStatus = hurtright;
		}
	}



	void runLeft(Scene& scene) // 游戏角色向左奔跑
	{
		float correctedX = x_left;

		if (checkHorizontalCollision(vx, scene, false)) {
			x_left = correctedX; // 使用修正后的x坐标
			// 保持当前动画状态
			if (playerStatus == standleft || playerStatus == jumpleft) {
				frame(&frameDelay, &currentFrame, &totalFrames);
			}
			return;
		}
		if (playerStatus != dieright && playerStatus != dieright) {
			x_left -= vx; // 横坐标减少，向左移动	
		}
		
		if (playerStatus != hurtleft && playerStatus != hurtright && playerStatus != dieright && playerStatus != dieright) // 已经受伤的话，不要播放其他动画
		{
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
		else if(playerStatus == hurtright){
			playerStatus = hurtleft;
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

	void beginJump(Scene& scene) // 按下w或向上方向键后，游戏角色跳跃的处理
	{
		if (!isNotOnAllLadders(scene.ladders, vy)) {
			im_show = im_climb_sprite; // 切换到爬图片
			playerStatus = climb; // 切换到爬状态
			vy = -3; // 给角色一个向上的初速度
			useSpriteCut = true;
		}
		else {
			if ((playerStatus != jumpleft && playerStatus != jumpright)||((playerStatus == hurtleft || playerStatus == hurtright || playerStatus == dieleft || playerStatus == dieright )&& isNotOnAllLands(scene.lands, vy))) // 已经在空中的话，不要起跳
			{
				if (playerStatus == standleft) {
					im_show = im_jumpleft_sprite; // 切换到向左起跳图片
					playerStatus = jumpleft; // 切换到向左起跳状态
				}
				else if (playerStatus == standright)// 起跳前是向右跑或向右站立状态
				{
					im_show = im_jumpright_sprite;// 切换到向右起跳图片
					playerStatus = jumpright;// 切换到向右起跳状态
				}
				vy = -35; // 给角色一个向上的初速度
				PlayMusicOnce(_T("jump.mp3"));
			}
			useSpriteCut = true;
		}
	}

	// 判断游戏角色是否正站在这块地面上，如果是的话返回1，否则返回0
	int isOnLand(Land& land, float ySpeed)
	{
		float x_right = x_left + width;
		// 判断是否站在地面上，还需要考虑player的y方向速度情况，速度过快有可能直接穿透地面
		if (ySpeed <= 0) // y轴方向速度小于0，表示正在向上运动，不需要考虑速度的影响
			ySpeed = 0;
		if (land.left_x - x_left <= width * 0.6 && x_right - land.right_x <= width * 0.6 && abs(y_bottom - land.top_y) <= 0 + ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<Land>& lands, float speed) // 判断玩家是否不在所有的地面上
	{
		for (int i = 0; i < lands.size(); i++)
		{
			if (isOnLand(lands[i], speed))
				return 0; // 在任何一块地面上，返回0
		}
		return 1; // 不在所有地面上，返回1
	}

	void updateYcoordinate(Scene& scene) {

		if (playerStatus == hurtright || playerStatus == hurtleft) {
			frame(&hurtFrameDelay, &hurtCurrentFrame, &hurtTotalFrames);
			if (isNotOnAllLands(scene.lands, vy)) {
				if (vy <= 8) vy += gravity;
			}
		}

		if (playerStatus == dieright || playerStatus == dieleft) {
			frame2(&dieFrameDelay, &dieCurrentFrame, &dieTotalFrames);
			if (isNotOnAllLands(scene.lands, vy)) {
				if (vy <= 8) vy += gravity;
			}
		}

		// 统一加速度
		if (playerStatus == jumpleft || playerStatus == jumpright) {
			if (vy <= 8) vy += gravity;
		}

		float newY = y_bottom + vy;
		float topBound = (HEIGHT - ACTIVE_RANGE_Y) / 2;
		float bottomBound = (HEIGHT + ACTIVE_RANGE_Y) / 2;

		// 计算角色屏幕坐标位置（角色坐标 - 场景偏移）
		float playerScreenY = newY - sceneOffsetY;

		// 角色在活动区内，直接更新位置
		if (playerScreenY >= topBound && playerScreenY <= bottomBound) {
			y_bottom = newY;
		}
		// 角色要往上超出活动区
		else if (playerScreenY < topBound) {
			sceneOffsetY += vy;
			y_bottom = newY;
		}
		// 角色要往下超出活动区
		else if (playerScreenY > bottomBound) {
			sceneOffsetY += vy;
			y_bottom = newY;
		}

		// 跳跃动画帧播放
		if (playerStatus == jumpright || playerStatus == jumpleft) {
			frame(&jumpFrameDelay, &jumpCurrentFrame, &jumpTotalFrames);
			if (y_bottom  > 1000) {
				if (playerStatus == jumpleft) {
					playerStatus = dieleft; 
				}
				else if (playerStatus == jumpright)
				{
					playerStatus = dieright;
				}
			}
		}
		else if (playerStatus == climb && (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))) {
			frame(&climbFrameDelay, &climbCurrentFrame, &climbTotalFrames);
		}

		// 检查地面碰撞（落地）
		bool hasCollision = false;
		if ((playerStatus == jumpleft || playerStatus == jumpright) && vy < 0) {
			for (int i = 0; i < scene.lands.size(); ++i) {
				Land
					& land = scene.lands[i];
				float playerTop = getYTop(); // 人物顶部Y坐标

				// 最简单坐标判定：人物顶部与Land下边缘坐标重合（允许±2像素误差）
				bool verticalOverlap = (playerTop >= land.top_y - 10) && (playerTop <= land.top_y + 2);

				// 水平方向重叠判断（至少30%宽度）
				float playerRight = x_left + width;
				bool horizontalOverlap = (x_left + width * 0.1 <= land.right_x) &&
					(playerRight - width * 0.1 >= land.left_x);

				if (verticalOverlap && horizontalOverlap) {
					// 碰撞后强制调整位置并反弹
					y_bottom
						= land.top_y + height + 2; // 确保人物在Land下方
					vy
						= -vy; // 向下反弹速度
					jumpCurrentFrame
						= 0; // 重置跳跃动画
					hasCollision
						= true;
					PlayMusicOnce(_T("bounce.mp3")); // 播放碰撞音效
					break;
				}
			}
		}

		// 原有地面碰撞检测（仅在未发生反弹时执行）
		if (!hasCollision && (playerStatus == jumpleft || playerStatus == jumpright)) {
			for (int i = 0; i < scene.lands.size(); ++i) {
				if (isOnLand(scene.lands[i], vy)) {
					y_bottom
						= scene.lands[i].top_y;
					vy
						= 0;
					jumpCurrentFrame
						= 2;
					jumpFrameDelay
						= 0;
					playerStatus
						= (playerStatus == jumpleft) ? standleft : standright;
					break;
				}
			}
			for (int i = 0; i < scene.ladders.size(); ++i) {
				if (isOnLadder(scene.ladders[i], vy)) {
					y_bottom = scene.ladders[i].top_y;
					vy = 0;
					climbCurrentFrame = 0;
					climbFrameDelay = 0;
					playerStatus = standright;
					break;
				}
			}
		}
		// 检查地面碰撞（落地）
		if (playerStatus == hurtleft || playerStatus == hurtright || playerStatus == dieright || playerStatus == dieleft) {
			for (int i = 0; i < scene.lands.size(); ++i) {
				if (isOnLand(scene.lands[i], vy)) {
					y_bottom = scene.lands[i].top_y;
					vy = 0;
					break;
				}
			}
			for (int i = 0; i < scene.ladders.size(); ++i) {
				if (isOnLadder(scene.ladders[i], vy)) {
					y_bottom = scene.ladders[i].top_y;
					vy = 0;
					break;
				}
			}
		}

		// 爬梯逻辑
		if (playerStatus == climb && (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))) {
			if (isNotOnAllLadders(scene.ladders, vy)) {
				playerStatus = standright;
				vy = 0;
			}
		}
		else if (playerStatus == climb) {
			vy = 0;
		}
	}


	void frame(int* frameDelay, int* currentFrame, int* totalFrames) {
		useSpriteCut = true; // 启用精灵图裁剪

		// 更新动画帧
		(*frameDelay)++;
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
	void frame2(int* frameDelay, int* currentFrame, int* totalFrames) {
		useSpriteCut = true; // 启用精灵图裁剪

		// 更新动画帧
		(*frameDelay)++;
		if (*frameDelay >= 2) // 控制动画速度，数值越大动画越慢
		{
			*frameDelay = 0;
			(*currentFrame)++;
			if (*currentFrame >= *totalFrames) // 循环播放
			{
				*currentFrame = 0;
				if (playerStatus == dieright || playerStatus == dieleft)
					death = 1;
				playerStatus = standright;
			}
		}
	}

	// 判断游戏角色是否正站在梯子上，如果是的话返回1，否则返回0
	int isOnLadder(Ladder& ladder, float ySpeed)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = ladder.top_y - ladder.ladder_height;
		// 判断是否站在梯子上
		if (ladder.left_x - x_left <= width * 0.6 && x_right - ladder.right_x <= width * 0.6 && y_bottom - bottom_y > height * 0.6 && y_top - ladder.top_y < height * 0.6)
			return 1;
		else
			return 0;
	}
	int isNotOnAllLadders(vector<Ladder>& Ladders, float speed) // 判断玩家是否不在所有的梯子上
	{
		for (int i = 0; i < Ladders.size(); i++)
		{
			if (isOnLadder(Ladders[i], speed))
				return 0; // 在任何一块梯子上，返回0
		}
		return 1; // 不在所有梯子上，返回1
	}

	int isOnGroundThorn(GroundThorn& groundthorn)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = groundthorn.top_y - groundthorn.groundthorn_height;
		if (groundthorn.left_x - x_left <= width * 0.3 && x_right - groundthorn.right_x <= width * 0.3 && y_bottom - bottom_y >= height * 0.3 && y_top - groundthorn.top_y <= height * 0.3)
			return 1;
		else
			return 0;
	}

	int isNotOnAllGroundThorns(vector<GroundThorn>& GroundThorns)
	{
		for (int i = 0; i < GroundThorns.size(); i++)
		{
			if (isOnGroundThorn(GroundThorns[i]))
				return 0;
		}
		return 1;
	}

	int isOnEnemy(Enemy& enemy)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = enemy.top_y - enemy.enemy_height;
		if (enemy.left_x - x_left <= width * 0.3 && x_right - enemy.right_x <= width * 0.3 && y_bottom - bottom_y >= height * 0.3 && y_top - enemy.top_y <= height * 0.3)
			return 1;
		else
			return 0;
	}

	int isNotOnAllEnemys(vector<Enemy>& Enemys)
	{
		for (int i = 0; i < Enemys.size(); i++)
		{
			if (isOnEnemy(Enemys[i]))
				return 0;
		}
		return 1;
	}

	int isOnKey(Key& key)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = key.top_y - key.key_height;
		if (key.left_x - x_left <= width * 0.6 && x_right - key.right_x <= width * 0.6 && y_bottom - bottom_y >= height * 0.6 && y_top - key.top_y <= height * 0.6)
			return 1;
		else
			return 0;
	}

	int isOnTheKey(vector<Key>& Keys)
	{
		for (int i = 0; i < Keys.size(); i++)
		{
			if (isOnKey(Keys[i]))
				return i;
		}
		return -1;
	}

	int isOnStar(Star& star)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = star.top_y - star.star_height;
		if (star.left_x - x_left <= width * 0.6 && x_right - star.right_x <= width * 0.6 && y_bottom - bottom_y >= height * 0.6 && y_top - star.top_y <= height * 0.6)
			return 1;
		else
			return 0;
	}

	int isOnTheStar(vector<Star>& Stars)
	{
		for (int i = 0; i < Stars.size(); i++)
		{
			if (isOnStar(Stars[i]))
				return i;
		}
		return -1;
	}

	int isOnRod(Rod& rod)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = rod.top_y - rod.rod_height;
		if (rod.left_x - x_left <= width * 0.6 && x_right - rod.right_x <= width * 0.6 && y_bottom - bottom_y >= height * 0.6 && y_top - rod.top_y <= height * 0.6)
			return 1;
		else
			return 0;
	}

	/*int isOnTheRod(vector<Rod>& Rods)
	{
		for (int i = 0; i < Rods.size(); i++)
		{
			if (isOnRod(Rods[i]))
				return i;
		}
		return -1;
	}

	int isOnGate(Gate& gate)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = gate.top_y - gate.gate_height;
		if (gate.left_x - x_left <= width * 0.6 && x_right - gate.right_x <= width * 0.6 && y_bottom - bottom_y >= height * 0.6 && y_top - gate.top_y <= height * 0.6)
			return 1;
		else
			return 0;
	}*/

	int isOnTheRod(vector<Rod>& Rods)
	{
		for (int i = 0; i < Rods.size(); i++)
		{
			if (isOnRod(Rods[i]))
				return i;
		}
		return -1;
	}

	int isOnGate(Gate& gate)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = gate.top_y - gate.gate_height;
		if (gate.left_x - x_left <= width * 0.3 && x_right - gate.right_x <= width * 0.3 && y_bottom - bottom_y >= height * 0.3 && y_top - gate.top_y <= height * 0.3)
			return 1;
		else
			return 0;
	}

	int isOnTheGate(vector<Gate>& Gates)
	{
		for (int i = 0; i < Gates.size(); i++)
		{
			if (isOnGate(Gates[i]))
				return i;
		}
		return -1;
	}

	void PlayMusicOnce(const wchar_t* fileName) // 播放一次音乐文件
	{
		wchar_t cmdString1[50];
		swprintf_s(cmdString1, L"open %s alias tmpmusic", fileName); // 构造命令字符串
		mciSendStringW(L"close tmpmusic", NULL, 0, NULL); // 先将当前的一次音乐停止关闭
		mciSendStringW(cmdString1, NULL, 0, NULL); // 打开音乐
		mciSendStringW(L"play tmpmusic", NULL, 0, NULL); // 播放一次
	}


	// 检测左右移动是否会与地面碰撞
	bool checkHorizontalCollision(float moveDelta, Scene& scene, bool isRight) {
		float newXLeft = x_left + (isRight ? moveDelta : -moveDelta);
		float newXRight = newXLeft + width;
		float yTop = getYTop();
		float yBottom = y_bottom;
		const float collisionTolerance = 20.0f;

		for (auto& land : scene.lands) {
			// 垂直方向是否重叠
			bool verticalOverlap = (yBottom > land.top_y) && (yTop < land.top_y + land.land_height);
			if (!verticalOverlap) continue;

			// 向右移动：检测是否会撞上地面左侧
			if (isRight && newXRight > land.left_x + collisionTolerance && newXLeft < land.left_x) {
				return true;
			}
			// 向左移动：检测是否会撞上地面右侧
			else if (!isRight && newXLeft < land.right_x - collisionTolerance && newXRight > land.right_x) {
				return true;
			}
		}

		return false;
	}

	void reduceHealth(bool halfHeart) {
		switch (healthStatus) {
		case full_health:
			if (!isInvincible) {
				if (halfHeart) {
					healthStatus = half_health;
					if (playerStatus == standright || playerStatus == jumpright) {
						playerStatus = hurtright;
					}
					else if (playerStatus == standleft || playerStatus == jumpleft) {
						playerStatus = hurtleft;
					}
				}
				else {
					healthStatus = no_health;
					if (playerStatus == standright || playerStatus == jumpright) {
						playerStatus = dieright;
					}
					else if (playerStatus == standleft || playerStatus == jumpleft) {
						playerStatus = dieleft;
					}
				}
				isInvincible = true;
				invincibleStartTime = clock();
			}
			break;
		case half_health:
			if (!isInvincible) {
				healthStatus = no_health;
				if (playerStatus == standright || playerStatus == jumpright) {
					playerStatus = dieright;
				}
				else if (playerStatus == standleft || playerStatus == jumpleft) {
					playerStatus = dieleft;
				}
				isInvincible = true;
				invincibleStartTime = clock();
			}
			break;
		case no_health:
			break;
		}
	}

	void update()
	{
		clock_t currentTime = clock();
		if (isInvincible) {
			if (currentTime - invincibleStartTime >= invincibleDuration) {
				isInvincible = false; // 无敌时间结束
				if (playerStatus == hurtright) {
					playerStatus = standright;
				}
				else if (playerStatus == hurtleft) {
					playerStatus = standleft;
				}
			}
		}

	}
};