#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"
#include "Timer.h"
#include "Land.h"
#include "Scene.h"
#include "Player.h"
#include <vector>
#include <windows.h>
#include "MusicPlayer.h"
#include "HealthHeart.h"
#pragma comment(lib,"Winmm.lib")
#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <io.h> 
#include <cstdlib> 

using namespace std;

// 窗口尺寸
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 颜色定义
const COLORREF PRIMARY_COLOR = RGB(255, 107, 107);
const COLORREF SECONDARY_COLOR = RGB(78, 205, 196);
const COLORREF ACCENT_COLOR = RGB(255, 209, 102);
const COLORREF PIXEL_GRAY = RGB(149, 165, 166);
const COLORREF PIXEL_GREEN = RGB(46, 204, 113);
const COLORREF PIXEL_BLUE = RGB(52, 152, 219);
const COLORREF PIXEL_RED = RGB(231, 76, 60);
const COLORREF PIXEL_YELLOW = RGB(241, 196, 15);
const COLORREF PIXEL_PURPLE = RGB(155, 89, 182);
const COLORREF DARK_COLOR = RGB(41, 47, 54);
const COLORREF LIGHT_COLOR = RGB(247, 255, 247);



// 按钮类型枚举
enum class ButtonType {
	START,
	SETTINGS,
	LEADERBOARD,
	HELP,
	CLOSE_SETTINGS,
	SAVE_SETTINGS,
	MUSIC_ON,
	MUSIC_OFF,
	SFX_ON,
	SFX_OFF,
	DIFFICULTY_EASY,
	DIFFICULTY_MEDIUM,
	DIFFICULTY_HARD,
	EXIT
};

// 按钮结构
struct Button {
	int x, y, width, height;
	std::wstring text;
	COLORREF normalColor;
	COLORREF hoverColor;
	COLORREF textColor;
	ButtonType type;
	bool isHovered;
	bool isPressed;

	Button(int _x, int _y, int _w, int _h, const std::wstring& _text,
		COLORREF _normalColor, COLORREF _hoverColor, COLORREF _textColor, ButtonType _type)
		: x(_x), y(_y), width(_w), height(_h), text(_text),
		normalColor(_normalColor), hoverColor(_hoverColor), textColor(_textColor),
		type(_type), isHovered(false), isPressed(false) {
	}

	bool contains(int mx, int my) const {
		return mx >= x && mx <= x + width && my >= y && my <= y + height;
	}

	void draw() const {
		// 绘制按钮阴影效果
		if (!isPressed) {
			setfillcolor(DARK_COLOR);
			solidrectangle(x + 4, y + 4, x + width + 4, y + height + 4);
		}

		// 绘制按钮主体
		setfillcolor(isHovered ? hoverColor : normalColor);
		setlinecolor(DARK_COLOR);
		setlinestyle(PS_SOLID, 4);

		int offsetX = isPressed ? 2 : 0;
		int offsetY = isPressed ? 2 : 0;

		solidrectangle(x + offsetX, y + offsetY, x + width + offsetX, y + height + offsetY);
		rectangle(x + offsetX, y + offsetY, x + width + offsetX, y + height + offsetY);

		// 绘制文本
		settextcolor(textColor);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, L"Arial");

		int textWidth = textwidth(text.c_str());
		int textHeight = textheight(text.c_str());
		int textX = x + (width - textWidth) / 2 + offsetX;
		int textY = y + (height - textHeight) / 2 + offsetY;

		outtextxy(textX, textY, text.c_str());
	}
};

// 粒子结构
struct Particle {
	float x, y;
	float vx, vy;
	COLORREF color;
	float life;
	float maxLife;
	int size;

	Particle(float _x, float _y, COLORREF _color)
		: x(_x), y(_y), color(_color) {
		vx = (rand() % 200 - 100) / 100.0f;
		vy = (rand() % 200 - 100) / 100.0f;
		maxLife = life = 3.0f + (rand() % 300) / 100.0f;
		size = 2 + rand() % 4;
	}

