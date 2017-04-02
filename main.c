

#include "variable.h"

#include "common.h"
#include "mylib.h"
#include "egg.h" 
#include <string.h>

LISTNODEPTR headp;//普通客户队列头指针
LISTNODEPTR headpVIP;//VIP客户队列头指针
RESTLISTNODEPTR headpWinRest;//窗口申请休息队列头指针
int currentNor=0,currentVIP=0,currentRest=0;//目前排队的普通客户数，VIP客户数，排队休息的窗口数 
int totalNor=0,totalVIP=0;//一共来的普通客户和VIP客户 
int leaveNor=0,leaveVIP=0;//离开的客户 
int Qflag=0,printFlag,QueFlag=0;//下班的标志和队列和窗口状态有变化的标志 
int openTime=0;//开放第二个VIP窗口且队列人数小于2的时间 
int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag;//配置文件里的参数，后三个依次为周期性输出间隔，窗口等待客户的时间，策略 
long closeTime;//配置文件的参数，下班时间 
HANDLE hMutex;
extern char Wnorm[4],WVIP[3];

int main()
{
	WINDOW windows[8]; //窗口结构数组
	FILE *inputPtr,*output1Ptr,*output2Ptr,*sta,*client,*configPtr;//打开文件的地址 
	int time=0,KeyFlag;//计时，是否键盘输入 
	char choice;//用户输入的选择 
	int i,servCount=0,j;//现在服务客户的窗口数 
	REQLISTNODE theReqs[40];//数组
	hMutex=CreateMutex(NULL,FALSE,NULL);
	ARG parameters;//线程里需要传递的参数 
	HANDLE hThread;
	EVENT_TYPE ev;
	double X,Y;
	int VIPflag;
	char * Numbers;

		
		for(i=0;i<8;i++)//窗口状态初始化 
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
		/*以上都是初始化*/
	
		printf("                                Welcome!\n");
				
		while(1)//一开始的选择 
		{
			system("cls");
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			printf("Main:\n");
			printf("请输入您的选择:\n1 - 配置信息维护\n2 - VIP客户信息维护\n3 - 运行键盘输入版银行\n4 - 运行文件版银行\n5 - 运行动画版本银行\n");
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
				printf("请输入正确的指令。\n");
			}
		} 
		
		
		
		
		
		
