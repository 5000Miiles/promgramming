//有考虑过用GUI写这个但是.......还是算了吧....在这里写的关键在于每秒刷新界面.所以获取时间和方向键显得尤为重要. 
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<cstdio>
#include<windows.h> 
#include<fstream>
#include<string>
#include<cstring> 
using namespace std;
bool main_menu(); 
class user                                            //用户的类   
{
	public:
		void registor();
		bool login();
	protected:
	    char name[10];
		char password[20];
};
void user:: registor()                                //打开文件 
{
	void Main_menu();
	ofstream fout("user.txt",ios::app);
	if(!fout) {
		cout<<"无法打开文件"<<endl;
		system("pause");
		exit(0);
	}
	
	cout<<"请输入用户名: ";
	cin>>name;
	cout<<"请输入密码: ";
	cin>>password;
	cout<<"注册成功!"<<endl;
	
	fout<<name<<" "<<password<<endl;
	fout.close();
	main_menu(); 
} 
bool user::login()
{
	int flag=0;
	string temp; 
	string pass;
	void son_menu();
	void main_menu();
	ifstream fin("user.txt");
	if(!fin) 
	{
		cout<<"文件打开失败"<<endl; 
		system("pause");
		exit(0);
	}
	cout<<"请输入用户名 ";
	cin>>name;
	while (fin>>temp)                                //用户名 
	{
		if (temp==name)
		{	
			fin>>temp;
			cout<<"请输入密码: "; cin>>pass;        //密码 
			if (pass==temp) 
			{
				cout<<"登录成功"<<endl;
				return true; 
			}
			else cout<<"密码错误"<<endl;
		} 
		if(flag==1) break;
		else continue;
	}
	if(flag==0)
	{
	    cout<<"对不起找不到该用户"<<endl;
	    system("pause");
		return false;
	}
	else return true;
} 
bool main_menu()                                   //主菜单 
{
	bool flag;
    user op;
    cout<<"\t************************************************************"<<endl;
    cout<<"\t\t\t1.登录\n";
    cout<<"\t\t\t2.注册\n";
    cout<<"\t\t\t3.退出\n";
    cout<<"\t************************************************************"<<endl;
    cout<<"请输入序号进行操作：";
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:flag=op.login();break;
    case 2:op.registor();break;
    case 3:exit(0);break;
    default: cout<<"输入序号出错!";
    }
    return flag;
}

char map[22][32];
typedef class 
{
	public: 
        int x,y; 
}Point;
Point  snake[600],food,Next;
int head,tail,grade,length,autotime;
char diraction;
void gotoxy(int x,int y)//用光标解决画面闪烁的问题 
{
	HANDLE hConsoleOutput;
	COORD dwCursorPostion;
	dwCursorPostion.X=x;
	dwCursorPostion.Y=y;
	hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPostion); 
} 
inline void Update(char map[][32],int grade,int length,int autotime)//用内联函数降低内存的占用率 
{
	//system("cls");
	gotoxy(0,0);
	int c,y; 
	cout<<endl;
	for(c=0;c<22;c++)
	{
	    cout<<"   ";
	    for(y=0;y<32;y++) 
	    	cout<<map[c][y];
		if(c==0)  cout<<"	"<<"等级为:"<<grade;
		if(c==2)  cout<<"	"<<"长度为:"<<length;
		if(c==6)  cout<<"	"<<"自动前进时间";
		if(c==8)  cout<<"	"<<"间隔为:"<<autotime;
       	cout<<endl;   
	}
}                
inline void welcome()
{
    cout<<endl<<endl<<endl<<"			"<<"贪吃蛇游戏马上开始!";
	double start;
	int i;
	for(i=3;i>=0;i--)
	{
	    start=(double)clock()/CLOCKS_PER_SEC;//程序运行到现在的时间
		while((double)clock()/CLOCKS_PER_SEC-start<=1);
		if(i>0)
		{
			system("cls");
			cout<<endl<<endl<<endl<<"			"<<"进入倒计时"<<i<<endl;
		} 
		else  Update(map,grade,length,autotime);
	}
}  
inline void creatfood()
{
	srand(int(time (0)));
	do{
		food.x=rand()%30+1;
		food.y=rand()%20+1;
	}while(map[food.x][food.y]!=' ');
	map[food.x][food.y]='*';
} 
inline void youxijiemian()
{
	int c,y;
	for(c=1;c<=20;c++)
	for(y=1;y<=30;y++) 
		map[c][y]=' '; 
	for(c=0;c<=21;c++)
	{map[c][0]='*';map[c][31]='*';}
	for(c=0;c<=31;c++)
	{map[21][c]='*';map[0][c]='*';}
	map[1][1]=map[1][2]=' ';
	map[1][3]='*';
	head=2;tail=0;
	snake[head].x=1;snake[head].y=3;//蛇头下标;
	snake[tail].x=1;snake[tail].y=1;//蛇尾下标; 
	creatfood();
	grade=1;length=3;autotime=500;diraction=77;//77是向右 
} 
inline  int rungame()
{
	bool over=true;
	double start=(double)clock()/CLOCKS_PER_SEC;//程序运行到现在所用时间;
	while((over=(double)clock()/CLOCKS_PER_SEC-start<=autotime/1000.0)&&!_kbhit());//不断循环直至超过自动更新时间或者有敲击键盘; 
	if(over)
	{
		getch();
		diraction=getch(); 
	} 
	switch(diraction)
	{
		case 72:Next.x=snake[head].x-1;Next.y=snake[head].y;break;//上 
		case 80:Next.x=snake[head].x+1;Next.y=snake[head].y;break;//下
		case 75:Next.x=snake[head].x;Next.y=snake[head].y-1;break;//左 
		case 77:Next.x=snake[head].x;Next.y=snake[head].y+1;break;//右
		default:cout<<"    错误按键,游戏结束!"<<endl;
		return 0; 
	} 
	if(Next.x==0||Next.x==21||Next.y==0||Next.y==31){ cout<<"    撞到边界,游戏结束!"<<endl;return 0;}
	if(map[Next.x][Next.y]!=' '&&!(Next.x==food.x&&Next.y==food.y)) { cout<<"    吃到自己,游戏结束!"<<endl;return 0;}
	if(length==600) { cout<<"    通关啦!"<<endl;return 0;}
	return 1; 
} 
inline void eatfood()
{
	length++; 
	int egrade=length/10+1;
	if(egrade!=grade){grade=egrade;if(autotime>=100){autotime=550-grade;}} //每升一级减少自动时间,增加游戏难度;
	map[Next.x][Next.y]='*'; //蛇头位置变化
	head++;
	creatfood();
	snake[head].x=Next.x;snake[head].y=Next.y; 
	Update(map,grade,length,autotime); 
}
inline void noteat()
{
	map[snake[tail].x][snake[tail].y]=' ';
	tail=(tail+1)%600;
	map[Next.x][Next.y]='*'; 
	head=(head+1)%600;
	snake[head].x=Next.x;snake[head].y=Next.y; 
	Update(map,grade,length,autotime); 
} 
int main()
{
	system("color 85"); //背景颜色以及字体颜色
    while(!main_menu())
    { 
	    main_menu();
	} 
	system("cls");
	youxijiemian();
	welcome();
	while(true)
	{
		if(rungame())
		{
			if(Next.x==food.x&&Next.y==food.y) eatfood();
			else noteat();
	    }
	    else break;
	} 
	return 0;
}
 

