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

// 定义拉杆状态枚举
enum RodStatus {
    ROD_CLOSED,
    ROD_OPEN
};

class Rod
{
public:
    IMAGE im_rod_closed;  // 拉杆关闭状态图片
    IMAGE im_rod_open;    // 拉杆打开状态图片
    float left_x, right_x, top_y; // 拉杆的左上角坐标
    float rod_width, rod_height;  // 拉杆图片的宽度和高度
    LPCTSTR imagePath_closed;     // 拉杆关闭状态图片路径
    LPCTSTR imagePath_open;       // 拉杆打开状态图片路径
    RodStatus status;             // 拉杆当前状态

    Rod(LPCTSTR path_closed, LPCTSTR path_open, float x, float y) : imagePath_closed(path_closed), imagePath_open(path_open), left_x(x), top_y(y), status(ROD_CLOSED) {}

    void initialize() // 初始化
    {
        loadImageEnlarged(&im_rod_closed, imagePath_closed); // 加载关闭状态图片
        loadImageEnlarged(&im_rod_open, imagePath_open);     // 加载打开状态图片
        rod_width = im_rod_closed.getwidth(); // 获取图片宽度
        rod_height = im_rod_closed.getheight();
        right_x = left_x + rod_width;
		status = ROD_CLOSED; // 默认状态为关闭
    }

    void draw(float px, float py) // 绘制拉杆
    {
        if (status == ROD_CLOSED) {
            putimagePng(left_x - px, top_y - py, &im_rod_closed); // 绘制关闭状态图片
        }
        else {
            putimagePng(left_x - px, top_y - py, &im_rod_open);   // 绘制打开状态图片
        }
    }

    void changeStatus() // 更改拉杆状态
    {
        if (status == ROD_CLOSED) {
            status = ROD_OPEN;
        }
        else {
            status = ROD_CLOSED;
        }
    }
};