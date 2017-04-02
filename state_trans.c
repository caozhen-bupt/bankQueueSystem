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
    int i, come, statis; //i�Ǵ��������±꣬come�����ģ��˿͵�����statis�����ģ��˿������ 
    char wnum[2];//�ַ����� 
    LISTNODEPTR tempPtr;
    srand((int)time(NULL));//������� 

    //�ж��Ƿ���Ҫ�رջ�򿪴��� 
    openClose(windows);
    
    for(i=0;i<8;i++){
        switch(windows[i].state) {//����״̬ 
            case idle://����:
                if(strcmp(windows[i].CliNum,"   ")!=0){//�пͻ������䵽�ô��� 
                    printFlag=1;
					windows[i].state=waiting;//״̬�л������ȴ��˿͡�,��ȡ�˿ͺ��룬ɾ�������еĸù˿�
					 
					windows[i].nowtime=0;                   //�����ȴ���ʱ;
					if(eggFlag==1)//������ͼ�ν���汾 
					{
						MovePen(51+i*135,620);//�ƶ����� 
						DrawString("                  ");//���ԭ��״̬ 
						MovePen(51+i*135,620);
						DrawString("WAITING");//��ӡ״̬WAITING
						MovePen(0,700);
						DrawBitmap("С����.bmp");//��ͼƬ 
						//���´�ӡ�뼸�Ź˿͵����Ŵ��� 
						MovePen(500,700);
						DrawString("��");
						DrawString(windows[i].CliNum);
						DrawString("�Ź˿͵�");
						wnum[0]=i+'0'+1; //�����ʹ��ںű���ַ��ʹ洢��wnum��0���� 
						wnum[1]='\0';
						DrawString(wnum); 
						DrawString("�Ŵ��ڡ�");
						 
						QueFlag=1;//���б仯����־��ֵΪ�� 
					} 
					
					if(windows[i].CliNum[0]!='V'){//����ͨ�ͻ� 
						tempPtr=headp;
						headp=headp->nextPtr;
						free(tempPtr);//�ͷ���ͨ�ͻ�������иýڵ� 
						currentNor--;//��ǰ��ͨ�ͻ���������-1 
					}  
					else if(windows[i].CliNum[0]=='V'){//��VIP�ͻ� 
						tempPtr=headpVIP;
						headpVIP=headpVIP->nextPtr;
						free(tempPtr);//�ͷ�VIP�ͻ�������иýڵ� 
						currentVIP--;//��ǰVIP�ͻ���������-1 
					}  
                }
                else if(windows[i].restflag==1){//����������Ϣ����׼ 
                	if(eggFlag==1)//������ͼ�ν���汾 
                	{
	                	MovePen(15+i*135,580);
						DrawString("                        ");//���ԭ�е��ַ��� 
	                	MovePen(15+i*135,580);
						DrawString("RestLen:");
					}
                	
                    printFlag=1;//��ӡ��־��Ϊ�� 
					windows[i].state=rest;                  //״̬�л�������ͣ��;
					if(eggFlag==1)//������ͼ�ν���汾 
					{
						MovePen(51+i*135,620);
						DrawString("                   ");//���ԭ��״̬ 
						MovePen(51+i*135,620);
						DrawString("REST"); //��ӡ״̬REST 
					}
					
                    windows[i].nowtime=0;
                    windows[i].restflag=0;//������Ϣ��־���¸�ֵΪ�� 
                    windows[i].orderTime=rand()%(MaxRestSec-MinRestSec+1)+MinRestSec;//������Ϣ��Ԥ��ʱ�� 
                }

                break;
            case waiting://�ȴ��˿ͣ�
                come=rand()%100;//���ģ��ͻ������������ �������ż��δ���� 
                if(come%2==0)//�˿�δ����
				{
					if(windows[i].nowtime>WaitTime)//�ȴ�ʱ�䵽
					{
						printFlag=1;
						if(windows[i].CliNum[0]!='V'){//�ֱ�����뿪�Ŀͻ� 
							leaveNor++;
						}
						else if(windows[i].CliNum[0]=='V'){
							leaveVIP++;
						} 
						windows[i].state=idle;//���ڵȴ�ʱ�䵽���ҿͻ���δ�������ʴ������±�Ϊ����״̬ 
						if(eggFlag==1)//������ͼ�ν���汾 
						{
							MovePen(51+i*135,620);
							DrawString("                    ");//���ԭ��״̬ 
							MovePen(51+i*135,620);
							DrawString("IDLE"); //��ӡ״̬IDLE 
							MovePen(0,700);
							DrawBitmap("С����.bmp");//��ͼƬ 
						}
						
						windows[i].nowtime=0;
						strcpy(windows[i].CliNum,"   ");//������ڽṹ��ͻ��� 
					}
					else{
						windows[i].nowtime++;//ʱ������ 
					}
				}
				else
				{
					printFlag=1;
					windows[i].state=serving;
					if(eggFlag==1)//������ͼ�ν���汾 
					{
						MovePen(51+i*135,620);
						DrawString("                   ");//���ԭ��״̬ 
						MovePen(51+i*135,620);
						DrawString("SERVING");//��ӡ״̬SERVING 
						MovePen(0,700);
						DrawBitmap("С����.bmp");//��ͼƬ 
					}
					 
					windows[i].custCount++;//�ô��ڷ���ͻ���+1 
					windows[i].nowtime=0;
					windows[i].orderTime=rand()%(MaxSec-MinSec+1)+MinSec;//����ҵ�����ʱ�� 
				}
                break;
            case serving://�����У�
				if(windows[i].nowtime<=windows[i].orderTime-1){//����δ���� 
                    windows[i].state=serving; 
                    ++windows[i].nowtime;//�ô��ڵ�ǰ����ʱ��++ 
                    ++windows[i].totalSerLen; //�ô��ڷ�����ʱ��++ 
                } 
                else{//���� 
                    printFlag=1;
                    windows[i].state=over;
                    if(eggFlag==1)//������ͼ�ν���汾 
                    {
	                	MovePen(51+i*135,620);
						DrawString("                      ");//���ԭ��״̬ 
						MovePen(51+i*135,620);
						DrawString("OVER"); //��ӡ״̬OVER
						MovePen(1030,200);
						if(windows[i].CliNum[0]=='V'){
							DrawBitmap("5.bmp");
						} 
						else{
							DrawBitmap("4.bmp");
						}
					}
					
                    strcpy(windows[i].CliNum,"   ");//������ڷ���ͻ��� 
                    windows[i].nowtime=0;
                    windows[i].orderTime=0;
                    statis=rand()%3;//���ģ��ͻ������ 
					if(statis%3==0){//���� 
						windows[i].satGoodCount++;//������++ 
						if(eggFlag==1) satGood(i);//������ͼ�ν���汾 ����ʾЦ�� 
					}
					else if(statis%3==1){//���� 
						windows[i].satNormCount++;//������++ 
						if(eggFlag==1) satNorm(i);//������ͼ�ν���汾 ����ʾƲ��
					}
					else{//���� 
						windows[i].satBadCount++;//������++ 
						if(eggFlag==1) satBad(i);//������ͼ�ν���汾 ����ʾ����
					} 
            	}
	            break;
	        case over://�������
	        	if(eggFlag==1) clear(i);//������ͼ�ν���汾   ������� 
                if(windows[i].restflag==1){//����������Ϣ����׼ 
                if(eggFlag==1)//������ͼ�ν���汾 
                {
                	MovePen(15+i*135,580);
					DrawString("                        ");//��� 
                	MovePen(15+i*135,580);
					DrawString("RestLen:");
                	
                     
					MovePen(51+i*135,620);
					DrawString("                        ");//��� 
					MovePen(51+i*135,620);
					DrawString("REST"); //��ӡ״̬REST 
				}
					windows[i].state=rest;//״̬�仯��rest 
                	printFlag=1;
                    windows[i].nowtime=0;//������Ϣ��ʱ�� 
                    windows[i].restflag=0;//��Ϣ��־���¸�ֵΪ�� 
                    windows[i].orderTime=rand()%(MaxRestSec-MinRestSec+1)+MinRestSec;//������Ϣ��Ԥ��ʱ�� 
				} 
				else if(strcmp(windows[i].CliNum,"   ")!=0){//�ӵ����񣬱�����ͻ� 
				    printFlag=1;
					windows[i].state=waiting; 
					if(eggFlag==1)//������ͼ�ν���汾 
					{
						MovePen(51+i*135,620);
						DrawString("                       ");
						MovePen(51+i*135,620);
						DrawString("WAITING");
					}
					 
				    windows[i].nowtime=0;//�����ȴ���ʱ�� 
				    if(windows[i].CliNum[0]!='V'){//����ͨ�ͻ� 
						tempPtr=headp;
						headp=headp->nextPtr;
						free(tempPtr);//�ͷ���ͨ�ͻ�������иýڵ� 
						currentNor--;
					}  
					else if(windows[i].CliNum[0]=='V'){//��VIP�ͻ� 
						tempPtr=headpVIP;
						headpVIP=headpVIP->nextPtr;
						free(tempPtr);//�ͷ�VIP�ͻ�������иýڵ� 
						currentVIP--;
					}   
		    	}
		    	else{//������ 
		    		printFlag=1;
		    		windows[i].state=idle; 
		    		if(eggFlag==1)//������ͼ�ν���汾 
		    		{
			    		MovePen(51+i*135,620);
						DrawString("                     ");//���ԭ��״̬ 
						MovePen(51+i*135,620);
						DrawString("IDLE"); //��ӡ״̬IDLE 
					}
					
		    		windows[i].nowtime=0; 
		    	}
				break;
	        case rest://��ͣ��
                if(windows[i].nowtime == windows[i].orderTime){ //ʱ�䵽 
                    printFlag=1;
					windows[i].state=idle;
					if(eggFlag==1)//������ͼ�ν���汾 
					{
						MovePen(51+i*135,620);
						DrawString("                     ");//���ԭ��״̬ 
						MovePen(51+i*135,620);
						DrawString("IDLE"); //��ӡ״̬IDLE 
						MovePen(15+i*135,580);
						DrawString("                        ");
	                	MovePen(15+i*135,580);
						DrawString("ServeLen:");
					} 
					
                    windows[i].nowtime=0;
                    windows[i].orderTime=0;
				}
				else{//ʱ��δ��
				    windows[i].state=rest; 
				    ++windows[i].nowtime;
				    ++windows[i].totalRestLen;
				} 
				break;
			case close:
				if(eggFlag==1)//������ͼ�ν���汾 
				{
					MovePen(51+i*135,620);
					DrawString("                     ");//���ԭ��״̬ 
					MovePen(51+i*135,620);
					DrawString("CLOSING"); //��ӡ״̬ CLOSING 
					clear(i);
				}
				
				break;
	    }
	    openClose(windows);//�ж��Ƿ���Ҫ�رջ�򿪴��� 
	}
}
//�ж��Ƿ���Ҫ�رջ�򿪴��� 
void openClose(WINDOW *windows)
{
	int countG, countV, i;
	int newOpenG=0, newOpenV=0, openTime;//newOpenG��newOpenV�ֱ�Ϊ��ȳ�ʼ��ʱ�´򿪵���ͨ��VIP���ڸ��� 
	
	countG=countNorW(windows);//�ֱ�����������δ��Ϣ�Ĵ��ڵĸ��� 
    countV=countVIPW(windows);
    
    for(i=3;i<6 && windows[i].state!=close;i++){
    	newOpenG++;
    }
    if(windows[7].state!=close){
    	newOpenV=1;
    }
	if((newOpenG<=3)&&(newOpenG>=0)){
		if(newOpenG<=2){//����ͨ���� 
			if((float)currentNor/countG-3>=0){
			    windows[3+newOpenG].state=idle;
				newOpenG++;
				countG++;
		    }
		}
		if(newOpenG>=1){
			if((float)currentNor/countG-2<0){//����ͨ���� 
			    if((windows[2+newOpenG].state==idle||windows[2+newOpenG].state==over)&&countG>3){
			    	windows[2+newOpenG].state=close;
					newOpenG--;
			    }
		    }
		}
		
	}
	if((newOpenV==1)||(newOpenV==0)){
		if(newOpenV==0){
			if(currentVIP>=3){//��vip���� 
			   	windows[7].state=idle;
			   	newOpenV++;
			   	openTime=0;
			   	countV++;
		    }
		}
		else if(newOpenV==1){
			if(currentVIP<3){
				openTime++;
				if((openTime>=VIPSERVLen&&(windows[7].state==idle||windows[7].state==over))&&countV>1){//��vip���� 
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

void satGood(int i)//��ʾЦ�� 
{
	MovePen(60+135*i,480);
	DrawBitmap("21.bmp");
}

void satNorm(int i)//��ʾƲ�� 
{
	MovePen(60+135*i,480);
	DrawBitmap("22.bmp");
}

void satBad(int i)//��ʾ���� 
{
	MovePen(60+135*i,480);
	DrawBitmap("23.bmp");
}
 
void clear(int i)// �������
{
	MovePen(60+135*i,480);
	DrawBitmap("40.bmp");
}
