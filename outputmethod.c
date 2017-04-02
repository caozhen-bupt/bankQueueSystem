#include "variable.h"
#include"common.h"
#include"egg.h"
char a[4],b[4],ser[5],res[5];
char a1[4],b1[4],c[4],d[4],e[4],g[4];


void transfer(int time,char a[4])        //将整型转换成字符数组 
{
	
	
	
		if(time>=100)
	{   a[0]=time/100+48;
		a[1]=(time/10)%10+48;
		a[2]=time%10+48;
		a[3]='\0';
		
	}
	else if(time<100&&time>=10)
	{
		a[0]=' ';
		a[1]=time/10+48;
		a[2]=time%10+48;
		a[3]='\0';
    }
	else if(time<10&&time>=0)
	{
		a[0]=' ';
		a[1]=' ';
		a[2]=time+48;
		a[3]='\0';
	}
	
	
	
	
}
void transfer2(int time,char a[5])          //将时间转化成数组 
{
	
	
	
		if(time>=1000)
	{   a[0]=time/1000+48;
		a[1]=(time/100)%10+48;
		a[2]=(time/10)%10+48;
		a[3]=time%10+48;
		a[4]='\0';
		
	}
	else if(time<1000&&time>=100)
	{
		a[0]=' ';
		a[1]=time/100+48;
		a[2]=(time/10)%10+48;
		a[3]=time%10+48;
		a[4]='\0';
    }
	else if(time<100&&time>=10)
	{
		a[0]=' ';
		a[1]=' ';
		a[2]=time/10+48;
		a[3]=time%10+48;
		a[4]='\0';
	}
	else if(time<10&&time>=0)
	{
		a[0]=' ';
		a[1]=' ';
		a[2]=' ';
		a[3]=time+48;
		a[4]='\0';
	}
	
	
	
	
}



