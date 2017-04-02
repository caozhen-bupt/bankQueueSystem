#include<string.h>
#include"variable.h"
#include"common.h"
//分配客户到窗口要用到各个窗口的状态 
//strategyFlag为 服务策略 1为 vip窗口定向服务 ，2为顺便服务 
void control1(WINDOW *windows)
{
	int i;//i是数组下标 
	LISTNODEPTR curp=headp, curpVIP=headpVIP;

	for(i=0;i<6;i++){//普通窗口 
		if((windows[i].state==idle)&&(curp!=NULL)&&(windows[i].restflag==0)){//若该窗口为空闲状态，并且有客户排队，并且该窗口未被允许休息，则分配客户到窗口
		    strcpy(windows[i].CliNum,curp->CliNum);
		    curp=curp->nextPtr;
		}
	}
	for(i=6;i<8;i++){//VIP窗口 
		if((curpVIP!=NULL)&&(windows[i].state==idle)&&(windows[i].restflag==0)){//若该窗口为空闲状态，并且有客户排队，并且该窗口未被允许休息，则分配客户到窗口
			strcpy(windows[i].CliNum,curpVIP->CliNum);
			curpVIP=curpVIP->nextPtr;
		} 
		else if((curpVIP==NULL)&&(strategyFlag==2)&&(windows[i].state==idle)&&(curp!=NULL)&&(windows[i].restflag==0)){//策略转换，如果为顺便服务策略则strategyFlag==2，只有当VIP客户为0并且为顺便服务原则时才会把普通用户分配给VIP窗口  
			strcpy(windows[i].CliNum,curp->CliNum);
		    curp=curp->nextPtr;
		}
	}
}

//当前工作的普通窗口数
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

//当前工作的VIP窗口数
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
void control2(WINDOW windows[])//休息的决策 
{
	RESTLISTNODEPTR restPtr,previousPtr,currentPtr,tempPtr;
	int countGW=0,countVW=0;//countGW：当前工作的普通窗口数, countVW：当前工作的vip窗口数, wind：窗口号, i：数组下标, applyRestCount：休息链表中的排队窗口数 
	int aTime,tTime;//aTime为当前链表节点窗口的申请休息时间； tTime为当前链表节点的窗口的已经休息时长 
	restPtr=NULL;//指向休息的节点 
	previousPtr=NULL;
	currentPtr=headpWinRest;
	countGW=countNorW(windows);//计算开放窗口数 
	countVW=countVIPW(windows);
	
	if(currentPtr!=NULL)
	{
		aTime=currentPtr->applyTime;
		tTime=currentPtr->totalTimeCount;
		if((((currentPtr->winNum)<6&&countGW>3&&(float)currentNor/countGW<MaxSeqLen)||
		((currentPtr->winNum)>5&&countVW>1&&(float)currentVIP/countVW<MaxSeqLen))&&
		(windows[(currentPtr->winNum)-1].state==idle||windows[(currentPtr->winNum)-1].state==over)) restPtr=currentPtr;//如果头满足就让restPtr等于它 
		while(currentPtr->nextPtr!=NULL)
		{
			currentPtr=currentPtr->nextPtr;
			if(currentPtr->applyTime==aTime)//同时间里的判断，如果申请时间相同 
			{
				if(currentPtr->totalTimeCount<tTime&&(windows[(currentPtr->winNum)-1].state==idle||windows[(currentPtr->winNum)-1].state==over)&&
				(((currentPtr->winNum)<6&&countGW>3&&(float)currentNor/countGW<MaxSeqLen)||((currentPtr->winNum)>5&&countVW>1&&(float)currentVIP/countVW<MaxSeqLen)))//当前节点窗口满足休息条件 
				{
					restPtr=currentPtr;
					tTime=currentPtr->totalTimeCount;
				}
			}
			else//申请时间不相同 
			{
				if(restPtr!=NULL) break;//如果早的时间有窗口可以休息就让那个窗口休息 
				//没有的话就继续判断遍历链表 
				aTime=currentPtr->applyTime;
				tTime=currentPtr->totalTimeCount;
				if((((currentPtr->winNum)<6&&countGW>3&&(float)currentNor/countGW<MaxSeqLen)||
				((currentPtr->winNum)>5&&countVW>1&&(float)currentVIP/countVW<MaxSeqLen))&&
				(windows[(currentPtr->winNum)-1].state==idle||windows[(currentPtr->winNum)-1].state==over)) restPtr=currentPtr;//当前节点窗口满足休息条件 


			}
		}
	}
	if(restPtr!=NULL)//如果有窗口休息的情况 
	{

		if(restPtr==headpWinRest)//头结点休息 
		{
			windows[(restPtr->winNum)-1].restflag=1;
			tempPtr=headpWinRest;
			headpWinRest=headpWinRest->nextPtr;
			free(tempPtr);//释放链表中的头节点 
		}
		else//非头节点休息 
		{
			windows[(restPtr->winNum)-1].restflag=1;
			previousPtr=headpWinRest;
			while(previousPtr->nextPtr!=restPtr) previousPtr=previousPtr->nextPtr;
			previousPtr->nextPtr=restPtr->nextPtr;
			tempPtr=restPtr;
			free(tempPtr);//释放链表中的该节点 
		}
		
		
	}
} 
