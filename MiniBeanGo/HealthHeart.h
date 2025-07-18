#pragma once
#include <graphics.h>  
#include <windows.h>
#include <string>

class HealthHeart {
public:
    IMAGE im_hearts[3];  // 三种血量状态的心形图案
    float left_x, top_y; // 血量图片的左上角坐标
    int currentHealth;   // 当前血量状态（0 - 2）

    HealthHeart(const std::wstring& imagePath1, const std::wstring& imagePath2, const std::wstring& imagePath3, float x, float y) {
        loadImageEnlarged(&im_hearts[2], imagePath1.c_str());
        loadImageEnlarged(&im_hearts[1], imagePath2.c_str());
        loadImageEnlarged(&im_hearts[0], imagePath3.c_str());
        left_x = x;
        top_y = y;
        currentHealth = 2; // 初始血量状态
    }

    void changeHealth(int deduction) {
        // 检查输入是否有效
        if (deduction > 0) {
            // 根据输入扣除血量
            currentHealth = (currentHealth + deduction > 2) ? 2 : currentHealth + deduction;
        }
    }

    void draw() {
        putimagePng(left_x, top_y, &im_hearts[currentHealth]);
    }
};