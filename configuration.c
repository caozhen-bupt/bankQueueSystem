#include"variable.h"
#include"common.h"


void Configuration(FILE* filePtr)
{
	int input;
	long time;
	char choice; 
	int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag;//�����ļ���Ĳ���������������Ϊ�����������������ڵȴ��ͻ���ʱ�䣬���� 
	long closeTime;//�����ļ��Ĳ������°�ʱ��
	while(1)
	{	
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("Main->configuraion:\n") ;
		printf("��ǰ����Ϊ:\n");
		fscanf(filePtr,"[MaxSeqLen]%d\n[MinSec]%d\n[MaxSec]%d\n[MinRestSec]%d\n[MaxRestSec]%d\n[VIPSERVLen]%d\n[OutputSec]%d\n[WaitTime]%d\n[strategyFlag]%d\n[closeTime]%ld"
		,&MaxSeqLen,&MinSec,&MaxSec,&MinRestSec,&MaxRestSec,&VIPSERVLen,&OutputSec,&WaitTime,&strategyFlag,&closeTime);
		printf("�������������ȴ�����:%d\n��ҵ��������ʱ��:%d\n""��ҵ������ʱ��:%d\n������Ϣ���ʱ��:%d\n"
		"������Ϣ�ʱ��:%d\n��VIP��������2��ʱ�������ڶ���VIP���ڵ��ʱ��:%d\n""�������״̬��ʱ����:%d\nÿ�����ڵȴ��ͻ�ʱ��:%d\n"
		"Ŀǰѡ��Ĳ���:%d\n(1 - ������� 2 - ˳�����)\n"
		"�°�ʱ��:%ld\n",
		MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag,closeTime);
		
		
		fseek(filePtr,0,SEEK_SET);
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("Please input your choice:\n");
		printf("D - ʹ��Ĭ������;\nN-�Զ�������;\nE-������һ��.\n");
		choice=getch();
		if(choice=='D')//Ĭ�� 
		{
			fprintf(filePtr,"[MaxSeqLen]5\n[MinSec]10\n[MaxSec]30\n[MinRestSec]20\n[MaxRestSec]50\n[VIPSERVLen]200\n[OutputSec]1\n[WaitTime]3\n[strategyFlag]1\n[closeTime]3600");
			printf("�ɹ�.\n");
			break;
		}
		else if(choice=='N')//�Լ��޸� 
		{
			printf("�����뵥�����������ȴ�����:");
			scanf("%d",&input);
			fprintf(filePtr,"[MaxSeqLen]%d\n",input);
			printf("�����뵥ҵ��������ʱ��:");
			scanf("%d",&input);
			fprintf(filePtr,"[MinSec]%d\n",input);
			printf("������ҵ��������ʱ��:");
			scanf("%d",&input);
			fprintf(filePtr,"[MaxSec]%d\n",input);
			printf("�����봰����Ϣ���ʱ��:");
			scanf("%d",&input);
			fprintf(filePtr,"[MinRestSec]%d\n",input);
			printf("�����봰����Ϣ�ʱ��:");
			scanf("%d",&input);
			fprintf(filePtr,"[MaxRestSec]%d\n",input);
			printf("�����뵱VIP��������2��ʱ�������ڶ���VIP���ڵ��ʱ��:");
			scanf("%d",&input);
			fprintf(filePtr,"[VIPSERVLen]%d\n",input);
			printf("�������������״̬��ʱ����:");
			scanf("%d",&input);
			fprintf(filePtr,"[OutputSec]%d\n",input);
			printf("������ÿ�����ڵȴ��ͻ�ʱ��:");
			scanf("%d",&input);
			fprintf(filePtr,"[WaitTime]%d\n",input);
			printf("��ѡ�����(1 - ������� 2 - ˳�����):");
			scanf("%d",&input);
			fprintf(filePtr,"[strategyFlag]%d\n",input);
			printf("�������°�ʱ��:\n");
			scanf("%ld",&time);
			fprintf(filePtr,"[closeTime]%ld",time);
			printf("�ɹ�.\n");
			break;
		}
		else if(choice=='E') break;
		else
		{
			printf("��������ȷָ��\n");
			
		}
	}
	
}
