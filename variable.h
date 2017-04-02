#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
enum Satis{bad=1,norm,good};//枚举满意度
enum State{idle=1,waiting,close,serving,rest,over};//枚举窗口状态
enum EventType{Q,R1,R2,R3,R4,R5,R6,R7,R8,G,V};//枚举事件类型
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
              };//窗口信息建模
typedef struct Window WINDOW;
struct REQ{int REQ;
           int time;
		  };//请求信息建模
typedef struct REQ REQLISTNODE;
typedef struct REQ* REQLISTNODEPTR;
struct listNode{
              char CliNum[4];
              struct listNode * nextPtr;
              
               };//客户到来队列请求队列链表节结点
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
//线程传递的参数 

//窗口休息请求队列结点
//#define size 8
/*#define MaxSeqLen 5
#define MinSec 10
#define MaxSec 30
#define MinRestSec 2
#define MaxRestSec 10
#define VIPSERVLen 10 
#define waitTime 3

*/