	void update(float deltaTime) {
		x += vx * deltaTime * 50;
		y += vy * deltaTime * 50;
		life -= deltaTime;

		// 边界检查
		if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
			life = 0;
		}
	}

	void draw() const {
		if (life > 0) {
			setfillcolor(color);
			setlinecolor(DARK_COLOR);
			setlinestyle(PS_SOLID, 1);

			solidcircle((int)x, (int)y, size);
			circle((int)x, (int)y, size);
		}
	}

	bool isAlive() const {
		return life > 0;
	}
};

class MiniBeanGoUI {
private:
	std::vector<Button> buttons;
	std::vector<Particle> particles;
	bool showSettingsModal;
	bool musicEnabled;
	bool sfxEnabled;
	int difficulty; // 0=Easy, 1=Medium, 2=Hard

	// 动画变量
	clock_t lastTime;
	float heroOffset;
	float heroAnimTime;

	// 英雄位置
	int heroX, heroY;

	// 英雄图片
	IMAGE heroImg;

public:
	bool startGameRequested;  // 新增：开始游戏请求标志

	MiniBeanGoUI() : showSettingsModal(false), musicEnabled(true), sfxEnabled(true),
		difficulty(1), heroOffset(0), heroAnimTime(0), startGameRequested(false) {  // 初始化标志
		heroX = WINDOW_WIDTH / 2 - 50;
		heroY = 200;
		lastTime = clock();

		// 加载英雄图片
		loadimage(&heroImg, L"StartPlayer.png", 100, 100); // 加载并缩放图片

		initializeMainButtons();
		initializeParticles();
	}

	void initializeMainButtons() {
		buttons.clear();

		int buttonWidth = 200;
		int buttonHeight = 50;
		int startX = (WINDOW_WIDTH - buttonWidth) / 2;
		int startY = 350;
		int spacing = 60;

		buttons.push_back(Button(startX, startY, buttonWidth, buttonHeight,
			L"Start Game", PRIMARY_COLOR, RGB(255, 87, 87), WHITE, ButtonType::START));
		buttons.push_back(Button(startX, startY + spacing, buttonWidth, buttonHeight,
			L"Settings", SECONDARY_COLOR, RGB(58, 185, 176), WHITE, ButtonType::SETTINGS));
		buttons.push_back(Button(startX, startY + spacing * 2, buttonWidth, buttonHeight,
			L"Leaderboard", ACCENT_COLOR, RGB(235, 189, 82), DARK_COLOR, ButtonType::LEADERBOARD));
		buttons.push_back(Button(startX, startY + spacing * 3, buttonWidth, buttonHeight,
			L"Help", PIXEL_GRAY, RGB(129, 145, 146), WHITE, ButtonType::HELP));
	}

	void initializeSettingsButtons() {
		buttons.clear();

		// 关闭按钮
		buttons.push_back(Button(680, 120, 40, 40, L"X", PIXEL_RED, RGB(200, 0, 0), WHITE, ButtonType::CLOSE_SETTINGS));

		// 音乐按钮
		buttons.push_back(Button(300, 200, 40, 32, L"M", musicEnabled ? PIXEL_GREEN : PIXEL_GRAY,
			musicEnabled ? RGB(26, 184, 93) : RGB(129, 145, 146), WHITE, ButtonType::MUSIC_ON));
		buttons.push_back(Button(350, 200, 40, 32, L"M", !musicEnabled ? PIXEL_GREEN : PIXEL_GRAY,
			!musicEnabled ? RGB(26, 184, 93) : RGB(129, 145, 146), WHITE, ButtonType::MUSIC_OFF));

		// 音效按钮
		buttons.push_back(Button(300, 250, 40, 32, L"S", sfxEnabled ? PIXEL_GREEN : PIXEL_GRAY,
			sfxEnabled ? RGB(26, 184, 93) : RGB(129, 145, 146), WHITE, ButtonType::SFX_ON));
		buttons.push_back(Button(350, 250, 40, 32, L"S", !sfxEnabled ? PIXEL_GREEN : PIXEL_GRAY,
			!sfxEnabled ? RGB(26, 184, 93) : RGB(129, 145, 146), WHITE, ButtonType::SFX_OFF));

		// 难度按钮
		COLORREF easyColor = (difficulty == 0) ? PIXEL_GREEN : PIXEL_BLUE;
		COLORREF mediumColor = (difficulty == 1) ? PIXEL_GREEN : DARK_COLOR;
		COLORREF hardColor = (difficulty == 2) ? PIXEL_GREEN : PIXEL_RED;

		buttons.push_back(Button(250, 300, 80, 32, L"Easy", easyColor, RGB(32, 132, 199), WHITE, ButtonType::DIFFICULTY_EASY));
		buttons.push_back(Button(340, 300, 80, 32, L"Medium", mediumColor, RGB(50, 50, 50), WHITE, ButtonType::DIFFICULTY_MEDIUM));
		buttons.push_back(Button(430, 300, 80, 32, L"Hard", hardColor, RGB(211, 56, 40), WHITE, ButtonType::DIFFICULTY_HARD));

		// 保存按钮
		buttons.push_back(Button(300, 400, 200, 50, L"Save Settings", PRIMARY_COLOR, RGB(255, 87, 87), WHITE, ButtonType::SAVE_SETTINGS));
	}

