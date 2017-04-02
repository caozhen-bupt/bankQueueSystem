extern void DrawWindow(void);
//void door(void);
extern char* AddNorm(void);
extern char* AddVIP(void);
extern void TransWaitNPeo(void);
extern void TransWaitVPeo(void);
extern void AddRest(int,WINDOW[],int);
extern int isVIP(FILE*);
extern void mainTain(FILE * );//VIP客户资料维护 
extern void Configuration(FILE * );//配置文件维护 
extern void get_Finput(FILE *,int,WINDOW[],FILE*,REQLISTNODE[]); /*获取客户到来、窗口休息等事件*/
extern DWORD WINAPI get_input(LPVOID parameters);//键盘输入 
extern void control1(WINDOW[]); //根据策略分配顾客到空闲窗口接受服务
extern void control2(WINDOW[]);//决定窗口是否休息 
extern void state_trans(WINDOW[],int); /*计算此刻银行各窗口的状态 */               	
extern void print_message(WINDOW[],int,FILE*,FILE*,int,int);/*输出此刻各窗口的状态，以及客户队列的状态*/


extern void PrintWin(WINDOW[],int);
extern void PrintQue() ;





extern void printStatistics(WINDOW[],FILE*);//输出统计信息

