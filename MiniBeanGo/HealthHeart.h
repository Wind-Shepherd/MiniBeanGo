#pragma once
#include <graphics.h>  
#include <windows.h>
#include <string>

class HealthHeart {
public:
    IMAGE im_hearts[3];  // ����Ѫ��״̬������ͼ��
    float left_x, top_y; // Ѫ��ͼƬ�����Ͻ�����
    int currentHealth;   // ��ǰѪ��״̬��0 - 2��

    HealthHeart(const std::wstring& imagePath1, const std::wstring& imagePath2, const std::wstring& imagePath3, float x, float y) {
        loadImageEnlarged(&im_hearts[2], imagePath1.c_str());
        loadImageEnlarged(&im_hearts[1], imagePath2.c_str());
        loadImageEnlarged(&im_hearts[0], imagePath3.c_str());
        left_x = x;
        top_y = y;
        currentHealth = 2; // ��ʼѪ��״̬
    }

    void changeHealth(int deduction) {
        // ��������Ƿ���Ч
        if (deduction > 0) {
            // ��������۳�Ѫ��
            currentHealth = (currentHealth + deduction > 2) ? 2 : currentHealth + deduction;
        }
    }

    void draw() {
        putimagePng(left_x, top_y, &im_hearts[currentHealth]);
    }
};