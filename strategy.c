#include<string.h>
#include"variable.h"
#include"common.h"
//����ͻ�������Ҫ�õ��������ڵ�״̬ 
//strategyFlagΪ ������� 1Ϊ vip���ڶ������ ��2Ϊ˳����� 
void control1(WINDOW *windows)
{
	int i;//i�������±� 
	LISTNODEPTR curp=headp, curpVIP=headpVIP;

	for(i=0;i<6;i++){//��ͨ���� 
		if((windows[i].state==idle)&&(curp!=NULL)&&(windows[i].restflag==0)){//���ô���Ϊ����״̬�������пͻ��Ŷӣ����Ҹô���δ��������Ϣ�������ͻ�������
		    strcpy(windows[i].CliNum,curp->CliNum);
		    curp=curp->nextPtr;
		}
	}
	for(i=6;i<8;i++){//VIP���� 
		if((curpVIP!=NULL)&&(windows[i].state==idle)&&(windows[i].restflag==0)){//���ô���Ϊ����״̬�������пͻ��Ŷӣ����Ҹô���δ��������Ϣ�������ͻ�������
			strcpy(windows[i].CliNum,curpVIP->CliNum);
			curpVIP=curpVIP->nextPtr;
		} 
		else if((curpVIP==NULL)&&(strategyFlag==2)&&(windows[i].state==idle)&&(curp!=NULL)&&(windows[i].restflag==0)){//����ת�������Ϊ˳����������strategyFlag==2��ֻ�е�VIP�ͻ�Ϊ0����Ϊ˳�����ԭ��ʱ�Ż����ͨ�û������VIP����  
			strcpy(windows[i].CliNum,curp->CliNum);
		    curp=curp->nextPtr;
		}
	}
}

//��ǰ��������ͨ������
int countNorW(WINDOW *windows)
{
	int countNorW=0, i;
	for(i=0;i<6;i++){
		if(windows[i].state!=close&&windows[i].state!=rest&&windows[i].restflag==0){
			countNorW++;
		}
	}
	return countNorW;
}

//��ǰ������VIP������
int countVIPW(WINDOW *windows)
{
	int countVIPW=0, i;
	for(i=6;i<8;i++){
		if(windows[i].state!=close&&windows[i].state!=rest&&windows[i].restflag==0){
			countVIPW++;
		}
	}
	return countVIPW;
}
void control2(WINDOW windows[])//��Ϣ�ľ��� 
{
	RESTLISTNODEPTR restPtr,previousPtr,currentPtr,tempPtr;
	int countGW=0,countVW=0;//countGW����ǰ��������ͨ������, countVW����ǰ������vip������, wind�����ں�, i�������±�, applyRestCount����Ϣ�����е��ŶӴ����� 
	int aTime,tTime;//aTimeΪ��ǰ����ڵ㴰�ڵ�������Ϣʱ�䣻 tTimeΪ��ǰ����ڵ�Ĵ��ڵ��Ѿ���Ϣʱ�� 
	restPtr=NULL;//ָ����Ϣ�Ľڵ� 
	previousPtr=NULL;
	currentPtr=headpWinRest;
	countGW=countNorW(windows);//���㿪�Ŵ����� 
	countVW=countVIPW(windows);
	
	if(currentPtr!=NULL)
	{
		aTime=currentPtr->applyTime;
		tTime=currentPtr->totalTimeCount;
		if((((currentPtr->winNum)<6&&countGW>3&&(float)currentNor/countGW<MaxSeqLen)||
		((currentPtr->winNum)>5&&countVW>1&&(float)currentVIP/countVW<MaxSeqLen))&&
		(windows[(currentPtr->winNum)-1].state==idle||windows[(currentPtr->winNum)-1].state==over)) restPtr=currentPtr;//���ͷ�������restPtr������ 
		while(currentPtr->nextPtr!=NULL)
		{
			currentPtr=currentPtr->nextPtr;
			if(currentPtr->applyTime==aTime)//ͬʱ������жϣ��������ʱ����ͬ 
			{
				if(currentPtr->totalTimeCount<tTime&&(windows[(currentPtr->winNum)-1].state==idle||windows[(currentPtr->winNum)-1].state==over)&&
				(((currentPtr->winNum)<6&&countGW>3&&(float)currentNor/countGW<MaxSeqLen)||((currentPtr->winNum)>5&&countVW>1&&(float)currentVIP/countVW<MaxSeqLen)))//��ǰ�ڵ㴰��������Ϣ���� 
				{
					restPtr=currentPtr;
					tTime=currentPtr->totalTimeCount;
				}
			}
			else//����ʱ�䲻��ͬ 
			{
				if(restPtr!=NULL) break;//������ʱ���д��ڿ�����Ϣ�����Ǹ�������Ϣ 
				//û�еĻ��ͼ����жϱ������� 
				aTime=currentPtr->applyTime;
				tTime=currentPtr->totalTimeCount;
				if((((currentPtr->winNum)<6&&countGW>3&&(float)currentNor/countGW<MaxSeqLen)||
				((currentPtr->winNum)>5&&countVW>1&&(float)currentVIP/countVW<MaxSeqLen))&&
				(windows[(currentPtr->winNum)-1].state==idle||windows[(currentPtr->winNum)-1].state==over)) restPtr=currentPtr;//��ǰ�ڵ㴰��������Ϣ���� 


			}
		}
	}
	if(restPtr!=NULL)//����д�����Ϣ����� 
	{

		if(restPtr==headpWinRest)//ͷ�����Ϣ 
		{
			windows[(restPtr->winNum)-1].restflag=1;
			tempPtr=headpWinRest;
			headpWinRest=headpWinRest->nextPtr;
			free(tempPtr);//�ͷ������е�ͷ�ڵ� 
		}
		else//��ͷ�ڵ���Ϣ 
		{
			windows[(restPtr->winNum)-1].restflag=1;
			previousPtr=headpWinRest;
			while(previousPtr->nextPtr!=restPtr) previousPtr=previousPtr->nextPtr;
			previousPtr->nextPtr=restPtr->nextPtr;
			tempPtr=restPtr;
			free(tempPtr);//�ͷ������еĸýڵ� 
		}
		
		
	}
} 