	void initializeParticles() {
		particles.clear();
		COLORREF colors[] = { PIXEL_RED, PIXEL_GREEN, PIXEL_BLUE, PIXEL_YELLOW, PIXEL_PURPLE };

		for (int i = 0; i < 15; i++) {
			float x = (float)(rand() % WINDOW_WIDTH);
			float y = (float)(rand() % WINDOW_HEIGHT);
			COLORREF color = colors[rand() % 5];
			particles.push_back(Particle(x, y, color));
		}
	}

	void handleClick(int x, int y) {
		for (auto& button : buttons) {
			if (button.contains(x, y)) {
				button.isPressed = true;

				switch (button.type) {
				case ButtonType::START:
					startGameRequested = true;  // 设置标志而不弹出消息框
					break;
				case ButtonType::SETTINGS:
					showSettingsModal = true;
					initializeSettingsButtons();
					break;
				case ButtonType::LEADERBOARD:
					MessageBox(GetHWnd(), L"Leaderboard coming soon!", L"MiniBeanGo", MB_OK);
					break;
				case ButtonType::HELP:
					MessageBox(GetHWnd(), L"Use arrow keys to move, spacebar to jump! Collect coins and reach the goal!", L"Game Help", MB_OK);
					break;
				case ButtonType::CLOSE_SETTINGS:
					showSettingsModal = false;
					initializeMainButtons();
					break;
				case ButtonType::SAVE_SETTINGS:
					MessageBox(GetHWnd(), L"Settings saved!", L"MiniBeanGo", MB_OK);
					showSettingsModal = false;
					initializeMainButtons();
					break;
				case ButtonType::MUSIC_ON:
					musicEnabled = true;
					initializeSettingsButtons();
					break;
				case ButtonType::MUSIC_OFF:
					musicEnabled = false;
					initializeSettingsButtons();
					break;
				case ButtonType::SFX_ON:
					sfxEnabled = true;
					initializeSettingsButtons();
					break;
				case ButtonType::SFX_OFF:
					sfxEnabled = false;
					initializeSettingsButtons();
					break;
				case ButtonType::DIFFICULTY_EASY:
					difficulty = 0;
					initializeSettingsButtons();
					break;
				case ButtonType::DIFFICULTY_MEDIUM:
					difficulty = 1;
					initializeSettingsButtons();
					break;
				case ButtonType::DIFFICULTY_HARD:
					difficulty = 2;
					initializeSettingsButtons();
					break;
				}
				break;
			}
		}
	}

	void handleMouseMove(int x, int y) {
		for (auto& button : buttons) {
			button.isHovered = button.contains(x, y);
		}
	}

	void update() {
		clock_t currentTime = clock();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		// 更新英雄动画
		heroAnimTime += deltaTime;
		heroOffset = sin(heroAnimTime * 2) * 10;

		// 更新粒子
		for (auto& particle : particles) {
			particle.update(deltaTime);
		}

		// 移除死亡粒子
		particles.erase(std::remove_if(particles.begin(), particles.end(),
			[](const Particle& p) { return !p.isAlive(); }),
			particles.end());

		// 补充新粒子
		while (particles.size() < 15) {
			COLORREF colors[] = { PIXEL_RED, PIXEL_GREEN, PIXEL_BLUE, PIXEL_YELLOW, PIXEL_PURPLE };
			float x = (float)(rand() % WINDOW_WIDTH);
			float y = (float)(rand() % WINDOW_HEIGHT);
			COLORREF color = colors[rand() % 5];
			particles.push_back(Particle(x, y, color));
		}

		// 重置按钮按下状态
		for (auto& button : buttons) {
			button.isPressed = false;
		}
	}

