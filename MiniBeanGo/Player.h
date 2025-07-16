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
	IMAGE im_jumpright; // ���ҷ�����Ծͼ��
	IMAGE im_jumpleft; // ��������Ծͼ��
	vector <IMAGE> ims_runright; // ���ұ��ܵ�ͼ������
	vector <IMAGE> ims_runleft; // �����ܵ�ͼ������
	int animId;  // ����ѭ���������ŵ�id
	PlayerStatus playerStatus; // ��ǰ��״̬
	int x_left, y_bottom; // ��Ϊint����
	int vx, vy;           // ��Ϊint����
	int gravity;          // ��Ϊint����
	int width, height;    // ��Ϊint����

	void draw(int sceneOffsetX)
	{
		// �����½�Ϊê����ƽ�ɫ
		putimagePng(x_left - sceneOffsetX, y_bottom - height, &im_show);
	}

	void initialize() // ��ʼ��
	{
		ims_runleft.clear(); // ����յ�vector
		ims_runright.clear();
		loadImageEnlarged(&im_standleft, _T("Beanleft0.png")); // ����վ��ͼƬ
		loadImageEnlarged(&im_jumpleft, _T("Beanleft1.png")); // ������ͼƬ
		loadImageEnlarged(&im_standright, _T("Beanright0.png")); // ����վ��ͼƬ
		loadImageEnlarged(&im_jumpright, _T("Beanright1.png")); // ������ͼƬ

		playerStatus = standright; // ��ʼΪվ������Ϸ״̬
		im_show = im_standright;  // ��ʼ��ʾվ����ͼƬ
		width = im_standright.getwidth(); // ���ͼ��Ŀ��ߣ����ж���ͼƬ��Сһ��
		height = im_standright.getheight();


		TCHAR filename[80];
		for (int i = 0; i <= 1; i++) // �����ұ��ܵ�����ͼƬ������ӵ�ims_runleft��
		{
			_stprintf_s(filename, _T("Beanleft%d.png"), i);
			IMAGE im;
			loadImageEnlarged(&im, filename);
			ims_runleft.push_back(im);
		}
		for (int i = 0; i <= 1; i++) // �������ܵ�����ͼƬ������ӵ�ims_runright��
		{
			_stprintf_s(filename, _T("Beanright%d.png"), i);
			IMAGE im;
			loadImageEnlarged(&im, filename);
			ims_runright.push_back(im);
		}
		animId = 0; // ����id��ʼ��Ϊ0

		updateXY(WIDTH / 2, HEIGHT / 2); // ��ʼ����ɫ���ڻ����м�
		vx = 4; // ˮƽ������ٶ�
		vy = 0;  // ��ֱ�����ٶȳ�ʼΪ0
		gravity = 4;  // �趨�������ٶ�
	}

	void updateXY(int mx, int my) // �������룬�����������
	{
		x_left = mx;
		y_bottom = my;
	}

	void runRight(Scene& scene) // ��Ϸ��ɫ���ұ���
	{
		x_left += vx; // ���������ӣ������ƶ�
		if (isNotOnAllLands(scene.lands, vy))  // �ƶ������κ�һ���������
		{
			im_show = im_jumpright;// �л�����������ͼƬ
			playerStatus = jumpright;// �л�����������״̬
			return;
		}

		if (playerStatus == jumpleft || playerStatus == jumpright) // ���������״̬
		{
			im_show = im_jumpright; // �ı�����Ϊ������������
		}
		else
		{
			if (playerStatus != standright) // ���֮ǰ��ɫ״̬�������ұ���
			{
				playerStatus = standright; // �л�Ϊ���ұ���״̬
				animId = 0; // ��������id��ʼ��Ϊ0
			}
			else // ��ʾ֮ǰ�������ұ���״̬��
			{
			animId++; // ����ͼƬ��ʼ�л�
			if (animId >= ims_runright.size()) // ѭ���л�
				animId = 0;
			}
			im_show = ims_runright[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	 
		}
	}

	void runRight(Scene& scene, bool switchAnimationOnly) // �µ����غ�����������������
	{
		if (switchAnimationOnly) // ���switchAnimationOnlyΪtrue�����л�����
		{
			if (playerStatus != standright) // ���֮ǰ��ɫ״̬�������ұ���
			{
				playerStatus = standright; // �л�Ϊ���ұ���״̬
				animId = 0; // ��������id��ʼ��Ϊ0
			}
			else // ֮ǰ�������ұ���״̬��
			{
				animId++; // ����ͼƬ��ʼ�л�
				if (animId >= ims_runright.size()) // ѭ���л�
					animId = 0;
			}
			im_show = ims_runright[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ
		}
		else // ���switchAnimationOnlyΪfalse��ִ�����ұ���
		{
			runRight(scene); // �������е�runRight����
		}
	}

	void runLeft(Scene& scene) // ��Ϸ��ɫ������
	{
		x_left -= vx; // ��������٣������ƶ�		
		if (isNotOnAllLands(scene.lands, vy))  // �ƶ������κ�һ���������
		{
			im_show = im_jumpleft; // �л�����������ͼƬ
			playerStatus = jumpleft; // �л�����������״̬
			return;
		}

		if (playerStatus == jumpleft || playerStatus == jumpright) // ���������״̬
		{
			im_show = im_jumpleft; // �ı�����Ϊ������������
		}
		else
		{
			if (playerStatus != standleft) // ���֮ǰ��ɫ״̬����������
			{
				playerStatus = standleft; // �л�Ϊ������״̬
				animId = 0; // ��������id��ʼ��Ϊ0
			}
			else // ֮ǰ����������״̬��
			{
			animId++; // ����ͼƬ��ʼ�л�
			if (animId >= ims_runleft.size()) // ѭ���л�
				animId = 0;
			}
			im_show = ims_runleft[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	
		}
	}

	void runLeft(Scene& scene, bool switchAnimationOnly) // �µ����غ�����������������
	{
		if (switchAnimationOnly) // ���switchAnimationOnlyΪtrue�����л�����
		{
			if (playerStatus != standleft) // ���֮ǰ��ɫ״̬����������
			{
				playerStatus = standleft; // �л�Ϊ������״̬
				animId = 0; // ��������id��ʼ��Ϊ0
			}
			else // ֮ǰ����������״̬��
			{
			animId++; // ����ͼƬ��ʼ�л�
			if (animId >= ims_runleft.size()) // ѭ���л�
				animId = 0;
			}
			im_show = ims_runleft[animId];	 // ����Ҫ��ʾ�Ķ�ӦͼƬ	
		}
		else // ���switchAnimationOnlyΪfalse��ִ��������
		{
			runLeft(scene); // �������е�runLeft����
		}
	}

	void standStill() // ��Ϸ��ɫĬ��Ϊ��������Ҿ�ֹվ��
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

	void beginJump() // ����w�����Ϸ��������Ϸ��ɫ��Ծ�Ĵ���
	{
		if (playerStatus != jumpleft && playerStatus != jumpright) // �Ѿ��ڿ��еĻ�����Ҫ����
		{
			if (playerStatus == standleft)  // ����ǰ�������ܻ�����վ��״̬
			{
				im_show = im_jumpleft; // �л�����������ͼƬ
				playerStatus = jumpleft; // �л�����������״̬
			}
			else if (playerStatus == standright)// ����ǰ�������ܻ�����վ��״̬
			{
				im_show = im_jumpright;// �л�����������ͼƬ
				playerStatus = jumpright;// �л�����������״̬
			}
			vy = -40; // ����ɫһ�����ϵĳ��ٶ�
		}
	}

	// �ж���Ϸ��ɫ�Ƿ���վ���������ϣ�����ǵĻ�����1�����򷵻�0
	int isOnLand(Land& land, int ySpeed)
	{
		int x_right = x_left + width;
		// �ж��Ƿ�վ�ڵ����ϣ�����Ҫ����player��y�����ٶ�������ٶȹ����п���ֱ�Ӵ�͸����
		if (ySpeed <= 0) // y�᷽���ٶ�С��0����ʾ���������˶�������Ҫ�����ٶȵ�Ӱ��
			ySpeed = 0;
		if (land.left_x - x_left <= width * 0.6 && x_right - land.right_x <= width * 0.6 && abs(y_bottom - land.top_y) <= 3 + ySpeed)
			return 1;
		else
			return 0;
	}

	int isNotOnAllLands(vector<Land>& lands, int speed) // �ж�����Ƿ������еĵ�����
	{
		for (int i = 0;i < lands.size();i++)
		{
			if (isOnLand(lands[i], speed))
				return 0; // ���κ�һ������ϣ�����0
		}
		return 1; // �������е����ϣ�����1
	}

	void updateYcoordinate(Scene& scene) // x�����ǰ����̿��Ƶģ���y������ÿ֡�Զ����µ�
	{
		if (playerStatus == jumpleft || playerStatus == jumpright) // ��ǰ���ڿ�����Ծ״̬
		{
			if (vy <= 8)
			{
				vy += gravity; // y�����ٶ�������Ӱ��仯
			}
			y_bottom += vy;  // y����λ�����ٶ�Ӱ��仯
			for (int i = 0;i < scene.lands.size();i++)   // �����е������
			{
				if (isOnLand(scene.lands[i], vy)) // �����������վ��һ��������ʱ
				{
					y_bottom = scene.lands[i].top_y; // ��֤�������ڵ�����
					if (playerStatus == jumpleft) // ����������غ��л�������վ������
						playerStatus = standleft;
					if (playerStatus == jumpright) // ����������غ��л�������վ������
						playerStatus = standright;
					break; // ����ѭ��������Ҫ�ٶ����������ж���
				}
			}
		}
	}
};
