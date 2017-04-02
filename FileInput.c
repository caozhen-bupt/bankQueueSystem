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
		if(theReqs[0].time==time)//�����ǰʱ��Ͷ�����ʱ��һ�� 
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
	fscanf(filePtr,"T=%d,EVENT=",&(theReqs[0].time));//��ȡ��ǰʱ��
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
					printf("����������%dλ.",j-5);
				} 
				else
				{
					printf("����������%dλ.",5-j);
				}
				printf("�Ҳ����ÿͻ�.\n");
				printf("Ϊ��������ͨ����.\n");
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
						printf("%s,����VIP�ͻ�.\n",currentCli.name);
						printf("��������: %s ����ID: %s �����˻�: %.2lf\n",currentCli.name,currentCli.ID,currentCli.account);
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
					printf("�Ҳ���IDΪ%s�Ŀͻ�.\n",ID);
					printf("Ϊ��������ͨ����.\n\n");
					theReqs[0].REQ=9;
					i++;
				}
			}
			
		} 
		else if(req=='R') 
		{
			fscanf(filePtr,"%d",&theReqs->REQ);
			i++;//������һ��
		}
		else if(req=='S')
		{
			fscanf(filePtr,"%d",&theReqs[i].REQ);
			theReqs[i].REQ+=10;//������״̬���� 
			i++;
	 	} 

	
 	while((check=fgetc(filePtr))!='\n'&&!feof(filePtr))//ÿһ����Ϣ֮���|���Լ���Ƿ񵽽�β 
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
						printf("����������%dλ.",j-5);
					} 
					else
					{
						printf("����������%dλ.",5-j);
					}
					printf("�Ҳ���IDΪ%s�Ŀͻ�.\n",ID);
					printf("Ϊ��������ͨ����.\n");;
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
							printf("%s,����VIP�ͻ�.\n",currentCli.name);
							printf("��������: %s ����ID: %s �����˻�: %.2lf\n",currentCli.name,currentCli.ID,currentCli.account);
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
						printf("�Ҳ���IDΪ%s�Ŀͻ�.\n",ID);
						printf("Ϊ��������ͨ����.\n\n");
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
				theReqs[i].REQ+=10;//������״̬���� 
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
			currentNor++;//�˿���+1 
			norPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
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
		else if(theReqs[i].REQ==10)
		{
			printFlag=1;
			totalVIP++;
			currentVIP++;//��ǰVIP�˿���+1 
			VIPPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
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

