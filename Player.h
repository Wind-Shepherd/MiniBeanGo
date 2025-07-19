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
#define ACTIVE_RANGE_Y 300 // ��ɫ���Χ�߶�

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

enum PlayerStatus // ö�����ͣ���Ϸ��ɫ���еĿ���״̬
{
	standright, jumpright, standleft, jumpleft, climb, hurtright, hurtleft, dieright, dieleft
};

enum PlayerHealthStatus {
	no_health,
	half_health,
	full_health,
};

class Player  // ��ҿ��Ƶ���Ϸ��ɫ��
{
public:
	IMAGE im_show;  // ��ǰʱ��Ҫ��ʾ��ͼ��
	IMAGE im_standright; // ����վ��ͼ��
	IMAGE im_standleft; // ����վ��ͼ��

	// ���������ڲü������ĵ���ͼƬ
	IMAGE im_runright_sprite; // ���ұ��ܵľ���ͼ��������֡��
	IMAGE im_runleft_sprite;  // �����ܵľ���ͼ��������֡��
	IMAGE im_jumpright_sprite; // ������Ծ�ľ���ͼ��������֡��
	IMAGE im_jumpleft_sprite;  // ������Ծ�ľ���ͼ��������֡��
	IMAGE im_climb_sprite;// �����ľ���ͼ��������֡��
	IMAGE im_hurtright_sprite; // �������˵ľ���ͼ��������֡��
	IMAGE im_hurtleft_sprite;  // �������˵ľ���ͼ��������֡��
	IMAGE im_dieright_sprite; // ���������ľ���ͼ��������֡��
	IMAGE im_dieleft_sprite;  // ������Ծ�ľ���ͼ��������֡��

	// ������Ѫ��״̬��Ӧ��ͼƬ
	IMAGE im_full_health;
	IMAGE im_half_health;
	IMAGE im_no_health;

	bool isInvincible; // �Ƿ����޵�״̬
	clock_t invincibleStartTime; // �޵п�ʼʱ��
	int invincibleDuration; // �޵г���ʱ�䣨���룩

	int death = 0;
	int key = 0;
	int win = 0;
	PlayerStatus playerStatus; // ��ǰ��״̬
	float x_left, y_bottom; // ���������꣬��ΪֻҪ���������͵�����ײ������
	float vx, vy; // �ٶ�
	float gravity; // �������ٶ�
	float width, height; // ͼƬ�Ŀ�ȡ��߶�

	// �����ܲ������ı���
	int frameWidth, frameHeight; // ��֡�Ŀ�Ⱥ͸߶�
	int totalFrames; // ��֡��
	int frameDelay; // ֡�ӳټ�����
	int currentFrame; // ��ǰ֡����
	bool useSpriteCut; // �Ƿ�ʹ�þ���ͼ�ü�ģʽ

	// ��Ծ������ر���
	int jumpFrameWidth, jumpFrameHeight; // ��Ծ������֡�Ŀ�Ⱥ͸߶�
	int jumpTotalFrames; // ��Ծ������֡��
	int jumpFrameDelay; // ��Ծ����֡�ӳټ�����
	int jumpCurrentFrame; // ��Ծ������ǰ֡����

	// ��������ر���
	int climbFrameWidth, climbFrameHeight; // ��������֡�Ŀ�Ⱥ͸߶�
	int climbTotalFrames; // ��������֡��
	int climbFrameDelay; // ������֡�ӳټ�����
	int climbCurrentFrame; // ��������ǰ֡����

	// ���˶�����ر���
	int hurtFrameWidth, hurtFrameHeight; // ���˶�����֡�Ŀ�Ⱥ͸߶�
	int hurtTotalFrames; // ���˶�����֡��
	int hurtFrameDelay; // ���˶���֡�ӳټ�����
	int hurtCurrentFrame; // ���˶�����ǰ֡����

	// ����������ر���
	int dieFrameWidth, dieFrameHeight; // ����������֡�Ŀ�Ⱥ͸߶�
	int dieTotalFrames; // ����������֡��
	int dieFrameDelay; // ��������֡�ӳټ�����
	int dieCurrentFrame; // ����������ǰ֡����

