#include"variable.h"
#include"common.h"


void Configuration(FILE* filePtr)
{
	int input;
	long time;
	char choice; 
	int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag;//配置文件里的参数，后三个依次为周期性输出间隔，窗口等待客户的时间，策略 
	long closeTime;//配置文件的参数，下班时间
	while(1)
	{	
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("Main->configuraion:\n") ;
		printf("当前配置为:\n");
		fscanf(filePtr,"[MaxSeqLen]%d\n[MinSec]%d\n[MaxSec]%d\n[MinRestSec]%d\n[MaxRestSec]%d\n[VIPSERVLen]%d\n[OutputSec]%d\n[WaitTime]%d\n[strategyFlag]%d\n[closeTime]%ld"
		,&MaxSeqLen,&MinSec,&MaxSec,&MinRestSec,&MaxRestSec,&VIPSERVLen,&OutputSec,&WaitTime,&strategyFlag,&closeTime);
		printf("单队列最大允许等待长度:%d\n单业务办理最短时长:%d\n""单业务办理最长时长:%d\n窗口休息最短时长:%d\n"
		"窗口休息最长时长:%d\n当VIP人数少于2人时，开启第二个VIP窗口的最长时间:%d\n""输出窗口状态的时间间隔:%d\n每个窗口等待客户时间:%d\n"
		"目前选择的策略:%d\n(1 - 定向服务 2 - 顺便服务)\n"
		"下班时间:%ld\n",
		MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag,closeTime);
		
		
		fseek(filePtr,0,SEEK_SET);
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("Please input your choice:\n");
		printf("D - 使用默认配置;\nN-自定义配置;\nE-返回上一级.\n");
		choice=getch();
		if(choice=='D')//默认 
		{
			fprintf(filePtr,"[MaxSeqLen]5\n[MinSec]10\n[MaxSec]30\n[MinRestSec]20\n[MaxRestSec]50\n[VIPSERVLen]200\n[OutputSec]1\n[WaitTime]3\n[strategyFlag]1\n[closeTime]3600");
			printf("成功.\n");
			break;
		}
		else if(choice=='N')//自己修改 
		{
			printf("请输入单队列最大允许等待长度:");
			scanf("%d",&input);
			fprintf(filePtr,"[MaxSeqLen]%d\n",input);
			printf("请输入单业务办理最短时长:");
			scanf("%d",&input);
			fprintf(filePtr,"[MinSec]%d\n",input);
			printf("请输入业单务办理最长时长:");
			scanf("%d",&input);
			fprintf(filePtr,"[MaxSec]%d\n",input);
			printf("请输入窗口休息最短时长:");
			scanf("%d",&input);
			fprintf(filePtr,"[MinRestSec]%d\n",input);
			printf("请输入窗口休息最长时长:");
			scanf("%d",&input);
			fprintf(filePtr,"[MaxRestSec]%d\n",input);
			printf("请输入当VIP人数少于2人时，开启第二个VIP窗口的最长时间:");
			scanf("%d",&input);
			fprintf(filePtr,"[VIPSERVLen]%d\n",input);
			printf("请输入输出窗口状态的时间间隔:");
			scanf("%d",&input);
			fprintf(filePtr,"[OutputSec]%d\n",input);
			printf("请输入每个窗口等待客户时间:");
			scanf("%d",&input);
			fprintf(filePtr,"[WaitTime]%d\n",input);
			printf("请选择策略(1 - 定向服务 2 - 顺便服务):");
			scanf("%d",&input);
			fprintf(filePtr,"[strategyFlag]%d\n",input);
			printf("请输入下班时间:\n");
			scanf("%ld",&time);
			fprintf(filePtr,"[closeTime]%ld",time);
			printf("成功.\n");
			break;
		}
		else if(choice=='E') break;
		else
		{
			printf("请输入正确指令\n");
			
		}
	}
	
}
