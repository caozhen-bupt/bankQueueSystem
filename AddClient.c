#include "variable.h"

#include <string.h>
#include "common.h"
#include "egg.h"
extern void transfer(int ,char[]); 
char Wnorm[4];
char WVIP[3];
void TransWaitNPeo(void)
{
	
	if(currentNor/100==0)
	{
		Wnorm[0]=' ';
		if((currentNor%100)/10==0)
		{
			Wnorm[1]=' ';
			Wnorm[2]=currentNor%10+'0';
		}
		else
		{
			Wnorm[1]=(currentNor%100)/10+'0';
			Wnorm[2]=currentNor%10+'0';
		}
	} 
	else
	{
		Wnorm[0]=currentNor/100+'0';
		Wnorm[1]=(currentNor%100)/10+'0';
		Wnorm[2]=currentNor%10+'0';
	}
	Wnorm[3]='\0';
	
}

void TransWaitVPeo(void)
{
	//char VIP[3];
	if(currentVIP/10==0)
	{
		WVIP[0]=' ';
		WVIP[1]=currentVIP%10+'0';
	}
	else
	{
		WVIP[0]=currentVIP/10+'0';
		WVIP[1]=currentVIP%10+'0';
	}
	WVIP[2]='\0';
}

char* AddNorm(void)
{
	LISTNODEPTR norPtr;
	static LISTNODEPTR preNorPtr=NULL;//previous
	printFlag=1; 
	totalNor++;
	currentNor++;//�˿���+1 
	norPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	while(norPtr==NULL) norPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	if(norPtr!=NULL)
	{
		norPtr->CliNum[0]=totalNor/100+48;//����Ÿ�ֵ 
		norPtr->CliNum[1]=(totalNor/10)%10+48;
		norPtr->CliNum[2]=totalNor%10+48;
		norPtr->CliNum[3]='\0';
		if(headp==NULL)
		{
			headp=norPtr;
			norPtr->nextPtr=NULL;
			preNorPtr=norPtr;
		}
		else
		{
			preNorPtr->nextPtr=norPtr;
			norPtr->nextPtr=NULL;
			preNorPtr=norPtr;
		}
		MovePen(1030,420);
		DrawBitmap("4.bmp");
		return norPtr->CliNum;
	} 
}


char* AddVIP(void)
{
		

	LISTNODEPTR VIPPtr;
	static LISTNODEPTR preVIPPtr=NULL;//previous
	printFlag=1;
	totalVIP++;
	currentVIP++;//��ǰVIP�˿���+1 
	VIPPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	while(VIPPtr==NULL) VIPPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	if(VIPPtr!=NULL)
	{
		VIPPtr->CliNum[0]='V';//����Ÿ�ֵ 
		VIPPtr->CliNum[1]=(totalVIP/10)+48;
		VIPPtr->CliNum[2]=totalVIP%10+48;
		VIPPtr->CliNum[3]='\0';
		if(headpVIP==NULL)
		{
			headpVIP=VIPPtr;
			VIPPtr->nextPtr=NULL;
			preVIPPtr=VIPPtr;
		}
		else
		{
			preVIPPtr->nextPtr=VIPPtr;
			VIPPtr->nextPtr=NULL;
			preVIPPtr=VIPPtr;
		}
		MovePen(1030,420);
		DrawBitmap("5.bmp");
		return VIPPtr->CliNum;
	}

}

void AddRest(int num,WINDOW windows[],int time)
{
	RESTLISTNODEPTR restPtr=NULL;
	static RESTLISTNODEPTR preRestPtr=NULL; 
	restPtr=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
	while(restPtr==NULL) restPtr=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
	if(restPtr!=NULL)
	{
		restPtr->winNum=num+1;
		restPtr->totalTimeCount=windows[num].totalRestLen;
		restPtr->applyTime=time;
		if(headpWinRest==NULL)
		{
			headpWinRest=restPtr;
			restPtr->nextPtr=NULL;
			preRestPtr=restPtr;
			}
		else
		{
			preRestPtr->nextPtr=restPtr;
			restPtr->nextPtr=NULL;
			preRestPtr=restPtr;
		}
		
	}
}