	float getXRight() const { return x_left + width; }  // ��ɫ�ұ߽�
	float getYTop() const { return y_bottom - height; } // ��ɫ�ϱ߽�
	float getYBottom() const { return y_bottom; }       // ��ɫ�±߽�

	PlayerHealthStatus healthStatus = full_health;

	void draw(int sceneOffsetX)// ��ʾ�����Ϣ	
	{
		if (useSpriteCut)
		{
			// ʹ�òü���Ⱦ
			drawClippedFrame(sceneOffsetX);
		}
		else
		{
			// ʹ��ԭ�е���Ⱦ��ʽ
			putimagePng(x_left - sceneOffsetX, y_bottom - height - sceneOffsetY, &im_show);
		}
	}

	// ���Ʋü�֡�ĺ���
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
			// ������ʱͼ��洢�ü����
			IMAGE tempImg;
			tempImg.Resize(frameW, frameH);

			// ���ü������Ƶ���ʱͼ��
			SetWorkingImage(&tempImg);
			putimage(0, 0, frameW, frameH, spriteImage, srcX, srcY);
			SetWorkingImage(); // �ָ���Ĭ�Ϲ���ͼ��

			// ��Ⱦ����Ļ
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
	//		putimagePng(100, 100, healthImg); // ��������Ļ���Ͻ�
	//	}
	//}

	void initialize() // ��ʼ��
	{

		loadImageEnlarged(&im_standright, _T("Standright.png")); // ������վ��ͼƬ
		loadImageEnlarged(&im_standleft, _T("Standleft.png")); // ������վ��ͼƬ
		loadImageEnlarged(&im_jumpright_sprite, _T("Jumpright.png")); // ��������ͼƬ
		loadImageEnlarged(&im_jumpleft_sprite, _T("Jumpleft.png")); // ��������ͼƬ
		loadImageEnlarged(&im_runright_sprite, _T("Runright.png")); // ���ұ��ܾ���ͼƬ
		loadImageEnlarged(&im_runleft_sprite, _T("Runleft.png"));   // �����ܾ���ͼƬ
		loadImageEnlarged(&im_climb_sprite, _T("Climb.png"));   // ��ͼƬ
		loadImageEnlarged(&im_hurtright_sprite, _T("Hurtright.png")); // ��������ͼƬ
		loadImageEnlarged(&im_hurtleft_sprite, _T("Hurtleft.png")); // ��������ͼƬ
		loadImageEnlarged(&im_dieright_sprite, _T("Dieright.png")); // ��������ͼƬ
		loadImageEnlarged(&im_dieleft_sprite, _T("Dieleft.png")); // ��������ͼƬ

		key = 0;
		win = 0;
		death = 0;
		playerStatus = standright; // ��ʼΪվ������Ϸ״̬
		im_show = im_standright;  // ��ʼ��ʾվ����ͼƬ
		width = im_standright.getwidth(); // ���ͼ��Ŀ��ߣ����ж���ͼƬ��Сһ��
		height = im_standright.getheight();

		totalFrames = 6; // ��6֡����
		frameDelay = 0;
		currentFrame = 0;

		jumpTotalFrames = 8; // ��Ծ������8֡
		jumpFrameDelay = 0;
		jumpCurrentFrame = 2;

		climbTotalFrames = 4; // ��������4֡
		climbFrameDelay = 0;
		climbCurrentFrame = 0;

		hurtTotalFrames = 4; // ���˶�����4֡
		hurtFrameDelay = 0;
		hurtCurrentFrame = 0;

		dieTotalFrames = 8; // ����������4֡
		dieFrameDelay = 0;
		dieCurrentFrame = 0;

		updateXY(WIDTH / 2, HEIGHT / 2); // ��ʼ����ɫ���ڻ����м�
		vx = 10; // ˮƽ������ٶ�
		vy = 0;  // ��ֱ�����ٶȳ�ʼΪ0
		gravity = GRAVITY;  // �趨�������ٶ�

		isInvincible = false;
		invincibleStartTime = 0;
		invincibleDuration = 2000; // ���磬�޵�ʱ������Ϊ 2 ��

		useSpriteCut = true; // ���þ���ͼ�ü�ģʽ
	}

