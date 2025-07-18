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

enum PlayerStatus // ö�����ͣ���Ϸ��ɫ���еĿ���״̬
{
	standright, jumpright, standleft, jumpleft, die
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


	vector <IMAGE> ims_runright; // ���ұ��ܵ�ͼ�����У�����ԭ�й��ܣ�
	vector <IMAGE> ims_runleft; // �����ܵ�ͼ�����У�����ԭ�й��ܣ�

	int animId;  // ����ѭ���������ŵ�id
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
			putimagePng(x_left - sceneOffsetX, y_bottom - height, &im_show);
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
			putimagePng(x_left - sceneOffsetX, y_bottom - height, &tempImg);
		}
	}

	void initialize() // ��ʼ��
	{
		ims_runleft.clear(); // ����յ�vector
		ims_runright.clear();
		loadImageEnlarged(&im_standright, _T("Standright.png")); // ������վ��ͼƬ
		loadImageEnlarged(&im_standleft, _T("Standleft.png")); // ������վ��ͼƬ
		loadImageEnlarged(&im_jumpright_sprite, _T("Jumpright.png")); // ��������ͼƬ
		loadImageEnlarged(&im_jumpleft_sprite, _T("Jumpleft.png")); // ��������ͼƬ
		loadImageEnlarged(&im_runright_sprite, _T("Runright.png")); // ���ұ��ܾ���ͼƬ
		loadImageEnlarged(&im_runleft_sprite, _T("Runleft.png"));   // �����ܾ���ͼƬ

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

		updateXY(WIDTH / 2, HEIGHT / 2); // ��ʼ����ɫ���ڻ����м�
		vx = 4; // ˮƽ������ٶ�
		vy = 0;  // ��ֱ�����ٶȳ�ʼΪ0
		gravity = 4;  // �趨�������ٶ�

		useSpriteCut = true; // ���þ���ͼ�ü�ģʽ
	}

	void updateXY(float mx, float my) // �������룬�����������
	{
		x_left = mx;
		y_bottom = my;
	}

	void runRight(Scene& scene) // ��Ϸ��ɫ���ұ���
	{
		x_left += vx; // ���������ӣ������ƶ�
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



	void runLeft(Scene& scene) // ��Ϸ��ɫ������
	{
		x_left -= vx; // ��������٣������ƶ�		
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

	void beginJump() // ����w�����Ϸ��������Ϸ��ɫ��Ծ�Ĵ���
	{
		if (playerStatus != jumpleft && playerStatus != jumpright) // �Ѿ��ڿ��еĻ�����Ҫ����
		{
			if (playerStatus == standleft)  // ����ǰ�������ܻ�����վ��״̬
			{
				im_show = im_jumpleft_sprite; // �л�����������ͼƬ
				playerStatus = jumpleft; // �л�����������״̬
			}
			else if (playerStatus == standright)// ����ǰ�������ܻ�����վ��״̬
			{
				im_show = im_jumpright_sprite;// �л�����������ͼƬ
				playerStatus = jumpright;// �л�����������״̬
			}
			vy = -40; // ����ɫһ�����ϵĳ��ٶ�w
			useSpriteCut = true; // ��Ծʱ��ʹ�þ���ͼ�ü�
		}
	}

	// �ж���Ϸ��ɫ�Ƿ���վ���������ϣ�����ǵĻ�����1�����򷵻�0
	int isOnLand(Land& land, float ySpeed)
	{
		float x_right = x_left + width;
		// �ж��Ƿ�վ�ڵ����ϣ�����Ҫ����player��y�����ٶ�������ٶȹ����п���ֱ�Ӵ�͸����
		if (ySpeed <= 0) // y�᷽���ٶ�С��0����ʾ���������˶�������Ҫ�����ٶȵ�Ӱ��
			ySpeed = 0;
		if (land.screenX - x_left <= width * 0.6 && x_right - (land.screenX - 1) <= width * 0.6 && abs(y_bottom - land.screenY) <= +ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<vector<Land>>& lands, float speed) // �ж�����Ƿ������еĵ�����
	{
		for (int i = 0; i < lands.size(); i++)
		{
			for (int j = 0; j < lands[i].size(); j++)
			{
				// ��ÿһ���������ж�
				if (isOnLand(lands[i][j], speed))
					return 0; // ���κ�һ������ϣ�����0
			}
		}
		return 1; // �������е����ϣ�����1
	}

	void updateYcoordinate(Scene& scene) // x�����ǰ����̿��Ƶģ���y������ÿ֡�Զ����µ�
	{
		if (playerStatus == jumpleft || playerStatus == jumpright) // ��ǰ���ڿ�����Ծ״̬
		{
			if (vy <= 8) {
				vy += gravity; // y�����ٶ�������Ӱ��仯
			}
			y_bottom += vy;  // y����λ�����ٶ�Ӱ��仯
			frame(&jumpFrameDelay, &jumpCurrentFrame, &jumpTotalFrames);
			for (int i = 0; i < scene.lands.size(); i++) {
				for (int j = 0; j < scene.lands[i].size(); j++)
				{
					if (isOnLand(scene.lands[i][j], vy)) // �����������վ��һ��������ʱ
					{
						y_bottom = scene.lands[i][j].screenY; // ��֤�������ڵ�����
						jumpCurrentFrame = 0; // ������Ծ����֡
						jumpFrameDelay = 0;
						if (playerStatus == jumpleft) // ����������غ��л�������վ������
							playerStatus = standleft;
						if (playerStatus == jumpright) // ����������غ��л�������վ������
							playerStatus = standright;
						break; // ����ѭ��������Ҫ�ٶ����������ж���
					}
				}
			}
		}
	}

	void frame(int* frameDelay,int* currentFrame,int* totalFrames) {
		useSpriteCut = true; // ���þ���ͼ�ü�

		// ���¶���֡
		(*frameDelay) ++;
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
};