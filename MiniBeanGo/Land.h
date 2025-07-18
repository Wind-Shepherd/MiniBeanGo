#pragma once

#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include <vector>
#include <windows.h>

using namespace std;
#define GRID_SIZE 18  
// ����������������Ⱥ͸߶ȷ���
#define GRID_WIDTH 25
#define GRID_HEIGHT 13
// ���㴰���ܴ�С
#define  WIDTH (GRID_SIZE * GRID_WIDTH)  
#define  HEIGHT (GRID_SIZE * GRID_HEIGHT)

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

void loadImageEnlarged(IMAGE* img, LPCTSTR filename);
#endif

enum LandType {
    EMPTY,
    GRASS_BLOCK1,
    GRASS_BLOCK2,
    GRASS_BLOCK3,
    SOIL_BLOCK1,
    SOIL_BLOCK2,
    DIRT_PATH1,
    DIRT_PATH2,
    SNOW_BLOCK1,
    SNOW_BLOCK2,
    SNOW_BLOCK3,
    // ��������
};
class Land  // ������
{
public:
    IMAGE im_land;  // ����ͼ��
    LandType type;  // ��������
    int gridX, gridY; // ��������

    void initialize(LandType t) {
        type = t;
        if (type == EMPTY) {
            return;
        }
        LPCTSTR filename;

        switch (t) {
        case GRASS_BLOCK1: filename = _T("GRASS_BLOCK1.png"); break;
        case GRASS_BLOCK2: filename = _T("GRASS_BLOCK2.png"); break;
        case GRASS_BLOCK3: filename = _T("GRASS_BLOCK3.png"); break;
        case SOIL_BLOCK1: filename = _T("SOIL_BLOCK1.png"); break;
        case SOIL_BLOCK2: filename = _T("SOIL_BLOCK2.png"); break;
        case DIRT_PATH1:  filename = _T("DIRT_PATH1.png"); break;
        case DIRT_PATH2:  filename = _T("DIRT_PATH2.png"); break;
        case SNOW_BLOCK1:  filename = _T("SNOW_BLOCK1.png"); break;
        case SNOW_BLOCK2:  filename = _T("SNOW_BLOCK2.png"); break;
        case SNOW_BLOCK3:  filename = _T("SNOW_BLOCK3.png"); break;
        default:return;
        }

        loadimage(&im_land, filename, GRID_SIZE, GRID_SIZE); // ֱ�Ӽ���Ϊ�����С
    }

    void draw() {
        if (type == EMPTY) {
            return;
        }
        int screenX = gridX * GRID_SIZE;
        int screenY = gridY * GRID_SIZE;
        putimage(screenX, screenY, &im_land);  // ���Ƶ���
    }
};

