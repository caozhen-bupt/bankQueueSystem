#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
enum Satis{bad=1,norm,good};//ö�������
enum State{idle=1,waiting,close,serving,rest,over};//ö�ٴ���״̬
enum EventType{Q,R1,R2,R3,R4,R5,R6,R7,R8,G,V};//ö���¼�����
struct Window{int winNum;
              char CliNum[4];
              int nowtime;
              int orderTime;
              int state;
			  int restflag;
              int custCount;
              int totalSerLen;
              int totalRestLen;
              int satGoodCount;
              int satNormCount;
              int satBadCount;
              };//������Ϣ��ģ
typedef struct Window WINDOW;
struct REQ{int REQ;
           int time;
		  };//������Ϣ��ģ
typedef struct REQ REQLISTNODE;
typedef struct REQ* REQLISTNODEPTR;
struct listNode{
              char CliNum[4];
              struct listNode * nextPtr;
              
               };//�ͻ��������������������ڽ��
typedef struct listNode LISTNODE;
typedef struct listNode* LISTNODEPTR;

struct winToRest{int winNum;
               struct winToRest * nextPtr;
               int totalTimeCount;
               int applyTime;
               };
typedef struct winToRest RESTLISTNODE;
typedef struct winToRest* RESTLISTNODEPTR;

struct clientFile{
	char name[20];
	char ID[6];
	double account;
};
typedef struct clientFile CLIENT;

typedef struct
{
	FILE* client;
	int* timePtr;
	WINDOW* windows;
}ARG;
typedef ARG* argPtr;
//�̴߳��ݵĲ��� 

//������Ϣ������н��
//#define size 8
/*#define MaxSeqLen 5
#define MinSec 10
#define MaxSec 30
#define MinRestSec 2
#define MaxRestSec 10
#define VIPSERVLen 10 
#define waitTime 3

*/
