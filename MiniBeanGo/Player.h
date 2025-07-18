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

enum PlayerStatus // ��ɫ״̬ö��
{
    standright, jumpright, standleft, jumpleft, die
};

class Player  // ��ҽ�ɫ��
{
public:
    IMAGE im_show;               // ��ǰ��ʾͼ��
    IMAGE im_standright;         // ����վ��
    IMAGE im_standleft;          // ����վ��
    IMAGE im_jumpright;          // ������Ծ
    IMAGE im_jumpleft;           // ������Ծ
    vector<IMAGE> ims_runright;  // ���ұ�������
    vector<IMAGE> ims_runleft;   // ����������
    int animId;                  // ����֡����
    PlayerStatus playerStatus;   // ��ǰ״̬
    float x, y;                  // ��ɫλ�ã��������꣩
    float vx, vy;                // ˮƽ����ֱ�ٶ�
    float gravity;               // �������ٶ�
    float width, height;         // ��ɫ��ߣ����أ�


    Player() : x(0), y(0), animId(0), playerStatus(standright) {}

    void draw()// ���ƽ�ɫ
    {
        // ����������ת��Ϊ��������
        float screenX = x * GRID_SIZE;
        float screenY = y * GRID_SIZE - height;  // �ӵײ����ϻ���

        putimagePng(screenX, screenY, &im_show);
    }

    void initialize() // ��ʼ��
    {
        // ��ն�������
        ims_runleft.clear();
        ims_runright.clear();

        // ���ؽ�ɫͼƬ
        loadImageEnlarged(&im_standleft, _T("Beanleft0.png"));
        loadImageEnlarged(&im_jumpleft, _T("Beanleft1.png"));
        loadImageEnlarged(&im_standright, _T("Beanright0.png"));
        loadImageEnlarged(&im_jumpright, _T("Beanright1.png"));

        // ���ر��ܶ�������
        TCHAR filename[80];
        for (int i = 0; i <= 1; i++) {
            _stprintf_s(filename, _T("Beanleft%d.png"), i);
            IMAGE im;
            loadImageEnlarged(&im, filename);
            ims_runleft.push_back(im);
        }
        for (int i = 0; i <= 1; i++) {
            _stprintf_s(filename, _T("Beanright%d.png"), i);
            IMAGE im;
            loadImageEnlarged(&im, filename);
            ims_runright.push_back(im);
        }

        // ��ȡͼƬ�ߴ�
        width = im_standright.getwidth();
        height = im_standright.getheight();

        // ��ʼ��״̬����
        playerStatus = standright;
        im_show = im_standright;
        animId = 0;

        // ��ʼλ�ã��������꣩
        x = GRID_WIDTH / 2;
        y = 0;  // �Ӷ�����ʼ��0��ʾ������һ�У�

        vx = 0.2f;         // ˮƽ�ٶȣ�����λ/֡��
        vy = 0.0f;         // ��ʼ��ֱ�ٶ�
        gravity = 0.1f;    // �������ٶ�
    }

    void updateXY(float gridX, float gridY) // ������������
    {
        // �߽���
        if (gridX < 0) gridX = 0;
        if (gridX > GRID_WIDTH - 1) gridX = GRID_WIDTH - 1;
        if (gridY < 0) gridY = 0;
        if (gridY > GRID_HEIGHT - 1) gridY = GRID_HEIGHT - 1;

        x = gridX;
        y = gridY;
    }

    void runRight(Scene& scene) // ���ұ���
    {
        float newX = x + vx;

        // ����Ƿ�����ƶ������⴩ǽ��
        if (!isCollidingWithLand(scene, newX, y)) {
            x = newX;
        }

        // ����״̬�Ͷ���
        if (playerStatus == jumpleft || playerStatus == jumpright) {
            im_show = im_jumpright;
            playerStatus = jumpright;
        }
        else {
            playerStatus = standright;
            animId = (animId + 1) % ims_runright.size();
            im_show = ims_runright[animId];
        }
    }

    void runLeft(Scene& scene) // ������
    {
        float newX = x - vx;

        // ����Ƿ�����ƶ������⴩ǽ��
        if (!isCollidingWithLand(scene, newX, y)) {
            x = newX;
        }

        // ����״̬�Ͷ���
        if (playerStatus == jumpleft || playerStatus == jumpright) {
            im_show = im_jumpleft;
            playerStatus = jumpleft;
        }
        else {
            playerStatus = standleft;
            animId = (animId + 1) % ims_runleft.size();
            im_show = ims_runleft[animId];
        }
    }