	void drawPixelRect(int x, int y, int width, int height, COLORREF fillColor, COLORREF borderColor) {
		setfillcolor(fillColor);
		setlinecolor(borderColor);
		setlinestyle(PS_SOLID, 4);
		solidrectangle(x, y, x + width, y + height);
		rectangle(x, y, x + width, y + height);
	}

	void drawHero() {
		int currentY = heroY + (int)heroOffset;

		// 使用图片绘制英雄角色
		putimage(heroX, currentY, &heroImg);

		// 绘制装饰小方块
		drawPixelRect(heroX - 20, currentY - 20, 12, 12, PIXEL_YELLOW, DARK_COLOR);
		drawPixelRect(heroX + 108, currentY + 80, 8, 8, PIXEL_BLUE, DARK_COLOR);
	}

	void drawMainMenu() {
		// 背景渐变效果
		setfillcolor(RGB(240, 248, 255));
		solidrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		// 绘制背景粒子
		for (const auto& particle : particles) {
			particle.draw();
		}

		// 绘制装饰方块
		drawPixelRect(50, 50, 60, 60, PIXEL_BLUE, DARK_COLOR);
		drawPixelRect(690, 50, 50, 50, PIXEL_PURPLE, DARK_COLOR);

		// 使用与人物相同的偏移量绘制游戏标题
		settextcolor(PRIMARY_COLOR);
		settextstyle(100, 0, L"Arial");
		setbkmode(TRANSPARENT);

		std::wstring title = L"MINIBEANGO";
		int titleWidth = textwidth(title.c_str());
		int titleX = (WINDOW_WIDTH - titleWidth) / 2;
		outtextxy(titleX, 50 + (int)heroOffset, title.c_str());  // 添加偏移量

		// 使用与人物相同的偏移量绘制副标题
		settextcolor(RGB(100, 100, 100));
		settextstyle(16, 0, L"Arial");
		std::wstring subtitle = L"Pixel Platform Adventure Game";
		int subtitleWidth = textwidth(subtitle.c_str());
		int subtitleX = (WINDOW_WIDTH - subtitleWidth) / 2;
		outtextxy(subtitleX, 150 + (int)heroOffset, subtitle.c_str());  // 添加偏移量

		// 绘制英雄（已使用偏移量）
		drawHero();

		// 绘制按钮
		for (const auto& button : buttons) {
			button.draw();
		}

		// 绘制版权信息（保持静态）
		settextcolor(RGB(100, 100, 100));
		settextstyle(12, 0, L"Arial");
		std::wstring copyright = L"Copyright 2025 MiniBeanGo";
		int copyrightWidth = textwidth(copyright.c_str());
		int copyrightX = (WINDOW_WIDTH - copyrightWidth) / 2;
		outtextxy(copyrightX, 585, copyright.c_str());
	}

	void drawSettingsModal() {
		// 绘制半透明背景
		setfillcolor(RGB(0, 0, 0));
		setlinestyle(PS_SOLID, 0);
		solidrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		// 绘制模态框
		drawPixelRect(200, 125, 400, 350, LIGHT_COLOR, DARK_COLOR);

		// 绘制标题
		settextcolor(DARK_COLOR);
		settextstyle(24, 0, L"Arial");
		setbkmode(TRANSPARENT);
		outtextxy(220, 140, L"Settings");

		// 绘制标签
		settextstyle(14, 0, L"Arial");
		outtextxy(220, 190, L"Music:");
		outtextxy(220, 240, L"Sound:");
		outtextxy(220, 290, L"Difficulty:");

		// 绘制状态指示
		settextcolor(musicEnabled ? PIXEL_GREEN : PIXEL_RED);
		outtextxy(400, 200, musicEnabled ? L"ON" : L"OFF");

		settextcolor(sfxEnabled ? PIXEL_GREEN : PIXEL_RED);
		outtextxy(400, 250, sfxEnabled ? L"ON" : L"OFF");

		settextcolor(DARK_COLOR);
		std::wstring diffText = (difficulty == 0) ? L"Easy" : (difficulty == 1) ? L"Medium" : L"Hard";
		outtextxy(520, 300, diffText.c_str());

		// 绘制按钮
		for (const auto& button : buttons) {
			button.draw();
		}
	}

