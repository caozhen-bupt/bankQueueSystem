#include "variable.h"
#include"common.h"
#include"egg.h"
char a[4],b[4],ser[5],res[5];
char a1[4],b1[4],c[4],d[4],e[4],g[4];


void transfer(int time,char a[4])        //������ת�����ַ����� 
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
void transfer2(int time,char a[5])          //��ʱ��ת�������� 
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

   transfer(windows[i].nowtime,a);           //ת������ 
   transfer(windows[i].orderTime,b);
   transfer2(windows[i].totalSerLen,ser);
   transfer2(windows[i].totalRestLen,res);


   			
   	switch(windows[i].state){                       //��ӡ����״̬ 
   		case 1:                                     //���� 
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
   			
   		case 2://�ȴ� 
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
   			
   		case 3://�ر� 
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
   			
   		case 4://���� 
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
   			
   		case 5://��Ϣ 
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
   			
   		case 6://������� 
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
void PrintQue()                                                 //��ӡ���� 
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
		DrawString("Normal queque:");//��ͨ�ͻ����� 
	                    
							while(currentPtr!=NULL)//��ӡ�������� 
							{
								if(currentPtr->nextPtr==NULL)
								{
									if(flag==0)//���һ���˿� 
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
									flag=2;//��ʾ��ӡ���� 
									break;
									}
									
								}
								else
								{
								 if(row==3&&line==8)                         //������˵����ŵ�8�� 
									{
										while(currentPtr->nextPtr!=NULL)         //ֱ�Ӵ�ӡ���һ���˿� 
										{
										currentPtr=currentPtr->nextPtr;
										}
									strcpy(s1,currentPtr->CliNum);
									DrawString("......");                           //�����˿���ʡ�ԺŴ��� 
									MovePen(560,270);
									DrawString(s1);
									
									DrawBitmap("4.bmp");
									flag=1;//��ʾ��ӡ����β�� 
									row=4;
									line=0;
									break;
									}
									else{
									strcpy(s1,currentPtr->CliNum);           //�������һ����������ӡ�˿� 
									DrawString(s1);
									DrawBitmap("4.bmp");
									currentPtr=currentPtr->nextPtr;         //ָ����һ�� 
									line++;                                   //һ�еĹ˿���+1 
									}
									
									if(line==10&&flag==0)                              //һ�Ŵ�ӡ�����Ҳ�û�д�ӡ����β�Ҳ�û�д�ӡ�꣬�ͻ��� ���Ŵ�ӡ 
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
								if(flag==0)//���һ���˿� 
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
									flag=2;//��ʾ��ӡ���� 
									break;
									}
									
								}
								else
								{
								 if(row==3&&line==8)                         //������˵����ŵ�18�� 
									{
										while(currentPtrVIP->nextPtr!=NULL)         //ֱ�Ӵ�ӡ���һ���˿� 
										{
										currentPtrVIP=currentPtrVIP->nextPtr;
										}
									strcpy(s2,currentPtrVIP->CliNum);
									DrawString("......");                           //�����˿���ʡ�ԺŴ��� 
									MovePen(540,70);
									DrawString(s2);
									DrawBitmap("5.bmp");
									line=0;
									row=4;
									flag=1;
									break;
									}
									else{
									strcpy(s2,currentPtrVIP->CliNum);           //��ӡ�˿� 
									DrawString(s2);
									DrawBitmap("5.bmp");
									currentPtrVIP=currentPtrVIP->nextPtr;
									line++;                                   //һ�еĹ˿���+1 
									}
									
									if(line==10)                              //һ�Ŵ�ӡ���˾ͻ��� 
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

	
	//�ļ���� 
	if(PrintTime!=0)                               //�����ӡ 
	{
		       if(time%PrintTime==0)                
	        	{
					fprintf(output1Ptr,"T=%3d\n",time);    //�����ǰʱ�� 
					 for(i=0;i<=7;i++)                       //�����˸����� 
					{	switch(windows[i].state){            //����״̬�ж���� 
						
						case 1:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //����ʱ�̵�״̬ 
							break;
							
						case 2:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
							break;    
							                                              //�ȴ��˿�ʱ״̬			
						case 3:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
					        break;                                                  //�ر�״̬ 
					    
						case 4:
						    fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						    break;                                                  //������״̬ 
						    
				        case 5:
					        fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
					        break;                                                  //��Ϣ״̬ 
					        
					    case 6:
							fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
					        break;                                                  //�������״̬ 
					    }
					}
					
					fprintf(output1Ptr,"NormList=");                                          //��ӡ��ͨ�ͻ����� 
					
					
					
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
						
						fprintf(output1Ptr,"\nVIPlist=");                                            //��ӡVIP 
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
					
				if(printFlag==1)                                                              //״̬�仯 
				{
				fprintf(output2Ptr,"T=%3d\n",time);                                                  //�����ǰʱ�� 
						 for(i=0;i<=7;i++)                                                                  //�����˸����� 
						{	switch(windows[i].state){                                                    //����״̬�ж���� 
							
							case 1:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //����ʱ�̵�״̬ 
								break;
								
							case 2:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
								break;    
								                                              //�ȴ��˿�ʱ״̬			
							case 3:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
						        break;                                                  //�ر�״̬ 
						    
							case 4:
							    fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
							    break;                                                  //������״̬ 
							    
					        case 5:
						        fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						        break;                                                  //��Ϣ״̬ 
						        
						    case 6:
								fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
						        break;                                                  //�������״̬ 
						    }
						}
				
				   fprintf(output2Ptr,"NormList=");                                          //��ӡ��ͨ�ͻ����� 
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
					
					fprintf(output2Ptr,"\nVIPlist=");                                            //��ӡVIP 
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
					
			
		
	    
		else if(PrintTime==0)                      //ÿ���ӡ 
		{
			fprintf(output1Ptr,"T=%3d\n",time);    //�����ǰʱ�� 
				 for(i=0;i<=7;i++)                       //�����˸����� 
				{	switch(windows[i].state){            //����״̬�ж���� 
					
					case 1:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //����ʱ�̵�״̬ 
						break;
						
					case 2:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						break;    
						                                              //�ȴ��˿�ʱ״̬			
					case 3:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
				        break;                                                  //�ر�״̬ 
				    
					case 4:
					    fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
					    break;                                                  //������״̬ 
					    
			        case 5:
				        fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
				        break;                                                  //��Ϣ״̬ 
				        
				    case 6:
						fprintf(output1Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
				        break;                                                  //�������״̬ 
				    }
				}
				
				fprintf(output1Ptr,"NormList=");                                          //��ӡ��ͨ�ͻ����� 
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
					
					fprintf(output1Ptr,"\nVIPlist=");                                            //��ӡVIP 
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
		
					if(printFlag==1)                                                              //״̬�仯 
					{
					fprintf(output2Ptr,"T=%3d\n",time);                                                  //�����ǰʱ�� 
					 for(i=0;i<=7;i++)                                                                  //�����˸����� 
					{	switch(windows[i].state){                                                    //����״̬�ж���� 
						
						case 1:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"IDLE",windows[i].CliNum);   //����ʱ�̵�״̬ 
							break;
							
						case 2:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"WAITING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
							break;    
							                                              //�ȴ��˿�ʱ״̬			
						case 3:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"CLOSE",windows[i].CliNum);
					        break;                                                  //�ر�״̬ 
					    
						case 4:
						    fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=%3d/%3d,RestLen=   /   \n",windows[i].winNum,"SERVING",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						    break;                                                  //������״̬ 
						    
				        case 5:
					        fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=%3d/%3d\n",windows[i].winNum,"REST",windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
					        break;                                                  //��Ϣ״̬ 
					        
					    case 6:
							fprintf(output2Ptr,"WIN%d:State=%11s,ServNo=%s,ServLen=   /   ,RestLen=   /   \n",windows[i].winNum,"OVER",windows[i].CliNum);
					        break;                                                  //�������״̬ 
					    }
					}
					
					fprintf(output2Ptr,"NormList=");                                          //��ӡ��ͨ�ͻ����� 
					
					
					
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
						
						fprintf(output2Ptr,"\nVIPlist=");                                            //��ӡVIP 
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
	   


	
	if(PrintMethod==1)                                      //�������
	{
	
	if(PrintTime!=0)
	{
	if(time%PrintTime==0)
	{   
		
		
		//��Ļ��� 
	 printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	 printf("T=%3d\n",time);                                                             //�����ǰʱ�� 
     printf("WIN\tState\t  ServNo\tServLen\t   RestLen\t\n");
	 for(i=0;i<=7;i++)                                                                  //�����˸����� 
		{	switch(windows[i].state){                                                    //����״̬�ж���� 
			
			case 1:
				printf("%d\tIDLE\t  NONE\t\n",windows[i].winNum);   //����ʱ�̵�״̬ 
				break;
				
			case 2:
				printf("%d\tWAITING\t  %4s\t\n",windows[i].winNum,windows[i].CliNum);
				break;    
				                                              //�ȴ��˿�ʱ״̬			
			case 3:
				printf("%d\tCLOSE\t  NONE\t\n",windows[i].winNum);
		        break;                                                  //�ر�״̬ 
		    
			case 4:
			    printf("%d\tSERVING\t  %4s\t        %3d/%3d\t\n",windows[i].winNum,windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
			    break;                                                  //������״̬ 
			    
	        case 5:
		        printf("%d\tRESTING\t  NONE\t\t           %3d/%3d\t\n",windows[i].winNum,windows[i].nowtime,windows[i].orderTime);
		        break;                                                  //��Ϣ״̬ 
		        
		    case 6:
				printf("%d\tOVER\t  NONE\t\n",windows[i].winNum);
		        break;                                                  //�������״̬ 
		    }
		}
	
        printf("NormList=");                                          //��ӡ��ͨ�ͻ����� 
	
	
	
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
		
		printf("\nVIPlist=");                                            //��ӡVIP 
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
						printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n�����Ѿ��°���.\n");
			            }
						else
						{
						printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n����������ѡ��:\nG - ��ͨ�ͻ�����\nV - VIP�ͻ�����\nR - ���봰����Ϣ\nS - ת������\nQ - �°�\nX - VIP�ͻ���Ϣά��\n");
			            }
			            
	}
	}
	
	
	else if(PrintTime==0)
	{
			
			if(printFlag==1)
			{  
			   //��Ļ��� 
			   printf("T=%3d\n",time);                                                             //�����ǰʱ�� 
			   	 printf("WIN\tState\t  ServNo\tServLen\t   RestLen\t\n");
				 for(i=0;i<=7;i++)                                                                  //�����˸����� 
					{	switch(windows[i].state){                                                    //����״̬�ж���� 
						
						case 1:
							printf("%d\tIDLE\t  NONE\t\n",windows[i].winNum);   //����ʱ�̵�״̬ 
							break;
							
						case 2:
							printf("%d\tWAITING\t  %4s\t\n",windows[i].winNum,windows[i].CliNum);
							break;    
							                                              //�ȴ��˿�ʱ״̬			
						case 3:
							printf("%d\tCLOSE\t  NONE\t\n",windows[i].winNum);
					        break;                                                  //�ر�״̬ 
					    
						case 4:
						    printf("%d\tSERVING\t  %4s\t        %3d/%3d\t\n",windows[i].winNum,windows[i].CliNum,windows[i].nowtime,windows[i].orderTime);
						    break;                                                  //������״̬ 
						    
				        case 5:
					        printf("%d\tRESTING\t  NONE\t\t           %3d/%3d\t\n",windows[i].winNum,windows[i].nowtime,windows[i].orderTime);
					        break;                                                  //��Ϣ״̬ 
					        
					    case 6:
							printf("%d\tOVER\t  NONE\t\n",windows[i].winNum);
					        break;                                                  //�������״̬ 
					    }
					}
			
					    printf("NormList=");                                          //��ӡ��ͨ�ͻ����� 
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
						
						printf("\nVIPlist=");                                            //��ӡVIP 
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
	   {totalcust+=windows[i].custCount;                                  //������ͨ�ͻ����� 
	   }
	   for(i=6;i<=7;i++)
	   {totalcustv+=windows[i].custCount;                                //����VIP�ͻ����� 
	   }
	   for(i=0;i<=7;i++)                                                  //��ӡ�˸����ڵ�ͳ������ 
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
				
			
			if(a<=0.7||b>=0.1)     //�����ҳ����ϸ񴰿ڴ�ӡ 
			{
				fprintf(outputPtr1,"win%d ",i+1);
			}
		}
		}
		fprintf(outputPtr1,"\n");
	
	  
	
}


