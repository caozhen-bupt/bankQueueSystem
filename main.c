

#include "variable.h"

#include "common.h"
#include "mylib.h"
#include "egg.h" 
#include <string.h>

LISTNODEPTR headp;//��ͨ�ͻ�����ͷָ��
LISTNODEPTR headpVIP;//VIP�ͻ�����ͷָ��
RESTLISTNODEPTR headpWinRest;//����������Ϣ����ͷָ��
int currentNor=0,currentVIP=0,currentRest=0;//Ŀǰ�Ŷӵ���ͨ�ͻ�����VIP�ͻ������Ŷ���Ϣ�Ĵ����� 
int totalNor=0,totalVIP=0;//һ��������ͨ�ͻ���VIP�ͻ� 
int leaveNor=0,leaveVIP=0;//�뿪�Ŀͻ� 
int Qflag=0,printFlag,QueFlag=0;//�°�ı�־�Ͷ��кʹ���״̬�б仯�ı�־ 
int openTime=0;//���ŵڶ���VIP�����Ҷ�������С��2��ʱ�� 
int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag;//�����ļ���Ĳ���������������Ϊ�����������������ڵȴ��ͻ���ʱ�䣬���� 
long closeTime;//�����ļ��Ĳ������°�ʱ�� 
HANDLE hMutex;
extern char Wnorm[4],WVIP[3];

