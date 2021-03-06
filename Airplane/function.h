#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<pthread.h>
#include<windows.h>
#pragma comment(lib, "Winmm.lib")

// 全局变量
int position_x,position_y; // 飞机位置
int bullet_x,bullet_y; // 子弹位置
int enemy_x,enemy_y; // 敌机位置
int high,width; //  游戏画面尺寸
int score; // 得分
int speed; //敌机速度
int speed1; //敌机速度参照
int flag; //循环执行标示
int flag1; //循环标示参照
int life; //生命数
int box; //军火箱
int box_x,box_y; //军火箱的位置

void gotoxy(int x,int y) //类似于清屏函数，光标移动到原点位置进行重画
{
    HANDLE hOut;
    COORD pos={x,y};
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void GameStart() //游戏开始
{
    PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	draw();
	gotoxy(6,7); printf("Airplane Fire Game");
	gotoxy(11,9); printf("Welcome!");
	gotoxy(12,11); printf("Hello!");
	gotoxy(8,14); system("pause");
}

void GameOver() //游戏结束
{
    PlaySound(TEXT("defeat.wav"), NULL, SND_FILENAME | SND_ASYNC);
    system("cls");
	draw();
	gotoxy(9,8); printf("Game Over");
	gotoxy(10,10); printf("score:%d", score);
	gotoxy(2,12);
	printf("Press any key to continue.");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	getch();
	exit(0);
}

void startup() // 数据初始化
{
	high=20;
	width=30;
	position_x=high-4;
	position_y=width/2;
	bullet_x=-2;
	bullet_y=position_y;
	enemy_x=0;
	enemy_y=position_y;
	box_x=0;
	box_y=position_y+7;
	score=0;
	speed1=20;
    flag=0;
    flag1=0;
    life=5;
}

int draw() //画边框
{
    int i,j;
    for(i=0;i<=30;i++)
    {
      gotoxy(i,20);
      printf("#");
    }
    for(j=0;j<=19;j++)
    {
      gotoxy(30,j);
      printf("#");
    }
    return 0;
}

void show() // 显示画面
{
    int i,j;
    draw();
    dynamic_info();
	gotoxy(0,0);  // 光标移动到原点位置进行重画清屏
	if(box==0)//一次发射一发子弹
	{
       for (i=0;i<high;i++)
       {
          for (j=0;j<width;j++)
		    {
			if ((i==position_x-4) && (j==position_y)||(i==position_x-3) && (j==position_y-1))
				printf("*");  //   输出飞机*
			else if ((i==position_x-3) && (j==position_y)||(i==position_x-3) && (j==position_y+1))
                printf("*");  //   输出飞机*
            else if ((i==position_x-2) && (j==position_y-2)||(i==position_x-2) && (j==position_y-1))
                printf("*");  //   输出飞机*
            else if ((i==position_x-2) && (j==position_y)||(i==position_x-2) && (j==position_y+1))
                printf("*");  //   输出飞机*
            else if ((i==position_x-2) && (j==position_y+2)||(i==position_x-1) && (j==position_y-1)||(i==position_x-1) && (j==position_y+1))
                printf("*");  //   输出飞机*
			else if ((i==enemy_x) && (j==enemy_y))
				printf("*");  //   输出敌机*
            else if ((i==box_x) && (j==box_y))
				printf("@");  //   输出军火箱@
			else if ((i==bullet_x) && (j==bullet_y))
				printf("|");  //   输出子弹|
			else
				printf(" ");  //   输出空格
		    }
		    printf("\n");
	   }
	}
	else
    {
        for (i=0;i<high;i++)
       {
          for (j=0;j<width;j++)
		    {
			if ((i==position_x-4) && (j==position_y)||(i==position_x-3) && (j==position_y-1))
				printf("*");  //   输出飞机*
			else if ((i==position_x-3) && (j==position_y)||(i==position_x-3) && (j==position_y+1))
                printf("*");  //   输出飞机*
            else if ((i==position_x-2) && (j==position_y-2)||(i==position_x-2) && (j==position_y-1))
                printf("*");  //   输出飞机*
            else if ((i==position_x-2) && (j==position_y)||(i==position_x-2) && (j==position_y+1))
                printf("*");  //   输出飞机*
            else if ((i==position_x-2) && (j==position_y+2)||(i==position_x-1) && (j==position_y-1)||(i==position_x-1) && (j==position_y+1))
                printf("*");  //   输出飞机*
			else if ((i==enemy_x) && (j==enemy_y))
				printf("*");  //   输出敌机*
            else if ((i==box_x) && (j==box_y))
				printf("@");  //   输出军火箱@
			else if ((i==bullet_x) && (j==bullet_y)||(i==bullet_x+1) && (j==bullet_y-1)||(i==bullet_x+1) && (j==bullet_y+1))
				printf("|");  //   输出子弹|
			else
				printf(" ");  //   输出空格
		    }
		    printf("\n");
	   }
    }
}

void static_info() //静态信息，如游戏侧栏文字提示
{
	gotoxy(high+14,0); printf("%c %c %c %c 控制移动方向", 'w', 'a', 's', 'd');
	gotoxy(width+4,2); printf("按p键暂停");
	gotoxy(width+4,4); printf("F1加速,F2减速");
	gotoxy(width+4,6); printf("得分:");
	gotoxy(width+4,8); printf("生命:");
	gotoxy(width+4,10); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                        FOREGROUND_RED |FOREGROUND_INTENSITY); printf("F4:■");                   //红色
	gotoxy(width+4,12); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                        FOREGROUND_GREEN | FOREGROUND_RED |FOREGROUND_INTENSITY); printf("F5:■");//黄色
	gotoxy(width+4,14); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                        FOREGROUND_GREEN |FOREGROUND_INTENSITY); printf("F6:■");                 //绿色
	gotoxy(width+4,16); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                        FOREGROUND_BLUE | FOREGROUND_RED |FOREGROUND_INTENSITY); printf("F7:■"); //紫色
	gotoxy(width+4,18); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED |FOREGROUND_INTENSITY); printf("F8:■");//亮白色
	gotoxy(width+4,20); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                        FOREGROUND_GREEN | FOREGROUND_BLUE |FOREGROUND_RED);printf("F9:■");      //灰色
}

