#include "function.h"


void main()
{
    direction();
    GameStart();
    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	startup();  // ���ݳ�ʼ��
	static_info();
    sweep();
	while (!flag) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		if(flag1==5)flag=!flag;
		updateWithInput();  // ���û������йصĸ���
	}
    GameOver();
}
