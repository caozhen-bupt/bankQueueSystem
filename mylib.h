extern void DrawWindow(void);
//void door(void);
extern char* AddNorm(void);
extern char* AddVIP(void);
extern void TransWaitNPeo(void);
extern void TransWaitVPeo(void);
extern void AddRest(int,WINDOW[],int);
extern int isVIP(FILE*);
extern void mainTain(FILE * );//VIP�ͻ�����ά�� 
extern void Configuration(FILE * );//�����ļ�ά�� 
extern void get_Finput(FILE *,int,WINDOW[],FILE*,REQLISTNODE[]); /*��ȡ�ͻ�������������Ϣ���¼�*/
extern DWORD WINAPI get_input(LPVOID parameters);//�������� 
extern void control1(WINDOW[]); //���ݲ��Է���˿͵����д��ڽ��ܷ���
extern void control2(WINDOW[]);//���������Ƿ���Ϣ 
extern void state_trans(WINDOW[],int); /*����˿����и����ڵ�״̬ */               	
extern void print_message(WINDOW[],int,FILE*,FILE*,int,int);/*����˿̸����ڵ�״̬���Լ��ͻ����е�״̬*/


extern void PrintWin(WINDOW[],int);
extern void PrintQue() ;





extern void printStatistics(WINDOW[],FILE*);//���ͳ����Ϣ

