#include"variable.h"
#include"common.h"
#include<string.h>

void PrintInfo(FILE*);
int enterChoice(FILE*);                                   /*输入选择的函数*/ 
void writeIn(FILE *);                                    /*写入学生信息*/ 

void change(FILE*);                                      /*修改学生信息*/  
void Delete(FILE*);                                      /*删除某一条学生信息*/ 



void mainTain(FILE * clientPtr)
{
	int choice;
//	while(1)
//	{
		while((choice=enterChoice(clientPtr))<4)                     /*仿照书上的菜单，当输入为5时结束*/ 
		{
			
			switch (choice)                                  /*对选择进行不同的操作*/ 
			{
				case 1:                                      /*输入1，进行写入*/ 
					writeIn(clientPtr);
					break;
				case 2:                                     /*输入2，进行删除*/ 
					Delete(clientPtr);
					break;
				case 3:                                     /*输入3，进行修改*/ 
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
	printf("请输入您的选择:\nV+ - 添加一个VIP客户\nV- - 删除一个VIP客户的信息\nV/ - 修改一个客户的信息\nE - 返回上一级\n"); 
	menuChoice=getch();
	if(menuChoice=='E')	return 4;
	else if(menuChoice=='V')
	{
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("请输入您的选择:\n+ - 添加一个VIP客户\n- - 删除一个VIP客户的信息\n/ - 修改一个客户的信息\n");
		menuChoice=getch();
		if(menuChoice=='+') return 1;
		else if(menuChoice=='-') return 2;
		else if(menuChoice=='/') return 3;
		else printf("请输入正确的指令.\n");
	}
	else printf("请输入正确的指令.\n");
}

void writeIn(FILE* cliPtr)
{
	FILE* filePtr=cliPtr;
	CLIENT currentCli={" "," ",0},readCli={" "," ",0}; 						 /*变量初始化*/ 
	printf("\n请输入要添加的信息:\n");
	fflush(stdin);  
	printf("请输入要添加的客户名字:");                                    /*清空缓冲区便于gets*/ 
	gets(currentCli.name);
	fflush(stdin);
	printf("请输入要添加的客户ID:");
	gets(currentCli.ID);
	fseek(cliPtr,0,SEEK_SET);
	while(!feof(cliPtr))
	{
		fread(&readCli,sizeof(CLIENT),1,filePtr);
		if(strcmp(readCli.ID,currentCli.ID)==0)
		{
			printf("该ID已存在，请重新输入。\n"); 
			fflush(stdin);
			printf("请输入要添加的客户ID:");
			gets(currentCli.ID);
			fseek(cliPtr,0,SEEK_SET);
		}
	}
	fflush(stdin);
	printf("请输入要添加的客户的账户总额:");
	scanf("%lf",&(currentCli.account));

	fseek(cliPtr,0,SEEK_END);
	filePtr=cliPtr;
	fwrite(&currentCli,sizeof(CLIENT),1,cliPtr);   	 /*写入*/ 
	printf("成功.\n");
}


void change(FILE* cliPtr)                               /*修改客户信息*/ 
{
	FILE* filePtr=cliPtr;
	int i=0,flag=0;                                      /*flag用于判断是否找到*/ 
	CLIENT currentCli={" "," ",0},readCli={" "," ",0},blankCli={" "," ",0};
	char a[6];
	printf("请输入要修改的客户的ID:\n");
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
		printf("找不到该客户.\n");
	}
	else
	{
		printf("您要修改的客户的信息为:\n");
		printf("姓名：%s ID：%s 账户：%.2lf",currentCli.name,currentCli.ID,currentCli.account);/*输出待修改的记录*/ 
		currentCli=blankCli;
		fseek(cliPtr,i*sizeof(CLIENT),SEEK_SET);
		filePtr=cliPtr;
		printf("\n请输入要修改的信息:\n");
		fflush(stdin);  
		printf("请输入要修改的客户名字:");                                    /*清空缓冲区便于gets*/ 
		gets(currentCli.name);
		fflush(stdin);
		printf("请输入要修改的客户ID:");
		gets(currentCli.ID);
		fseek(cliPtr,0,SEEK_SET);
		while(!feof(filePtr))
		{
			fread(&readCli,sizeof(CLIENT),1,filePtr);
			if(strcmp(readCli.ID,currentCli.ID)==0)
			{
				printf("该ID已存在，请重新输入。"); 
				fflush(stdin);
				printf("请输入要修改的客户ID:");
				gets(currentCli.ID);
				fseek(filePtr,0,SEEK_SET);
			}
		}
		fflush(stdin);
		printf("请输入要修改的客户的账户总额:");
		scanf("%lf",&(currentCli.account));
		fwrite(&currentCli,sizeof(CLIENT),1,filePtr);                        /*写入修改后的记录*/ 
	}
	printf("成功.\n");
}

void Delete(FILE* cliPtr)                                  /*删除客户信息*/ 
{
	FILE* filePtr=cliPtr;
	int i=0,flag=0,n=0;
	CLIENT currentCli[100]={" "," ",0},current,currentC,blankCli={"","",0};   /*current为记录共有多少客户时循环用，currentS为待删除的学生记录*/ 
	char a[20]={ };
	printf("请输入要删除的客户ID:\n");
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
	
	if(flag==0)                                       /*如果没找到这位客户*/ 
	{
		printf("找不到该客户.\n");
	}
	else                                              /*找到这位客户后，把后面的记录前移覆盖这条记录*/ 
	{
		printf("您要删除的客户信息是:\n");
		printf("姓名：%s ID: %s 账户: %.2lf",currentC.name,currentC.ID,currentC.account);
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
//		else                                           /*删除最后一位的情况*/ 
//		{
			
			fseek(filePtr,i*sizeof(CLIENT),SEEK_SET);
			fwrite(&blankCli,sizeof(CLIENT),1,filePtr);
			printf("\n");
//		}
	}
	printf("成功.\n");
}

void PrintInfo(FILE*filePtr)
{
	CLIENT currentCli={" "," ",0},blankCli={" "," ",0};
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("已有的VIP客户信息:\n姓名\t\t\tID\t账户\n");
	fseek(filePtr,0,SEEK_SET);
	fread(&currentCli,sizeof(CLIENT),1,filePtr);
	while(!feof(filePtr))
	{
		printf("%-20s\t%-5s\t%.2lf\n",currentCli.name,currentCli.ID,currentCli.account);
		fread(&currentCli,sizeof(CLIENT),1,filePtr);
		
	}
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}
