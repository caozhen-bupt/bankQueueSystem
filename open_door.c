#include"egg.h"
#include<windows.h>
void door(void)//开门 
{
	HEGG door[2];//句柄

	double time;//用作计时 
	double X,Y;
	SetAutoUpdate(0);//让界面不自动更新 
	
	DrawBitmap("10.bmp");//打开背景图片
	MovePen(1000,680);
	DrawBitmap("跳过点击前.bmp");
	door[0]=LayEgg();//下蛋 
	DrawBitmap("left.bmp");//蛋上打开图片，为左门 
	OffsetEgg(174,-134);//移动蛋的位置 
	door[1]=LayEgg();//下蛋 
	DrawBitmap("right.bmp");//蛋上打开图片，为右门 
	OffsetEgg(546,-134);//移动蛋的位置 
	
	Update();//更新界面 
	time=0;//此时开始计时 
	while(WaitFor(100)){//等0.1s    实现开门功能 
		SetActiveEgg(door[0]);//设置活动蛋 
		OffsetEgg(-10,0);//移动蛋的位置 
		SetActiveEgg(door[1]);//设置活动蛋 
		OffsetEgg(10,0);//移动蛋的位置   
		Update();//更新界面 
		time=time+0.1;// 时间+0.1s 
		if(WaitForEvent()==KEYDOWN)
		{
			if(GetStruckKey() == VK_LBUTTON)
			{
				X = GetMouseX();
				Y = GetMouseY();
				if((X >= 1000 && X <= 1100) && (Y >= 580 && Y <= 680))
				{
					MovePen(1000,680);
					DrawBitmap("跳过点击后.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(1000,680);
						DrawBitmap("跳过点击前.bmp");
					}
					break;
				}
			}
		}
		if(time>=6){//时间大于等于6s时，开门完毕，跳出循环 
			break;
		}
	}
	SetAutoUpdate(1);//让界面自动更新 
	SetActiveEgg(door[0]);//设置活动蛋 
	EatEgg();//吃蛋 
	SetActiveEgg(door[1]);//设置活动蛋 
	EatEgg();//吃蛋 
}
