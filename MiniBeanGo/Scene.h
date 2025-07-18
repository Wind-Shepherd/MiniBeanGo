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

class Scene // ��Ϸ������
{
private:
    // ��ά����洢����Land��
    vector
        <vector<Land>> lands;

    // ��ʼ������Land��
    void initLands() {
        lands.resize(GRID_HEIGHT);
        for (int y = 0; y < GRID_HEIGHT; y++) {
            lands[y].resize(GRID_WIDTH);
            for (int x = 0; x < GRID_WIDTH; x++) {
                lands[y][x].gridX = x;
                lands[y][x].gridY = y;
                lands[y][x].initialize(EMPTY); // Ĭ��ȫ��Ϊ�ݵ�
            }
        }
    }

public:
    IMAGE im_bk
        ;  // ����ͼ��	

    void draw() {
        putimage(0, 0, &im_bk);	// ��ʾ����	
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                lands
                    [y][x].draw();  // �������е���
            }
        }
    }

    void initialize() {
        loadimage(&im_bk, _T("landscape1.png"), WIDTH, HEIGHT); // ���뱳��ͼƬ
        initLands();
    }

    // ���Ĺ��ܣ�����ָ������λ�õ�Land����
    void setLandType(int gridX, int gridY, LandType type) {
        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
            return;
        }
        // ���µ������Ͳ����¼���ͼƬ
        lands[gridY][gridX].initialize(type);
    }
    // ��ȡָ������λ�õ�Land����
    LandType getLandType(int gridX, int gridY) {
        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
            return EMPTY;
        }
        return lands[gridY][gridX].type;
    }
};