	void draw() {
		BeginBatchDraw();

		if (showSettingsModal) {
			drawSettingsModal();
		}
		else {
			drawMainMenu();
		}

		EndBatchDraw();
	}

	bool run() {  // 修改返回类型为bool
		// 初始化图形窗口
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
		SetWindowText(GetHWnd(), L"MiniBeanGo Game");

		srand((unsigned int)time(nullptr));

		ExMessage msg;
		bool running = true;

		while (running) {
			// 处理消息
			while (peekmessage(&msg)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN:
					handleClick(msg.x, msg.y);
					break;
				case WM_MOUSEMOVE:
					handleMouseMove(msg.x, msg.y);
					break;
				case WM_KEYDOWN:
					if (msg.vkcode == VK_ESCAPE && showSettingsModal) {
						showSettingsModal = false;
						initializeMainButtons();
					}
					break;
				case WM_CLOSE:
					running = false;
					break;
				}
			}

			// 检查是否请求开始游戏
			if (startGameRequested) {
				closegraph();
				return true;  // 返回true表示要开始游戏
			}

			update();
			draw();

			Sleep(16); // 约60FPS
		}

		closegraph();
		return false;  // 返回false表示用户关闭了窗口
	}
};
class GameOverUI {
private:
	vector<Button> buttons;
	vector<Particle> particles;
	bool exitRequested;

	// 动画变量
	clock_t lastTime;

	// 结束图片
	IMAGE* gameOverImg;  // 改为指针类型

public:
	GameOverUI() : exitRequested(false), gameOverImg(NULL) {
		lastTime = clock();

		// 修复备用图片创建逻辑
		if (_waccess(L"GameOverImg.png", 0) == 0) {
			gameOverImg = new IMAGE;
			loadimage(gameOverImg, L"GameOverImg.png", 200, 200);
		}
		else {
			// 创建空图像
			gameOverImg = new IMAGE(200, 200);

			// 设置背景
			DWORD* dst = GetImageBuffer(gameOverImg);
			for (int y = 0; y < 200; y++) {
				for (int x = 0; x < 200; x++) {
					dst[y * 200 + x] = RGB(100, 30, 30); // 深红色背景
				}
			}

			// 在图像上绘制叉叉
			for (int i = 0; i < 200; i++) {
				// 两条对角线
				if (i < 200) {
					dst[i * 200 + i] = RGB(255, 255, 255);
					dst[i * 200 + (199 - i)] = RGB(255, 255, 255);
				}
			}
		}

		initializeButtons();
		initializeParticles();
	}

	~GameOverUI() {
		if (gameOverImg) delete gameOverImg;
	}

	void initializeButtons() {
		buttons.clear();

		int buttonWidth = 200;
		int buttonHeight = 50;
		int startX = (WINDOW_WIDTH - buttonWidth) / 2;
		int startY = 400;

		buttons.push_back(Button(startX, startY, buttonWidth, buttonHeight,
			L"Exit Game", PRIMARY_COLOR, RGB(211, 56, 40), WHITE, ButtonType::EXIT));
	}

	void initializeParticles() {
		particles.clear();
		COLORREF colors[] = { PIXEL_RED, PIXEL_YELLOW, PIXEL_GRAY, ACCENT_COLOR };

		for (int i = 0; i < 15; i++) {
			float x = (float)(rand() % WINDOW_WIDTH);
			float y = (float)(rand() % WINDOW_HEIGHT);
			COLORREF color = colors[rand() % 4];
			particles.push_back(Particle(x, y, color));
		}
	}

	void handleClick(int x, int y) {
		for (auto& button : buttons) {
			if (button.contains(x, y)) {
				button.isPressed = true;

				switch (button.type) {
				case ButtonType::EXIT:
					exitRequested = true;
					break;
				}
				break;
			}
		}
	}

	void handleMouseMove(int x, int y) {
		for (auto& button : buttons) {
			button.isHovered = button.contains(x, y);
		}
	}

