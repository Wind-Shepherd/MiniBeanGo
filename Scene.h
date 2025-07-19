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
#include "Enemy.h"
#include "Key.h"
#include "Rod.h"
#include "Gate.h"

using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
#define GRID_SIZE 18*2
#define ACTIVE_RANGE 400 // ��ɫ���Χ���
#define ACTIVE_RANGE_Y 200 // ��ɫ���Χ�߶�

float sceneOffsetX = 0; // ��������ƫ����
float sceneOffsetY = 0; // ��������ƫ����

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

class Scene // ��Ϸ������
{
public:
    IMAGE im_bk;  // ����ͼ��    
    vector<Land> lands; // �������
    vector<Ladder> ladders; // �������
    vector<GroundThorn> groundthorns; // �ش�
    vector<Star> stars; // ����
    vector<Enemy> enemys; // �������
    vector<Key> keys; // Կ��
    vector<Rod> rods; // ����
    vector<Gate> gates; // ����

    // ���������������ͼ��·������Land��
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

    // ɾ��ָ������ķ���
    void deleteLand(float x, float y) {
        for (auto it = lands.begin(); it != lands.end(); ++it) {
            if (it->left_x == x && it->top_y == y) {
                lands.erase(it);
                break;
            }
        }
    }

    void addGroundThorn(LPCTSTR imagePath, float x, float y)
    {
        GroundThorn groundthorn(imagePath, x, y);
        groundthorn.initialize();
        groundthorns.push_back(groundthorn);
    }

    void addStar(LPCTSTR imagePath, float x, float y) // �������
    {
        Star star(imagePath, x, y);
        star.initialize();
        stars.push_back(star);
    }

    void addEnemy(float x, float y,int end, EnemyType type)//x��y��ʼλ��;end�߼���type�������ͣ��Ѱ��������߼���
    {
        Enemy enemy(x, y, end, type);
        enemy.initialize();
        enemys.push_back(enemy);
    }
    void addKey(LPCTSTR imagePath, float x, float y) // ���Կ��
    {
        Key key(imagePath, x, y);
        key.initialize();
        keys.push_back(key); // ��Կ��Ҳ��Ϊ���ǵ�һ�ִ���
    }

    void addRod(LPCTSTR imagePath_closed, LPCTSTR imagePath_open, float x, float y) // �������
    {
        Rod rod(imagePath_closed, imagePath_open, x, y);
        rod.initialize();
        rods.push_back(rod);
    }

    void addGate(LPCTSTR imagePath, float x, float y) // ��Ӵ���
    {
        Gate gate(imagePath, x, y);
        gate.initialize();
        gates.push_back(gate);
    }

    void draw(float px, float py)// ��ʾ�����Ϣ    
    {
        // ��ɫ���������Ʊ�����һ��ƫ����
        // ����ƫ����/20�����γ�������Ȳ��ǰ�󾰵��Ӿ�Ч��
        putimage(-sceneOffsetX / 20, -100 - sceneOffsetY / 20, &im_bk);	// ��ʾ����
        for (int i = 0;i < lands.size();i++)
        {
            lands[i].draw(sceneOffsetX, sceneOffsetY);  // ��������ƫ����
        }

        for (int i = 0;i < ladders.size();i++)
        {
            ladders[i].draw(sceneOffsetX, sceneOffsetY);  // ��������ƫ����
        }
        for (int i = 0;i < groundthorns.size();i++)
        {
            groundthorns[i].draw(sceneOffsetX, sceneOffsetY); // �������еش�
        }
        for (int i = 0;i < stars.size();i++)
        {
            stars[i].draw(sceneOffsetX, sceneOffsetY); // ������������
        }
        for (int i = 0;i < enemys.size();i++)
        {
            enemys[i].draw(sceneOffsetX, sceneOffsetY); // ������������
        }
        for (int i = 0; i < keys.size(); i++)
        {
            keys[i].draw(sceneOffsetX, sceneOffsetY); // ��������Կ��
        }
        for (int i = 0;i < rods.size();i++)
        {
            rods[i].draw(sceneOffsetX, sceneOffsetY); // ������������
        }
        for (int i = 0;i < gates.size();i++)
        {
            gates[i].draw(sceneOffsetX, sceneOffsetY); // �������д���
        }
    }

