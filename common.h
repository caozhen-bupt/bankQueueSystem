

extern int Qflag,printFlag,QueFlag;//�����ⲿ��ȫ�ֱ����������ж��Ƿ�ֹͣ��ȡ 
extern LISTNODEPTR headp;//��ͨ�ͻ�����ͷָ��
extern LISTNODEPTR headpVIP;//VIP�ͻ�����ͷָ��
extern RESTLISTNODEPTR headpWinRest;//����������Ϣ����ͷָ��
extern int currentNor,currentVIP;//Ŀǰ�Ŷӵ���ͨ�ͻ�����VIP�ͻ��� 
extern int totalNor,totalVIP;
extern int leaveNor,leaveVIP;
extern LISTNODEPTR preNorPtr,preVIPPtr;//��һ����ӵ�β��ַ 
extern RESTLISTNODEPTR preRestPtr;
extern int openTime;//����3��ʱVIP���ӵĴ��ڿ���ʱ��
extern int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,OutputSec,WaitTime,strategyFlag;
extern HANDLE hMutex;
