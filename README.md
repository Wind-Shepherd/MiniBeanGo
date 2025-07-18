# MiniBeanGo
A little alien named “MiniBean” crash-landed on a strange planet and needs to find the 3 scattered engine parts in order to go home.
一、游戏简介
MiniBeanGo 是一款充满趣味的冒险游戏，玩家将操控游戏角色在充满挑战的场景中冒险，收集星星和钥匙，避开危险，最终到达目的地。游戏拥有丰富的场景元素和多种游戏设定，能为玩家带来精彩的游戏体验。

二、游戏设定
1. 角色设定
角色状态：游戏角色具有多种状态，包括站立（左右）、跳跃（左右）、攀爬、受伤（左右）和死亡（左右）。不同状态下角色的动作和形象会有所不同。
健康状态：角色有三种健康状态，分别是满血（full_health）、半血（half_health）和无血（no_health）。健康状态会影响角色的生存能力。
无敌状态：角色在受到攻击后会进入无敌状态，持续一段时间，在此期间角色不会受到伤害。
2. 场景设定
背景：游戏场景拥有美丽的背景图像，为游戏增添了氛围。
元素：场景中包含多种元素，如陆地（Land）、梯子（Ladder）、地刺（GroundThorn）、星星（Star）、钥匙（Key）、杆（Rod）和门（Gate）等。
陆地：角色可以在陆地上行走和站立。
梯子：角色可以通过梯子进行攀爬。
地刺：地刺会对角色造成伤害。
星星：收集星星可以获得一定的奖励或成就。
钥匙：用于打开对应的门。
杆：可能具有特殊的功能，如触发机关等。
门：需要使用钥匙才能打开，通过门可以进入新的区域。
3. 难度设定
游戏提供三种难度级别，分别是简单（Easy）、中等（Medium）和困难（Hard）。不同难度下，场景中的危险元素数量和角色受到的伤害程度会有所不同。
4. 音乐和音效
音乐：游戏支持音乐开关，玩家可以根据自己的喜好选择是否开启背景音乐。
音效：同样支持音效开关，音效可以增强游戏的真实感和趣味性。

三、游戏玩法
1. 移动
左右移动：使用左右箭头键控制角色向左或向右移动。
跳跃：按下空格键使角色跳跃。
攀爬：当角色靠近梯子时，按上下箭头键可以进行攀爬。
2. 收集
星星：在场景中寻找星星并收集，收集星星可以获得一定的奖励。
钥匙：找到钥匙并收集，钥匙用于打开对应的门。
3. 避免危险
地刺：避免碰到地刺，否则角色会受到伤害并进入受伤状态。
其他危险：根据不同难度，场景中可能会有其他危险元素，玩家需要小心应对。
4. 通关目标
使用收集到的钥匙打开门，到达场景的指定目标区域，即可通关游戏。

四、使用方法
1. 环境要求
本游戏基于图形库进行开发，需要确保你的开发环境支持相关图形库（如代码中使用的 graphics.h 等）。
游戏代码使用 C++ 编写，需要有相应的 C++ 编译器。
2. 编译和运行
将所有相关代码文件（如 main.cpp、Player.h、Scene.h 等）放置在同一目录下。
确保所有所需的图片文件（如 StartPlayer.png、Standright.png、landscape1.png 等）存在于正确的路径中。
使用 C++ 编译器编译 main.cpp 文件。例如，在 Visual Studio 中创建一个新的 C++ 项目，将代码文件添加到项目中，然后进行编译和运行。
3. 游戏操作
启动游戏：编译运行程序后，会显示游戏的主界面。
主界面操作：
开始游戏：点击 “Start Game” 按钮开始游戏。
设置：点击 “Settings” 按钮可以进入设置界面，在设置界面中可以进行音乐、音效开关的设置，以及选择游戏难度。
排行榜：点击 “Leaderboard” 按钮会弹出提示框，目前排行榜功能暂未开放。
帮助：点击 “Help” 按钮会弹出帮助信息，显示游戏的基本操作方法。
游戏中操作：在游戏过程中，使用左右箭头键控制角色移动，空格键进行跳跃，靠近梯子时使用上下箭头键攀爬。

五、注意事项
确保所有图片文件的路径和名称与代码中引用的一致，否则可能会导致图片加载失败。
在不同的开发环境中，可能需要对代码进行适当的调整和配置，以确保游戏能够正常运行。
希望你能在 MiniBeanGo 游戏中度过愉快的时光！如果有任何问题或建议，欢迎随时反馈。
