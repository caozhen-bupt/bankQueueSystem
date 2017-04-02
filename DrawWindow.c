#include "egg.h" 
void door(void);
void DrawWindow()
{
	int i;
	EggStart(1100,700);
		
		
		
		
		
		
//曹桢的函数
		door();		
		
//窗口125*200
//休息按钮50*50
//客户按钮125*60 
//下班50*100 
	MovePen(0,700); 
	DrawBitmap("背景.bmp");
	MovePen(15,680);
	DrawBitmap("窗口1.bmp");

	MovePen(150,680);
	DrawBitmap("窗口2.bmp");

	MovePen(285,680);
	DrawBitmap("窗口3.bmp");

	MovePen(420,680);
	DrawBitmap("窗口4.bmp");

	MovePen(555,680);
	DrawBitmap("窗口5.bmp");

	MovePen(690,680);
	DrawBitmap("窗口6.bmp");

	MovePen(825,680);
	DrawBitmap("窗口7.bmp");

	MovePen(960,680);
	DrawBitmap("窗口8.bmp");
	for(i=0;i<8;i++)
	{
		MovePen(110+135*i,510);
		DrawBitmap("休息点击前.bmp");
	} 
	MovePen(620,420);
	DrawBitmap("取号机.bmp");
	MovePen(670,330);
	DrawBitmap("普通客户按钮点击前.bmp");
	MovePen(670,260);
	DrawString("排队人数：普通客户  0人，VIP客户 0人。"); 
	MovePen(845,330);
	DrawBitmap("VIP点击前.bmp");
	SetPenColor(DARK_BLUE);
	MovePen(670,240);
	DrawLine(300,0);
	DrawLine(0,-45);
	DrawLine(-300,0);
	DrawLine(0,45);
	SetPenColor(DARK_GREEN);
	MovePen(720,165);
	DrawLine(200,0);
	DrawLine(0,25);
	DrawLine(-200,0);
	DrawLine(0,-25);
	SetPenColor(BLACK);
	MovePen(670,150);
	DrawBitmap("1点击前.bmp");
	MovePen(780,150);
	DrawBitmap("2点击前.bmp");
	MovePen(890,150);
	DrawBitmap("3点击前.bmp");
	MovePen(670,120);
	DrawBitmap("4点击前.bmp"); 
	MovePen(780,120);
	DrawBitmap("5点击前.bmp");
	MovePen(890,120);
	DrawBitmap("6点击前.bmp");
	MovePen(670,90);
	DrawBitmap("7点击前.bmp");
	MovePen(780,90);
	DrawBitmap("8点击前.bmp");
	MovePen(890,90);
	DrawBitmap("9点击前.bmp");
	MovePen(670,60);
	DrawBitmap("重输点击前.bmp");
	MovePen(780,60);
	DrawBitmap("0点击前.bmp");
	MovePen(890,60);
	DrawBitmap("确定点击前.bmp");
	MovePen(1030,420);
	DrawBitmap("进.bmp");
	MovePen(1030,320);
	DrawBitmap("顺便服务点击前.bmp");
	MovePen(1070,320);
	DrawBitmap("定向服务点击前.bmp");
	MovePen(1030,200);
	DrawBitmap("出.bmp");
	MovePen(1030,120);
	DrawBitmap("退出点击前.bmp"); 
	MovePen(10,420);
	DrawBitmap("等候区.bmp");
	for(i=0;i<8;i++)
	{
		MovePen(15+i*135,620);
		DrawString("State:");
		MovePen(15+i*135,600);
		DrawString("ServNo:");
		MovePen(15+i*135,580);
		DrawString("ServeLen:");
	   MovePen(15+i*135,560);
	   DrawString("TotalSerLen:");
	   MovePen(15+i*135,540);
	  	DrawString("TotalRestLen:");
	}
	
		
}