	void update() {
		clock_t currentTime = clock();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		// 更新粒子
		for (auto& particle : particles) {
			particle.update(deltaTime);
		}

		// 移除死亡粒子 - 修正使用方式
		particles.erase(std::remove_if(particles.begin(), particles.end(),
			[](const Particle& p) { return !p.isAlive(); }),
			particles.end());

		// 补充新粒子
		while (particles.size() < 15) {
			COLORREF colors[] = { PIXEL_RED, PIXEL_YELLOW, PIXEL_GRAY, ACCENT_COLOR };
			float x = (float)(rand() % WINDOW_WIDTH);
			float y = (float)(rand() % WINDOW_HEIGHT);
			COLORREF color = colors[rand() % 4];
			particles.push_back(Particle(x, y, color));
		}

		// 重置按钮按下状态
		for (auto& button : buttons) {
			button.isPressed = false;
		}
	}

	void drawPixelRect(int x, int y, int width, int height, COLORREF fillColor, COLORREF borderColor) {
		setfillcolor(fillColor);
		setlinecolor(borderColor);
		setlinestyle(PS_SOLID, 4);
		solidrectangle(x, y, x + width, y + height);
		rectangle(x, y, x + width, y + height);
	}

	void draw() {
		// 使用双缓冲防止闪烁
		BeginBatchDraw();

		// 深色渐变背景
		setfillcolor(RGB(173, 216, 230));
		solidrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		// 绘制背景粒子
		for (const auto& particle : particles) {
			particle.draw();
		}

		// 绘制装饰方块
		drawPixelRect(50, 50, 50, 50, PIXEL_GRAY, DARK_COLOR);
		drawPixelRect(700, 50, 50, 50, PIXEL_RED, DARK_COLOR);
		drawPixelRect(150, 500, 30, 30, ACCENT_COLOR, DARK_COLOR);
		drawPixelRect(650, 450, 40, 40, SECONDARY_COLOR, DARK_COLOR);

		// 游戏结束标题
		settextcolor(PRIMARY_COLOR);
		settextstyle(80, 0, L"Arial");
		setbkmode(TRANSPARENT);

		wstring title = L"GAME OVER";
		int titleWidth = textwidth(title.c_str());
		int titleX = (WINDOW_WIDTH - titleWidth) / 2;
		outtextxy(titleX, 70, title.c_str());

		// 副标题
		settextcolor(LIGHT_COLOR);
		settextstyle(20, 0, L"Arial");
		wstring subtitle = L"The adventure has ended...";
		int subtitleWidth = textwidth(subtitle.c_str());
		int subtitleX = (WINDOW_WIDTH - subtitleWidth) / 2;
		outtextxy(subtitleX, 160, subtitle.c_str());

		// 绘制结束图片
		if (gameOverImg) {
			int imgX = (WINDOW_WIDTH - 200) / 2;
			putimage(imgX, 200, gameOverImg);
		}

		// 绘制按钮
		for (const auto& button : buttons) {
			button.draw();
		}

		// 绘制版权信息
		settextcolor(RGB(100, 100, 100));
		settextstyle(12, 0, L"Arial");
		wstring copyright = L"Copyright 2025 MiniBeanGo";
		int copyrightWidth = textwidth(copyright.c_str());
		int copyrightX = (WINDOW_WIDTH - copyrightWidth) / 2;
		outtextxy(copyrightX, 585, copyright.c_str());

		// 结束双缓冲绘制
		EndBatchDraw();
	}

	bool run() {
		ExMessage msg;
		bool running = true;

		while (running && !exitRequested) {
			// 处理消息
			while (peekmessage(&msg)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN:
					handleClick(msg.x, msg.y);
					break;
				case WM_MOUSEMOVE:
					handleMouseMove(msg.x, msg.y);
					break;
				case WM_KEYDOWN:
					if (msg.vkcode == VK_ESCAPE) {
						exitRequested = true;
					}
					break;
				case WM_CLOSE:
					running = false;
					break;
				}
			}

			if (exitRequested) {
				return true;  // 退出请求
			}

			update();
			draw();

			Sleep(16); // 约60FPS
		}

		return false;
	}
};



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------