void PrintWin(WINDOW windows[],int time)
{
   int i,j;
   
   for(i=0;i<=7;i++)
   { 

   transfer(windows[i].nowtime,a);           //转换整型 
   transfer(windows[i].orderTime,b);
   transfer2(windows[i].totalSerLen,ser);
   transfer2(windows[i].totalRestLen,res);


   			
   	switch(windows[i].state){                       //打印窗口状态 
   		case 1:                                     //空闲 
   			MovePen(55+i*135,620);
   			if(time==0) DrawString("IDLE");
   			MovePen(68+i*135,600);
			DrawString("       ");

   			MovePen(80+i*135,580);
   			DrawString(a);
   			DrawString("/");
   			DrawString(b);
   			DrawString("     ");
   			MovePen(100+i*135,560);
			DrawString("         ");
   			MovePen(100+i*135,560);
   			DrawString(ser);
   			MovePen(110+i*135,540);
			DrawString("       ");
   			MovePen(110+i*135,540);
   	        DrawString(res);
   			MovePen(15+i*135,520);
   			DrawBitmap("2.bmp");
   			break;
   			
   		case 2://等待 
   			MovePen(55+i*135,620);
   			if(time==0) DrawString("WAITING");
   			MovePen(68+i*135,600);
   			DrawString(windows[i].CliNum);
   			MovePen(80+i*135,580);
   			DrawString("            ");
   			MovePen(100+i*135,560);
			DrawString("         ");
   			MovePen(100+i*135,560);
   			DrawString(ser);
   			MovePen(110+i*135,540);
			DrawString("       ");
   			MovePen(110+i*135,540);
   	        DrawString(res);
   			MovePen(15+i*135,520);
   			DrawBitmap("2.bmp");
   			break;
   			
   		case 3://关闭 
   			MovePen(51+i*135,620);
   			if(time==0) DrawString("CLOSING");
   			MovePen(68+i*135,600);
			DrawString("       ");
   			MovePen(80+i*135,580);
   			DrawString(a);
   			DrawString("/");
   			DrawString(b);
   			DrawString("   ");
   			MovePen(100+i*135,560);
   			DrawString(ser);
   			MovePen(110+i*135,540);
   	        DrawString(res);
   			MovePen(15+i*135,520);
   			DrawBitmap("1.bmp");
   			MovePen(i*135,480);
   			DrawBitmap("bei.bmp");
   			break;
   			
   		case 4://服务 
   			MovePen(55+i*135,620);
   			if(time==0) DrawString("SERVING");
   			MovePen(80+i*135,580);
   			DrawString(a);
   			DrawString("/");
   			DrawString(b);
   			DrawString("   ");
   			MovePen(100+i*135,560);
			DrawString("         ");
   			MovePen(100+i*135,560);
   			DrawString(ser);
   			MovePen(15+i*135,520);
   			DrawBitmap("3.bmp");
   			if(windows[i].CliNum[0]!='V')
   			{
			MovePen(15+i*135,480);
   			DrawBitmap("4.bmp");
   			}
   			else
   			{
			MovePen(15+i*135,480);
   			DrawBitmap("5.bmp");
   			}
   			
   			break;
   			
   		case 5://休息 
   			MovePen(55+i*135,620);
   			if(time==0) DrawString("RESTING");
   			MovePen(68+i*135,600);
   			DrawString(windows[i].CliNum);
   			MovePen(80+i*135,580);
   			DrawString(a);
   			DrawString("/");
   			DrawString(b);
   			DrawString("   ");
   			MovePen(110+i*135,540);
   	        DrawString(res);
   			MovePen(15+i*135,520);
   			DrawBitmap("1.bmp");
   			break;
   			
   		case 6://服务结束 
   			MovePen(55+i*135,620);
   			if(time==0) DrawString("OVER");
   			MovePen(68+i*135,600);
			DrawString("       ");
   			MovePen(80+i*135,580);
   			DrawString(a);
   			DrawString("/");
   			DrawString(b);
   			DrawString("   ");
   			MovePen(100+i*135,560);
			DrawString("         ");
   			MovePen(100+i*135,560);
   			DrawString(ser);
   			MovePen(110+i*135,540);
			DrawString("       ");
   			MovePen(110+i*135,540);
   	        DrawString(res);
   			MovePen(15+i*135,520);
   			DrawBitmap("3.bmp");
   			MovePen(i*135,480);
   			DrawBitmap("bei.bmp");
   			break;
   			
   	   }
   	
   }	
}
void PrintQue()                                                 //打印队列 
{
	LISTNODEPTR currentPtr,currentPtrVIP;
	char s1[4],s2[4];
	int line=0,row=0,flag=0;
	int j,i,k;
	if(QueFlag==1)
	{
		currentPtr=headp;
		currentPtrVIP=headpVIP;
		
		MovePen(60,420);
		DrawString("Normal queque:");//普通客户队列 
	                    
							while(currentPtr!=NULL)//打印队列链表 
							{
								if(currentPtr->nextPtr==NULL)
								{
									if(flag==0)//最后一个顾客 
									{
									line++;
									
									if(line==10)
									{
									line=0;
									row++;
									}
									strcpy(s1,currentPtr->CliNum);
									DrawString(s1);
									//OffsetPen(0,-20);
									DrawBitmap("4.bmp");
									flag=2;//表示打印完了 
									break;
									}
									
								}
								else
								{
								 if(row==3&&line==8)                         //如果到了第四排第8个 
									{
										while(currentPtr->nextPtr!=NULL)         //直接打印最后一个顾客 
										{
										currentPtr=currentPtr->nextPtr;
										}
									strcpy(s1,currentPtr->CliNum);
									DrawString("......");                           //其他顾客用省略号代替 
									MovePen(560,270);
									DrawString(s1);
									
									DrawBitmap("4.bmp");
									flag=1;//表示打印到结尾了 
									row=4;
									line=0;
									break;
									}
									else{
									strcpy(s1,currentPtr->CliNum);           //不是最后一个则正常打印顾客 
									DrawString(s1);
									DrawBitmap("4.bmp");
									currentPtr=currentPtr->nextPtr;         //指针下一个 
									line++;                                   //一行的顾客数+1 
									}
									
									if(line==10&&flag==0)                              //一排打印满了且并没有打印到结尾且并没有打印完，就换行 接着打印 
									{
									row++;
									MovePen(160,420-row*50);
									line=0;
									}

								}
							}
		if(line!=0)
		{   
			for(j=line;j<9;j++)
				{
					DrawBitmap("bei.bmp");
					
				}
			DrawBitmap("bei1.bmp");
				row++;


			   for(j=row+1;j<=4;j++)
				{
				MovePen(160,420-(j-1)*50);
				for(k=1;k<9;k++)
				{
				DrawBitmap("bei.bmp");
				}
				DrawBitmap("bei1.bmp");
				}
				
			}

		else
		{   
              if(row<4){
			  
			  for(j=row+1;j<=4;j++)
				{
				MovePen(160,420-(j-1)*50);
				for(k=1;k<9;k++)
				{
				DrawBitmap("bei.bmp");
				}
				DrawBitmap("bei1.bmp");
				}
              }
			  
			

	   }
		line=0;
		row=0;	
		flag=0;		
		MovePen(60,220);
		DrawString("VIP queque:");
	                    
							while(currentPtrVIP!=NULL)
							{
								if(currentPtrVIP->nextPtr==NULL)
								{
								if(flag==0)//最后一个顾客 
									{
									line++;
									
									if(line==10)
									{
									line=0;
									row++;
									}
									strcpy(s1,currentPtrVIP->CliNum);
									DrawString(s1);
									DrawBitmap("5.bmp");
									flag=2;//表示打印完了 
									break;
									}
									
								}
								else
								{
								 if(row==3&&line==8)                         //如果到了第四排第18个 
									{
										while(currentPtrVIP->nextPtr!=NULL)         //直接打印最后一个顾客 
										{
										currentPtrVIP=currentPtrVIP->nextPtr;
										}
									strcpy(s2,currentPtrVIP->CliNum);
									DrawString("......");                           //其他顾客用省略号代替 
									MovePen(540,70);
									DrawString(s2);
									DrawBitmap("5.bmp");
									line=0;
									row=4;
									flag=1;
									break;
									}
									else{
									strcpy(s2,currentPtrVIP->CliNum);           //打印顾客 
									DrawString(s2);
									DrawBitmap("5.bmp");
									currentPtrVIP=currentPtrVIP->nextPtr;
									line++;                                   //一行的顾客数+1 
									}
									
									if(line==10)                              //一排打印满了就换行 
									{
									row++;
									MovePen(140,220-row*50);
									line=0;
									}

									
								}
							}
	if(line!=0)
		{   
			for(j=line;j<9;j++)
				{
					DrawBitmap("bei.bmp");
					
				}
				DrawBitmap("bei1.bmp");
				row++;


			   for(j=row+1;j<=4;j++)
				{
				MovePen(160,220-(j-1)*50);
				for(k=1;k<9;k++)
				{
				DrawBitmap("bei.bmp");
				}
				DrawBitmap("bei1.bmp");
				}
				
			}

		else
		{   

			  for(j=row+1;j<=4;j++)
				{
				MovePen(160,220-(j-1)*50);
				for(k=1;k<=9;k++)
				{
				DrawBitmap("bei.bmp");
				}
				}
			

	   }

	

}
}

