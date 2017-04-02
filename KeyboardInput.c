#include "variable.h"

#include <string.h>
#include "common.h"


void mainTain(FILE * );
void addServList(int,WINDOW*,int);

DWORD WINAPI get_input(LPVOID parameters)
{
	argPtr parameter=(argPtr)parameters;
	int i,flag,j; 
	static int reqCount;
	char req,ID[20],check;
	CLIENT currentCli={" "," ",0},blankCli={" "," ",0};
	int event; 
	FILE* maintain=parameter->client;
	while(1)
	{
		if(Qflag==0)
		{
			req=getch();
			WaitForSingleObject(hMutex,INFINITE);

			if(req=='G'||req=='V'||req=='R'||req=='Q'||req=='S'||req=='X')
			{
				if(req=='X')//VIP�ͻ���Ϣά�� 
				{
					fseek(parameter->client,0,SEEK_SET);
					mainTain(parameter->client);
				} 
				else 
				{
					if(req=='G')//��ͨ�ͻ� 
					{
						event=9;
					} 
					else if(req=='Q') //�°�ָ�� 
					{
						event=0;
					}
					else if(req=='V')//VIP�ͻ� 
					{
						flag=0;
						for(i=0;i<3;i++)
						{
							printf("����������ID:(����5λ����)\n");
							fflush(stdin); 
							j=0;
							while((ID[j]=getchar())>='0'&&ID[j]<='9')
							{
								j++;
							}
							ID[j]='\0';
							if(j==5)
							{
								fseek(parameter->client,0,SEEK_SET);
								maintain=parameter->client;
								while(!feof(maintain))
								{
								
									fread(&currentCli,sizeof(CLIENT),1,maintain);
									if(strcmp(currentCli.ID,ID)==0)
									{
										flag=1;
										printf("%s,����VIP�ͻ�.\n",currentCli.name);
										printf("��������: %s ����ID: %s �����˻�: %.2lf\n",currentCli.name,currentCli.ID,currentCli.account);
										printf("\n");
										break;
									}
									currentCli=blankCli;
								}
							}
							if(flag==1) 
							{
								event=10;
								break;
							}
							
							else
							{
								if(j>5)
								{
									printf("����������%dλ.",j-5);
								} 
								else
								{
									printf("����������%dλ.",5-j);
								}
								if(i==0)
								{
									printf("�Ҳ���IDΪ%s�Ŀͻ�.\n",ID);
									printf("����������.\n");
									printf("�㻹�����λ���.\n\n");
								}
								else if(i==1)
								{
									printf("�Ҳ���IDΪ%s�Ŀͻ�.\n",ID);
									printf("����������.\n");
									printf("�㻹��һ�λ���.\n\n");
								}
								else
								{
									printf("�Ҳ���IDΪ%s�Ŀͻ�.\n",ID);;
									printf("Ϊ��������ͨ����.\n\n");
									event=9;
								}
								
							}
		
						}
			
					} 
					else if(req=='R') //��Ϣ 
					{
						printf("������Ҫ��Ϣ�Ĵ���(from 1 to 8):\n");
						fflush(stdin);
						event=getchar();
						
						if(event>0&&event<9&&(check=getchar())=='\n')
						{
							printf("����%c������Ϣ.\n",event);
							event-='0'; 
						}
						else printf("��������ȷ������.\n");
					}
					else if(req=='S')//����ת�� 
					{
						fflush(stdin);
						printf("��ѡ�����(1 - ������� 2 - ˳�����)");
						event=getchar()-'0';
						event+=10;
					}
				}
				addServList(event,parameter->windows,*(parameter->timePtr));
			}
			else if(req!='\n')
			{
				printf("��������ȷ��ָ��.\n");
			}
			
			ReleaseMutex(hMutex);
		
		}
		else return;
	}
	

}


void addServList(int event,WINDOW windows[],int time) 
{
	int i;
	LISTNODEPTR norPtr,VIPPtr;
	static LISTNODEPTR preNorPtr=NULL,preVIPPtr=NULL;//previous
	static RESTLISTNODEPTR preRestPtr=NULL;

	RESTLISTNODEPTR restPtr=NULL; 


		if(event==0)
		{
			Qflag=1;
			return;
		} 
		else if(event==9)
		{
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
			}
			
		}
		else if(event==10)
		{
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
			}
			
		}
		else if(event<=8&&event>=1)//��Ϣ���� 
		{

			restPtr=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
			while(restPtr==NULL) restPtr=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
			if(restPtr!=NULL)
			{
				restPtr->winNum=event;
				restPtr->totalTimeCount=windows[event-1].totalRestLen;
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
		else if(event==11) strategyFlag=1;
		else if(event==12) strategyFlag=2;
}