	void updateXY(float mx, float my) // �������룬�����������
	{
		x_left = mx;
		y_bottom = my;

	}

	void runRight(Scene& scene) // ��Ϸ��ɫ���ұ���
	{
		float correctedX = x_left;

		if (checkHorizontalCollision(vx, scene, true)) {
			x_left = correctedX; // ʹ���������x����
			// ���ֵ�ǰ����״̬
			if (playerStatus == standright || playerStatus == jumpright) {
				frame(&frameDelay, &currentFrame, &totalFrames);
			}
			return;
		}
		if (playerStatus != dieright && playerStatus != dieright) {
			x_left += vx; // ���������ӣ������ƶ�
		}
		
		if (playerStatus != hurtleft && playerStatus != hurtright && playerStatus != dieright && playerStatus != dieright) // �Ѿ����˵Ļ�����Ҫ������������
		{
			if (isNotOnAllLands(scene.lands, vy))  // �ƶ������κ�һ���������
			{
				im_show = im_jumpright_sprite;// �л�����������ͼƬ
				playerStatus = jumpright;// �л�����������״̬
				useSpriteCut = true; // ��Ծʱʹ�þ���ͼ�ü�
				return;
			}

			if (playerStatus == jumpleft || playerStatus == jumpright) // ���������״̬
			{
				im_show = im_jumpright_sprite; // �ı�����Ϊ������������
				useSpriteCut = true; // ��Ծʱʹ�þ���ͼ�ü�
				frame(&jumpFrameDelay, &jumpCurrentFrame, &jumpTotalFrames);
			}
			else
			{
				playerStatus = standright; // ����Ϊ����״̬
				useSpriteCut = true; // ���þ���ͼ�ü�
				frame(&frameDelay, &currentFrame, &totalFrames);
			}
		}
		else if (playerStatus == hurtleft) {
			playerStatus = hurtright;
		}
	}



	void runLeft(Scene& scene) // ��Ϸ��ɫ������
	{
		float correctedX = x_left;

		if (checkHorizontalCollision(vx, scene, false)) {
			x_left = correctedX; // ʹ���������x����
			// ���ֵ�ǰ����״̬
			if (playerStatus == standleft || playerStatus == jumpleft) {
				frame(&frameDelay, &currentFrame, &totalFrames);
			}
			return;
		}
		if (playerStatus != dieright && playerStatus != dieright) {
			x_left -= vx; // ��������٣������ƶ�	
		}
		
		if (playerStatus != hurtleft && playerStatus != hurtright && playerStatus != dieright && playerStatus != dieright) // �Ѿ����˵Ļ�����Ҫ������������
		{
			if (isNotOnAllLands(scene.lands, vy))  // �ƶ������κ�һ���������
			{
				im_show = im_jumpleft_sprite; // �л�����������ͼƬ
				playerStatus = jumpleft; // �л�����������״̬
				useSpriteCut = true; // ��Ծʱʹ�þ���ͼ�ü�
				return;
			}

			if (playerStatus == jumpleft || playerStatus == jumpright) // ���������״̬
			{
				im_show = im_jumpleft_sprite; // �ı�����Ϊ������������
				useSpriteCut = true; // ��Ծʱʹ�þ���ͼ�ü�
				frame(&jumpFrameDelay, &jumpCurrentFrame, &jumpTotalFrames);
			}
			else
			{
				playerStatus = standleft; // ����Ϊ����״̬
				useSpriteCut = true; // ���þ���ͼ�ü�
				frame(&frameDelay, &currentFrame, &totalFrames);
			}
		}
		else if(playerStatus == hurtright){
			playerStatus = hurtleft;
		}

	}

	void standStill() // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��
	{
		if (playerStatus == standleft)
		{
			im_show = im_standleft;
			useSpriteCut = false; // ��ֹʱ��ʹ�þ���ͼ�ü�
		}
		else if (playerStatus == standright)
		{
			im_show = im_standright;
			useSpriteCut = false; // ��ֹʱ��ʹ�þ���ͼ�ü�
		}
	}

