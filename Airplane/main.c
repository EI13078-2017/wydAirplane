#include "function.h"


void main()
{
    direction();
    GameStart();
    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	startup();  // 数据初始化
	static_info();
    sweep();
	while (!flag) //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		if(flag1==5)flag=!flag;
		updateWithInput();  // 与用户输入有关的更新
	}
    GameOver();
}
