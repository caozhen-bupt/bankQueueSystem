

extern int Qflag,printFlag,QueFlag;//声明外部的全局变量，用于判断是否停止读取 
extern LISTNODEPTR headp;//普通客户队列头指针
extern LISTNODEPTR headpVIP;//VIP客户队列头指针
extern RESTLISTNODEPTR headpWinRest;//窗口申请休息队列头指针
extern int currentNor,currentVIP;//目前排队的普通客户数，VIP客户数 
extern int totalNor,totalVIP;
extern int leaveNor,leaveVIP;
extern LISTNODEPTR preNorPtr,preVIPPtr;//上一个添加的尾地址 
extern RESTLISTNODEPTR preRestPtr;
extern int openTime;//少于3人时VIP增加的窗口开放时间
extern int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag;
extern HANDLE hMutex;