	void beginJump(Scene& scene) // ����w�����Ϸ��������Ϸ��ɫ��Ծ�Ĵ���
	{
		if (!isNotOnAllLadders(scene.ladders, vy)) {
			im_show = im_climb_sprite; // �л�����ͼƬ
			playerStatus = climb; // �л�����״̬
			vy = -3; // ����ɫһ�����ϵĳ��ٶ�
			useSpriteCut = true;
		}
		else {
			if ((playerStatus != jumpleft && playerStatus != jumpright)||((playerStatus == hurtleft || playerStatus == hurtright || playerStatus == dieleft || playerStatus == dieright )&& isNotOnAllLands(scene.lands, vy))) // �Ѿ��ڿ��еĻ�����Ҫ����
			{
				if (playerStatus == standleft) {
					im_show = im_jumpleft_sprite; // �л�����������ͼƬ
					playerStatus = jumpleft; // �л�����������״̬
				}
				else if (playerStatus == standright)// ����ǰ�������ܻ�����վ��״̬
				{
					im_show = im_jumpright_sprite;// �л�����������ͼƬ
					playerStatus = jumpright;// �л�����������״̬
				}
				vy = -35; // ����ɫһ�����ϵĳ��ٶ�
				PlayMusicOnce(_T("jump.mp3"));
			}
			useSpriteCut = true;
		}
	}

