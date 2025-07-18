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

enum PlayerStatus // 角色状态枚举
{
    standright, jumpright, standleft, jumpleft, die
};

class Player  // 玩家角色类
{
public:
    IMAGE im_show;               // 当前显示图像
    IMAGE im_standright;         // 向右站立
    IMAGE im_standleft;          // 向左站立
    IMAGE im_jumpright;          // 向右跳跃
    IMAGE im_jumpleft;           // 向左跳跃
    vector<IMAGE> ims_runright;  // 向右奔跑序列
    vector<IMAGE> ims_runleft;   // 向左奔跑序列
    int animId;                  // 动画帧索引
    PlayerStatus playerStatus;   // 当前状态
    float x, y;                  // 角色位置（网格坐标）
    float vx, vy;                // 水平、竖直速度
    float gravity;               // 重力加速度
    float width, height;         // 角色宽高（像素）


    Player() : x(0), y(0), animId(0), playerStatus(standright) {}

    void draw()// 绘制角色
    {
        // 将网格坐标转换为像素坐标
        float screenX = x * GRID_SIZE;
        float screenY = y * GRID_SIZE - height;  // 从底部向上绘制

        putimagePng(screenX, screenY, &im_show);
    }

    void initialize() // 初始化
    {
        // 清空动画序列
        ims_runleft.clear();
        ims_runright.clear();

        // 加载角色图片
        loadImageEnlarged(&im_standleft, _T("Beanleft0.png"));
        loadImageEnlarged(&im_jumpleft, _T("Beanleft1.png"));
        loadImageEnlarged(&im_standright, _T("Beanright0.png"));
        loadImageEnlarged(&im_jumpright, _T("Beanright1.png"));

        // 加载奔跑动画序列
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

        // 获取图片尺寸
        width = im_standright.getwidth();
        height = im_standright.getheight();

        // 初始化状态参数
        playerStatus = standright;
        im_show = im_standright;
        animId = 0;

        // 初始位置（网格坐标）
        x = GRID_WIDTH / 2;
        y = 0;  // 从顶部开始（0表示最上面一行）

        vx = 0.2f;         // 水平速度（网格单位/帧）
        vy = 0.0f;         // 初始竖直速度
        gravity = 0.1f;    // 重力加速度
    }

    void updateXY(float gridX, float gridY) // 更新网格坐标
    {
        // 边界检查
        if (gridX < 0) gridX = 0;
        if (gridX > GRID_WIDTH - 1) gridX = GRID_WIDTH - 1;
        if (gridY < 0) gridY = 0;
        if (gridY > GRID_HEIGHT - 1) gridY = GRID_HEIGHT - 1;

        x = gridX;
        y = gridY;
    }

    void runRight(Scene& scene) // 向右奔跑
    {
        float newX = x + vx;

        // 检查是否可以移动（避免穿墙）
        if (!isCollidingWithLand(scene, newX, y)) {
            x = newX;
        }

        // 更新状态和动画
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

    void runLeft(Scene& scene) // 向左奔跑
    {
        float newX = x - vx;

        // 检查是否可以移动（避免穿墙）
        if (!isCollidingWithLand(scene, newX, y)) {
            x = newX;
        }

        // 更新状态和动画
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

    void standStill() // 静止站立
    {
        if (playerStatus == standleft) {
            im_show = im_standleft;
        }
        else if (playerStatus == standright) {
            im_show = im_standright;
        }
    }

    // 跳跃处理（增加scene参数，用于传递场景信息）
    void beginJump(Scene& scene)
    {
        // 仅在地面上时可跳跃
        if (isOnGround(scene)) {  // 调用带场景参数的isOnGround
            vy = -1.5f;  // 向上跳跃速度
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

    // 检查角色是否在地面上（增加scene参数，用于获取地形）
    bool isOnGround(Scene& scene)
    {
        // 检查角色下方的网格是否为可站立的地面
        int gridY = static_cast<int>(y) + 1;
        if (gridY >= GRID_HEIGHT) return false;

        // 获取角色底部所在的网格列
        int startCol = static_cast<int>(x);
        int endCol = static_cast<int>(x + width / GRID_SIZE);
        if (endCol > GRID_WIDTH - 1) endCol = GRID_WIDTH - 1;

        // 检查角色下方的网格是否有可站立的地面
        for (int col = startCol; col <= endCol; col++) {
            LandType landType = getLandTypeAt(scene, col, gridY);  // 调用带场景参数的getLandTypeAt
            if (landType != EMPTY) {
                return true;
            }
        }

        return false;
    }

    // 检查是否与地面碰撞
    bool isCollidingWithLand(Scene& scene, float testX, float testY)
    {
        // 计算角色所在的网格范围
        int startRow = static_cast<int>(testY);
        int endRow = static_cast<int>(testY + height / GRID_SIZE);
        int startCol = static_cast<int>(testX);
        int endCol = static_cast<int>(testX + width / GRID_SIZE);

        // 边界检查
        if (startRow < 0) startRow = 0;
        if (endRow >= GRID_HEIGHT) endRow = GRID_HEIGHT - 1;
        if (startCol < 0) startCol = 0;
        if (endCol >= GRID_WIDTH) endCol = GRID_WIDTH - 1;

        // 检查范围内的所有网格
        for (int row = startRow; row <= endRow; row++) {
            for (int col = startCol; col <= endCol; col++) {
                LandType landType = getLandTypeAt(scene, col, row);  // 调用带场景参数的getLandTypeAt
                if (landType != EMPTY) {
                    return true; // 与非空地面碰撞
                }
            }
        }

        return false;
    }

    void updateYcoordinate(Scene& scene) // 更新竖直坐标（物理模拟）
    {
        if (playerStatus == jumpleft || playerStatus == jumpright) {
            // 应用重力
            vy += gravity;

            // 计算新位置
            float newY = y + vy;

            // 检查碰撞
            if (isCollidingWithLand(scene, x, newY)) {
                // 发生碰撞，调整位置到最近的非碰撞位置
                if (vy > 0) { // 下落
                    // 找到角色下方最近的地面
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
                else { // 上升
                    // 找到角色上方最近的障碍物
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
                // 没有碰撞，更新位置
                y = newY;
            }

            // 边界检查
            if (y > GRID_HEIGHT - 1) {
                // 掉出屏幕底部，重置游戏
                initialize();
            }
        }
    }

    // 获取指定网格位置的地面类型（增加scene参数，从场景中获取地形）
    LandType getLandTypeAt(Scene& scene, int gridX, int gridY)
    {
        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
            return EMPTY; // 超出边界视为空
        }

        // 通过场景的getLandType方法获取实际地形类型
        return scene.getLandType(gridX, gridY);
    }
};