#include "egg.h" 
void door(void);
void DrawWindow()
{
	int i;
	EggStart(1100,700);
		
		
		
		
		
		
//����ĺ���
		door();		
		
//����125*200
//��Ϣ��ť50*50
//�ͻ���ť125*60 
//�°�50*100 
	MovePen(0,700); 
	DrawBitmap("����.bmp");
	MovePen(15,680);
	DrawBitmap("����1.bmp");

	MovePen(150,680);
	DrawBitmap("����2.bmp");

	MovePen(285,680);
	DrawBitmap("����3.bmp");

	MovePen(420,680);
	DrawBitmap("����4.bmp");

	MovePen(555,680);
	DrawBitmap("����5.bmp");

	MovePen(690,680);
	DrawBitmap("����6.bmp");

	MovePen(825,680);
	DrawBitmap("����7.bmp");

	MovePen(960,680);
	DrawBitmap("����8.bmp");
	for(i=0;i<8;i++)
	{
		MovePen(110+135*i,510);
		DrawBitmap("��Ϣ���ǰ.bmp");
	} 
	MovePen(620,420);
	DrawBitmap("ȡ�Ż�.bmp");
	MovePen(670,330);
	DrawBitmap("��ͨ�ͻ���ť���ǰ.bmp");
	MovePen(670,260);
	DrawString("�Ŷ���������ͨ�ͻ�  0�ˣ�VIP�ͻ� 0�ˡ�"); 
	MovePen(845,330);
	DrawBitmap("VIP���ǰ.bmp");
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
	DrawBitmap("1���ǰ.bmp");
	MovePen(780,150);
	DrawBitmap("2���ǰ.bmp");
	MovePen(890,150);
	DrawBitmap("3���ǰ.bmp");
	MovePen(670,120);
	DrawBitmap("4���ǰ.bmp"); 
	MovePen(780,120);
	DrawBitmap("5���ǰ.bmp");
	MovePen(890,120);
	DrawBitmap("6���ǰ.bmp");
	MovePen(670,90);
	DrawBitmap("7���ǰ.bmp");
	MovePen(780,90);
	DrawBitmap("8���ǰ.bmp");
	MovePen(890,90);
	DrawBitmap("9���ǰ.bmp");
	MovePen(670,60);
	DrawBitmap("������ǰ.bmp");
	MovePen(780,60);
	DrawBitmap("0���ǰ.bmp");
	MovePen(890,60);
	DrawBitmap("ȷ�����ǰ.bmp");
	MovePen(1030,420);
	DrawBitmap("��.bmp");
	MovePen(1030,320);
	DrawBitmap("˳�������ǰ.bmp");
	MovePen(1070,320);
	DrawBitmap("���������ǰ.bmp");
	MovePen(1030,200);
	DrawBitmap("��.bmp");
	MovePen(1030,120);
	DrawBitmap("�˳����ǰ.bmp"); 
	MovePen(10,420);
	DrawBitmap("�Ⱥ���.bmp");
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
