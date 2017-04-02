#include"variable.h"
#include"common.h"
#include"egg.h"
#include<string.h>
#include<time.h>
extern int countNorW(WINDOW *windows);
extern int countVIPW(WINDOW *windows);
void openClose(WINDOW *windows);
void satGood(int i);
void satNorm(int i);
void satBad(int i);
void clear(int i); 
void state_trans(WINDOW *windows,int eggFlag)
{
    int i, come, statis; //i是窗口数组下标，come是随机模拟顾客到来，statis是随机模拟顾客满意度 
    char wnum[2];//字符数组 
    LISTNODEPTR tempPtr;
    srand((int)time(NULL));//随机种子 

    //判断是否需要关闭或打开窗口 
    openClose(windows);
    
    for(i=0;i<8;i++){
        switch(windows[i].state) {//窗口状态 
            case idle://空闲:
                if(strcmp(windows[i].CliNum,"   ")!=0){//有客户被分配到该窗口 
                    printFlag=1;
					windows[i].state=waiting;//状态切换到“等待顾客”,获取顾客号码，删除链表中的该顾客
					 
					windows[i].nowtime=0;                   //启动等待计时;
					if(eggFlag==1)//若运行图形界面版本 
					{
						MovePen(51+i*135,620);//移动画笔 
						DrawString("                  ");//清除原有状态 
						MovePen(51+i*135,620);
						DrawString("WAITING");//打印状态WAITING
						MovePen(0,700);
						DrawBitmap("小背景.bmp");//打开图片 
						//以下打印请几号顾客到几号窗口 
						MovePen(500,700);
						DrawString("请");
						DrawString(windows[i].CliNum);
						DrawString("号顾客到");
						wnum[0]=i+'0'+1; //将整型窗口号变成字符型存储在wnum【0】中 
						wnum[1]='\0';
						DrawString(wnum); 
						DrawString("号窗口。");
						 
						QueFlag=1;//队列变化，标志赋值为真 
					} 
					
					if(windows[i].CliNum[0]!='V'){//是普通客户 
						tempPtr=headp;
						headp=headp->nextPtr;
						free(tempPtr);//释放普通客户链表队列该节点 
						currentNor--;//当前普通客户队列人数-1 
					}  
					else if(windows[i].CliNum[0]=='V'){//是VIP客户 
						tempPtr=headpVIP;
						headpVIP=headpVIP->nextPtr;
						free(tempPtr);//释放VIP客户链表队列该节点 
						currentVIP--;//当前VIP客户队列人数-1 
					}  
                }
                else if(windows[i].restflag==1){//窗口申请休息被批准 
                	if(eggFlag==1)//若运行图形界面版本 
                	{
	                	MovePen(15+i*135,580);
						DrawString("                        ");//清空原有的字符串 
	                	MovePen(15+i*135,580);
						DrawString("RestLen:");
					}
                	
                    printFlag=1;//打印标志设为真 
					windows[i].state=rest;                  //状态切换到“暂停”;
					if(eggFlag==1)//若运行图形界面版本 
					{
						MovePen(51+i*135,620);
						DrawString("                   ");//清除原有状态 
						MovePen(51+i*135,620);
						DrawString("REST"); //打印状态REST 
					}
					
                    windows[i].nowtime=0;
                    windows[i].restflag=0;//窗口休息标志重新赋值为假 
                    windows[i].orderTime=rand()%(MaxRestSec-MinRestSec+1)+MinRestSec;//窗口休息的预设时长 
                }

                break;
            case waiting://等待顾客：
                come=rand()%100;//随机模拟客户到来的情况： 奇数到达，偶数未到达 
                if(come%2==0)//顾客未到达
				{
					if(windows[i].nowtime>WaitTime)//等待时间到
					{
						printFlag=1;
						if(windows[i].CliNum[0]!='V'){//分别计数离开的客户 
							leaveNor++;
						}
						else if(windows[i].CliNum[0]=='V'){
							leaveVIP++;
						} 
						windows[i].state=idle;//由于等待时间到并且客户还未到来，故窗口重新变为空闲状态 
						if(eggFlag==1)//若运行图形界面版本 
						{
							MovePen(51+i*135,620);
							DrawString("                    ");//清除原有状态 
							MovePen(51+i*135,620);
							DrawString("IDLE"); //打印状态IDLE 
							MovePen(0,700);
							DrawBitmap("小背景.bmp");//打开图片 
						}
						
						windows[i].nowtime=0;
						strcpy(windows[i].CliNum,"   ");//清除窗口结构体客户号 
					}
					else{
						windows[i].nowtime++;//时间推移 
					}
				}
				else
				{
					printFlag=1;
					windows[i].state=serving;
					if(eggFlag==1)//若运行图形界面版本 
					{
						MovePen(51+i*135,620);
						DrawString("                   ");//清除原有状态 
						MovePen(51+i*135,620);
						DrawString("SERVING");//打印状态SERVING 
						MovePen(0,700);
						DrawBitmap("小背景.bmp");//打开图片 
					}
					 
					windows[i].custCount++;//该窗口服务客户数+1 
					windows[i].nowtime=0;
					windows[i].orderTime=rand()%(MaxSec-MinSec+1)+MinSec;//窗口业务办理时长 
				}
                break;
            case serving://办理中：
				if(windows[i].nowtime<=windows[i].orderTime-1){//服务未结束 
                    windows[i].state=serving; 
                    ++windows[i].nowtime;//该窗口当前服务时长++ 
                    ++windows[i].totalSerLen; //该窗口服务总时长++ 
                } 
                else{//结束 
                    printFlag=1;
                    windows[i].state=over;
                    if(eggFlag==1)//若运行图形界面版本 
                    {
	                	MovePen(51+i*135,620);
						DrawString("                      ");//清除原有状态 
						MovePen(51+i*135,620);
						DrawString("OVER"); //打印状态OVER
						MovePen(1030,200);
						if(windows[i].CliNum[0]=='V'){
							DrawBitmap("5.bmp");
						} 
						else{
							DrawBitmap("4.bmp");
						}
					}
					
                    strcpy(windows[i].CliNum,"   ");//清除窗口服务客户号 
                    windows[i].nowtime=0;
                    windows[i].orderTime=0;
                    statis=rand()%3;//随机模拟客户满意度 
					if(statis%3==0){//好评 
						windows[i].satGoodCount++;//好评数++ 
						if(eggFlag==1) satGood(i);//若运行图形界面版本 则显示笑脸 
					}
					else if(statis%3==1){//中评 
						windows[i].satNormCount++;//中评数++ 
						if(eggFlag==1) satNorm(i);//若运行图形界面版本 则显示撇嘴
					}
					else{//差评 
						windows[i].satBadCount++;//差评数++ 
						if(eggFlag==1) satBad(i);//若运行图形界面版本 则显示哭脸
					} 
            	}
	            break;
	        case over://服务结束
	        	if(eggFlag==1) clear(i);//若运行图形界面版本   清除表情 
                if(windows[i].restflag==1){//窗口申请休息被批准 
                if(eggFlag==1)//若运行图形界面版本 
                {
                	MovePen(15+i*135,580);
					DrawString("                        ");//清除 
                	MovePen(15+i*135,580);
					DrawString("RestLen:");
                	
                     
					MovePen(51+i*135,620);
					DrawString("                        ");//清除 
					MovePen(51+i*135,620);
					DrawString("REST"); //打印状态REST 
				}
					windows[i].state=rest;//状态变化成rest 
                	printFlag=1;
                    windows[i].nowtime=0;//启动休息计时器 
                    windows[i].restflag=0;//休息标志重新赋值为假 
                    windows[i].orderTime=rand()%(MaxRestSec-MinRestSec+1)+MinRestSec;//窗口休息的预设时长 
				} 
				else if(strcmp(windows[i].CliNum,"   ")!=0){//接到任务，被分配客户 
				    printFlag=1;
					windows[i].state=waiting; 
					if(eggFlag==1)//若运行图形界面版本 
					{
						MovePen(51+i*135,620);
						DrawString("                       ");
						MovePen(51+i*135,620);
						DrawString("WAITING");
					}
					 
				    windows[i].nowtime=0;//启动等待计时器 
				    if(windows[i].CliNum[0]!='V'){//是普通客户 
						tempPtr=headp;
						headp=headp->nextPtr;
						free(tempPtr);//释放普通客户链表队列该节点 
						currentNor--;
					}  
					else if(windows[i].CliNum[0]=='V'){//是VIP客户 
						tempPtr=headpVIP;
						headpVIP=headpVIP->nextPtr;
						free(tempPtr);//释放VIP客户链表队列该节点 
						currentVIP--;
					}   
		    	}
		    	else{//无任务 
		    		printFlag=1;
		    		windows[i].state=idle; 
		    		if(eggFlag==1)//若运行图形界面版本 
		    		{
			    		MovePen(51+i*135,620);
						DrawString("                     ");//清除原有状态 
						MovePen(51+i*135,620);
						DrawString("IDLE"); //打印状态IDLE 
					}
					
		    		windows[i].nowtime=0; 
		    	}
				break;
	        case rest://暂停：
                if(windows[i].nowtime == windows[i].orderTime){ //时间到 
                    printFlag=1;
					windows[i].state=idle;
					if(eggFlag==1)//若运行图形界面版本 
					{
						MovePen(51+i*135,620);
						DrawString("                     ");//清除原有状态 
						MovePen(51+i*135,620);
						DrawString("IDLE"); //打印状态IDLE 
						MovePen(15+i*135,580);
						DrawString("                        ");
	                	MovePen(15+i*135,580);
						DrawString("ServeLen:");
					} 
					
                    windows[i].nowtime=0;
                    windows[i].orderTime=0;
				}
				else{//时间未到
				    windows[i].state=rest; 
				    ++windows[i].nowtime;
				    ++windows[i].totalRestLen;
				} 
				break;
			case close:
				if(eggFlag==1)//若运行图形界面版本 
				{
					MovePen(51+i*135,620);
					DrawString("                     ");//清除原有状态 
					MovePen(51+i*135,620);
					DrawString("CLOSING"); //打印状态 CLOSING 
					clear(i);
				}
				
				break;
	    }
	    openClose(windows);//判断是否需要关闭或打开窗口 
	}
}
//判断是否需要关闭或打开窗口 
void openClose(WINDOW *windows)
{
	int countG, countV, i;
	int newOpenG=0, newOpenV=0, openTime;//newOpenG和newOpenV分别为相比初始化时新打开的普通和VIP窗口个数 
	
	countG=countNorW(windows);//分别数：开着且未休息的窗口的个数 
    countV=countVIPW(windows);
    
    for(i=3;i<6 && windows[i].state!=close;i++){
    	newOpenG++;
    }
    if(windows[7].state!=close){
    	newOpenV=1;
    }
	if((newOpenG<=3)&&(newOpenG>=0)){
		if(newOpenG<=2){//开普通窗口 
			if((float)currentNor/countG-3>=0){
			    windows[3+newOpenG].state=idle;
				newOpenG++;
				countG++;
		    }
		}
		if(newOpenG>=1){
			if((float)currentNor/countG-2<0){//关普通窗口 
			    if((windows[2+newOpenG].state==idle||windows[2+newOpenG].state==over)&&countG>3){
			    	windows[2+newOpenG].state=close;
					newOpenG--;
			    }
		    }
		}
		
	}
	if((newOpenV==1)||(newOpenV==0)){
		if(newOpenV==0){
			if(currentVIP>=3){//开vip窗口 
			   	windows[7].state=idle;
			   	newOpenV++;
			   	openTime=0;
			   	countV++;
		    }
		}
		else if(newOpenV==1){
			if(currentVIP<3){
				openTime++;
				if((openTime>=VIPSERVLen&&(windows[7].state==idle||windows[7].state==over))&&countV>1){//关vip窗口 
					windows[7].state=close;
					openTime=0;

				}
		    }
		    else{
		    	openTime=0;
		    }
		}
	}
}

void satGood(int i)//显示笑脸 
{
	MovePen(60+135*i,480);
	DrawBitmap("21.bmp");
}

void satNorm(int i)//显示撇嘴 
{
	MovePen(60+135*i,480);
	DrawBitmap("22.bmp");
}

void satBad(int i)//显示哭脸 
{
	MovePen(60+135*i,480);
	DrawBitmap("23.bmp");
}
 
void clear(int i)// 清除表情
{
	MovePen(60+135*i,480);
	DrawBitmap("40.bmp");
}