void print_message(WINDOW windows[],int time,FILE*output1Ptr,FILE*output2Ptr,int PrintTime,int PrintMethod)
{int i;
LISTNODEPTR currentPtr1=headp,currentPtr2=headpVIP;

	
	//文件输出 
	if(PrintTime!=0)                               //间隔打印 
	{
		       if(time%PrintTime==0)                
	        	{
					fprintf(output1Ptr,"T=%3d\n",time);    //输出当前时间 
					 for(i=0;i<=7;i++)                       //遍历八个窗口 
					{	switch(windows[i].state){            //根据状态判断输出 
						
						case 1:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //空闲时刻的状态 
							break;
							
						case 2:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
							break;    
							                                              //等待顾客时状态			
						case 3:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
					        break;                                                  //关闭状态 
					    
						case 4:
						    fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						    break;                                                  //服务中状态 
						    
				        case 5:
					        fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
					        break;                                                  //休息状态 
					        
					    case 6:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
					        break;                                                  //服务结束状态 
					    }
					}
					
					fprintf(output1Ptr,"NormList=");                                          //打印普通客户队列 
					
					
					
						currentPtr1=headp; 
						while(currentPtr1!=NULL)
						{
							if(currentPtr1->nextPtr==NULL)
							{
								fprintf(output1Ptr,"%s",currentPtr1->CliNum);
								currentPtr1=currentPtr1->nextPtr;
							}
							else
							{
								fprintf(output1Ptr,"%s->",currentPtr1->CliNum);
								currentPtr1=currentPtr1->nextPtr;
							}
						}
						
						fprintf(output1Ptr,"\nVIPlist=");                                            //打印VIP 
					    currentPtr2=headpVIP;
						while(currentPtr2!=NULL)
						{
							if(currentPtr2->nextPtr==NULL)
							{
								fprintf(output1Ptr,"%s",currentPtr2->CliNum);
								currentPtr2=currentPtr2->nextPtr;
							}
							else
							{
								fprintf(output1Ptr,"%s->",currentPtr2->CliNum);
								currentPtr2=currentPtr2->nextPtr;
							}
						}
						fprintf(output1Ptr,"\n");
				}
					
				if(printFlag==1)                                                              //状态变化 
				{
				fprintf(output2Ptr,"T=%3d\n",time);                                                  //输出当前时间 
						 for(i=0;i<=7;i++)                                                                  //遍历八个窗口 
						{	switch(windows[i].state){                                                    //根据状态判断输出 
							
							case 1:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //空闲时刻的状态 
								break;
								
							case 2:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
								break;    
								                                              //等待顾客时状态			
							case 3:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
						        break;                                                  //关闭状态 
						    
							case 4:
							    fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
							    break;                                                  //服务中状态 
							    
					        case 5:
						        fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						        break;                                                  //休息状态 
						        
						    case 6:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
						        break;                                                  //服务结束状态 
						    }
						}
				
				   fprintf(output2Ptr,"NormList=");                                          //打印普通客户队列 
				   currentPtr1=headp; 
					while(currentPtr1!=NULL)
					{
						if(currentPtr1->nextPtr==NULL)
						{
							fprintf(output2Ptr,"%s",currentPtr1->CliNum);
							currentPtr1=currentPtr1->nextPtr;
						}
						else
						{
							fprintf(output2Ptr,"%s->",currentPtr1->CliNum);
							currentPtr1=currentPtr1->nextPtr;
						}
					}
					
					fprintf(output2Ptr,"\nVIPlist=");                                            //打印VIP 
				    currentPtr2=headpVIP;
					while(currentPtr2!=NULL)
					{
						if(currentPtr2->nextPtr==NULL)
						{
							fprintf(output2Ptr,"%s",currentPtr2->CliNum);
							currentPtr2=currentPtr2->nextPtr;
						}
						else
						{
							fprintf(output2Ptr,"%s->",currentPtr2->CliNum);
							currentPtr2=currentPtr2->nextPtr;
						}
					}
					fprintf(output2Ptr,"\n");
				
			    }
	}
					
			
		
	    
		else if(PrintTime==0)                      //每秒打印 
		{
			fprintf(output1Ptr,"T=%3d\n",time);    //输出当前时间 
				 for(i=0;i<=7;i++)                       //遍历八个窗口 
				{	switch(windows[i].state){            //根据状态判断输出 
					
					case 1:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //空闲时刻的状态 
						break;
						
					case 2:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						break;    
						                                              //等待顾客时状态			
					case 3:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
				        break;                                                  //关闭状态 
				    
					case 4:
					    fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
					    break;                                                  //服务中状态 
					    
			        case 5:
				        fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
				        break;                                                  //休息状态 
				        
				    case 6:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
				        break;                                                  //服务结束状态 
				    }
				}
				
				fprintf(output1Ptr,"NormList=");                                          //打印普通客户队列 
				currentPtr1=headp; 
					while(currentPtr1!=NULL)
					{
						if(currentPtr1->nextPtr==NULL)
						{
							fprintf(output1Ptr,"%s",currentPtr1->CliNum);
							currentPtr1=currentPtr1->nextPtr;
						}
						else
						{
							fprintf(output1Ptr,"%s->",currentPtr1->CliNum);
							currentPtr1=currentPtr1->nextPtr;
						}
					}
					
					fprintf(output1Ptr,"\nVIPlist=");                                            //打印VIP 
				    currentPtr2=headpVIP;
					while(currentPtr2!=NULL)
					{
						if(currentPtr2->nextPtr==NULL)
						{
							fprintf(output1Ptr,"%s",currentPtr2->CliNum);
							currentPtr2=currentPtr2->nextPtr;
						}
						else
						{
							fprintf(output1Ptr,"%s->",currentPtr2->CliNum);
							currentPtr2=currentPtr2->nextPtr;
						}
					}
					fprintf(output1Ptr,"\n");
		
					if(printFlag==1)                                                              //状态变化 
					{
					fprintf(output2Ptr,"T=%3d\n",time);                                                  //输出当前时间 
					 for(i=0;i<=7;i++)                                                                  //遍历八个窗口 
					{	switch(windows[i].state){                                                    //根据状态判断输出 
						
						case 1:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //空闲时刻的状态 
							break;
							
						case 2:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
							break;    
							                                              //等待顾客时状态			
						case 3:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
					        break;                                                  //关闭状态 
					    
						case 4:
						    fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						    break;                                                  //服务中状态 
						    
				        case 5:
					        fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
					        break;                                                  //休息状态 
					        
					    case 6:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
					        break;                                                  //服务结束状态 
					    }
					}
					
					fprintf(output2Ptr,"NormList=");                                          //打印普通客户队列 
					
					
					
						currentPtr1=headp; 
						while(currentPtr1!=NULL)
						{
							if(currentPtr1->nextPtr==NULL)
							{
								fprintf(output2Ptr,"%s",currentPtr1->CliNum);
								currentPtr1=currentPtr1->nextPtr;
							}
							else
							{
								fprintf(output2Ptr,"%s->",currentPtr1->CliNum);
								currentPtr1=currentPtr1->nextPtr;
							}
						}
						
						fprintf(output2Ptr,"\nVIPlist=");                                            //打印VIP 
					    currentPtr2=headpVIP;
						while(currentPtr2!=NULL)
						{
							if(currentPtr2->nextPtr==NULL)
							{
								fprintf(output2Ptr,"%s",currentPtr2->CliNum);
								currentPtr2=currentPtr2->nextPtr;
							}
							else
							{
								fprintf(output2Ptr,"%s->",currentPtr2->CliNum);
								currentPtr2=currentPtr2->nextPtr;
							}
						}
						fprintf(output2Ptr,"\n");
					
					
					
				}
				
	       }
	   


	
	if(PrintMethod==1)                                      //键盘输出
	{
	
	if(PrintTime!=0)
	{
	if(time%PrintTime==0)
	{   
		
		
		//屏幕输出 
	 printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	 printf("T=%3d\n",time);                                                             //输出当前时间 
     printf("WIN\tState\t  ServNo\tServLen\t   RestLen\t\n");
	 for(i=0;i<=7;i++)                                                                  //遍历八个窗口 
		{	switch(windows[i].state){                                                    //根据状态判断输出 
			
			case 1:
				printf("%d\tIDLE\t  NONE\t\n",windows[i].winNum);   //空闲时刻的状态 
				break;
				
			case 2:
				printf("%d\tWAITING\t  %4s\t\n",windows[i].winNum,windows[i].CliNum);
				break;    
				                                              //等待顾客时状态			
			case 3:
				printf("%d\tCLOSE\t  NONE\t\n",windows[i].winNum);
		        break;                                                  //关闭状态 
		    
			case 4:
			    printf("%d\tSERVING\t  %4s\t        %3d/%3d\t\n",windows[i].winNum,windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
			    break;                                                  //服务中状态 
			    
	        case 5:
		        printf("%d\tRESTING\t  NONE\t\t           %3d/%3d\t\n",windows[i].winNum,windows[i].nowtime,windows[i].orderTime);
		        break;                                                  //休息状态 
		        
		    case 6:
				printf("%d\tOVER\t  NONE\t\n",windows[i].winNum);
		        break;                                                  //服务结束状态 
		    }
		}
	
        printf("NormList=");                                          //打印普通客户队列 
	
	
	
		currentPtr1=headp; 
		while(currentPtr1!=NULL)
		{
			if(currentPtr1->nextPtr==NULL)
			{
				printf("%s",currentPtr1->CliNum);
				currentPtr1=currentPtr1->nextPtr;
			}
			else
			{
				printf("%s->",currentPtr1->CliNum);
				currentPtr1=currentPtr1->nextPtr;
			}
		}
		
		printf("\nVIPlist=");                                            //打印VIP 
	    currentPtr2=headpVIP;
		while(currentPtr2!=NULL)
		{
			if(currentPtr2->nextPtr==NULL)
			{
				printf("%s",currentPtr2->CliNum);
				currentPtr2=currentPtr2->nextPtr;
			}
			else
			{
				printf("%s->",currentPtr2->CliNum);
				currentPtr2=currentPtr2->nextPtr;
			}
		}
		printf("\n");
	         	if(Qflag==1)
						{
						printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n银行已经下班啦.\n");
			            }
						else
						{
						printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n请输入您的选择:\nG - 普通客户到来\nV - VIP客户到来\nR - 申请窗口休息\nS - 转换策略\nQ - 下班\nX - VIP客户信息维护\n");
			            }
			            
	}
	}
	
	
	else if(PrintTime==0)
	{
			
			if(printFlag==1)
			{  
			   //屏幕输出 
			   printf("T=%3d\n",time);                                                             //输出当前时间 
			   	 printf("WIN\tState\t  ServNo\tServLen\t   RestLen\t\n");
				 for(i=0;i<=7;i++)                                                                  //遍历八个窗口 
					{	switch(windows[i].state){                                                    //根据状态判断输出 
						
						case 1:
							printf("%d\tIDLE\t  NONE\t\n",windows[i].winNum);   //空闲时刻的状态 
							break;
							
						case 2:
							printf("%d\tWAITING\t  %4s\t\n",windows[i].winNum,windows[i].CliNum);
							break;    
							                                              //等待顾客时状态			
						case 3:
							printf("%d\tCLOSE\t  NONE\t\n",windows[i].winNum);
					        break;                                                  //关闭状态 
					    
						case 4:
						    printf("%d\tSERVING\t  %4s\t        %3d/%3d\t\n",windows[i].winNum,windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						    break;                                                  //服务中状态 
						    
				        case 5:
					        printf("%d\tRESTING\t  NONE\t\t           %3d/%3d\t\n",windows[i].winNum,windows[i].nowtime,windows[i].orderTime);
					        break;                                                  //休息状态 
					        
					    case 6:
							printf("%d\tOVER\t  NONE\t\n",windows[i].winNum);
					        break;                                                  //服务结束状态 
					    }
					}
			
					    printf("NormList=");                                          //打印普通客户队列 
					    currentPtr1=headp; 
						while(currentPtr1!=NULL)
						{
							if(currentPtr1->nextPtr==NULL)
							{
								printf("%s",currentPtr1->CliNum);
								currentPtr1=currentPtr1->nextPtr;
							}
							else
							{
								printf("%s->",currentPtr1->CliNum);
								currentPtr1=currentPtr1->nextPtr;
							}
						}
						
						printf("\nVIPlist=");                                            //打印VIP 
					    currentPtr2=headpVIP;
						while(currentPtr2!=NULL)
						{
							if(currentPtr2->nextPtr==NULL)
							{
								printf("%s",currentPtr2->CliNum);
								currentPtr2=currentPtr2->nextPtr;
							}
							else
							{
								printf("%s->",currentPtr2->CliNum);
								currentPtr2=currentPtr2->nextPtr;
							}
						}
						printf("\n");
				        if(Qflag==1)
						{
						printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \nThe bank has received closing signal.Please don't enter anything else.\n");
			            }
						else
						{
						printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \nPlease input your choice:\nG-to add a normal customer\nV-to add a VIP customer\nR-to apply for rest\nS-to change the stratedy\nQ-to stop serving\n");
			            }
			            
			            
			}
    }
   }
   
   
	 
}






void printStatistics(WINDOW windows[],FILE*outputPtr1)
{
	int i,totalcust=0,totalcustv=0;
	double a,b;

	   for(i=0;i<=5;i++)
	   {totalcust+=windows[i].custCount;                                  //计算普通客户总数 
	   }
	   for(i=6;i<=7;i++)
	   {totalcustv+=windows[i].custCount;                                //计算VIP客户总数 
	   }
	   for(i=0;i<=7;i++)                                                  //打印八个窗口的统计数据 
		{
			if(windows[i].custCount==0)
			{
			fprintf(outputPtr1,"WIN%d:CustCount=  0,ServLen=  0,PerServLen=  0,CustSatifyGood=  0,CustSatisfyNorm=  0,CustSatisfyBad=  0\n",i);
			}
			else
			{
			fprintf(outputPtr1,"WIN%d:CustCount=%3d,ServLen=%3d,PerServLen=%3d,CustSatifyGood=%3d,CustSatisfyNorm=%3d,CustSatisfyBad=%3d\n",i,windows[i].custCount,windows[i].totalSerLen,windows[i].totalSerLen/windows[i].custCount,windows[i].satGoodCount,windows[i].satNormCount,windows[i].satBadCount);
			}
		}
		
		fprintf(outputPtr1,"TotalCustNormCount=%3d\nTotalCustVIPCount=%3d\nSatisfyNotGoodWin=",totalcust,totalcustv);
		 
		for(i=0;i<=7;i++)
		{    if(windows[i].custCount!=0)
				{    
				     a=(double)(windows[i].satGoodCount/windows[i].custCount);
				     b=(double)(windows[i].satBadCount/windows[i].custCount);
				
			
			if(a<=0.7||b>=0.1)     //遍历找出不合格窗口打印 
			{
				fprintf(outputPtr1,"win%d ",i+1);
			}
		}
		}
		fprintf(outputPtr1,"\n");
	
	  
	
}