int main()
{
	WINDOW windows[8]; //���ڽṹ����
	FILE *inputPtr,*output1Ptr,*output2Ptr,*sta,*client,*configPtr;//���ļ��ĵ�ַ 
	int time=0,KeyFlag;//��ʱ���Ƿ�������� 
	char choice;//�û������ѡ�� 
	int i,servCount=0,j;//���ڷ���ͻ��Ĵ����� 
	REQLISTNODE theReqs[40];//����
	hMutex=CreateMutex(NULL,FALSE,NULL);
	ARG parameters;//�߳�����Ҫ���ݵĲ��� 
	HANDLE hThread;
	EVENT_TYPE ev;
	double X,Y;
	int VIPflag;
	char * Numbers;

		
		for(i=0;i<8;i++)//����״̬��ʼ�� 
		{
			windows[i].winNum=i+1;
			strcpy(windows[i].CliNum,"   ");
			windows[i].nowtime=0;
			windows[i].orderTime=0;
			windows[i].restflag=0;
			windows[i].custCount=0;
			windows[i].totalSerLen=0;
			windows[i].totalRestLen=0;
			windows[i].satGoodCount=0;
			windows[i].satNormCount=0;
			windows[i].satBadCount=0;
			if((i>=0&&i<=2)||i==6) windows[i].state=idle;
			else windows[i].state=close;
		}
		time=0;
		Qflag=0,printFlag=0; 
		currentNor=0,currentVIP=0,currentRest=0;
		totalNor=0,totalVIP=0;
		leaveNor=0,leaveVIP=0;
		openTime=0;
		headp=NULL;
		headpVIP=NULL;
		headpWinRest=NULL;
		/*���϶��ǳ�ʼ��*/
	
		printf("                                Welcome!\n");
				
		while(1)//һ��ʼ��ѡ�� 
		{
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			printf("Main:\n");
			printf("����������ѡ��:\n1 - ������Ϣά��\n2 - VIP�ͻ���Ϣά��\n3 - ���м������������\n4 - �����ļ�������\n5 - ���ж����汾����\n");
			fflush(stdin);
			choice=getch();
			if(choice=='3')
			{
				system("cls");
				KeyFlag=1;
				break;
			}
			else if(choice=='4')
			{
				system("cls");
				KeyFlag=0;
				break;
			}
			else if(choice=='2')
			{
				if((client=fopen("vip.dat","rb+"))==NULL)
				{
					printf("The file could not be opened.\n");
				}
				else
				{
					system("cls");
					mainTain(client);
					fclose(client);
				}
			}
			else if(choice=='1')
			{
				if((configPtr=fopen("Config.ini","r+"))==NULL)
				{
					printf("The file could not be opened.\n");
				}
				else
				{
					system("cls");
					Configuration(configPtr); 
					fclose(configPtr);
				}
			}
			else if(choice=='5')
			{
				system("cls");
				KeyFlag=2;
				break;
			} 
			else
			{
				printf("��������ȷ��ָ�\n");
			}
		} 
		
		
		
		
		
		
//		door();
		
		
		/*�����Ǵ�ʱ������ѡ��*/ 
		if((configPtr=fopen("Config.ini","r"))==NULL)
		{
			printf("The file could not be opened.\n");
		}
		else
		{
			fscanf(configPtr,"[MaxSeqLen]%d\n[MinSec]%d\n[MaxSec]%d\n[MinRestSec]%d\n[MaxRestSec]%d\n[VIPSERVLen]%d\n[OutputSec]%d\n[WaitTime]%d\n[strategyFlag]%d\n[closeTime]%ld"
			,&MaxSeqLen,&MinSec,&MaxSec,&MinRestSec,&MaxRestSec,&VIPSERVLen,&OutputSec,&WaitTime,&strategyFlag,&closeTime);
		}
	
	//�����Ƕ�ȡ������Ϣ 
		

		
		
		
		
		if((inputPtr=fopen("input.txt","r"))==NULL||(output1Ptr=fopen("output1.txt","w"))==NULL
		||(output2Ptr=fopen("output2.txt","w"))==NULL||(sta=fopen("statistics.txt","w"))==NULL||(client=fopen("vip.dat","rb+"))==NULL)
		{
			printf("The file could not be opened.\n");
		}
		else
		{
			if(KeyFlag==1)//�������� 
			{
				printf("����������ѡ��:\nG - ��ͨ�ͻ�����\nV - VIP�ͻ�����\nR - ���봰����Ϣ\nS - ת������\nQ - �°�\nX - VIP�ͻ���Ϣά��\n");
				parameters.client=client;
				parameters.timePtr=&time;
				parameters.windows=windows;
				for(i=0;i<7;i++)
				{
					if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
				}
				hThread=CreateThread(NULL,0,get_input,(LPVOID)&parameters,0,NULL);//�߳� 
				CloseHandle(hThread);
				while(servCount!=0||Qflag==0||headp!=NULL||headpVIP!=NULL)
				{
					
					printFlag=0;
					
					WaitForSingleObject(hMutex,INFINITE);
					if(time%OutputSec==0) system("cls");
					
					control2(windows);/*���������Ƿ���Ϣ*/ 
					control1(windows);/*���ݲ��Է���˿͵����д��ڽ��ܷ���*/
					state_trans(windows,0);/*����˿����и����ڵ�״̬ */
					print_message(windows,time,output1Ptr,output2Ptr,OutputSec,KeyFlag);/*����˿̸����ڵ�״̬���Լ��ͻ����е�״̬*/
				
					if(time==closeTime) Qflag=1;
					time++; 
					
					ReleaseMutex(hMutex);
			//		if(time%OutputSec==0) system("cls");
					Sleep(1000);

					servCount=0;
					for(i=0;i<8;i++)
					{
						if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
					}
				}
			}
			else if(KeyFlag==0)//�ļ����� 
			{
				for(i=0;i<7;i++)
				{
					if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
				}
				while(servCount!=0||Qflag==0||headp!=NULL||headpVIP!=NULL)
				{
					printFlag=0;
					get_Finput(inputPtr,time,windows,client,theReqs);/*��ȡ�ͻ�������������Ϣ���¼�*/
					control2(windows);/*���������Ƿ���Ϣ*/ 
					control1(windows);/*���ݲ��Է���˿͵����д��ڽ��ܷ���*/
					state_trans(windows,0);/*����˿����и����ڵ�״̬ */
					print_message(windows,time,output1Ptr,output2Ptr,OutputSec,KeyFlag);/*����˿̸����ڵ�״̬���Լ��ͻ����е�״̬*/
					if(time==closeTime) Qflag=1;
					time++; 
					servCount=0;
					for(i=0;i<8;i++)
					{
						if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
					}
				}
			}
			
			
			
			
			else if(KeyFlag==2)
			{
				DrawWindow();
				for(i=0;i<7;i++)
				{
					if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
				}
				StartTimer(1000);
				
				while((ev=WaitForEvent())!=EXIT&&(Qflag==0||headp!=NULL||headpVIP!=NULL||servCount!=0))
				{
					printFlag=0;
					switch (ev)
					{
						case TIMER:
							control2(windows);/*���������Ƿ���Ϣ*/ 
							control1(windows);/*���ݲ��Է���˿͵����д��ڽ��ܷ���*/
							state_trans(windows,1);/*����˿����и����ڵ�״̬ */
//							init();
							PrintWin(windows,time);
							PrintQue();
							print_message(windows,time,output1Ptr,output2Ptr,OutputSec,2);/*����˿̸����ڵ�״̬���Լ��ͻ����е�״̬*/
							if(time==closeTime) Qflag=1;
							MovePen(670,260);
							DrawString("�Ŷ���������ͨ�ͻ�");
							TransWaitNPeo();
							DrawString(Wnorm);
							DrawString("�ˣ�VIP�ͻ�");
							TransWaitVPeo();
							DrawString(WVIP);
							DrawString("�ˡ�");
							MovePen(1030,420);
							DrawBitmap("��.bmp");
							MovePen(1030,200);
							DrawBitmap("��.bmp");
							time++; 
							QueFlag=0;
							servCount=0;
							for(i=0;i<7;i++)
							{
								if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
							}
							break;
						case KEYDOWN:
							if(Qflag==0)
							{
								if(GetStruckKey() == VK_LBUTTON)
								{
									X = GetMouseX();
									Y = GetMouseY();
									if((X >= 670 && X <= 795) && (Y >= 270 && Y <= 330))
									{
										MovePen(670,330);
										DrawBitmap("��ͨ�ͻ���ť�����.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(670,330);
											DrawBitmap("��ͨ�ͻ���ť���ǰ.bmp");
										}
										
										Numbers=AddNorm();
										QueFlag=1;
										MovePen(672,235);
										DrawString("                                           ");
										MovePen(672,215);
										DrawString("                                       ");
										MovePen(672,215);
										DrawString("���ĺ�����:");
										DrawString(Numbers); 
									}
									else if((X >= 845 && X <= 970) && (Y >= 270 && Y <= 330))
									{
										MovePen(845,330);
										DrawBitmap("VIP�����.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(845,330);
											DrawBitmap("VIP���ǰ.bmp");
										}
										
										VIPflag=0;
										MovePen(672,235);
										DrawString("                                           ");
										MovePen(672,235);
										DrawString("����������5λID��");
										
										MovePen(672,215);
										DrawString("                                           ");
										VIPflag=isVIP(client);
										QueFlag=1;
										if(VIPflag==1)
										{
											Numbers=AddVIP();
											MovePen(672,235);
											MovePen(672,215);
											DrawString("                                           ");
											MovePen(672,215);
											DrawString("���ĺ�����:");
											DrawString(Numbers); 
										}
										else
										{
											Numbers=AddNorm();
											QueFlag=1;
											MovePen(672,235);
											DrawString("                                            ");
											MovePen(672,235);
											DrawString("�����������Ϊ��������ͨ���롣");
											MovePen(672,215);
											DrawString("                                       ");
											MovePen(672,215);
											DrawString("���ĺ�����:");
											DrawString(Numbers); 
										}
					
									}
									else if((X >= 1030 && X <= 1060) && (Y >= 220 && Y <= 320))
									{
										MovePen(1030,320);
										DrawBitmap("˳���������.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(1030,320);
											DrawBitmap("˳�������ǰ.bmp");
										}
										
										strategyFlag=2;
									}
									else if((X >= 1070 && X <= 1100) && (Y >= 220 && Y <= 320)) 
									{
										MovePen(1070,320);
										DrawBitmap("�����������.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(1070,320);
											DrawBitmap("���������ǰ.bmp");
										}
										
										strategyFlag=1;
									}
									else if((X >= 1030 && X <= 1080) && (Y >= 20 && Y <= 120))
									{
										MovePen(1030,120);
										DrawBitmap("�˳������.bmp"); 
										if(WaitForEvent() == KEYUP)
										{
											MovePen(1030,120);
											DrawBitmap("�˳����ǰ.bmp");
										}
										 
										Qflag=1;
										MovePen(800,20);
										DrawString("�����°࣬����������κ��¼���");
									}
									for(j=0;j<8;j++)
									{
										if((X >= (110+135*j) && X <= (140+135*j)) && (Y >= 470 && Y <= 510))
										{
											MovePen(110+135*j,510);
											DrawBitmap("��Ϣ�����.bmp");
											AddRest(j,windows,time);
										}
									}
		
	
								}
							}
							
							break;
						case KEYUP:
							X = GetMouseX();
							Y = GetMouseY();
							if((X >= 670 && X <= 795) && (Y >= 270 && Y <= 330))
							{
								MovePen(670,330);
								DrawBitmap("��ͨ�ͻ���ť���ǰ.bmp");
							}
							else if((X >= 845 && X <= 970) && (Y >= 270 && Y <= 330))
							{
								MovePen(845,330);
								DrawBitmap("VIP���ǰ.bmp");
							}
							else if((X >= 1030 && X <= 1060) && (Y >= 220 && Y <= 320))
							{
								MovePen(1030,320);
								DrawBitmap("˳�������ǰ.bmp");
							}
							else if((X >= 1070 && X <= 1100) && (Y >= 220 && Y <= 320)) 
							{
								MovePen(1070,320);
								DrawBitmap("���������ǰ.bmp");
							}
							else if((X >= 1030 && X <= 1080) && (Y >= 20 && Y <= 120))
							{
								MovePen(1030,120);
								DrawBitmap("�˳����ǰ.bmp"); 
							}
							for(j=0;j<8;j++)
							{
								if((X >= (110+135*j) && X <= (140+135*j)) && (Y >= 480 && Y <= 510))
								{
									
									MovePen(110+135*j,510);
									DrawBitmap("��Ϣ���ǰ.bmp");
										
								}
							}
							break;
	
					} 
						
							
				}
				
				StopTimer();
				MovePen(672,235);
				DrawString("                                                  ");
				MovePen(672,215);
				DrawString("                                                  ");
				if(Qflag==1&&ev!=EXIT)
				{
					MovePen(0,700);
					DrawBitmap("С����.bmp"); 
					MovePen(500,700);
					DrawString("���°ࡣ");
					WaitForExit();
				}
			}

			 

		}
	
			
	
			printStatistics(windows,sta);/*���ͳ����Ϣ*/
			fclose(inputPtr);
			fclose(output1Ptr);
			fclose(output2Ptr);
			fclose(sta);
			fclose(client); 
			printf("����״̬�������Ե������output1.txt������״̬���б仯ʱ�������output2.txt��ͳ�������������statistics.txt��\n");

	return 0;
}