int isVIP(FILE * filePtr)
{
	FILE* maintain;
	int cntForInput,i,j;
	double X,Y; 
	char strForInput[20],flag;				//���ڻ����û�����
	CLIENT currentCli={" "," ",0},blankCli={" "," ",0};


	for(i=0;i<3;i++)
	{
		cntForInput=0;
		for(j=0;j<20;j++)
		{
			strForInput[j]='\0';
		}
		while(1)
		{
			while(!(WaitForEvent() == KEYDOWN)) {}
			if((flag=GetStruckKey()) == VK_LBUTTON)
			{
				X = GetMouseX();
				Y = GetMouseY();
				if((X >= 670 && X <= 730) && (Y >= 40 && Y <= 60))
				{
	
					MovePen(670,60);
					DrawBitmap("��������.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(670,60);
						DrawBitmap("������ǰ.bmp");
					}
					MovePen(720,190);
					DrawBitmap("���.bmp");
					SetPenColor(DARK_GREEN);
					MovePen(720,165);
					DrawLine(200,0);
					DrawLine(0,25);
					DrawLine(-200,0);
					DrawLine(0,-25);
					SetPenColor(BLACK);
					cntForInput=0;
					for(j=0;j<20;j++)
					{
						strForInput[j]='\0';
					}
					continue; 
				}
				else if	((X >= 890 && X <= 950) && (Y >= 40 && Y <= 60)) 
				{
	
					MovePen(890,60);
					DrawBitmap("ȷ�������.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(890,60);
						DrawBitmap("ȷ�����ǰ.bmp");
					}
					MovePen(720,190);
					DrawBitmap("���.bmp");
					SetPenColor(DARK_GREEN);
					MovePen(720,165);
					DrawLine(200,0);
					DrawLine(0,25);
					DrawLine(-200,0);
					DrawLine(0,-25);
					SetPenColor(BLACK);
					
					break;
				}
				else if((X >= 780 && X <= 840) && (Y >= 40 && Y <= 60))
				{
					strForInput[cntForInput]='0';
					MovePen(780,60);
					DrawBitmap("0�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(780,60);
						DrawBitmap("0���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 670 && X <= 730) && (Y >= 130 && Y <= 150))
				{
					strForInput[cntForInput]='1';
					MovePen(670,150);
					DrawBitmap("1�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(670,150);
						DrawBitmap("1���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 670 && X <= 730) && (Y >= 100 && Y <= 120))
				{
					strForInput[cntForInput]='4';
					MovePen(670,120);
					DrawBitmap("4�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(670,120);
						DrawBitmap("4���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 670 && X <= 730) && (Y >= 70 && Y <= 90))
				{
					strForInput[cntForInput]='7';
					MovePen(670,90);
					DrawBitmap("7�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(670,90);
						DrawBitmap("7���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 780 && X <= 840) && (Y >= 70 && Y <= 90))
				{
					strForInput[cntForInput]='8';
					MovePen(780,90);
					DrawBitmap("8�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(780,90);
						DrawBitmap("8���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 890 && X <= 950) && (Y >= 70 && Y <= 90))
				{
					strForInput[cntForInput]='9';
					MovePen(890,90);
					DrawBitmap("9�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(890,90);
						DrawBitmap("9���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 890 && X <= 950) && (Y >= 100 && Y <= 120)) 
				{
					strForInput[cntForInput]='6';
					MovePen(890,120);
					DrawBitmap("6�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(890,120);
						DrawBitmap("6���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 890 && X <= 950) && (Y >= 130 && Y <= 150)) 
				{
					strForInput[cntForInput]='3';
					MovePen(890,150);
					DrawBitmap("3�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(890,150);
						DrawBitmap("3���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 780 && X <= 840) && (Y >= 130 && Y <= 150))
				{
					strForInput[cntForInput]='2';
					MovePen(780,150);
					DrawBitmap("2�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(780,150);
						DrawBitmap("2���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
				else if((X >= 780 && X <= 840) && (Y >= 100 && Y <= 120))
				{
					strForInput[cntForInput]='5';
					MovePen(780,120);
					DrawBitmap("5�����.bmp");
					if(WaitForEvent() == KEYUP)
					{
						MovePen(780,120);
						DrawBitmap("5���ǰ.bmp");
					}
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++;
				}
			}
			else
			{
				if(flag == VK_BACK )
				{
					MovePen(720,190);
					DrawBitmap("���.bmp");
					SetPenColor(DARK_GREEN);
					MovePen(720,165);
					DrawLine(200,0);
					DrawLine(0,25);
					DrawLine(-200,0);
					DrawLine(0,-25);
					SetPenColor(BLACK);
					cntForInput=0;
					for(j=0;j<20;j++)
					{
						strForInput[j]='\0';
					}
					continue; 
				}
				else if(flag == VK_RETURN)
				{
					MovePen(720,190);
					DrawBitmap("���.bmp");
					SetPenColor(DARK_GREEN);
					MovePen(720,165);
					DrawLine(200,0);
					DrawLine(0,25);
					DrawLine(-200,0);
					DrawLine(0,-25);
					SetPenColor(BLACK);
					
					break;
				}
				else
				{
					strForInput[cntForInput]=flag;
					MovePen(720+(200-GetStringWidth(strForInput))/2, 183);
					DrawString(strForInput);
					cntForInput++; 
				}
			}
			
		} 
			//�������ж� 
		if(cntForInput==5)
		{
			fseek(filePtr,0,SEEK_SET);
			maintain=filePtr;
			while(!feof(maintain))
			{
				fread(&currentCli,sizeof(CLIENT),1,maintain);
				if(strcmp(currentCli.ID,strForInput)==0)
				{

					MovePen(672,235);
					DrawString("                                                                  ");
					MovePen(672,235);
					DrawString(currentCli.name);
					DrawString(",you are VIP client.");
					return 1;
				}
				currentCli=blankCli;
			}
		}
		char ch[4];
		if(cntForInput>5)
		{
			MovePen(672,215);
			DrawString("��������");
			transfer((cntForInput-5),ch);
			DrawString(ch);
			DrawString("λ��");
		} 
		else if(cntForInput<5) 
		{
			MovePen(672,215);
			DrawString("��������");
			transfer((5-cntForInput),ch);
			DrawString(ch);
			DrawString("λ��");
		}
		else if(cntForInput==5) 
		{
			MovePen(672,215);
			DrawString("                               ");
		}
		switch (i)
		{
		
			case 0:
//				MovePen(672,235);

				MovePen(672,235);
				DrawString("�ͻ������ڣ����������루2�λ��ᣩ��");
				break;
			case 1:
//				MovePen(672,235);
	
				MovePen(672,235);
				DrawString("�ͻ������ڣ����������루1�λ��ᣩ��");
				break;
			case 2:
				return 0;
			}
		

			
	}
	
}
