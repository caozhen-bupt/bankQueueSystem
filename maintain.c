#include"variable.h"
#include"common.h"
#include<string.h>

void PrintInfo(FILE*);
int enterChoice(FILE*);                                   /*����ѡ��ĺ���*/ 
void writeIn(FILE *);                                    /*д��ѧ����Ϣ*/ 

void change(FILE*);                                      /*�޸�ѧ����Ϣ*/  
void Delete(FILE*);                                      /*ɾ��ĳһ��ѧ����Ϣ*/ 



void mainTain(FILE * clientPtr)
{
	int choice;
//	while(1)
//	{
		while((choice=enterChoice(clientPtr))<4)                     /*�������ϵĲ˵���������Ϊ5ʱ����*/ 
		{
			
			switch (choice)                                  /*��ѡ����в�ͬ�Ĳ���*/ 
			{
				case 1:                                      /*����1������д��*/ 
					writeIn(clientPtr);
					break;
				case 2:                                     /*����2������ɾ��*/ 
					Delete(clientPtr);
					break;
				case 3:                                     /*����3�������޸�*/ 
					change(clientPtr);
					break;
			}
			fseek(clientPtr,0,SEEK_SET);
		}
//		if(choice==4) break;
//	} 
	
} 

int enterChoice(FILE* clientPtr)
{
	char menuChoice;
	PrintInfo(clientPtr);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Main->VIP information:\n");
	printf("����������ѡ��:\nV+ - ���һ��VIP�ͻ�\nV- - ɾ��һ��VIP�ͻ�����Ϣ\nV/ - �޸�һ���ͻ�����Ϣ\nE - ������һ��\n"); 
	menuChoice=getch();
	if(menuChoice=='E')	return 4;
	else if(menuChoice=='V')
	{
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("����������ѡ��:\n+ - ���һ��VIP�ͻ�\n- - ɾ��һ��VIP�ͻ�����Ϣ\n/ - �޸�һ���ͻ�����Ϣ\n");
		menuChoice=getch();
		if(menuChoice=='+') return 1;
		else if(menuChoice=='-') return 2;
		else if(menuChoice=='/') return 3;
		else printf("��������ȷ��ָ��.\n");
	}
	else printf("��������ȷ��ָ��.\n");
}

void writeIn(FILE* cliPtr)
{
	FILE* filePtr=cliPtr;
	CLIENT currentCli={" "," ",0},readCli={" "," ",0}; 						 /*������ʼ��*/ 
	printf("\n������Ҫ��ӵ���Ϣ:\n");
	fflush(stdin);  
	printf("������Ҫ��ӵĿͻ�����:");                                    /*��ջ���������gets*/ 
	gets(currentCli.name);
	fflush(stdin);
	printf("������Ҫ��ӵĿͻ�ID:");
	gets(currentCli.ID);
	fseek(cliPtr,0,SEEK_SET);
	while(!feof(cliPtr))
	{
		fread(&readCli,sizeof(CLIENT),1,filePtr);
		if(strcmp(readCli.ID,currentCli.ID)==0)
		{
			printf("��ID�Ѵ��ڣ����������롣\n"); 
			fflush(stdin);
			printf("������Ҫ��ӵĿͻ�ID:");
			gets(currentCli.ID);
			fseek(cliPtr,0,SEEK_SET);
		}
	}
	fflush(stdin);
	printf("������Ҫ��ӵĿͻ����˻��ܶ�:");
	scanf("%lf",&(currentCli.account));

	fseek(cliPtr,0,SEEK_END);
	filePtr=cliPtr;
	fwrite(&currentCli,sizeof(CLIENT),1,cliPtr);   	 /*д��*/ 
	printf("�ɹ�.\n");
}


