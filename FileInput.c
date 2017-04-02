#include "variable.h"
#include <string.h>
#include "common.h"

//enum STATE{start,q1}; 
void FaddServList(REQLISTNODE[],int,WINDOW[],int) ;
int get_fileInput(REQLISTNODE[],FILE *,FILE*);
void get_Finput(FILE* inputPtr,int time,WINDOW windows[],FILE*maintain,REQLISTNODE theReqs[])
{
	
	int i; 
	static int reqCount;
	if(time==0)
	{
		fseek(inputPtr,0,SEEK_SET);
		reqCount=get_fileInput(theReqs,inputPtr,maintain);
	} 
	if(Qflag==0||feof(inputPtr))
	{
		if(theReqs[0].time==time)//如果当前时间和读到的时间一致 
		{
			FaddServList(theReqs,reqCount,windows,time);
			if(Qflag==0) reqCount=get_fileInput(theReqs,inputPtr,maintain);
		}
    	
	}
	else return;

}

int get_fileInput(REQLISTNODE theReqs[],FILE * filePtr,FILE* maintain)
{
	int i=0,j,flag;
	char req,check,ID[20];
	FILE* maintain1=maintain;
	CLIENT currentCli={" "," ",0},blankCli={" "," ",0};
	fscanf(filePtr,"T=%d,EVENT=",&(theReqs[0].time));//读取当前时间
	req=fgetc(filePtr);

		if(req=='G')
		{
			theReqs[0].REQ=9;
			i++;
		} 
		else if(req=='Q') 
		{
			theReqs[0].REQ=0;
			i++;
		}
		else if(req=='V')
		{
			flag=0;
			fseek(filePtr,2*sizeof(char),SEEK_CUR);
			j=0;
			while((ID[j]=fgetc(filePtr))>='0'&&ID[j]<='9')
			{
				j++;
			}
			ID[j]='\0';
			fseek(filePtr,(-1)*sizeof(char),SEEK_CUR);
			if(j!=5)
			{
				if(j>5)
				{
					printf("您多输入了%d位.",j-5);
				} 
				else
				{
					printf("您少输入了%d位.",5-j);
				}
				printf("找不到该客户.\n");
				printf("为您分配普通号码.\n");
			}
			else
			{
				fseek(maintain,0,SEEK_SET);
				maintain1=maintain;
				while(!feof(maintain1))
				{
					fread(&currentCli,sizeof(CLIENT),1,maintain1);
					if(strcmp(currentCli.ID,ID)==0)
					{
						flag=1;
						printf("%s,您是VIP客户.\n",currentCli.name);
						printf("您的姓名: %s 您的ID: %s 您的账户: %.2lf\n",currentCli.name,currentCli.ID,currentCli.account);
						printf("\n");
						break;
					}
					currentCli=blankCli;
				}
				if(flag==1) 
				{
					theReqs[0].REQ=10;
					i++;
				}
				else if(flag==0)
				{
					printf("找不到ID为%s的客户.\n",ID);
					printf("为您分配普通号码.\n\n");
					theReqs[0].REQ=9;
					i++;
				}
			}
			
		} 
		else if(req=='R') 
		{
			fscanf(filePtr,"%d",&theReqs->REQ);
			i++;//读到第一个
		}
		else if(req=='S')
		{
			fscanf(filePtr,"%d",&theReqs[i].REQ);
			theReqs[i].REQ+=10;//和其他状态区分 
			i++;
	 	} 

	
 	while((check=fgetc(filePtr))!='\n'&&!feof(filePtr))//每一条信息之间的|可以检测是否到结尾 
	{
		req=fgetc(filePtr);


			if(req=='G') 
			{
				theReqs[i].REQ=9;
				i++;
			}
			else if(req=='Q') 
			{
				theReqs[i].REQ=0;
				i++;
			}
			else if(req=='V')
			{
				flag=0;
				fseek(filePtr,2*sizeof(char),SEEK_CUR);
				j=0;
				while((ID[j]=fgetc(filePtr))>='0'&&ID[j]<='9')
				{
					j++;
				}
				ID[j]='\0';
				fseek(filePtr,(-1)*sizeof(char),SEEK_CUR);
				if(j!=5)
				{
					if(j>5)
					{
						printf("您多输入了%d位.",j-5);
					} 
					else
					{
						printf("您少输入了%d位.",5-j);
					}
					printf("找不到ID为%s的客户.\n",ID);
					printf("为您分配普通号码.\n");;
				}
				else
				{
					fseek(maintain,0,SEEK_SET);
					maintain1=maintain;
					while(!feof(maintain1))
					{
						fread(&currentCli,sizeof(CLIENT),1,maintain1);
						if(strcmp(currentCli.ID,ID)==0)
						{
							flag=1;
							printf("%s,您是VIP客户.\n",currentCli.name);
							printf("您的姓名: %s 您的ID: %s 您的账户: %.2lf\n",currentCli.name,currentCli.ID,currentCli.account);
							printf("\n");
							break;
						}
						currentCli=blankCli;
					}
					if(flag==1) 
					{
						theReqs[i].REQ=10;
						i++;
					}
					else if(flag==0)
					{
						printf("找不到ID为%s的客户.\n",ID);
						printf("为您分配普通号码.\n\n");
						theReqs[i].REQ=9;
						i++;
					}
				}
			} 
			else if(req=='R') 
			{
				fscanf(filePtr,"%d",&theReqs[i].REQ);
				i++;
			}
			else if(req=='S')
			{
				fscanf(filePtr,"%d",&theReqs[i].REQ);
				theReqs[i].REQ+=10;//和其他状态区分 
				i++;
			} 
	}
	return i;
	
}

void FaddServList(REQLISTNODE theReqs[],int reqCount,WINDOW windows[],int time) 
{
	int i,restcount=0;
	LISTNODEPTR norPtr,VIPPtr;
	static LISTNODEPTR preNorPtr=NULL,preVIPPtr=NULL;//previous
	static RESTLISTNODEPTR preRestPtr=NULL;

	RESTLISTNODEPTR restPtr=NULL;

	for(i=0;i<reqCount;i++)
	{
		if(theReqs[i].REQ==0)
		{
			Qflag=1;
			return;
		} 
		else if(theReqs[i].REQ==9)
		{
			printFlag=1;
			totalNor++;
			currentNor++;//顾客数+1 
			norPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
			if(norPtr!=NULL)
			{
				norPtr->CliNum[0]=totalNor/100+48;//将编号赋值 
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
		else if(theReqs[i].REQ==10)
		{
			printFlag=1;
			totalVIP++;
			currentVIP++;//当前VIP顾客数+1 
			VIPPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
			if(VIPPtr!=NULL)
			{
				VIPPtr->CliNum[0]='V';//将编号赋值 
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
		else if(theReqs[i].REQ<=8&&theReqs[i].REQ>=1)
		{
			restcount++;
			restPtr=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
			if(restPtr!=NULL)
			{
				restPtr->winNum=theReqs[i].REQ;
				restPtr->totalTimeCount=windows[(theReqs[i].REQ)-1].totalRestLen;
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
		else if(theReqs[i].REQ==11) strategyFlag=1;
		else if(theReqs[i].REQ==12) strategyFlag=2;
		else printf("Please input correct order.\n");
	}

		
}