using namespace std;
#define  WIDTH 1000  
#define  HEIGHT 600
#define ACTIVE_RANGE 400 // 角色活动范围宽度
#define ACTIVE_RANGE_Y 300 // 角色活动范围高度
HealthHeart healthHeart(L"heart_full.png", L"heart_half.png", L"heart_empty.png", 10, 10);

// 一些全局变量
Player player;  // 定义玩家控制的游戏角色对象
Scene scene;  // 定义场景全局对象
Timer timer;  // 用于精确延时

void startup()  // 初始化
{
	sceneOffsetX = 0; // 场景偏移量归零
	sceneOffsetY = 0; // 场景偏移量归零
	srand(time(0)); // 初始化随机数种子
	scene.initialize();  // 场景初始化
	player.initialize(); // 玩家角色初始化
	healthHeart = HealthHeart(L"heart_full.png", L"heart_half.png", L"heart_empty.png", 10, 10);

	initgraph(WIDTH, HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制

	mciSendString(_T("open game_music.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL); // 循环播放
}

void show()  // 显示
{
	scene.draw(sceneOffsetX, player.y_bottom - HEIGHT / 2);   // 显示场景相关信息
	player.draw(sceneOffsetX); // 显示玩家相关信息
	healthHeart.draw(); // 显示血量条
	FlushBatchDraw(); // 批量绘制
	timer.Sleep(50); // 暂停若干毫秒
}

void updateWithoutInput() // 和输入无关的更新
{
	player.updateYcoordinate(scene); // 游戏角色y坐标是每帧自动更新的
}

void updateWithInput() // 和输入有关的更新
{
	player.standStill(); // 游戏角色默认为向左或向右静止站立

	if (_kbhit()) // 当按键时，切换角色显示图片，更改位置
	{
		if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))) // 同时按下A键和D键或左右方向键
		{
			;//角色不动，既不向左也不向右奔跑
		}
		else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))  // 按下D键或右方向键
		{
			float rightBound = (WIDTH + ACTIVE_RANGE) / 2;
            if (player.x_left - sceneOffsetX < rightBound) {
                player.runRight(scene);
            } else {
                sceneOffsetX += player.vx; // 场景左移
                player.runRight(scene); // 只切换动画，不移动角色
            }
		}
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))// 按下A键或左方向键
		{
			float leftBound = (WIDTH - ACTIVE_RANGE) / 2;
            if (player.x_left - sceneOffsetX > leftBound) {
                player.runLeft(scene);
            } else {
                sceneOffsetX -= player.vx; // 场景右移
                player.runLeft(scene); // 只切换动画，不移动角色
            }
		}
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))     // 按下W键或上方向键
		{
			player.beginJump(scene);
		}

	}
}

void loadImageEnlarged(IMAGE* img, LPCTSTR filename) {
	IMAGE temp;
	loadimage(&temp, filename);

	int orig_width = temp.getwidth();
	int orig_height = temp.getheight();
	int new_width = orig_width * 2;
	int new_height = orig_height * 2;

	img->Resize(new_width, new_height);

	// 获取设备上下文
	HDC tempDC = GetImageHDC(&temp);
	HDC imgDC = GetImageHDC(img);

	// 使用StretchBlt进行缩放，保持透明色
	StretchBlt(imgDC, 0, 0, new_width, new_height,
		tempDC, 0, 0, orig_width, orig_height, SRCCOPY);
}

int main() // 主函数
{
	MiniBeanGoUI game;
	if (game.run()) {
		bool b = true;
		startup();  	// 初始化
		while (1)       // 一直循环
		{
			show();  // 显示
			updateWithoutInput(); // 与输入无关的更新
			updateWithInput();    // 与输入有关的更新



			if (_kbhit() && GetAsyncKeyState('P') & 0x8000) // 检测 'p' 键是否按下
			{
				// 重新初始化游戏
				b = false;
				break;
			}
		}
		if (!b) {
			initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
			SetWindowText(GetHWnd(), L"MiniBeanGo - Game Over");

			// 设置显示模式为双缓冲
			setbkmode(TRANSPARENT);
			// 初始化随机数生成器
			srand((unsigned int)time(nullptr));

			GameOverUI gameOverUI;
			gameOverUI.run();

			closegraph();
		}
	}
	return 0;
}