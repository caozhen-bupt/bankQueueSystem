#include"egg.h"
#include<windows.h>
void door(void)//���� 
{
	HEGG door[2];//���

	double time;//������ʱ 
	double X,Y;
	SetAutoUpdate(0);//�ý��治�Զ����� 
	
	DrawBitmap("10.bmp");//�򿪱���ͼƬ
	MovePen(1000,680);
	DrawBitmap("�������ǰ.bmp");
	door[0]=LayEgg();//�µ� 
	DrawBitmap("left.bmp");//���ϴ�ͼƬ��Ϊ���� 
	OffsetEgg(174,-134);//�ƶ�����λ�� 
	door[1]=LayEgg();//�µ� 
	DrawBitmap("right.bmp");//���ϴ�ͼƬ��Ϊ���� 
	OffsetEgg(546,-134);//�ƶ�����λ�� 
	
	Update();//���½��� 
	time=0;//��ʱ��ʼ��ʱ 
	while(WaitFor(100)){//��0.1s    ʵ�ֿ��Ź��� 
		SetActiveEgg(door[0]);//���û�� 
		OffsetEgg(-10,0);//�ƶ�����λ�� 
		SetActiveEgg(door[1]);//���û�� 
		OffsetEgg(10,0);//�ƶ�����λ��   
		Update();//���½��� 
		time=time+0.1;// ʱ��+0.1s 
		if(WaitForEvent()==KEYDOWN)
		{
			if(GetStruckKey() == VK_LBUTTON)
			{
				X = GetMouseX();
				Y = GetMouseY();
				if((X >= 1000 && X <= 1100) && (Y >= 580 && Y <= 680))
				{
					MovePen(1000,680);
					DrawBitmap("���������.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(1000,680);
						DrawBitmap("�������ǰ.bmp");
					}
					break;
				}
			}
		}
		if(time>=6){//ʱ����ڵ���6sʱ��������ϣ�����ѭ�� 
			break;
		}
	}
	SetAutoUpdate(1);//�ý����Զ����� 
	SetActiveEgg(door[0]);//���û�� 
	EatEgg();//�Ե� 
	SetActiveEgg(door[1]);//���û�� 
	EatEgg();//�Ե� 
}
