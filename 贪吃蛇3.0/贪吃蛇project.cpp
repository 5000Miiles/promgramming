//�п��ǹ���GUIд�������.......�������˰�....������д�Ĺؼ�����ÿ��ˢ�½���.���Ի�ȡʱ��ͷ�����Ե���Ϊ��Ҫ. 
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
class user                                            //�û�����   
{
	public:
		void registor();
		bool login();
	protected:
	    char name[10];
		char password[20];
};
void user:: registor()                                //���ļ� 
{
	void Main_menu();
	ofstream fout("user.txt",ios::app);
	if(!fout) {
		cout<<"�޷����ļ�"<<endl;
		system("pause");
		exit(0);
	}
	
	cout<<"�������û���: ";
	cin>>name;
	cout<<"����������: ";
	cin>>password;
	cout<<"ע��ɹ�!"<<endl;
	
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
		cout<<"�ļ���ʧ��"<<endl; 
		system("pause");
		exit(0);
	}
	cout<<"�������û��� ";
	cin>>name;
	while (fin>>temp)                                //�û��� 
	{
		if (temp==name)
		{	
			fin>>temp;
			cout<<"����������: "; cin>>pass;        //���� 
			if (pass==temp) 
			{
				cout<<"��¼�ɹ�"<<endl;
				return true; 
			}
			else cout<<"�������"<<endl;
		} 
		if(flag==1) break;
		else continue;
	}
	if(flag==0)
	{
	    cout<<"�Բ����Ҳ������û�"<<endl;
	    system("pause");
		return false;
	}
	else return true;
} 
bool main_menu()                                   //���˵� 
{
	bool flag;
    user op;
    cout<<"\t************************************************************"<<endl;
    cout<<"\t\t\t1.��¼\n";
    cout<<"\t\t\t2.ע��\n";
    cout<<"\t\t\t3.�˳�\n";
    cout<<"\t************************************************************"<<endl;
    cout<<"��������Ž��в�����";
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:flag=op.login();break;
    case 2:op.registor();break;
    case 3:exit(0);break;
    default: cout<<"������ų���!";
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
void gotoxy(int x,int y)//�ù����������˸������ 
{
	HANDLE hConsoleOutput;
	COORD dwCursorPostion;
	dwCursorPostion.X=x;
	dwCursorPostion.Y=y;
	hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPostion); 
} 
inline void Update(char map[][32],int grade,int length,int autotime)//���������������ڴ��ռ���� 
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
		if(c==0)  cout<<"	"<<"�ȼ�Ϊ:"<<grade;
		if(c==2)  cout<<"	"<<"����Ϊ:"<<length;
		if(c==6)  cout<<"	"<<"�Զ�ǰ��ʱ��";
		if(c==8)  cout<<"	"<<"���Ϊ:"<<autotime;
       	cout<<endl;   
	}
}                
inline void welcome()
{
    cout<<endl<<endl<<endl<<"			"<<"̰������Ϸ���Ͽ�ʼ!";
	double start;
	int i;
	for(i=3;i>=0;i--)
	{
	    start=(double)clock()/CLOCKS_PER_SEC;//�������е����ڵ�ʱ��
		while((double)clock()/CLOCKS_PER_SEC-start<=1);
		if(i>0)
		{
			system("cls");
			cout<<endl<<endl<<endl<<"			"<<"���뵹��ʱ"<<i<<endl;
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
	snake[head].x=1;snake[head].y=3;//��ͷ�±�;
	snake[tail].x=1;snake[tail].y=1;//��β�±�; 
	creatfood();
	grade=1;length=3;autotime=500;diraction=77;//77������ 
} 
inline  int rungame()
{
	bool over=true;
	double start=(double)clock()/CLOCKS_PER_SEC;//�������е���������ʱ��;
	while((over=(double)clock()/CLOCKS_PER_SEC-start<=autotime/1000.0)&&!_kbhit());//����ѭ��ֱ�������Զ�����ʱ��������û�����; 
	if(over)
	{
		getch();
		diraction=getch(); 
	} 
	switch(diraction)
	{
		case 72:Next.x=snake[head].x-1;Next.y=snake[head].y;break;//�� 
		case 80:Next.x=snake[head].x+1;Next.y=snake[head].y;break;//��
		case 75:Next.x=snake[head].x;Next.y=snake[head].y-1;break;//�� 
		case 77:Next.x=snake[head].x;Next.y=snake[head].y+1;break;//��
		default:cout<<"    ���󰴼�,��Ϸ����!"<<endl;
		return 0; 
	} 
	if(Next.x==0||Next.x==21||Next.y==0||Next.y==31){ cout<<"    ײ���߽�,��Ϸ����!"<<endl;return 0;}
	if(map[Next.x][Next.y]!=' '&&!(Next.x==food.x&&Next.y==food.y)) { cout<<"    �Ե��Լ�,��Ϸ����!"<<endl;return 0;}
	if(length==600) { cout<<"    ͨ����!"<<endl;return 0;}
	return 1; 
} 
inline void eatfood()
{
	length++; 
	int egrade=length/10+1;
	if(egrade!=grade){grade=egrade;if(autotime>=100){autotime=550-grade;}} //ÿ��һ�������Զ�ʱ��,������Ϸ�Ѷ�;
	map[Next.x][Next.y]='*'; //��ͷλ�ñ仯
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
	system("color 85"); //������ɫ�Լ�������ɫ
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
 