	// �ж���Ϸ��ɫ�Ƿ���վ���������ϣ�����ǵĻ�����1�����򷵻�0
	int isOnLand(Land& land, float ySpeed)
	{
		float x_right = x_left + width;
		// �ж��Ƿ�վ�ڵ����ϣ�����Ҫ����player��y�����ٶ�������ٶȹ����п���ֱ�Ӵ�͸����
		if (ySpeed <= 0) // y�᷽���ٶ�С��0����ʾ���������˶�������Ҫ�����ٶȵ�Ӱ��
			ySpeed = 0;
		if (land.left_x - x_left <= width * 0.6 && x_right - land.right_x <= width * 0.6 && abs(y_bottom - land.top_y) <= 0 + ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<Land>& lands, float speed) // �ж�����Ƿ������еĵ�����
	{
		for (int i = 0; i < lands.size(); i++)
		{
			if (isOnLand(lands[i], speed))
				return 0; // ���κ�һ������ϣ�����0
		}
		return 1; // �������е����ϣ�����1
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

		// ͳһ���ٶ�
		if (playerStatus == jumpleft || playerStatus == jumpright) {
			if (vy <= 8) vy += gravity;
		}

		float newY = y_bottom + vy;
		float topBound = (HEIGHT - ACTIVE_RANGE_Y) / 2;
		float bottomBound = (HEIGHT + ACTIVE_RANGE_Y) / 2;

		// �����ɫ��Ļ����λ�ã���ɫ���� - ����ƫ�ƣ�
		float playerScreenY = newY - sceneOffsetY;

		// ��ɫ�ڻ���ڣ�ֱ�Ӹ���λ��
		if (playerScreenY >= topBound && playerScreenY <= bottomBound) {
			y_bottom = newY;
		}
		// ��ɫҪ���ϳ������
		else if (playerScreenY < topBound) {
			sceneOffsetY += vy;
			y_bottom = newY;
		}
		// ��ɫҪ���³������
		else if (playerScreenY > bottomBound) {
			sceneOffsetY += vy;
			y_bottom = newY;
		}

		// ��Ծ����֡����
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

		// ��������ײ����أ�
		bool hasCollision = false;
		if ((playerStatus == jumpleft || playerStatus == jumpright) && vy < 0) {
			for (int i = 0; i < scene.lands.size(); ++i) {
				Land
					& land = scene.lands[i];
				float playerTop = getYTop(); // ���ﶥ��Y����

				// ��������ж������ﶥ����Land�±�Ե�����غϣ������2������
				bool verticalOverlap = (playerTop >= land.top_y - 10) && (playerTop <= land.top_y + 2);

				// ˮƽ�����ص��жϣ�����30%��ȣ�
				float playerRight = x_left + width;
				bool horizontalOverlap = (x_left + width * 0.1 <= land.right_x) &&
					(playerRight - width * 0.1 >= land.left_x);

				if (verticalOverlap && horizontalOverlap) {
					// ��ײ��ǿ�Ƶ���λ�ò�����
					y_bottom
						= land.top_y + height + 2; // ȷ��������Land�·�
					vy
						= -vy; // ���·����ٶ�
					jumpCurrentFrame
						= 0; // ������Ծ����
					hasCollision
						= true;
					PlayMusicOnce(_T("bounce.mp3")); // ������ײ��Ч
					break;
				}
			}
		}

		// ԭ�е�����ײ��⣨����δ��������ʱִ�У�
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
		// ��������ײ����أ�
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

		// �����߼�
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
		useSpriteCut = true; // ���þ���ͼ�ü�

		// ���¶���֡
		(*frameDelay)++;
		if (*frameDelay >= 2) // ���ƶ����ٶȣ���ֵԽ�󶯻�Խ��
		{
			*frameDelay = 0;
			(*currentFrame)++;
			if (*currentFrame >= *totalFrames) // ѭ������
			{
				*currentFrame = 0;
			}
		}
	}
	void frame2(int* frameDelay, int* currentFrame, int* totalFrames) {
		useSpriteCut = true; // ���þ���ͼ�ü�

		// ���¶���֡
		(*frameDelay)++;
		if (*frameDelay >= 2) // ���ƶ����ٶȣ���ֵԽ�󶯻�Խ��
		{
			*frameDelay = 0;
			(*currentFrame)++;
			if (*currentFrame >= *totalFrames) // ѭ������
			{
				*currentFrame = 0;
				if (playerStatus == dieright || playerStatus == dieleft)
					death = 1;
				playerStatus = standright;
			}
		}
	}

	// �ж���Ϸ��ɫ�Ƿ���վ�������ϣ�����ǵĻ�����1�����򷵻�0
	int isOnLadder(Ladder& ladder, float ySpeed)
	{
		float x_right = x_left + width;
		float y_top = y_bottom - height;
		float bottom_y = ladder.top_y - ladder.ladder_height;
		// �ж��Ƿ�վ��������
		if (ladder.left_x - x_left <= width * 0.6 && x_right - ladder.right_x <= width * 0.6 && y_bottom - bottom_y > height * 0.6 && y_top - ladder.top_y < height * 0.6)
			return 1;
		else
			return 0;
	}
	int isNotOnAllLadders(vector<Ladder>& Ladders, float speed) // �ж�����Ƿ������е�������
	{
		for (int i = 0; i < Ladders.size(); i++)
		{
			if (isOnLadder(Ladders[i], speed))
				return 0; // ���κ�һ�������ϣ�����0
		}
		return 1; // �������������ϣ�����1
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

	void PlayMusicOnce(const wchar_t* fileName) // ����һ�������ļ�
	{
		wchar_t cmdString1[50];
		swprintf_s(cmdString1, L"open %s alias tmpmusic", fileName); // ���������ַ���
		mciSendStringW(L"close tmpmusic", NULL, 0, NULL); // �Ƚ���ǰ��һ������ֹͣ�ر�
		mciSendStringW(cmdString1, NULL, 0, NULL); // ������
		mciSendStringW(L"play tmpmusic", NULL, 0, NULL); // ����һ��
	}


	// ��������ƶ��Ƿ���������ײ
	bool checkHorizontalCollision(float moveDelta, Scene& scene, bool isRight) {
		float newXLeft = x_left + (isRight ? moveDelta : -moveDelta);
		float newXRight = newXLeft + width;
		float yTop = getYTop();
		float yBottom = y_bottom;
		const float collisionTolerance = 20.0f;

		for (auto& land : scene.lands) {
			// ��ֱ�����Ƿ��ص�
			bool verticalOverlap = (yBottom > land.top_y) && (yTop < land.top_y + land.land_height);
			if (!verticalOverlap) continue;

			// �����ƶ�������Ƿ��ײ�ϵ������
			if (isRight && newXRight > land.left_x + collisionTolerance && newXLeft < land.left_x) {
				return true;
			}
			// �����ƶ�������Ƿ��ײ�ϵ����Ҳ�
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
				isInvincible = false; // �޵�ʱ�����
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