    void update(int i)//��Ϸ��ɾ������ʹ�ã���i�����ˣ�
    {
        switch (i) {
        case 0:
            deleteLand(GRID_SIZE * 63, HEIGHT * 3 / 4 - GRID_SIZE * 3);
            break;
        case 1:
            deleteLand(GRID_SIZE * 87, HEIGHT * 3 / 4 - GRID_SIZE * 1);
            break;
        case 2:
            deleteLand(GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 8);
            break;
        }
    }

    void initialize() // ��ʼ��
    {
        loadimage(&im_bk, _T("landscape1.png")); // ���뱳��ͼƬ
        lands.clear();// ����յ�vector

        // ʹ��addLand������������̶�����Land��
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
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 14, HEIGHT * 3 / 4 + GRID_SIZE * 3); // ��ӵش�
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 14, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 15, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("GRASS_BLOCK5.png"), GRID_SIZE * 15, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 16, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 17, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 18, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 19, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 20, HEIGHT * 3 / 4 + GRID_SIZE * 2); // ��ӵش�
        addLand(_T("GRASS_BLOCK6.png"), GRID_SIZE * 20, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 21, HEIGHT * 3 / 4 + GRID_SIZE * 2); // ��ӵش�
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
        addLadder(_T("LadderTop.png"), GRID_SIZE * 29, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLadder(_T("Ladder.png"), GRID_SIZE * 29, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLadder(_T("Ladder.png"), GRID_SIZE * 29, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLadder(_T("Ladder.png"), GRID_SIZE * 29, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLadder(_T("Ladder.png"), GRID_SIZE * 29, HEIGHT * 3 / 4 - GRID_SIZE * 2);
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
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 38, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 39, HEIGHT * 3 / 4 + GRID_SIZE * 1);
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
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 41, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 41, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 41, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 41, HEIGHT * 3 / 4);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 41, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 42, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 42, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH5.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SOIL_BLOCK7.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 43, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 44, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 44, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 44, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 45, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 45, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 45, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 46, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 46, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 46, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH5.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK0.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK7.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 47, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 48, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 48, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH6.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 + GRID_SIZE * 1);
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
        addLand(_T("DIRT_PATH7.png"), GRID_SIZE * 49, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 50, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 51, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 51, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 52, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 52, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("DIRT_PATH0.png"), GRID_SIZE * 52, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 54, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH0.png"), GRID_SIZE * 54, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 55, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLadder(_T("LadderTop.png"), GRID_SIZE * 55, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLadder(_T("Ladder.png"), GRID_SIZE * 55, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLadder(_T("Ladder.png"), GRID_SIZE * 55, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLadder(_T("Ladder.png"), GRID_SIZE * 55, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLadder(_T("Ladder.png"), GRID_SIZE * 55, HEIGHT * 3 / 4);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 58, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 59, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("DIRT_PATH2.png"), GRID_SIZE * 60, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 60, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 61, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 61, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("DIRT_PATH1.png"), GRID_SIZE * 61, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 61, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 62, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("DIRT_PATH3.png"), GRID_SIZE * 62, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 62, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 63, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("mechanism.png"), GRID_SIZE * 63, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 64, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 64, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 64, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 64, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 65, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 65, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 65, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 65, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 66, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 66, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 66, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 66, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 67, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 67, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 67, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 68, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 68, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 69, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 70, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 70, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addStar(_T("star.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 71, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 72, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 72, HEIGHT * 3 / 4);
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
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 84, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLand(_T("SNOW_BLOCK2.png"), GRID_SIZE * 85, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 85, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 85, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 85, HEIGHT * 3 / 4);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 85, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 - GRID_SIZE * 9);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 86, HEIGHT * 3 / 4);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 86, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK0.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("mechanism.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK5.png"), GRID_SIZE * 87, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 88, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 88, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 88, HEIGHT * 3 / 4);
        addStar(_T("star.png"), GRID_SIZE * 88, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 88, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 89, HEIGHT * 3 / 4);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 89, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 - GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 90, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 91, HEIGHT * 3 / 4 - GRID_SIZE * 6);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 91, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 91, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 92, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK1.png"), GRID_SIZE * 93, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 93, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLand(_T("SNOW_BLOCK3.png"), GRID_SIZE * 94, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 94, HEIGHT * 3 / 4 + GRID_SIZE * 7);
        addLadder(_T("LadderTop.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 - GRID_SIZE * 1);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 + GRID_SIZE * 5);
        addLadder(_T("Ladder.png"), GRID_SIZE * 95, HEIGHT * 3 / 4 + GRID_SIZE * 6);
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
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 106, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 106, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 107, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 107, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 107, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 108, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 108, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK6.png"), GRID_SIZE * 108, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addLand(_T("mechanism.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 8);
        addLand(_T("SNOW_BLOCK4.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 5);
        addLand(_T("SOIL_BLOCK1.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 4);
        addLand(_T("SOIL_BLOCK2.png"), GRID_SIZE * 109, HEIGHT * 3 / 4 - GRID_SIZE * 3);
        addLand(_T("BRICK_BLOCK.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addGroundThorn(_T("GROUND_THORN3.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 11);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addGroundThorn(_T("GROUND_THORN1.png"), GRID_SIZE * 110, HEIGHT * 3 / 4 - GRID_SIZE * 9);
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
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 119, HEIGHT * 3 / 4);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 119, HEIGHT * 3 / 4 + GRID_SIZE * 1);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 119, HEIGHT * 3 / 4 + GRID_SIZE * 2);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 119, HEIGHT * 3 / 4 + GRID_SIZE * 3);
        addGroundThorn(_T("GROUND_THORN2.png"), GRID_SIZE * 119, HEIGHT * 3 / 4 + GRID_SIZE * 4);
        addGroundThorn(_T("GROUND_THORN0.png"), GRID_SIZE * 119, HEIGHT * 3 / 4 + GRID_SIZE * 5);
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
        addStar(_T("star.png"), GRID_SIZE * 134, HEIGHT * 3 / 4 - GRID_SIZE * 7);
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
        addEnemy(GRID_SIZE * 15, HEIGHT * 3 / 4 + GRID_SIZE * 2, 5, Dada);
        addEnemy(GRID_SIZE * 22, HEIGHT * 3 / 4 + GRID_SIZE * 3, 4, Xiaoxiao);
        addEnemy(GRID_SIZE * 43, HEIGHT * 3 / 4 - GRID_SIZE * 6, 5, Feifei);
        addEnemy(GRID_SIZE * 59, HEIGHT * 3 / 4 - GRID_SIZE * 7, 10, Xiaoxiao);
        addEnemy(GRID_SIZE * 63, HEIGHT * 3 / 4, 8, Xiaoxiao);
        addEnemy(GRID_SIZE * 81, HEIGHT * 3 / 4 - GRID_SIZE * 9, 7, Feifei);
        addEnemy(GRID_SIZE * 92, HEIGHT * 3 / 4 - GRID_SIZE * 2, 8, Xiaoxiao);
        addEnemy(GRID_SIZE * 92, HEIGHT * 3 / 4 + GRID_SIZE * 3, 8, Xiaoxiao);
        addEnemy(GRID_SIZE * 102, HEIGHT * 3 / 4 - GRID_SIZE * 4, 7, Xiaoxiao);
        addEnemy(GRID_SIZE * 111, HEIGHT * 3 / 4 - GRID_SIZE * 4, 5, Xiaoxiao);
        addEnemy(GRID_SIZE * 120, HEIGHT * 3 / 4 + GRID_SIZE * 5, 12, Xiaoxiao);
        addEnemy(GRID_SIZE * 137, HEIGHT * 3 / 4 + GRID_SIZE * 4, 5, Feifei);
        addRod(_T("rod_closed.png"), _T("rod_open.png"), GRID_SIZE * 51, HEIGHT * 3 / 4 - GRID_SIZE * 12);
        addRod(_T("rod_closed.png"), _T("rod_open.png"), GRID_SIZE * 67, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addRod(_T("rod_closed.png"), _T("rod_open.png"), GRID_SIZE * 131, HEIGHT * 3 / 4 - GRID_SIZE * 11 );
        addKey(_T("Key.png"), GRID_SIZE * 106, HEIGHT * 3 / 4 - GRID_SIZE * 10);
        addGate(_T("gate0.png"), GRID_SIZE * 150, HEIGHT * 3 / 4 - GRID_SIZE * 2);
        addGate(_T("gate1.png"), GRID_SIZE * 150, HEIGHT * 3 / 4 - GRID_SIZE * 3);

        // ���Լ�����Ӹ���̶�λ�õĵؿ�...
    }
};