    void standStill() // ��ֹվ��
    {
        if (playerStatus == standleft) {
            im_show = im_standleft;
        }
        else if (playerStatus == standright) {
            im_show = im_standright;
        }
    }

    // ��Ծ��������scene���������ڴ��ݳ�����Ϣ��
    void beginJump(Scene& scene)
    {
        // ���ڵ�����ʱ����Ծ
        if (isOnGround(scene)) {  // ���ô�����������isOnGround
            vy = -1.5f;  // ������Ծ�ٶ�
            if (playerStatus == standleft) {
                playerStatus = jumpleft;
                im_show = im_jumpleft;
            }
            else {
                playerStatus = jumpright;
                im_show = im_jumpright;
            }
        }
    }

    // ����ɫ�Ƿ��ڵ����ϣ�����scene���������ڻ�ȡ���Σ�
    bool isOnGround(Scene& scene)
    {
        // ����ɫ�·��������Ƿ�Ϊ��վ���ĵ���
        int gridY = static_cast<int>(y) + 1;
        if (gridY >= GRID_HEIGHT) return false;

        // ��ȡ��ɫ�ײ����ڵ�������
        int startCol = static_cast<int>(x);
        int endCol = static_cast<int>(x + width / GRID_SIZE);
        if (endCol > GRID_WIDTH - 1) endCol = GRID_WIDTH - 1;

        // ����ɫ�·��������Ƿ��п�վ���ĵ���
        for (int col = startCol; col <= endCol; col++) {
            LandType landType = getLandTypeAt(scene, col, gridY);  // ���ô�����������getLandTypeAt
            if (landType != EMPTY) {
                return true;
            }
        }

        return false;
    }

    // ����Ƿ��������ײ
    bool isCollidingWithLand(Scene& scene, float testX, float testY)
    {
        // �����ɫ���ڵ�����Χ
        int startRow = static_cast<int>(testY);
        int endRow = static_cast<int>(testY + height / GRID_SIZE);
        int startCol = static_cast<int>(testX);
        int endCol = static_cast<int>(testX + width / GRID_SIZE);

        // �߽���
        if (startRow < 0) startRow = 0;
        if (endRow >= GRID_HEIGHT) endRow = GRID_HEIGHT - 1;
        if (startCol < 0) startCol = 0;
        if (endCol >= GRID_WIDTH) endCol = GRID_WIDTH - 1;

        // ��鷶Χ�ڵ���������
        for (int row = startRow; row <= endRow; row++) {
            for (int col = startCol; col <= endCol; col++) {
                LandType landType = getLandTypeAt(scene, col, row);  // ���ô�����������getLandTypeAt
                if (landType != EMPTY) {
                    return true; // ��ǿյ�����ײ
                }
            }
        }

        return false;
    }

    void updateYcoordinate(Scene& scene) // ������ֱ���꣨����ģ�⣩
    {
        if (playerStatus == jumpleft || playerStatus == jumpright) {
            // Ӧ������
            vy += gravity;

            // ������λ��
            float newY = y + vy;

            // �����ײ
            if (isCollidingWithLand(scene, x, newY)) {
                // ������ײ������λ�õ�����ķ���ײλ��
                if (vy > 0) { // ����
                    // �ҵ���ɫ�·�����ĵ���
                    int gridY = static_cast<int>(y) + 1;
                    while (gridY < GRID_HEIGHT) {
                        if (isCollidingWithLand(scene, x, gridY)) {
                            y = gridY - height / GRID_SIZE;
                            vy = 0;
                            playerStatus = (playerStatus == jumpleft) ? standleft : standright;
                            break;
                        }
                        gridY++;
                    }
                }
                else { // ����
                    // �ҵ���ɫ�Ϸ�������ϰ���
                    int gridY = static_cast<int>(y);
                    while (gridY >= 0) {
                        if (isCollidingWithLand(scene, x, gridY)) {
                            y = gridY + 1;
                            vy = 0;
                            break;
                        }
                        gridY--;
                    }
                }
            }
            else {
                // û����ײ������λ��
                y = newY;
            }

            // �߽���
            if (y > GRID_HEIGHT - 1) {
                // ������Ļ�ײ���������Ϸ
                initialize();
            }
        }
    }

    // ��ȡָ������λ�õĵ������ͣ�����scene�������ӳ����л�ȡ���Σ�
    LandType getLandTypeAt(Scene& scene, int gridX, int gridY)
    {
        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
            return EMPTY; // �����߽���Ϊ��
        }

        // ͨ��������getLandType������ȡʵ�ʵ�������
        return scene.getLandType(gridX, gridY);
    }
};