void change(FILE* cliPtr)                               /*�޸Ŀͻ���Ϣ*/ 
{
	FILE* filePtr=cliPtr;
	int i=0,flag=0;                                      /*flag�����ж��Ƿ��ҵ�*/ 
	CLIENT currentCli={" "," ",0},readCli={" "," ",0},blankCli={" "," ",0};
	char a[6];
	printf("������Ҫ�޸ĵĿͻ���ID:\n");
	scanf("%s",a); 
	fseek(cliPtr,0,SEEK_SET);
	filePtr=cliPtr;
	while(!feof(filePtr))
	{
		fread(&currentCli,sizeof(CLIENT),1,cliPtr);
		if(strcmp(currentCli.ID,a)==0)
		{
			flag=1;
			break;
		}
		i++;
		currentCli=blankCli;
	}
	if(flag==0)
	{
		printf("�Ҳ����ÿͻ�.\n");
	}
	else
	{
		printf("��Ҫ�޸ĵĿͻ�����ϢΪ:\n");
		printf("������%s ID��%s �˻���%.2lf",currentCli.name,currentCli.ID,currentCli.account);/*������޸ĵļ�¼*/ 
		currentCli=blankCli;
		fseek(cliPtr,i*sizeof(CLIENT),SEEK_SET);
		filePtr=cliPtr;
		printf("\n������Ҫ�޸ĵ���Ϣ:\n");
		fflush(stdin);  
		printf("������Ҫ�޸ĵĿͻ�����:");                                    /*��ջ���������gets*/ 
		gets(currentCli.name);
		fflush(stdin);
		printf("������Ҫ�޸ĵĿͻ�ID:");
		gets(currentCli.ID);
		fseek(cliPtr,0,SEEK_SET);
		while(!feof(filePtr))
		{
			fread(&readCli,sizeof(CLIENT),1,filePtr);
			if(strcmp(readCli.ID,currentCli.ID)==0)
			{
				printf("��ID�Ѵ��ڣ����������롣"); 
				fflush(stdin);
				printf("������Ҫ�޸ĵĿͻ�ID:");
				gets(currentCli.ID);
				fseek(filePtr,0,SEEK_SET);
			}
		}
		fflush(stdin);
		printf("������Ҫ�޸ĵĿͻ����˻��ܶ�:");
		scanf("%lf",&(currentCli.account));
		fwrite(&currentCli,sizeof(CLIENT),1,filePtr);                        /*д���޸ĺ�ļ�¼*/ 
	}
	printf("�ɹ�.\n");
}

void Delete(FILE* cliPtr)                                  /*ɾ���ͻ���Ϣ*/ 
{
	FILE* filePtr=cliPtr;
	int i=0,flag=0,n=0;
	CLIENT currentCli[100]={" "," ",0},current,currentC,blankCli={"","",0};   /*currentΪ��¼���ж��ٿͻ�ʱѭ���ã�currentSΪ��ɾ����ѧ����¼*/ 
	char a[20]={ };
	printf("������Ҫɾ���Ŀͻ�ID:\n");
	scanf("%s",a); 
	fseek(filePtr,0,SEEK_SET);
	while(!feof(filePtr))
	{
		fread(&current,sizeof(CLIENT),1,filePtr);
		if(strcmp(current.ID,a)==0)
		{
			flag=1;
			i=n;
			currentC=current;
		}
		n++;
	}
	
	if(flag==0)                                       /*���û�ҵ���λ�ͻ�*/ 
	{
		printf("�Ҳ����ÿͻ�.\n");
	}
	else                                              /*�ҵ���λ�ͻ��󣬰Ѻ���ļ�¼ǰ�Ƹ���������¼*/ 
	{
		printf("��Ҫɾ���Ŀͻ���Ϣ��:\n");
		printf("������%s ID: %s �˻�: %.2lf",currentC.name,currentC.ID,currentC.account);
//		if(i!=n-1)
//		{
//		 
//		
//			fseek(filePtr,(i+1)*sizeof(CLIENT),SEEK_SET);
//			fread(&currentCli,sizeof(CLIENT),n-i,filePtr);
//			fseek(filePtr,i*sizeof(CLIENT),SEEK_SET);
//			fwrite(&currentCli,sizeof(CLIENT),n-i,filePtr);
//			printf("\n");
//		}
//		else                                           /*ɾ�����һλ�����*/ 
//		{
			
			fseek(filePtr,i*sizeof(CLIENT),SEEK_SET);
			fwrite(&blankCli,sizeof(CLIENT),1,filePtr);
			printf("\n");
//		}
	}
	printf("�ɹ�.\n");
}

void PrintInfo(FILE*filePtr)
{
	CLIENT currentCli={" "," ",0},blankCli={" "," ",0};
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("���е�VIP�ͻ���Ϣ:\n����\t\t\tID\t�˻�\n");
	fseek(filePtr,0,SEEK_SET);
	fread(&currentCli,sizeof(CLIENT),1,filePtr);
	while(!feof(filePtr))
	{
		printf("%-20s\t%-5s\t%.2lf\n",currentCli.name,currentCli.ID,currentCli.account);
		fread(&currentCli,sizeof(CLIENT),1,filePtr);
		
	}
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}
