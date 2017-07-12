#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>
#include <time.h>

 void gotoxy(int a,int b);
 void  border ();
 void pattern(int x,int y);
 void clear_pattern(int x,int y);
int main()
{
    int i;
	int x=38;
	int y=10;
    char input;
    int isFire=0;
    int nx;
    int isKilled=1;

    srand( (unsigned)time( NULL ) );
    pattern(x,y);
    border ();
	while(1)
	{
	    //随机产生靶子
        if(isKilled==1){
            nx=rand();
            while(nx<35||nx>83)
            nx=rand();
            gotoxy(nx,1);
            printf("*");
            isKilled=0;
        }

	    //分别用ASDW键控制飞机方向
     	if(kbhit()){
            input=getch();
            switch (input){
                case 'a':
                    if(x!=35){
                        clear_pattern(x,y);
                        x--;
                        pattern(x,y);
                    }break;
                case 'd':
                    if(x!=83){
                        clear_pattern(x,y);
                        x++;
                        pattern(x,y);
                    }break;
                case 'w':
                    if(y!=1){
                        clear_pattern(x,y);
                        y--;
                        pattern(x,y);
                    }break;
                case 's':
                    if(y!=23){
                        clear_pattern(x,y);
                        y++;
                        pattern(x,y);
                    }break;
                case ' ':
                        {
                        isFire=1;
                        pattern(x,y);
                    }break;
            }
		}

        if((x==nx)&&(isFire==1))
                isKilled=1;


        if(isFire==1)
         {
             for(i=y-1;i>0;i--)
             {
                 gotoxy(x,i);
                 printf("|");
             }

            Sleep(200);
            for(i=y-1;i>0;i--)
             {
                 gotoxy(x,i);
                 printf(" ");
             }
             isFire=0;
         }
	}
  return 0;
 }


 void gotoxy(int a,int b)
{
    HANDLE hOut;
    COORD pos= {a,b};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}



//边界函数
void  border ()
{
    int i,j;
    for(i=32;i<=86;i++)
    {
      gotoxy(i,0);
      printf("*");
      gotoxy(i,27);
      printf("*");
    }

  for(j=1;j<=26;j++)
    {
      gotoxy(32,j);
      printf("*");
      gotoxy(86,j);
      printf("*");
    }
}

//飞机模型输出
void pattern(int x,int y)
{
    gotoxy(x,y);
    printf("*\n");
    gotoxy(x-1,y+1);
    printf("***\n");
    gotoxy(x-2,y+2);
    printf("*****\n");
    gotoxy(x-1,y+3);
    printf("* *\n");
}

//飞机模型消除
 void clear_pattern(int x,int y)
 {
    gotoxy(x,y);
    printf(" \n");
    gotoxy(x-1,y+1);
    printf("   \n");
    gotoxy(x-2,y+2);
    printf("     \n");
    gotoxy(x-1,y+3);
    printf("   \n");
 }