//		door();
		
		
		/*以上是打开时的三种选项*/ 
		if((configPtr=fopen("Config.ini","r"))==NULL)
		{
			printf("The file could not be opened.\n");
		}
		else
		{
			fscanf(configPtr,"[MaxSeqLen]%d\n[MinSec]%d\n[MaxSec]%d\n[MinRestSec]%d\n[MaxRestSec]%d\n[VIPSERVLen]%d\n[OutputSec]%d\n[WaitTime]%d\n[strategyFlag]%d\n[closeTime]%ld"
			,&MaxSeqLen,&MinSec,&MaxSec,&MinRestSec,&MaxRestSec,&VIPSERVLen,&OutputSec,&WaitTime,&strategyFlag,&closeTime);
		}
	
	//以上是读取配置信息 
		

		
		
		
		
		if((inputPtr=fopen("input.txt","r"))==NULL||(output1Ptr=fopen("output1.txt","w"))==NULL
		||(output2Ptr=fopen("output2.txt","w"))==NULL||(sta=fopen("statistics.txt","w"))==NULL||(client=fopen("vip.dat","rb+"))==NULL)
		{
			printf("The file could not be opened.\n");
		}
		else
		{
			if(KeyFlag==1)//键盘输入 
			{
				printf("请输入您的选择:\nG - 普通客户到来\nV - VIP客户到来\nR - 申请窗口休息\nS - 转换策略\nQ - 下班\nX - VIP客户信息维护\n");
				parameters.client=client;
				parameters.timePtr=&time;
				parameters.windows=windows;
				for(i=0;i<7;i++)
				{
					if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
				}
				hThread=CreateThread(NULL,0,get_input,(LPVOID)&parameters,0,NULL);//线程 
				CloseHandle(hThread);
				while(servCount!=0||Qflag==0||headp!=NULL||headpVIP!=NULL)
				{
					
					printFlag=0;
					
					WaitForSingleObject(hMutex,INFINITE);
					if(time%OutputSec==0) system("cls");
					
					control2(windows);/*决定窗口是否休息*/ 
					control1(windows);/*根据策略分配顾客到空闲窗口接受服务*/
					state_trans(windows,0);/*计算此刻银行各窗口的状态 */
					print_message(windows,time,output1Ptr,output2Ptr,OutputSec,KeyFlag);/*输出此刻各窗口的状态，以及客户队列的状态*/
				
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
			else if(KeyFlag==0)//文件输入 
			{
				for(i=0;i<7;i++)
				{
					if(windows[i].state==serving||windows[i].state==waiting||windows[i].state==over) servCount++;
				}
				while(servCount!=0||Qflag==0||headp!=NULL||headpVIP!=NULL)
				{
					printFlag=0;
					get_Finput(inputPtr,time,windows,client,theReqs);/*获取客户到来、窗口休息等事件*/
					control2(windows);/*决定窗口是否休息*/ 
					control1(windows);/*根据策略分配顾客到空闲窗口接受服务*/
					state_trans(windows,0);/*计算此刻银行各窗口的状态 */
					print_message(windows,time,output1Ptr,output2Ptr,OutputSec,KeyFlag);/*输出此刻各窗口的状态，以及客户队列的状态*/
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
							control2(windows);/*决定窗口是否休息*/ 
							control1(windows);/*根据策略分配顾客到空闲窗口接受服务*/
							state_trans(windows,1);/*计算此刻银行各窗口的状态 */
//							init();
							PrintWin(windows,time);
							PrintQue();
							print_message(windows,time,output1Ptr,output2Ptr,OutputSec,2);/*输出此刻各窗口的状态，以及客户队列的状态*/
							if(time==closeTime) Qflag=1;
							MovePen(670,260);
							DrawString("排队人数：普通客户");
							TransWaitNPeo();
							DrawString(Wnorm);
							DrawString("人，VIP客户");
							TransWaitVPeo();
							DrawString(WVIP);
							DrawString("人。");
							MovePen(1030,420);
							DrawBitmap("进.bmp");
							MovePen(1030,200);
							DrawBitmap("出.bmp");
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
										DrawBitmap("普通客户按钮点击后.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(670,330);
											DrawBitmap("普通客户按钮点击前.bmp");
										}
										
										Numbers=AddNorm();
										QueFlag=1;
										MovePen(672,235);
										DrawString("                                           ");
										MovePen(672,215);
										DrawString("                                       ");
										MovePen(672,215);
										DrawString("您的号码是:");
										DrawString(Numbers); 
									}
									else if((X >= 845 && X <= 970) && (Y >= 270 && Y <= 330))
									{
										MovePen(845,330);
										DrawBitmap("VIP点击后.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(845,330);
											DrawBitmap("VIP点击前.bmp");
										}
										
										VIPflag=0;
										MovePen(672,235);
										DrawString("                                           ");
										MovePen(672,235);
										DrawString("请输入您的5位ID：");
										
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
											DrawString("您的号码是:");
											DrawString(Numbers); 
										}
										else
										{
											Numbers=AddNorm();
											QueFlag=1;
											MovePen(672,235);
											DrawString("                                            ");
											MovePen(672,235);
											DrawString("三次输入错误，为您分配普通号码。");
											MovePen(672,215);
											DrawString("                                       ");
											MovePen(672,215);
											DrawString("您的号码是:");
											DrawString(Numbers); 
										}
					
									}
									else if((X >= 1030 && X <= 1060) && (Y >= 220 && Y <= 320))
									{
										MovePen(1030,320);
										DrawBitmap("顺便服务点击后.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(1030,320);
											DrawBitmap("顺便服务点击前.bmp");
										}
										
										strategyFlag=2;
									}
									else if((X >= 1070 && X <= 1100) && (Y >= 220 && Y <= 320)) 
									{
										MovePen(1070,320);
										DrawBitmap("定向服务点击后.bmp");
										if(WaitForEvent() == KEYUP)
										{
											MovePen(1070,320);
											DrawBitmap("定向服务点击前.bmp");
										}
										
										strategyFlag=1;
									}
									else if((X >= 1030 && X <= 1080) && (Y >= 20 && Y <= 120))
									{
										MovePen(1030,120);
										DrawBitmap("退出点击后.bmp"); 
										if(WaitForEvent() == KEYUP)
										{
											MovePen(1030,120);
											DrawBitmap("退出点击前.bmp");
										}
										 
										Qflag=1;
										MovePen(800,20);
										DrawString("正在下班，您不能添加任何事件。");
									}
									for(j=0;j<8;j++)
									{
										if((X >= (110+135*j) && X <= (140+135*j)) && (Y >= 470 && Y <= 510))
										{
											MovePen(110+135*j,510);
											DrawBitmap("休息点击后.bmp");
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
								DrawBitmap("普通客户按钮点击前.bmp");
							}
							else if((X >= 845 && X <= 970) && (Y >= 270 && Y <= 330))
							{
								MovePen(845,330);
								DrawBitmap("VIP点击前.bmp");
							}
							else if((X >= 1030 && X <= 1060) && (Y >= 220 && Y <= 320))
							{
								MovePen(1030,320);
								DrawBitmap("顺便服务点击前.bmp");
							}
							else if((X >= 1070 && X <= 1100) && (Y >= 220 && Y <= 320)) 
							{
								MovePen(1070,320);
								DrawBitmap("定向服务点击前.bmp");
							}
							else if((X >= 1030 && X <= 1080) && (Y >= 20 && Y <= 120))
							{
								MovePen(1030,120);
								DrawBitmap("退出点击前.bmp"); 
							}
							for(j=0;j<8;j++)
							{
								if((X >= (110+135*j) && X <= (140+135*j)) && (Y >= 480 && Y <= 510))
								{
									
									MovePen(110+135*j,510);
									DrawBitmap("休息点击前.bmp");
										
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
					DrawBitmap("小背景.bmp"); 
					MovePen(500,700);
					DrawString("已下班。");
					WaitForExit();
				}
			}

			 

		}
	
			
	
			printStatistics(windows,sta);/*输出统计信息*/
			fclose(inputPtr);
			fclose(output1Ptr);
			fclose(output2Ptr);
			fclose(sta);
			fclose(client); 
			printf("窗口状态已周期性地输出到output1.txt。窗口状态在有变化时已输出到output2.txt。统计数据已输出到statistics.txt。\n");

	return 0;
}