int dynamic_info() //动态信息，如游戏得分
{
	gotoxy(width+10,6); printf("%d", score);
	gotoxy(width+10,8); printf("%d", life);
}

void updateWithoutInput() // 与用户输入无关的更新
{
	if (bullet_x>-2)
		bullet_x--;
    if (box==0)
    {
       if ((bullet_x==box_x) && (bullet_y==box_y)) // 子弹击中火药箱
	   {
	      PlaySound(TEXT("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
	      box=1;
		  box_x=-1;           // 产生新的火药箱
		  box_y=rand()%width;
		  if(box_y==1)box_y++;
          if(box_y==29)box_y=box_y-3;
		  if(box_y==28)box_y--;
		  bullet_x=-3;          // 子弹无效
	   }
	   if ((bullet_x==enemy_x) && (bullet_y==enemy_y)) // 子弹击中敌机
	   {
	      PlaySound(TEXT("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		  score++;
		  dynamic_info();               // 分数加1
		  enemy_x=-1;           // 产生新的飞机
		  enemy_y=rand()%width;
		  if(enemy_y==1)enemy_y++;
          if(enemy_y==29)enemy_y=enemy_y-3;
		  if(enemy_y==28)enemy_y--;
		  bullet_x=-3;          // 子弹无效
	   }
    }
    else
    {
        if ((bullet_x==box_x) && (bullet_y==box_y)||(bullet_x+1==box_x) && (bullet_y-1==box_y)
           ||(bullet_x+1==box_x) && (bullet_y+1==box_y)) // 子弹击中火药箱
	    {
	      PlaySound(TEXT("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
	      box=1;
		  box_x=-1;           // 产生新的火药箱
		  box_y=rand()%width;
		  if(box_y==1)box_y++;
          if(box_y==29)box_y=box_y-3;
		  if(box_y==28)box_y--;
		  bullet_x=-3;          // 子弹无效
	    }
        if ((bullet_x==enemy_x) && (bullet_y==enemy_y)||(bullet_x+1==enemy_x) && (bullet_y-1==enemy_y)
           ||(bullet_x+1==enemy_x) && (bullet_y+1==enemy_y)) // 子弹击中敌机
	    {
	      PlaySound(TEXT("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		  score++;
		  dynamic_info();               // 分数加1
		  enemy_x=-1;           // 产生新的飞机
		  enemy_y=rand()%width;
		  if(enemy_y==1)enemy_y++;
          if(enemy_y==29)enemy_y=enemy_y-3;
		  if(enemy_y==28)enemy_y--;
		  bullet_x=-3;          // 子弹无效
	    }
    }
	if (enemy_x>high)   // 敌机跑出显示屏幕
	{
	    life--;
	    dynamic_info();
	    flag1++;
		enemy_x=-1;           // 产生新的飞机
		enemy_y=rand()%width;
		if(enemy_y==1)enemy_y++;
		if(enemy_y==29)enemy_y=enemy_y-3;
		if(enemy_y==28)enemy_y--;
	}
	if (box_x>high)   // 火药箱跑出显示屏幕
	{
		box_x=-1;           // 产生新的火药箱
		box_y=rand()%width;
		if(box_y==1)box_y++;
		if(box_y==29)box_y=box_y-3;
		if(box_y==28)box_y--;
	}
	if ((enemy_x==position_x-4)&&(enemy_y==position_y)||(enemy_x==position_x-3)&&(enemy_y==position_y-1)   //敌机碰撞飞机
        ||(enemy_x==position_x-3)&&(enemy_y==position_y+1)||(enemy_x==position_x-2)&&(enemy_y==position_y-2)
        ||(enemy_x==position_x-2)&&(enemy_y==position_y+2))
    {
        box=0;
        PlaySound(TEXT("strike.wav"), NULL, SND_FILENAME | SND_ASYNC);
        life--;
	    dynamic_info();
	    flag1++;
		enemy_x=-1;           // 产生新的飞机
		enemy_y=rand()%width;
		if(enemy_y==1)enemy_y++;
		if(enemy_y==29)enemy_y=enemy_y-3;
		if(enemy_y==28)enemy_y--;
    }

	// 用来控制敌机向下移动的速度。每隔几次循环，才移动一次敌机
	// 这样修改的话，用户按键交互速度还是保持很快，但我们NPC的移动显示可以降速
	static int speed = 0;
	    if (speed<speed1)
		    speed++;
	    if (speed==speed1)
	    {
		    enemy_x++;
		    box_x++;
		    speed = 0;
	    }
}

void updateWithInput() // 与用户输入有关的更新
{
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input=getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input=='a')
			{position_y--;
			  if(position_y==1)position_y++;
            }              // 位置左移
		if (input=='d')
			{position_y++;
			  if(position_y==28)position_y--;
			}              // 位置右移
		if (input=='w')
			{position_x--;
			  if(position_x==3)position_x++;
			}              // 位置上移
		if (input=='s')
			{position_x++;
			  if(position_x==21)position_x--;
			}              // 位置下移
        if (input=='p')while(getch()!='p');
        if (input==59 )
            {
                speed1--;
                if(speed1==6)speed1++;
            }
        if (input==60 )
            {
                speed1++;
                if(speed1==36)speed1=speed1--;
            }
        if (input==62 )
            {system("color 0C"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_INTENSITY); }
        if (input==63 )
            {system("color 0E"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED |
		FOREGROUND_INTENSITY); }
        if (input==64 )
            {system("color 0A"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN |
		FOREGROUND_INTENSITY); }
        if (input==65 )
            {system("color 0D"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED |
		FOREGROUND_INTENSITY); }
        if (input==66 )
            {system("color 0F"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE |
		FOREGROUND_RED | FOREGROUND_INTENSITY); }
        if (input==67 )
            {system("color 08"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE |
		FOREGROUND_RED);}
		if (input==' ')  // 发射子弹
		{
		    PlaySound(TEXT("fire(1).wav"), NULL, SND_FILENAME | SND_ASYNC);
			bullet_x=position_x-2;  // 发射子弹的初始位置在飞机的正上方
			bullet_y=position_y;
		}

	}
}

void sweep() //清光标
{
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);//获取光标信息
    cci.bVisible=FALSE;             //隐藏光标
    SetConsoleCursorInfo(hOut,&cci);//设置光标信息
}

void direction()
{
    FILE *fp;
    char a;
    if ((fp=fopen("Airplane fire文档说明.txt","r"))==NULL)
        {printf("Cannot open file!\n");exit(0);}
    while((a=fgetc(fp))!=EOF)
        putchar(a);
        fclose(fp);
        printf("\n");
    system("pause");
    system("cls");
}
